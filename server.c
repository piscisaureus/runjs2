
#include "process.h"
#include "server.h"
#include "util.h"

#include <assert.h>
#include <stdio.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>


static int server_fd;
static struct faio_handle server_handle;


static int write_end_packet(int client_fd, int result, int error) {
  end_packet_t packet;

  packet.type = END_PACKET;
  packet.result = result;
  packet.error = error;
  
  if (error == 0)
    packet.message = "Success";
  else
    packet.message = strerror(error);
  
  return write_packet(client_fd, (packet_t*) &packet);
}



void handle_start_packet(int client_fd, start_packet_t* packet) {
  process_t* proc;

  proc = process_start(packet);

  if (proc == NULL) {
    /* Failure */
    start_result_packet_t result_packet;
    
    result_packet.type = START_RESULT_PACKET;
    result_packet.tag = packet->tag;
    result_packet.id = -1;
    result_packet.pid = -1;
    result_packet.error = errno;
    result_packet.message = strerror(errno);
    write_packet(client_fd, (packet_t*) &result_packet);

    write_end_packet(client_fd, 0, 0);
    
    free(packet);

  } else {
    /* Success */
    start_result_packet_t result_packet;
    
    result_packet.type = START_RESULT_PACKET;
    result_packet.tag = packet->tag;
    result_packet.id = proc->id;
    result_packet.pid = proc->pid;
    result_packet.error = 0;
    result_packet.message = "Success";
    write_packet(client_fd, (packet_t*) &result_packet);

    write_end_packet(client_fd, 1, 0);
  }
}


struct stop_ctx {
  stop_packet_t* packet;
  int client_fd;
  int stopped_processes;
};

static void stop_process_visitor(process_t* proc, struct stop_ctx* ctx) {
  stop_result_packet_t result_packet;

  int r = process_stop(proc, 
                       ctx->packet->kill_signo, 
                       ctx->packet->kill_group, 
                       ctx->packet->hard_kill_timeout); 

  result_packet.type = STOP_RESULT_PACKET;
  result_packet.id = proc->id;
  result_packet.pid = proc->pid;    
  result_packet.state = (int32_t) proc->state;
  result_packet.result = r;
  
  if (r < 0) {
    /* Failure. */    
    result_packet.error = errno;
    result_packet.message = strerror(errno);    
  } else {
    /* Success. */
    ctx->stopped_processes++;
    result_packet.error = 0;
    result_packet.message = "Success";
  }

  write_packet(ctx->client_fd, (packet_t*) &result_packet);
}


static void handle_stop_packet(int client_fd, stop_packet_t* packet) {
  struct stop_ctx ctx;
  ctx.packet = packet;
  ctx.client_fd = client_fd;
  ctx.stopped_processes = 0;
  
  if (process_walk(packet->tag, 
                   packet->id, 
                   packet->wildcard, 
                   0, 
                   (process_visitor_t) stop_process_visitor,
                   &ctx) < 0) {
    /* Failure. */
    write_end_packet(client_fd, -1, errno);
  } else {
    /* Success. */
    write_end_packet(client_fd, ctx.stopped_processes, 0);
  }
  
  free(packet);
}


static void on_connection(struct faio_loop *loop, 
    struct faio_handle *handle, unsigned int revents) {
  int client_fd;
  packet_t* packet;
  ssize_t r;

  USE(loop);
  USE(handle);
  USE(revents);

  assert(revents & FAIO_POLLIN);

  client_fd = accept(server_fd, NULL, NULL);
  if (client_fd < 0)
    return;

  for(;;) {
    printf("read\n");
    r = read_packet(client_fd, &packet);
    if (r <= 0)
      break;

    switch (packet->type) {
      case START_PACKET:
        handle_start_packet(client_fd, (start_packet_t*) packet);
        break;

      case STOP_PACKET:
        handle_stop_packet(client_fd, (stop_packet_t*) packet);
        break;

      default:
        /* Unsupported packet type. Free packet and disconnect. */
        free(packet);
        break;
    }
  }

  printf("close\n");
  close(client_fd);
}


int server_setup(struct faio_loop* loop, const char* path) {
  int fd;
  size_t len;
  struct sockaddr_un addr;
  static const int yes = 1;

  fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd < 0)
    return -1;

  if (ioctl(fd, FIOCLEX, NULL) < 0)
    goto error;

  if (ioctl(fd, FIONBIO, (void*) &yes) < 0)
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
    
  if (faio_add(loop,
               &server_handle,
               on_connection,
               fd,
               FAIO_POLLIN) < 0)
    goto error;

  server_fd = fd;
  return 0;
  
 error:
  close(fd);
  return -1;
}

