#include "d3_string.h"

char* d3_strchr(const char* str, int c) {
  char* check;
  for (; *str != c && *str != '\0'; ++str) {
  }
  if (*str == c) {
    check = (char*)str;
  } else {
    check = d3_NULL;
  }
  return check;
}