
#include "cmd.h"
#include "proc.h"
#include "spawn.h"

#include <signal.h>

#define MAX_PROCESSES 16

static rjs_process_t procs[MAX_PROCESSES];
static struct pollfd pollfds[1 + MAX_PROCESSES];

static size_t proc_count = 0;

rjs_prot_t* rjs_proc_alloc() {
  int i;
  
  for (i = 0; i < MAX_PROCESSES; i++) {
    if (procs[i].state == RJS_FREE) {
      rjs_process_t* proc = &procs[i];
      memset(proc, 0, sizeof *proc);
      proc->state = RJS_ALLOCATED;
      return proc;
    }
  }
  
  errno = ENOSPC;
  return NULL;  
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
  int log_fd;
  
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
