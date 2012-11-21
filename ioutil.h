
#ifndef _IOUTIL_H
#define _IOUTIL_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/ioctl.h>

ssize_t read_all(int fd, void* buf, size_t bytes_needed);
ssize_t write_all(int fd, void* buf, size_t bytes_to_write);
int create_pipe(int fds[2], int rflags, int wflags);

#endif

