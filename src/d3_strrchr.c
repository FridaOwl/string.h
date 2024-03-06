#include "d3_string.h"

char *d3_strrchr(const char *str, int c) {
  char *res = d3_NULL;
  int i = d3_strlen(str);
  while (i >= 0) {
    if (str[i] == c) {
      res = ((char *)str) + i;
      break;
    }
    i--;
  }
  return res;
}