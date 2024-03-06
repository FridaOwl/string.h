#include "d3_string.h"

int d3_memcmp(const void* str1, const void* str2, d3_size_t n) {
  const unsigned char* s1 = str1;
  const unsigned char* s2 = str2;
  int result = 0;
  for (d3_size_t i = 0; i < n && result == 0; ++i) {
    if (s1[i] != s2[i]) {
      result = s1[i] - s2[i];
    }
  }
  return result;
}
