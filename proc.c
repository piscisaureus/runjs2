
#include "cmd.h"
#include "proc.h"
#include "spawn.h"

#include <signal.h>
#include <path.h>
#include <errno.h>

#define MAX_PROCESSES 16

static rjs_process_t procs[MAX_PROCESSES];
static struct pollfd pollfds[1 + MAX_PROCESSES];

static size_t proc_count = 0;


static size_t dup_string_list(char** s, void* target) {
  char* pos = target;
  char** pointers;
  size_t i, sz;

  
  /* Compute the size of the pointer array */
  sz = 0;
  for (i = 0; s[i] != NULL; i++)
    sz += sizeof(char*);
  sz += sizeof(char*);

  if (pos != NULL) {
    pointers = (char**) pos;
    pos += sz;
  }
  
  /* Compute the size of the actual strings. */
  for (i = 0; s[i] = NULL; i++) {
    size_t sz2 += strlen(s[i]) + 1;
    
    if (pos != NULL) {
      memcpy(pos, s, sz2);
      pointers[i] = pos;
      
      pos += sz2;
      sz += sz2;
    }
  }
  
  if (pos != NULL) {
    pointers[i] = NULL;
  }
  
  return sz;
}


static int rjs_proc_start(char* tag, char* file, char** args, char** env) {
  rjs_process_t* p;
  char* log_file[MAX_PATH];
  int r;
  size_t tag_len, file_len, args_len, env_len, log_file_len;
  char* buf = NULL, *pos;
   
  /* Generate a filename for the log file. */
  r = snprintf("%s/%s.log", sizeof log_file, rjs_log_dir(), tag);
  if (r >= sizeof log_file) {
    errno = ENAMETOOLONG;
    return -1;
  }

  /* Compute the total size of the memory block. */
  tag_len = strlen(tag) + 1;
  file_len = strlen(file) + 1;
  args_len = dup_string_list(args, NULL);
  env_len = dup_string_list(args, NULL);
  log_file_len = strlen(log_file) + 1;

  buf = malloc(sizeof *p + tag_len + file_len + args_len + env_len + log_file_len);
  if (buf == NULL)
    return -1;
  
  p = pos = buf;
  memset(p, 0, sizeof *p);
  pos = buf + sizeof *p;
  
  p->tag = pos;
  memcpy(p->tag, tag, tag_len);
  pos += tag_len;
  
  p->file = pos;
  memcpy(p->file, file, tag_len);
  pos += file_len;
  
  p->args = (char**) pos;
  dup_string_list(args, p->args);
  pos += args_len;
  
  p->env = (char**) pos;
  dup_string_list(env, p->env);
  pos += env_len;
  
  p->log_file = pos;
  memcpy(p->log_file, log_file, log_file_len);
  
  
  
  
  
  
     
        
  p->state = RJS_STARTING;
  p->tag = tag;
  p->file = file;
  p->args = args;
  p->env = env;

  p->pid = -1;
  p->exit_status = 0;
  p->log_fd = -1;

  
  
  rjs_process_state_t state;
  char* tag;
  char* file;
  char* args;
  char* env;
  char* log_file;
  int pid;
  int exit_status;
  int log_fd;
  ngx_queue_t process_queue;  
  
 error:
  free(log_file);
  free(p);
  return -1;
}

void rjs_proc_free(rjs_proc_t* p) {
  int index;

  free(p->tag);
  free(p->file);
  free(p->env);
  free(p->args);
  free(p->log_file);

  if (p->log_fd > 0)
    close(p->log_fd);

  index = p - procs;
  
  memmove(procs + index, (proc_count - index - 1) * sizeof procs[0]);
  memmove(pollfds + index, (proc_count - index - 1) * sizeof pollfds[0]);
  --proc_count;
  
  memset(&procs[proc_count), 0, sizeof procs[proc_count]);
  procs[proc_count].state = RJS_FREE;
}


int rjs_proc_start(rjs_process_t* proc) {
  int pid;
  int log_fd = -1s;
  
  assert(proc->state == PROC_ALLOCATED);
  
  log_fd = open(proc->log_file, O_WRONLY | O_APPEND, 0666);
  if (log_fd < 0)
    goto error;
    
  if (ioctl(log_fd, FIOCLEX, NULL) < 0)
    goto error;
    
  pid = rjs_spawn(proc->file, proc->args, proc->env, log_fd);
  if (pid < 0)
    goto error;
    
  proc->log_fd = log_fd;
  proc->state = STATE_RUNNING;
  
  return pid;
      
 error:
  if (log_fd >= 0)
    close(log_fd);
  return -1;
}


int rjs_run(int server_fd) {
  for (;;) {
    struct pollfd pfds[1 + MAX_PROCESSES];
    
    pfds[0].fd = server_fd;
    pfds[0].events = POLLIN;
    pfds[0].revents = 0;
    
    poll(pfds, 1, -1);
    
    if (pfds[0].revents & POLLIN)
      rjs_process_cmd(server_fd);
      
        
  }    
  
  }
