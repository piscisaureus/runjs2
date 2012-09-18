

#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>

#include "cmd.h"
#include "proc.h"
#include "spawn.h"


static int read_bytes(int fd, void* buf, size_t bytes_needed) {
  size_t bytes_read = 0;
  
  while (bytes_read < bytes_needed) {
    int r = read(fd, (char*) buf + bytes_read, bytes_needed - bytes_read);

    if (r > 0)
      bytes_read += r;

    if (r == 0 ||
        (r < 0 && errno != EINTR))
      return -1;
  }
  
  return bytes_read;
}


static char* read_string(int fd) {
  uint32_t len;
  char* s;
  
  if (read_bytes(fd, &len, sizeof len) < 0)
    return NULL;
    
  s = malloc(len + 1);
  if (s == NULL)
    return NULL;
  
  if (read_bytes(fd, s, len) < 0) {
    free(s);
    return NULL;
  }
  
  s[len] = '\0';

  return s;
}


static int write_bytes(int fd, void* buf, size_t bytes_to_write) {
  size_t bytes_written = 0;
  
  while (bytes_written < bytes_to_write) {
    int r = write(fd, (char*) buf + bytes_written, bytes_to_write - bytes_written);

    if (r > 0)
      bytes_written += r;

    if (r == 0 ||
        (r < 0 && errno != EINTR))
      return -1;
  }
  
  return bytes_written;
}


static int rjs_start_cmd(int fd) {
  rjs_process_t* p;
  int pid;
  
  p = rjs_proc_alloc(sizeof *p);
  if (p == NULL)
    return -1;
   
  memset(p, 0, sizeof *p);
    
  p->tag = read_string(fd);
  if (p->tag == NULL)
    goto err;
    
  p->file = read_string(fd);
  if (p->file == NULL)
    goto err;

  p->args = read_string(fd);
  if (p->args == NULL)
    goto err;   
    
  p->env = read_string(fd);
  if (p->env == NULL)
    goto err;
    
  pid = spawn(p->file, p->args, p->env, 1);
  if (pid < 0)
    pid = -errno;
    
  pid = rjs_proc_start(p);
  if (pid < 0)
    goto err;
    
  write_bytes(fd, &pid, sizeof pid);
  return 0;
  
 err:
  rjs_proc_free(p);
  return -1;
}


static void rjs_invalid_cmd(int fd, int err) {
  int32_t val;
  
  assert(err > 0);
    
  val = -err;
  write_bytes(fd, &val, sizeof val);
}


int rjs_process_cmd(int server_fd) {
  int fd;
  uint32_t cmd_type;
  
  fd = accept(server_fd, NULL, NULL); 
  if (fd < 0)
    return -1;

  if (read_bytes(fd, &cmd_type, sizeof cmd_type) < 0) {
    rjs_invalid_cmd(fd, EINVAL);
    goto out;
  }

  switch (cmd_type) {
#define CMD_CASE(utype, ltype) \
  case RJS_##utype: \
    rjs_##ltype##_cmd(fd); \
    break; 
    CMD_CASE(START, start)
    //CMD_CASE(STOP, stop)
    //CMD_CASE(QUERY, query)
    //CMD_CASE(LIST, list)
#undef CMD_CASE
    default:
      rjs_invalid_cmd(fd, ENOSYS);
  }
  
 out:
  close(fd);
  return 0;
}



