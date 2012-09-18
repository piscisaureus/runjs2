
#ifndef _RJS_PROC_H
#define _RJS_PROC_H

typedef enum {
  RJS_FREE = 0,
  RJS_ALLOCATED = 1,
  RJS_RUNNING = 3,
  RJS_STOPPING = 4,
  RJS_STOPPED = 5,
  RJS_RESTARTING = 6,
  RJS_RESTART_WAIT = 7,
} rjs_proc_state_t;

typedef struct {
  rjs_process_state_t state;
  char* tag;
  char* file;
  char* args;
  char* env;
  char* log_file;
  int pid;
  int exit_status;
  int log_fd;
} rjs_proc_t;

typedef struct rjs_command rjs_command_t;


int rjs_run(int server_fd);

rjs_process_t* rjs_proc_alloc();
void rjs_proc_free(rjs_process_t* p);
int rjs_proc_start(rjs_process_t* p);


#endif
