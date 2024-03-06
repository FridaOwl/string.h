#include "d3_string.h"

void* d3_to_lower(const char* str) {
  if (str == d3_NULL) {
    return d3_NULL;
  }
  d3_size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  char* result = (char*)malloc((len + 1) * sizeof(char));
  if (result == d3_NULL) {
    return d3_NULL;
  }
  for (d3_size_t i = 0; i < len; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      result[i] = str[i] + 32;
    } else {
      result[i] = str[i];
    }
  }
  result[len] = '\0';
  return result;
}