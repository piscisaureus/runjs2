

#include "ioutil.h"
#include "process.h"
#include "spawn.h"
#include "util.h"

#include <assert.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h> 
#include <sys/wait.h>


#define RESTART_BACKOFF 10000 /* In msec */


static void on_output(struct faio_loop* loop, struct faio_handle* handle,
    unsigned int revents);


static struct faio_loop* loop;
static struct faio_handle sigchld_handle;
static int sigchld_pipefd[2];
static ngx_queue_t process_queue;
static char read_buf[65536];
static int id_counter = 0;


static int process_spawn(process_t* proc) {
  int pid;
  start_packet_t* packet;

  USE(loop);
  
  packet = proc->start_packet;
  
  pid = spawn(packet->file,
              packet->argv,
              packet->envv,
              packet->cwd,
              proc->output_pipefd[1]);
                       
  if (pid < 0) {
    proc->spawn_errno = errno;
    return -1;   
  }
  
  proc->state = PROC_RUNNING;
  proc->pid = pid;
  proc->running = 1;
  proc->last_start_time = get_abs_time();
  proc->start_counter++;
  proc->spawn_errno = 0;
 
  return 0;
}


static int process_kill(process_t* proc, int signo, int group) {
  int pid;

  USE(loop);

  pid = proc->pid;

  if (pid == -1) {
    errno = ESRCH;
    return -1;
  }

  if (group)
    pid = -pid;

  return kill(pid, signo);
}


process_t* process_start(start_packet_t* packet) {
  process_t* proc = NULL;
  int errno_;

  if (id_counter == INT32_MAX) {
    errno_ = ENFILE;
    goto error1;
  }

  proc = malloc(sizeof *proc);
  if (proc == NULL) {
    errno_ = ENOMEM;
    goto error1;
  }

  memset(proc, 0, sizeof *proc);
  proc->start_packet = packet;

  if (create_pipe(proc->output_pipefd, O_NONBLOCK, 0) < 0) {
    errno_ = errno;
    goto error2;
  }

  if (faio_add(loop,
               &proc->output_handle,
               on_output,
               proc->output_pipefd[0],
               FAIO_POLLIN | FAIO_POLLERR) < 0) {
    errno_ = errno;
    goto error3;
  }

  if (process_spawn(proc) < 0) {
    errno_ = errno;
    goto error4;
  }

  proc->id = ++id_counter;
  ngx_queue_insert_tail(&process_queue, &proc->process_queue);

  return proc;

 error4:
  faio_del(loop, &proc->output_handle);

 error3:
  close(proc->output_pipefd[0]);
  close(proc->output_pipefd[1]);

 error2:
  free(proc);
  
 error1:
  errno = errno_;
  return NULL;
}


int process_stop(process_t* proc, int signo, int group, int64_t hard_kill_timeout) {
  if (hard_kill_timeout < 0 || signo < 0) {
    errno = EINVAL;
    return -1;
  }

  switch (proc->state) {
    case PROC_RUNNING:
    case PROC_STOPPING: /* Re-signal if already stopping. */
      if (signo > 0 &&
          process_kill(proc, signo, group) < 0 &&
          errno != ESRCH)
        return -1;      
        
      proc->state = PROC_STOPPING;
      if (hard_kill_timeout > 0)
        proc->alarm = get_abs_time() + hard_kill_timeout;

      break;
      
    case PROC_RESTART_PENDING:
      proc->alarm = 0;
      proc->state = PROC_DEAD;
      break;

    case PROC_DEAD:
      break;
    
    default:
      assert(0);
  }
  
  return 0;
}


int process_walk(const char* tag, int id, int wildcard, int archived, process_visitor_t visitor, void* baton) {
  size_t found;
  ngx_queue_t list;
  ngx_queue_t* q;
 
  USE(archived); /* FIXME */ 
  
  if (strlen(tag) == 0)
    tag = NULL;  
  
  found = 0;  
  ngx_queue_init(&list);
  
  ngx_queue_foreach(q, &process_queue) {
    process_t* proc = ngx_queue_data(q, process_t, process_queue);

    if ((!tag || strcmp(tag, proc->start_packet->tag) == 0) &&
        (!id || proc->id == id)) {
      found++;
      ngx_queue_insert_tail(&list, &proc->enum_queue);
    }
  }
    
  if (found == 0) {
    errno = ENOENT;
    return -1;
  }
  
  if (!wildcard && found > 1) {
    errno = E2BIG;
    return -1;
  }
  
  ngx_queue_foreach(q, &list) {
    process_t* proc = ngx_queue_data(q, process_t, enum_queue);
    visitor(proc, baton);
  }
   
  return found;
}


static void process_restart(process_t* proc) {
  if (process_spawn(proc) < 0) {
    /* Spawn failure on restart. Reset the alarm to retry later. */
    proc->alarm = get_abs_time() + RESTART_BACKOFF;    
  }
}



static void process_handle_exit(process_t* proc, int status) {
  int code, sig;
  int64_t now, restart_after;

  USE(loop);

  assert(WIFEXITED(status) || WIFSIGNALED(status));

  code = WIFEXITED(status) ? WEXITSTATUS(status) : 0;
  sig = WIFSIGNALED(status) ? WTERMSIG(status) : 0;

  now = get_abs_time();
  restart_after = proc->last_start_time + RESTART_BACKOFF;

  proc->running = 0;
  proc->last_exit_status = status;
  proc->last_exit_time = now;

  if (proc->state == PROC_STOPPING ||
      (proc->state == PROC_RUNNING && code == 0 && sig == -1)) {
    /* Process was stopping, or it exited gracefully. */
    proc->state = PROC_DEAD;

  } else if (proc->state == PROC_RUNNING &&
              now >= restart_after) {
    /* Restart immediately. */
    process_restart(proc);

  } else if (proc->state == PROC_RUNNING) {
    /* Restart as soon as we reach restart_after. */
    proc->state = PROC_RESTART_PENDING;
    proc->alarm = restart_after;

  } else {
    /* Invalid state. */
    assert(0);
  }
}


static void process_handle_alarm(process_t* proc) {
  proc->alarm = 0;

  switch (proc->state) {
    case PROC_RESTART_PENDING:
      process_restart(proc);
      break;

    case PROC_STOPPING:
      process_kill(proc, SIGKILL, 1);
      break;

    default:
      assert(0);
  }
}


void process_sweep() {
  int64_t now;
  ngx_queue_t* q;

  /* Scan all processes for exits and timeouts */
  now = get_abs_time();
  ngx_queue_foreach(q, &process_queue) {
    process_t* proc = ngx_queue_data(q, process_t, process_queue);
    if (proc->alarm > 0 && proc->alarm <= now)
      process_handle_alarm(proc);
  }
}


static void on_sigchld(struct faio_loop* loop_, struct faio_handle* handle,
    unsigned int revents) {
  ssize_t r;
  char buf[16];
  
  assert(loop == loop_);
  USE(handle);

  if (!(revents & FAIO_POLLIN))
    abort();

  /* Drain the sigchld pipe, that's all there is to it. */
  do {
    r = read(sigchld_pipefd[0], &buf, sizeof buf);
  } while ((r == -1 && errno == EINTR) || r == sizeof buf);

  if (r == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
    abort();

  /* Find exited child processes. */
  for (;;) {
    int pid, status;
    ngx_queue_t* q;

    printf("waitpid\n");
    pid = waitpid(-1, &status, WNOHANG);

    printf("w: %d %s %x\n", pid, strerror(errno), status);

    if (pid == -1 && errno == EINTR)
      continue;
    if (pid == 0 || (pid == -1 && errno == ECHILD))
      break;
    if (pid == -1)
      abort();

    if (!WIFEXITED(status) && !WIFSIGNALED(status))
      continue;

    ngx_queue_foreach(q, &process_queue) {
      process_t* proc = ngx_queue_data(q, process_t, process_queue);
      if (proc->pid == pid)
        process_handle_exit(proc, status);
    }
  }
}


static void on_output(struct faio_loop* loop_, struct faio_handle* handle,
    unsigned int revents) {
  ssize_t r;
  process_t* proc = container_of(handle, process_t, output_handle);

  assert(loop == loop_);

  printf("%d\n", __LINE__);

  if (revents & FAIO_POLLERR) {
    errno = EPIPE;
    goto error;
  }

  printf("%d\n", __LINE__);

  for (;;) {
    printf("%d\n", __LINE__);
    r = read(proc->output_pipefd[0], read_buf, sizeof read_buf);
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
    r=write(1, read_buf, r);
    USE(r);
  }
  printf("%d\n", __LINE__);
  return;

 error:
  return;

 eof:
  return;
}


static void sigchld_handler(int signal) {
  char byte = 42;
  ssize_t r;

  assert(signal == SIGCHLD);
  USE(signal);

  do {
    r = write(sigchld_pipefd[1], &byte, sizeof byte);
  } while (r == -1 && errno == EINTR);

  if (r == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
    abort();
}


int process_setup(struct faio_loop* loop_) {
  struct sigaction sa;

  loop = loop_;
  ngx_queue_init(&process_queue);

  if (create_pipe(sigchld_pipefd, O_NONBLOCK, O_NONBLOCK) < 0)
    return -1;

  if (faio_add(loop,
               &sigchld_handle,
               on_sigchld,
               sigchld_pipefd[0],
               FAIO_POLLIN) < 0)
    goto error;

  memset(&sa, 0, sizeof sa);

  sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
  sa.sa_handler = sigchld_handler;

  if (sigfillset(&sa.sa_mask) < 0)
    goto error;

  if (sigaction(SIGCHLD, &sa, NULL) < 0)
    goto error;

  return 0;

 error:
  close(sigchld_pipefd[0]);
  close(sigchld_pipefd[1]);

  return -1;
}


