
#ifndef _PROCESS_H
#define _PROCESS_H

#include "faio.h"
#include "ngx-queue.h"
#include "packet.h"

#include <stdint.h>
#include <sys/types.h>


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
  int id;

  int64_t last_start_time;
  int64_t start_counter;
  int spawn_errno;

  int64_t last_exit_time;
  int64_t last_exit_status;

  start_packet_t* start_packet;
  int pid;

  int output_pipefd[2];
  struct faio_handle output_handle;

  ngx_queue_t process_queue;
  ngx_queue_t enum_queue;
} process_t;


typedef void (*process_visitor_t)(process_t* process, void* baton);


int process_setup(struct faio_loop* loop);
process_t* process_start(start_packet_t* packet);
void process_sweep();
int process_walk(const char* tag, int id, int wildcard, int archived, process_visitor_t visitor, void* baton);
int process_stop(process_t* proc, int signo, int group, int64_t hard_kill_timeout);

#endif

