#include "d3_string.h"

void *d3_memcpy(void *dest, const void *src, d3_size_t n) {
  unsigned char *d = dest;
  const unsigned char *s = src;
  for (d3_size_t i = 0; i < n; ++i) {
    d[i] = s[i];
  }
  return dest;
}
