

#include "faio.h"
#include "ngx-queue.h"
#include "packet.h"
#include "spawn.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stddef.h>
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


static const int ON = 1;

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
    
  if (ioctl(fd, FIONBIO, (void*) &ON) < 0)
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
  int output_pipefds[2];
  struct faio_handle output_handle;
  int pid;
  ngx_queue_t process_queue;
} process_t;


#define container_of(ptr, type, member) \
  ((type *) ((char *) (ptr) - offsetof(type, member)))



static int server_fd;
static struct faio_handle server_handle;


static struct faio_loop loop;
static ngx_queue_t process_queue;

/* Statically allocated to avoid blowing up the stack. */
/* This makes on_output thread-unsafe. */
static char read_buf[65536];


void on_output(struct faio_loop* loop, struct faio_handle* handle, 
    unsigned int revents) {
  ssize_t r;
  process_t* proc = container_of(handle, process_t, output_handle);
  
  USE(loop);
  
  printf("%d\n", __LINE__);
  
  if (revents & FAIO_POLLERR) {
    errno = EPIPE;
    goto error;
  }
  
  printf("%d\n", __LINE__);

  for (;;) {
    printf("%d\n", __LINE__);
    r = read(proc->output_pipefds[0], read_buf, sizeof read_buf);
    printf("%d\n", __LINE__);
    if (r < 0) {
      if (errno == EINTR)
        continue;
      if (errno == EAGAIN || errno == EWOULDBLOCK)
        break;
      goto error;
    }
    printf("%d\n", __LINE__);
    if (r == 0)
      goto eof;
    printf("%d\n", __LINE__);
    write(1, read_buf, r);
  }
  printf("%d\n", __LINE__);
  return;
  
 error:
  return;
    
 eof:
  return;
}


static void set_error(error_packet_t* packet, int err, const char* syscall) {
  packet->type = ERROR_PACKET;
  packet->err = err;
  packet->message = strerror(errno);
  packet->syscall = (char*) syscall;
}

void handle_start_packet(int fd, start_packet_t* packet) {
  process_t* proc = NULL;
  start_success_packet_t success_packet;
  error_packet_t error_packet;
  
  printf("%d\n", __LINE__);
  
  proc = malloc(sizeof *proc);
  if (proc == NULL) {
    set_error(&error_packet, errno, "malloc");
    goto error1;
  }
    
  printf("%d\n", __LINE__);

  if (pipe(proc->output_pipefds) < -1) {
    set_error(&error_packet, errno, "pipe");
    goto error2;
  }
    
    printf("%d\n", __LINE__);
    
  if (ioctl(proc->output_pipefds[0], FIOCLEX, NULL) < 0) {
    set_error(&error_packet, errno, "ioctl(FIOCLEX)");
    goto error3;
  }
    
  printf("%d\n", __LINE__);

  if (ioctl(proc->output_pipefds[0], FIONBIO, &ON) < 0) {
    set_error(&error_packet, errno, "ioctl(FIONBIO)");
    goto error3;
  }
  
  printf("%d\n", __LINE__);
  
  if (ioctl(proc->output_pipefds[1], FIOCLEX, NULL) < 0) {
    set_error(&error_packet, errno, "ioctl(FIOCLEX)");
    goto error3;
  }
 
  printf("%d\n", __LINE__);
 
  if (faio_add(&loop,
               &proc->output_handle,
               on_output,
               proc->output_pipefds[0],
               FAIO_POLLIN | FAIO_POLLERR) < 0) {
    set_error(&error_packet, errno, "faio_add");
    goto error3;
  }
  
  printf("%d\n", __LINE__);
      
  proc->pid = do_spawn(packet->file,
                       packet->argv, 
                       packet->envv, 
                       packet->cwd, 
                       proc->output_pipefds[1]);
  if (proc->pid < 0) {
    set_error(&error_packet, errno, "do_spawn");
    goto error4;
  }

  success_packet.type = START_SUCCESS_PACKET;
  success_packet.pid = proc->pid;
  write_packet(fd, (packet_t*) &success_packet);

  return;
  
 error4:
  faio_del(&loop, &proc->output_handle);
  
 error3:
  close(proc->output_pipefds[0]);
  close(proc->output_pipefds[1]);
    
 error2:
  free(proc);
  
 error1:
  free(packet);
  
  write_packet(fd, (packet_t*) &error_packet);
}

void on_connection(struct faio_loop *loop,
                    struct faio_handle *handle,
                    unsigned int revents) {
  int fd;
  packet_t* packet;
  ssize_t r;
  
  USE(loop);
  USE(handle);
  USE(revents);
  
  assert(revents & FAIO_POLLIN);
  
  fd = accept(server_fd, NULL, NULL);
  if (fd < 0)
    return;
  
  for(;;) {
    printf("read\n");
    r = read_packet(fd, &packet);
    if (r <= 0)
      break;
      
    switch (packet->type) {
      case START_PACKET:
        handle_start_packet(fd, (start_packet_t*) packet);
        break;
      
      case STOP_PACKET:
        break;
      
      default:
        /* Unsupported packet type. Free packet and disconnect. */
        free(packet);
        break;
    }
  }
  
  printf("close\n");
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
    
  if (faio_add(&loop,
               &server_handle,
               on_connection,
               server_fd,
               FAIO_POLLIN))
    fatal_error("faio_add");

  for (;;)
    faio_poll(&loop, -1);


  /*if (rjs_run(server_fd))
    fatal_error("rjs_monitor");*/
     
  UNREACHABLE();
}


