#include "d3_string.h"

d3_size_t d3_strspn(const char *str, const char *delim) {
  d3_size_t count = 0;
  const char *ptr = str;
  while (*ptr != '\0' && d3_strchr(delim, *ptr) != d3_NULL) {
    count++;
    ptr++;
  }
  return count;
}