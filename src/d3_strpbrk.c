#include "d3_string.h"

const char *d3_strpbrk(const char *str1, const char *str2) {
  const char *buffer = NULL;
  for (d3_size_t i = 0; i < d3_strlen(str1); i++) {
    for (d3_size_t j = 0; j < d3_strlen(str2); j++) {
      if (str1[i] == str2[j]) {
        buffer = &str1[i];
        j = d3_strlen(str2);
        i = d3_strlen(str1);
      }
    }
  }
  return buffer;
}