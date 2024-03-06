#include "d3_string.h"

char *d3_strcpy(char *dest, const char *src) {
  if (dest && src) {
    d3_size_t i = 0;
    while (src[i] != '\0') {
      dest[i] = src[i];
      i++;
    }
    dest[i] = '\0';
  }
  return dest;
}