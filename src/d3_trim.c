#include "d3_string.h"

int left_side(const char *src, const char *trim_chars, int last) {
  int res = 0;
  int size = d3_strlen(trim_chars);
  for (int i = 0; i < size; i++) {
    if (src[last] == trim_chars[i]) {
      res = 1;
      break;
    }
  }
  return res;
}
int right_side(const char *src, const char *trim_chars, int last) {
  int res = 0;
  last--;
  int size = d3_strlen(trim_chars);
  for (int i = 0; i < size; i++) {
    if (src[last] == trim_chars[i]) {
      res = 1;
      break;
    }
  }
  return res;
}

void *d3_trim(const char *src, const char *trim_chars) {
  char *arr = d3_NULL;
  if (trim_chars == d3_NULL) {
    return d3_NULL;
  }
  if (src != d3_NULL) {
    if (trim_chars[0] != '\0') {
      arr = (char *)malloc((d3_strlen(src) + 1) * sizeof(char));
      if (arr != d3_NULL) {
        d3_size_t begin = 0, last = d3_strlen(src);
        while (left_side(src, trim_chars, begin)) {
          begin++;
        }
        if (begin != last) {
          while (right_side(src, trim_chars, last)) {
            last--;
          }
        } else {
          arr[0] = '\0';
        }
        d3_size_t arr_index = 0;
        for (d3_size_t i = begin; i < last; i++) {
          arr[arr_index] = src[i];
          arr_index++;
        }
        arr[arr_index] = '\0';
      }
    } else {
      arr = d3_trim(src, "\t\n ");
    }
  }
  return arr;
}