#ifndef _CPUCYCLES_H
#define _CPUCYCLES_H

#include <stdint.h>

static int64_t cpucycles(void) {
  unsigned int hi, lo;

  __asm__ volatile("rdtsc\n\t" : "=a"(lo), "=d"(hi));
  return ((int64_t)lo) | (((int64_t)hi) << 32);
}

#endif
