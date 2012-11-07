

#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ioutil.h"
#include "packet.h"
#include "util.h"


typedef struct {
  int32_t type;
  int32_t size;
} __attribute__((packed)) wire_data_header_t;


/* Define functions to parse individual packet types */
#define PROLOGUE(lc, uc)                                                      \
  static ssize_t decode_##lc##_packet(char* wire_data, size_t wire_data_size, \
      lc##_packet_t* packet) {                                                \
    char* field_data;                                                         \
    size_t wire_data_pos;                                                     \
    size_t field_data_pos;                                                    \
                                                                              \
    USE(field_data);                                                          \
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
      packet->field = field_data + field_data_pos;                            \
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
      packet->array_field = (char**) (field_data + field_data_pos);           \
      packet->array_field[count] = NULL;                                      \
    }                                                                         \
                                                                              \
    field_data_pos += array_size;                                             \
                                                                              \
    for (i = 0; i < count; i++) {                                             \
      STRING(array_field[i])                                                  \
    }                                                                         \
  }
#define EPILOGUE(lc, uc)                                                      \
    return sizeof(*packet) + field_data_pos;                                  \
  }
   
ALL_PACKET_TYPES()

#undef PROLOGUE
#undef NUMBER
#undef STRING
#undef STRING_LIST
#undef EPILOGUE


/* Define packet reading function. */
ssize_t read_packet(int fd, packet_t** packet_ptr) {
  char* wire_data;
  ssize_t r, result;
  wire_data_header_t header;
    
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
  } else if (r == 0) {
    /* EOF */
    *packet_ptr = NULL;
    return 0;
  } else if (r != header.size) {
    errno = EBADMSG;
    return -1;
  }
  
  switch ((packet_type_t) header.type) {
#define PROLOGUE(lc, uc)                                                      \
    case uc##_PACKET: {                                                       \
      lc##_packet_t* packet;                                                  \
      ssize_t size;                                                           \
                                                                              \
      size = decode_##lc##_packet(wire_data, header.size, NULL);              \
      if (size < 0) {                                                         \
        result = -1;                                                          \
        break;                                                                \
      }                                                                       \
                                                                              \
      packet = malloc(size);                                                  \
      if (packet == NULL) {                                                   \
        result = -1;                                                          \
        break;                                                                \
      }                                                                       \
                                                                              \
      size = decode_##lc##_packet(wire_data, header.size, packet);            \
      if (size < 0) {                                                         \
        free(packet);                                                         \
        packet = NULL;                                                        \
        result = -1;                                                          \
        break;                                                                \
      }                                                                       \
                                                                              \
      result = size;                                                          \
      *packet_ptr = (packet_t*) packet;                                       \
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


/* Define packet encoding functions for individual packet types. */
#define PROLOGUE(lc, uc)                                                      \
  static ssize_t encode_##lc##_packet(lc##_packet_t* packet,                  \
      char* wire_data) {                                                      \
    size_t wire_data_pos;                                                     \
    wire_data_header_t* header = (wire_data_header_t*) wire_data;             \
                                                                              \
    /* Skip over the header. */                                               \
    wire_data_pos = sizeof *header;
#define NUMBER(field)                                                         \
    {                                                                         \
      if (wire_data != NULL)                                                  \
        *(int32_t*) (wire_data + wire_data_pos) = packet->field;              \
      wire_data_pos += sizeof(int32_t);                                       \
    }
#define STRING(field)                                                         \
    {                                                                         \
      size_t len;                                                             \
                                                                              \
      len = strlen(packet->field);                                            \
                                                                              \
      if (wire_data != NULL)                                                  \
        *(int32_t*) (wire_data + wire_data_pos) = (int32_t) len;              \
      wire_data_pos += sizeof(int32_t);                                       \
                                                                              \
      if (wire_data != NULL)                                                  \
        memcpy(wire_data + wire_data_pos, packet->field, len);                \
      wire_data_pos += len;                                                   \
    }
#define STRING_LIST(count_field, array_field)                                 \
    {                                                                         \
      int32_t count, i;                                                       \
                                                                              \
      count = packet->count_field;                                            \
      if (count < 0) {                                                        \
        for (count = 0; packet->array_field[count] != NULL; count++)          \
          /* nothing */;                                                      \
      }                                                                       \
                                                                              \
      if (wire_data != NULL)                                                  \
        *(int32_t*) (wire_data + wire_data_pos) = (int32_t) count;            \
      wire_data_pos += sizeof(int32_t);                                       \
                                                                              \
      for (i = 0; i < count; i++) {                                           \
        STRING(array_field[i])                                                \
      }                                                                       \
    }
#define EPILOGUE(lc, uc)                                                      \
    /* Write header if wire_data was specified. */                            \
    if (header != NULL) {                                                     \
      header->type = (int32_t) packet->type;                                  \
      header->size = wire_data_pos - sizeof *header;                          \
    }                                                                         \
                                                                              \
    return wire_data_pos;                                                     \
  }

ALL_PACKET_TYPES()

#undef PROLOGUE
#undef NUMBER
#undef STRING
#undef STRING_LIST
#undef EPILOGUE


/* Function to write any packet. */
ssize_t write_packet(int fd, packet_t* packet) {
  ssize_t size, r;
  char* buf;
  
  switch (packet->type) {
#define PROLOGUE(lc, uc)                                                      \
    case uc##_PACKET: {                                                       \
      size = encode_##lc##_packet((lc##_packet_t*) packet, NULL);             \
      if (size < 0)                                                           \
        return -1;                                                            \
                                                                              \
      buf = malloc(size);                                                     \
      if (buf == NULL)                                                        \
        return -1;                                                            \
                                                                              \
      r = encode_##lc##_packet((lc##_packet_t*) packet, buf);                 \
      if (r < 0) {                                                            \
        free(buf);                                                            \
        return -1;                                                            \
      }                                                                       \
                                                                              \
      assert(r == size);                                                      \
                                                                              \
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
      assert(0);
  }
  
  r = write_all(fd, buf, size);
  if (r < 0) {
    free(buf);
    return -1;
  }
  
  assert(r == size);
  
  free(buf);

  return r;
}
