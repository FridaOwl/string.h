#include "d3_string.h"

char *d3_strncat(char *dest, const char *src, d3_size_t n) {
  char *dest_start = dest;
  while (*dest != '\0') {
    dest++;
  }
  while (*src != '\0' && n > 0) {
    *dest = *src;
    dest++;
    src++;
    n--;
  }
  *dest = '\0';
  return dest_start;
}