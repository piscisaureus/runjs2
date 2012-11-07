

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "ioutil.h"


#include <stdio.h>

ssize_t read_all(int fd, void* buf, size_t bytes_needed) {
  ssize_t bytes_read = 0;
  
  while (bytes_read < (ssize_t) bytes_needed) {
    ssize_t r = read(fd, (char*) buf + bytes_read, bytes_needed - bytes_read);

    if (r > 0)
      bytes_read += r;

    if (r == 0 ||
        (r < 0 && errno != EINTR))
      return -1;
  }
  
  return bytes_read;
}


ssize_t write_all(int fd, void* buf, size_t bytes_to_write) {
   ssize_t bytes_written = 0;
   
   while (bytes_written < (ssize_t) bytes_to_write) {
     ssize_t r = write(fd,
                       (char*) buf + bytes_written, 
                       bytes_to_write - bytes_written);
                       
    if (r > 0)
      bytes_written += r;
      
    if (r == 0 ||
        (r < 0 && errno != EINTR))
      return -1;
   }
   
   return bytes_written;
}