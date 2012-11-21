

#include "ioutil.h"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>


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


int create_pipe(int fds[2], int rflags, int wflags) {
  if (pipe(fds) < 0)
    return -1;

  if (ioctl(fds[0], FIOCLEX, NULL) < 0)
    goto error;

  if (ioctl(fds[1], FIOCLEX, NULL) < 0)
    goto error;

  if (rflags != 0) {
    int flags;

    flags = fcntl(fds[0], F_GETFL);
    if (flags < 0)
      goto error;

    flags |= rflags;

    if (fcntl(fds[0], F_SETFL, flags) < 0)
      goto error;
  }

  if (wflags != 0) {
    int flags;

    flags = fcntl(fds[1], F_GETFL);
    if (flags < 0)
      goto error;

    flags |= wflags;

    if (fcntl(fds[1], F_SETFL, flags) < 0)
      goto error;
  }

  return 0;

 error:
  close(fds[0]);
  close(fds[1]);
  return -1;
}

