
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "command.h"


#define SERVER_PATH "/tmp/runjs.sock"

#define USE(x) (void) (x)
#define UNREACHABLE() abort()


void fatal_error(const char* message) {
  perror(message);
  exit(1);
}


static int create_server(const char* path) {
  int fd;
  size_t len;
  struct sockaddr_un addr;
  
  fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd < 0)
    return -1;
    
  if (ioctl(fd, FIOCLEX, NULL) < 0)
    goto error;

  len = strlen(path);
  if (len >= sizeof addr.sun_path) {
    errno = ENAMETOOLONG;
    goto error;
  }
  
  addr.sun_family = AF_UNIX;
  memcpy(addr.sun_path, path, len + 1);  
   
  unlink(path);
      
  if (bind(fd, (struct sockaddr*) &addr, sizeof addr) < 0)
    goto error;
    
  if (listen(fd, 1024) < 0)
    goto error;
    
  return fd;  
  
 error:
  close(fd);
  return -1;
}


int main(int argc, char* argv[]) {
  int server_fd;

  USE(argc);
  USE(argv);
  
  signal(SIGPIPE, SIG_IGN);
  
  server_fd = create_server(SERVER_PATH);
  if (server_fd < 0)
    fatal_error("create_server");
   
  if (rjs_run(server_fd))
    fatal_error("rjs_monitor");
     
  UNREACHABLE();
}


