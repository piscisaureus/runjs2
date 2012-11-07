
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

#define STOP_PACKET() \
  PROLOGUE(stop, STOP) \
    STRING(tag) \
  EPILOGUE(stop, STOP)

#define START_SUCCESS_PACKET() \
  PROLOGUE(start_success, START_SUCCESS) \
    NUMBER(pid) \
  EPILOGUE(start_success, START_SUCCESS)

#define ERROR_PACKET() \
  PROLOGUE(error, ERROR) \
    NUMBER(err) \
    STRING(message) \
    STRING(syscall) \
  EPILOGUE(error, ERROR)


#define ALL_PACKET_TYPES() \
    START_PACKET() \
    STOP_PACKET() \
    START_SUCCESS_PACKET() \
    ERROR_PACKET()


/* Define enum with types. */
#define PROLOGUE(lc, uc) uc##_PACKET,
#define NUMBER(field) /* empty */
#define STRING(field) /* empty */
#define STRING_LIST(count_field, array_field) /* empty */
#define EPILOGUE(lc, uc) /* empty */

typedef enum {
  ALL_PACKET_TYPES()
  PACKET_TYPE_MAX
} packet_type_t;

#undef PROLOGUE
#undef NUMBER
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
#define NUMBER(field)                                                         \
    int32_t field;
#define STRING(field)                                                         \
    char* field;
#define STRING_LIST(count_field, array_field)                                 \
    int32_t count_field;                                                      \
    char** array_field;
#define EPILOGUE(lc, uc)                                                      \
  } lc##_packet_t;

ALL_PACKET_TYPES()

#undef PROLOGUE
#undef NUMBER
#undef STRING
#undef STRING_LIST
#undef EPILOGUE


ssize_t read_packet(int fd, packet_t** packet_ptr);
ssize_t write_packet(int fd, packet_t* packet);

#endif /* PACKET_H */
