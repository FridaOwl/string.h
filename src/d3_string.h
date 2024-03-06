#ifndef D3_STRING_H
#define D3_STRING_H

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define d3_size_t unsigned long long
#define BUFF_SIZE 1024
#define d3_NULL (void *)0

int d3_sprintf(char *str, const char *format, ...);
void *d3_memchr(const void *str, int c, d3_size_t n);
int d3_memcmp(const void *str1, const void *str2, d3_size_t n);
void *d3_memcpy(void *dest, const void *src, d3_size_t n);
void *d3_memset(void *str, int c, d3_size_t n);
d3_size_t d3_strcspn(const char *str1, const char *str2);
d3_size_t d3_strlen(const char *str);
char *d3_strncat(char *dest, const char *src, d3_size_t n);
int d3_strncmp(const char *str1, const char *str2, d3_size_t n);
char *d3_strcpy(char *dest, const char *src);
char *d3_strchr(const char *str, int c);
char *d3_strstr(const char *haystack, const char *needle);
char *d3_strncpy(char *dest, const char *src, d3_size_t n);
char *d3_strrchr(const char *str, int c);
char *d3_strerror(int errnum);
char *d3_strtok(char *str, const char *delim);
d3_size_t d3_strspn(const char *str, const char *delim);
void *d3_to_lower(const char *str);
void *d3_to_upper(const char *str);
void *d3_trim(const char *src, const char *trim_chars);
void *d3_insert(const char *src, const char *str, d3_size_t start_index);
const char *d3_strpbrk(const char *str1, const char *str2);
#endif  // D3_STRING_H
