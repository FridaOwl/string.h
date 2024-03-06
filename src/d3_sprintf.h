#ifndef SRC_D3_SPRINTF_H_
#define SRC_D3_SPRINTF_H_
#include <ctype.h>
#include <locale.h>
#include <stdint.h>

#include "d3_string.h"

typedef struct {
  int minus;
  int plus;
  int space;
  int sharp;
  int zero;
  int hash;
  int width;
  int precision;
  char specifier;
  char length;
  char e_spec;
  int precision_copy;
} flags;

int parsing_spec(const char format);
const char *parsing_flags(flags *fl, const char *format);
const char *parsing_width(flags *fl, const char *format, va_list args);
const char *parsing_precision(flags *fl, const char *format, va_list args);
const char *parsing_length(flags *fl, const char *format);
void parsing_spec_two(char format, char *buff, flags fl, va_list args,
                      char *str_start, char *str);
void parsing_char(flags fl, char *str, va_list args);
void wchar_t_to_string(flags fl, char *str, wchar_t c);
void char_to_string(flags fl, char *str, char c);
void parsing_int(flags fl, char *str, va_list args);
void int_to_string(flags fl, char *str, int64_t num, int base);
void int_write_to_array(flags fl, int num_count, char *str, char *buff,
                        int minus);
void parsing_e(flags fl, char *str, va_list args);
void e_to_string(flags fl, char *str, long double num);
void e_logic(flags *fl, long double num, char *str, int *pos, int *e_count,
             int *buff, int minus);
void e_zero(flags fl, char *str);
void parsing_float(flags fl, char *str, va_list args);
void float_to_string(flags fl, char *str, long double num);
int float_write_to_array(flags fl, long double num, long double num_copy,
                         long long int whole_num, char *buff, char *str,
                         int minus);
void parsing_g(flags fl, char *str, va_list args);
void g_to_string(flags fl, char *str, long double num);
void g_two_logic(char *str, long double num);
void parsing_o(flags fl, char *str, va_list args);
void o_to_string(int64_t num, char *str, flags fl);
void parsing_string(flags fl, char *str, va_list args);
void wchar_t_string_to_string(flags fl, char *str, wchar_t *c);
void string_to_string(flags fl, char *str, char *c);
void parsing_u(flags fl, char *str, va_list args);
void uint_to_string(flags fl, char *str, unsigned long num, int base);
void to_upper(char *str);
void parsing_x(flags fl, char *str, va_list args);
void x_to_string(int64_t num, char *str, flags fl);
void pointer_to_string(void *ptr, char *str, flags fl);
void n_to_string(const char *str, const char *str2, va_list args);
int prov_num(const char format);

#endif
