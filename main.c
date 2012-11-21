

#include "faio.h"
#include "server.h"
#include "process.h"
#include "util.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


#define SERVER_PATH "/tmp/runjs.sock"
#define CHECK_INTERVAL 1 /* In seconds. */


void fatal_error(const char* message) {
  perror(message);
  exit(1);
}


int main(int argc, char* argv[]) {
  struct faio_loop loop;

  USE(argc);
  USE(argv);

  signal(SIGPIPE, SIG_IGN);

  if (faio_init(&loop) < 0)
    fatal_error("faio_init");

  if (process_setup(&loop) < 0)
    fatal_error("process_setup");
    
  if (server_setup(&loop, SERVER_PATH) < 0)
    fatal_error("server_setup");

  for (;;) {
    printf("poll\n");
    faio_poll(&loop, CHECK_INTERVAL);
    process_sweep();
  }

  UNREACHABLE();
}

