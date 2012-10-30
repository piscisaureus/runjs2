

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ioutil.h"


#define START_PACKET() \
  PROLOGUE(start, START) \
    STRING(tag) \
    STRING(filename) \
    STRING(cwd) \
    STRING_LIST(argc, argv) \
    STRING_LIST(envc, envv) \
  EPILOGUE(start, START)

#define STOP_PACKET() \
  PROLOGUE(stop, STOP) \
    STRING(filename) \
    STRING(cwd) \
    STRING_LIST(argc, argv) \
    STRING_LIST(envc, envv) \
  EPILOGUE(stop, STOP)

#define ALL_PACKET_TYPES() \
    START_PACKET() \
    STOP_PACKET()

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


/* Define functions to parse individual packet types */
#define PROLOGUE(lc, uc)                                                      \
  ssize_t parse_##lc##_packet(char* wire_data, size_t wire_data_size,         \
      lc##_packet_t* packet) {                                                \
    char* field_data;                                                         \
    size_t wire_data_pos;                                                     \
    size_t field_data_pos;                                                    \
                                                                              \
    if (packet != NULL) {                                                     \
      field_data = (char*) (packet + 1);                                      \
      packet->type = uc##_PACKET;                                             \
    } else {                                                                  \
      field_data = NULL;                                                      \
    }                                                                         \
                                                                              \
    wire_data_pos = 0;                                                        \
    field_data_pos = 0;                                                       
#define NUMBER(field)                                                         \
  {                                                                           \
    if (wire_data_size < wire_data_pos + sizeof(int32_t))                     \
      return -1;                                                              \
                                                                              \
    if (packet)                                                               \
      packet->field = *(uint32_t*) (wire_data + wire_data_pos);               \
    wire_data_pos += sizeof(uint32_t);                                        \
  }
#define STRING(field)                                                         \
  {                                                                           \
    uint32_t len;                                                             \
                                                                              \
    if (wire_data_size < wire_data_pos + sizeof(int32_t))                     \
      return -1;                                                              \
                                                                              \
    len = *(uint32_t*) (wire_data + wire_data_pos);                           \
    field_data_pos += sizeof(uint32_t);                                       \
    wire_data_pos += sizeof(uint32_t);                                        \
                                                                              \
    if (wire_data_size < wire_data_pos + len)                                 \
      return -1;                                                              \
                                                                              \
    if (field_data) {                                                         \
      memcpy(field_data + field_data_pos, wire_data + wire_data_pos, len);    \
      field_data[field_data_pos + len] = '\0';                                \
    }                                                                         \
                                                                              \
    wire_data_pos += len;                                                     \
    field_data_pos += len + 1;                                                \
  }
#define STRING_LIST(count_field, array_field)                                 \
  {                                                                           \
    int32_t i, count;                                                         \
    size_t array_size;                                                        \
                                                                              \
    if (wire_data_size < wire_data_pos + sizeof(int32_t))                     \
      return -1;                                                              \
                                                                              \
    count = *(uint32_t*) (wire_data + wire_data_pos);                         \
                                                                              \
    if (packet != NULL)                                                       \
      packet->count_field = count;                                            \
                                                                              \
    wire_data_pos += sizeof(uint32_t);                                        \
                                                                              \
    /* Allocate space for the array, and an additional NULL. */               \
    array_size = sizeof(char*) * (count + 1);                                 \
                                                                              \
    if (packet) {                                                             \
      packet->array_field = (char**) field_data + field_data_pos;             \
      packet->array_field[count] = NULL;                                      \
    }                                                                         \
                                                                              \
    field_data_pos += array_size;                                             \
                                                                              \
    for (i = 0; i < count; i++) {                                             \
      STRING((packet)->(array_field)[i])                                      \
    }                                                                         \
  }
#define EPILOGUE(lc, uc)                                                      \
    return sizeof(*packet) + field_data_pos;                                  \
  }
   
ALL_PACKET_TYPES();

#undef PROLOGUE
#undef NUMBER
#undef STRING
#undef STRING_LIST
#undef EPILOGUE


/* Define packet reading function. */
int read_packet(int fd, void** packet_ptr) {
  char* wire_data;
  ssize_t r;
  int result;
  
  struct {
    int32_t type;
    int32_t size;
  } __attribute__((packed)) header;
  
  r = read_all(fd, &header, sizeof header);
  if (r < 0) {
    return -1;
  } else if (r != sizeof header) {
    errno = EBADMSG;
    return -1;
  }
    
  wire_data = malloc(header.size);
  if (wire_data == NULL)
    return -1;
    
  r = read_all(fd, wire_data, header.size);
  if (r < 0) {
    return -1;
  } else if (r != header.size) {
    errno = EBADMSG;
    return -1;
  }
  
  switch ((packet_type_t) header.type) {

#define PROLOGUE(lc, uc)                                                      \
    case uc##_PACKET: {                                                       \
      ssize_t size = parse_##lc##_packet(wire_data, header.size, NULL);       \
      if (size < 0) {                                                         \
        result = -1;                                                          \
        break;                                                                \
      }                                                                       \
                                                                              \
      lc##_packet_t* packet = malloc(size);                                   \
      if (packet == NULL) {                                                   \
        result = -1;                                                          \
        break;                                                                \
      }                                                                       \
                                                                              \
      size = parse_##lc##_packet(wire_data, header.size, packet);             \
      if (size < 0) {                                                         \
        result = -1;                                                          \
        break;                                                                \
      }                                                                       \
                                                                              \
      result = 0;                                                             \
      break;                                                                  \
    }
#define NUMBER(field) /* empty */
#define STRING(field) /* empty */
#define STRING_LIST(count_field, array_field) /* empty */
#define EPILOGUE(lc, uc) /* empty */

    ALL_PACKET_TYPES()
    
#undef PROLOGUE
#undef NUMBER
#undef STRING
#undef STRING_LIST
#undef EPILOGUE
     
    default:
      errno = EBADMSG;
      result = -1;
  }
  
  free(wire_data);
  
  return result;
}


