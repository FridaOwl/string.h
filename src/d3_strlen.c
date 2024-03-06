#include "d3_string.h"

d3_size_t d3_strlen(const char *str) {
  const char *ptr = str;
  while (*ptr != '\0') {
    ptr++;
  }
  return ptr - str;
}