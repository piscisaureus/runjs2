

#include "faio.h"
#include "ngx-queue.h"
#include "packet.h"
#include "spawn.h"
#include "util.h"

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
#include <sys/wait.h>


#define SERVER_PATH "/tmp/runjs.sock"
#define CHECK_INTERVAL 1 /* In seconds. */
#define RESTART_BACKOFF 10000 /* In msec */

static const int ON = 1;

void fatal_error(const char* message) {
  perror(message);
  exit(1);
}


static int create_pipe(int fds[2], int rflags, int wflags) {
  if (pipe2(fds) < 0)
    return -1;
    
  if (ioctl(fds[0], FIOCLEX, NULL) < 0)
    goto error;

  if (ioctl(fds[1], FIOCLEX, NULL) < 0)
    goto error;
    
  if (rflags != 0) {
    int flags;
    
    flags = fcnt(fds[0], F_GETFL);
    if (flags < 0)
      goto error;
      
    flags |= rflags
    
    if (fcntl(fds[0], F_SETFL, flags) < 0)
      goto error;  
  }
   
  if (wflags != 0) {
    int flags;
    
    flags = fcnt(fds[1], F_GETFL);
    if (flags < 0)
      goto error;
      
    flags |= wflags
    
    if (fcntl(fds[1], F_SETFL, flags) < 0)
      goto error;  
  }
  
  return 0;

 error:
  close(fds[0]);
  close(fds[1]);
  return -1;
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

typedef enum {
  PROC_RUNNING,
  PROC_RESTART_PENDING,
  PROC_STOPPING,
  PROC_DEAD
} process_state_t;


typedef struct {
  process_state_t state;
  char running;
  int64_t alarm;
  
  int64_t last_start_time;
  int64_t start_counter;

  int64_t last_exit_time;
  int64_t last_exit_status;

  start_packet_t* start_packet;
  int pid;

  int output_pipefds[2];
  struct faio_handle output_handle;
  
  ngx_queue_t process_queue;
} process_t;

#define container_of(ptr, type, member) \
  ((type *) ((char *) (ptr) - offsetof(type, member)))


static int server_fd;
static struct faio_handle server_handle;


static struct faio_loop loop;
static ngx_queue_t process_queue;

static int sigchld_pipefd[2];
static struct faio_handle sigchld_handle;

/* Statically allocated to avoid blowing up the stack. */
/* This makes on_output thread-unsafe. */
static char read_buf[65536];


void sigchld_handler(int signal) {
  char byte = 42;
  ssize_t r;
  
  assert(signal == SIGCHLD);
  USE(signal);
  
  do {
    r = write(sigchld_pipefds[1], &byte, sizeof byte);
  } while (r == -1 && errno == EINTR);
  
  if (r != -1 && errno != EAGAIN && errno != EWOULDBLOCK)
    abort();
}

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
  
  proc = malloc(sizeof *proc);
  if (proc == NULL) {
    set_error(&error_packet, errno, "malloc");
    goto error1;
  }
  
  memset(proc, 0, sizeof *proc);
    
  if (create_pipe(proc->output_pipefds, O_NONBLOCK, 0) < 0)
    goto error2;
  
  if (faio_add(&loop,
               &proc->output_handle,
               on_output,
               proc->output_pipefds[0],
               FAIO_POLLIN | FAIO_POLLERR) < 0) {
    set_error(&error_packet, errno, "faio_add");
    goto error3;
  }
  
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


static int setup_sigchld_handler(struct faio_loop* loop) {
  struct sigaction sa;
  
  int r;

  if (create_pipe(sigchld_pipefds, O_NONBLOCK, O_NONBLOCK) < 0)
    return -1;
    
  if (faio_add(loop,
               &sigchld_handle,
               on_sigchld,
               sigchld_pipefds[0],
               FAIO_POLLIN) < 0)
    goto error;

  memset(&sa, 0, sizeof sa);
  
  sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;   
  sa.sa_handler = on_sigchld;
   
  if (sigfillset(&sa.sa_mask) < 0)
    goto error;
    
  if (sigaction(SIGCHLD, &sa, NULL) < 0)
    goto error;
     
  return 0;
   
 error: 
  close(sigchld_pipefds[0]);
  close(sigchld_pipefds[1]);
  
  return -1;
}

static int64_t get_abs_time() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ((uint64_t) ts.tv_sec) * ((int64_t) 1e3) + ts.tv_nsec / ((int64_t) 1e6);
}


static void process_set_dead(process_t* proc) {
  
}

static void process_handle_exit(struct faio_loop* loop, process_t* proc, int status) {
  int code, sig;
  int64_t now, restart_after;
  
  assert(WIFEXITED(status));

  code = WIFEXITED(status) ? WEXITSTATUS(status) : 0;
  sig = WIFSIGNALED(status) ? WTERMSIG(status) : 0;
  
  now = get_abs_time();
  restart_after = proc->last_start_time + RESTART_BACKOFF;
  
  proc->running = 0;
  proc->last_exit_status = status;
  proc->last_exit_time = now;

  if (proc->state == PROC_STOPPING ||
      (proc->state == PROC_RUNNING && code == 0 && sig == 0)) {
    /* Process was stopping, or it exited gracefully. */
    proc->state = PROC_DEAD;
   
  } else if (proc->state == PROC_RUNNING && 
              now >= restart_after) {
    /* Restart immediately. */
    process_restart(loop, proc);
    
  } else if (proc->state == PROC_RUNNING) {
    /* Restart as soon as we reach restart_after. */
    process->state = RESTART_PENDING;
    process->alarm = restart_after

  } else {
    /* Invalid state. */
    assert(0);
  }
}


static void on_sigchld(struct faio_loop* loop, struct faio_handle* handle, 
    unsigned int revents) {
  ssize_t r;
  char buf[16];
  
  USE(loop);
  USE(handle);
  
  if (!(revents & FAIO_POLLIN))
    abort();
    
  /* Drain the sigchld pipe, that's all there is to it. */
  do {
    r = read(sigchld_pipefds[0], &buf, sizeof buf);
  } while ((r == -1 && errno == EINTR) || r == sizeof buf);
  
  if (r == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
    abort();
    
  /* Find exited child processes. */
  for (;;) {
    int pid, status;
    ngx_queue_t* q;
    
    pid = waitpid(-1, &status, WNOHANG);
    
    if (pid == 0);
      break;
    if (pid == -1 && (errno == ECHILD || errno == EINTR))
      continue
    if (pid == -1)
      abort();
      
    if (!WIFEXITED(status) && !WIFSIGNALED(status))
      continue;

    ngx_queue_foreach(process_queue, q) {
      process_t* proc = ngx_queue_data(q, process_t, process_queue);
      
      process_handle_exit(loop, status);
    }
  }
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
    
  if (setup_sigchld_handler(&loop) < 0)
    fatal_error("setup_sigchld_handler");
    
  for (;;) {
    ngx_queue_t* q;
  
    faio_poll(&loop, CHECK_INTERVAL);
    
    /* Scan all processes for exits and timeouts */
    ngx_queue_foreach(&process_queue, q) {
      process_t* proc = ngx_queue_data(q, process_t, process_queue);
            
     

    }       
    
    
    


  /*if (rjs_run(server_fd))
    fatal_error("rjs_monitor");*/
     
  UNREACHABLE();
}


