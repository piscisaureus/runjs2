
#ifndef _PACKET_H
#define _PACKET_H

#include <stdint.h>
#include <sys/types.h>


/* Packet layouts. */
#define START_PACKET() \
  PROLOGUE(start, START) \
    STRING(tag) \
    STRING(file) \
    STRING_LIST(argc, argv) \
    STRING_LIST(envc, envv) \
    STRING(cwd) \
  EPILOGUE(start, START)

#define START_RESULT_PACKET() \
  PROLOGUE(start_result, START_RESULT) \
    STRING(tag) \
    INTEGER(id) \
    INTEGER(pid) \
    INTEGER(error) \
    STRING(message) \
  EPILOGUE(start_result, START_RESULT)

#define STOP_PACKET() \
  PROLOGUE(stop, STOP) \
    STRING(tag) \
    INTEGER(id) \
    INTEGER(wildcard) \
    INTEGER(kill_signo) \
    INTEGER(kill_group) \
    INTEGER(hard_kill_timeout) \
  EPILOGUE(stop, STOP)

#define STOP_RESULT_PACKET() \
  PROLOGUE(stop_result, STOP_RESULT) \
    STRING(tag) \
    INTEGER(id) \
    INTEGER(pid) \
    INTEGER(state) \
    INTEGER(result) \
    INTEGER(error) \
    STRING(message) \
  EPILOGUE(stop_result, STOP_RESULT)

#define END_PACKET() \
  PROLOGUE(end, END) \
    INTEGER(result) \
    INTEGER(error) \
    STRING(message) \
  EPILOGUE(end, END)

#define ALL_PACKET_TYPES() \
    START_PACKET() \
    START_RESULT_PACKET() \
    STOP_PACKET() \
    STOP_RESULT_PACKET() \
    END_PACKET()


/* Define helpers for scalar types. */
#define INTEGER(field) SCALAR(field, int32_t)
#define FLOAT(field) SCALAR(field, double)


/* Define enum with packet types. */
#define PROLOGUE(lc, uc) uc##_PACKET,
#define SCALAR(field, type) /* empty */
#define STRING(field) /* empty */
#define STRING_LIST(count_field, array_field) /* empty */
#define EPILOGUE(lc, uc) /* empty */

typedef enum {
  ALL_PACKET_TYPES()
  PACKET_TYPE_MAX
} packet_type_t;

#undef PROLOGUE
#undef SCALAR
#undef STRING
#undef STRING_LIST
#undef EPILOGUE


/* Common packet header. */
typedef struct {
  packet_type_t type;
} packet_t;


/* Define structs. */
#define PROLOGUE(lc, uc)                                                      \
  typedef struct {                                                            \
    packet_type_t type;
#define SCALAR(field, type)                                                   \
    type field;
#define STRING(field)                                                         \
    char* field;
#define STRING_LIST(count_field, array_field)                                 \
    int32_t count_field;                                                      \
    char** array_field;
#define EPILOGUE(lc, uc)                                                      \
  } lc##_packet_t;

ALL_PACKET_TYPES()

#undef PROLOGUE
#undef SCALAR
#undef STRING
#undef STRING_LIST
#undef EPILOGUE


ssize_t read_packet(int fd, packet_t** packet_ptr);
ssize_t write_packet(int fd, packet_t* packet);

#endif /* PACKET_H */
