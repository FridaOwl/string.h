#include "d3_string.h"

char *d3_strtok(char *str, const char *delim) {
  static char *base = d3_NULL;
  if (str == d3_NULL && base == d3_NULL) {
    return d3_NULL;
  }
  if (!str) {
    str = base;
    if (str == d3_NULL) {
      return d3_NULL;
    }
  }
  if (*delim == '\0') {
    base = d3_strchr(str + 1, '\0');
    return str;
  }
  str += d3_strspn(str, delim);
  if (*str == '\0') {
    base = d3_NULL;
    return d3_NULL;
  }
  base = str + d3_strcspn(str, delim);
  if (base[0] != '\0') {
    base[0] = '\0';
    base++;
  } else {
    base = d3_NULL;
  }
  return str;
}