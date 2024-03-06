#include "d3_string.h"

char *d3_strncpy(char *dest, const char *src, d3_size_t n) {
  char *dest_start = dest;
  while (*src != '\0' && n > 0) {
    *dest = *src;
    dest++;
    src++;
    n--;
  }
  while (n > 0) {
    *dest = '\0';
    dest++;
    n--;
  }
  return dest_start;
}