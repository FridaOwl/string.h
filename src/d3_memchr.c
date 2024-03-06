#include "d3_string.h"

void* d3_memchr(const void* str, int c, d3_size_t n) {
  const char* ptr = (const char*)str;
  void* result = d3_NULL;
  d3_size_t i = 0;
  while (i < n && ptr) {
    if (*ptr == (char)c) {
      result = (void*)ptr;
      break;
    }
    ptr++;
    i++;
  }
  return result;
}