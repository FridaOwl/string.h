#include "d3_string.h"

int d3_strncmp(const char* str1, const char* str2, d3_size_t n) {
  int result = 0;
  d3_size_t i = 0;
  for (; result == 0 && i < n && (*str1 || *str2); ++i) {
    if (str1[i] != str2[i]) {
      result = str1[i] - str2[i];
    }
  }
  return result;
}
