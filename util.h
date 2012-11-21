

#ifndef _UTIL_H
#define _UTIL_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>


#define container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) - offsetof(type, member)))

#define USE(x) \
    ((void) x)

#define UNREACHABLE() \
    assert(0);


int64_t get_abs_time();

#endif

