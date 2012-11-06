

#include "faio.h"
#include "packet.h"

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
  int on = 1;
  
  fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd < 0)
    return -1;
    
  if (ioctl(fd, FIOCLEX, NULL) < 0)
    goto error;
    
  if (ioctl(fd, FIONBIO, (void*) &on) < 0)
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


typedef struct {
  start_packet_t* start_packet;
  ngx_queue_t process_queue;
  int output_fd;
  struct faio_handle output_handle;
  int pid;
} r_process_t;



static int server_fd;
static struct faio_handle server_handle;


static struct faio_loop loop;
static ngx_queue_t process_queue;


void on_server_data(struct faio_loop *loop,
                    struct faio_handle *handle,
                    unsigned int revents {
  int fd;
  rjs_packet_t* packet;
  ssize_t r;
  
  assert(revents & FAIO_POLLIN);
  
  fd = accept(server_fd, NULL, NULL);
  if (fd < 0)
    return;
  
  for(;;) {
    r = read_packet(fd, &packet);
    if (r <= 0)
      break;
      
    /* Handle packet */
    write_packet(fd, packet);
    write_packet(fd, packet);
    
    free(packet);
  }
  
  close(fd);                        
}


int main(int argc, char* argv[]) {
  USE(argc);
  USE(argv);
  
  signal(SIGPIPE, SIG_IGN);
  
  ngx_queue_init(&process_queue);

  if (faio_init(&loop) < 0)
    fatal_error("faio_init");
  
  server_fd = create_server(SERVER_PATH);
  if (server_fd < 0)
    fatal_error("create_server");

  faio_poll(&loop, -1);


  /*if (rjs_run(server_fd))
    fatal_error("rjs_monitor");*/
     
  UNREACHABLE();
}


