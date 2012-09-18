
#ifndef _RJS_CMD_H
#define _RJS_CMD_H

typedef enum {
  RJS_START = 1,
  RJS_STOP = 2,
  RJS_QUERY = 3,
  RJS_LIST = 4
} rjs_command_type_t;

int rjs_process_cmd(int server_fd);

#endif

