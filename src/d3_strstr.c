#include "d3_string.h"

char *d3_strstr(const char *haystack, const char *needle) {
  if (d3_strlen(haystack) >= d3_strlen(needle)) {
    d3_size_t i = 0;
    while (i <= d3_strlen(haystack) - d3_strlen(needle)) {
      int found = 1;
      d3_size_t m = i, r = 0;
      while (needle[r] && haystack[m] == needle[r]) {
        m++;
        r++;
      }
      if (needle[r] != '\0') {
        found = 0;
      }
      if (found) {
        return (char *)(haystack + i);
      }
      i++;
    }
  }
  return d3_NULL;
}