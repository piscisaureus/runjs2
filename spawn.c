
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "util.h"


extern char** environ;
static int null_fd = -1;


static int get_null_fd() {
  int fd;
  
  if (null_fd != -1)
    return null_fd;
  
  fd = open("/dev/null", O_RDONLY, 0);
  if (fd < 0)
    return -1;
    
  if (ioctl(fd, FIOCLEX, NULL) < 0) {
    close(fd);
    return -1;
  }

  null_fd = fd;
  return fd;
}


int do_spawn(char* file, char* argv[], char* envv[], char* cwd, int outfd) {
  int err_fds[2] = { -1, -1 };
  pid_t child_pid = 0;
  int spawn_error, r;
  size_t bytes_read;
    
  if (pipe(err_fds) < 0)
    goto error;
        
  child_pid = fork();
  if (child_pid < 0)
    goto error;
    
  if (child_pid == 0) {   
    /* We are the child. */
    int e;

    close(err_fds[0]);
    
    if (ioctl(err_fds[1], FIOCLEX, NULL) < 0)
      goto error;
    
    if (dup2(get_null_fd(), 0) < 0)
      goto child_error;
     
    if (dup2(outfd, 1) < 0)
      goto child_error;
      
    if (dup2(outfd, 2) < 0)
      goto child_error;
    
    if (chdir(cwd) < 0)
      goto child_error;
    
    environ = envv;

    execvp(file, argv);

   child_error:
    e = errno;
    r = write(err_fds[1], &e, sizeof e);
    USE(r);
    exit(127);
  }
  
  close(err_fds[1]);
  err_fds[1] = -1;
  
  spawn_error = 0;
  bytes_read = 0;
  
  while (bytes_read < sizeof spawn_error) {
    r = read(err_fds[0],
             bytes_read + (char*) &spawn_error, 
             sizeof spawn_error - bytes_read);
    if (r == -1 && errno == EINTR)
      continue;
    if (r == -1)
      goto error;
    if (r == 0)
      break;
    bytes_read += r;
  }
  
  if (bytes_read == 4) {
    errno = spawn_error;
    goto error;
  }
  
  if (r != 0)
    goto error;
  
  close(err_fds[0]);
  return child_pid;    

 error: {
    int saved_errno = errno;
  
    if (err_fds[0] != -1)
      close(err_fds[0]);
    if (err_fds[1] != -1)
      close(err_fds[1]);
    if (child_pid > 0)
      kill(-child_pid, SIGKILL);

    printf("spawn error %s\n", strerror(saved_errno));

    errno = saved_errno;
    return -1;  
  }
}
