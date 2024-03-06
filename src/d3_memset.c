#include "d3_string.h"

void* d3_memset(void* str, int c, d3_size_t n) {
  unsigned char* ptr = (unsigned char*)str;
  for (d3_size_t i = 0; i < n; ++i) {
    *ptr++ = (unsigned char)c;
  }
  return str;
}