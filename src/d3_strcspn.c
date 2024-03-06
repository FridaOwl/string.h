#include "d3_string.h"

d3_size_t d3_strcspn(const char* str1, const char* str2) {
  d3_size_t size = 0;
  int res = 1;
  d3_size_t i = 0;
  while (i < d3_strlen(str1) && res == 1) {
    d3_size_t j = 0;
    while (j < d3_strlen(str2)) {
      if (str1[i] == str2[j]) {
        res = 0;
        break;
      }
      j++;
    }
    if (res == 1) {
      size++;
    }
    i++;
  }
  return size;
}