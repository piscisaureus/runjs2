
#include "util.h"

#include <time.h>


int64_t get_abs_time() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ((uint64_t) ts.tv_sec) * ((int64_t) 1e3) + 
          ts.tv_nsec / ((int64_t) 1e6);
}

