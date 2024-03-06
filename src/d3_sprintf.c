#include "d3_sprintf.h"

#include "d3_string.h"

int d3_sprintf(char *str, const char *format, ...) {
  char *str_start = str;
  int i = 0;
  va_list args;
  va_start(args, format);
  while (*format != '\0') {
    char buff[BUFF_SIZE] = {'\0'};
    flags fl = {0};
    if (*format == '%') {
      format++;
      while (parsing_spec(*format)) {
        format = parsing_flags(&fl, format);
        format = parsing_width(&fl, format, args);
        format = parsing_precision(&fl, format, args);
        format = parsing_length(&fl, format);
      }
      parsing_spec_two(*format, buff, fl, args, str_start, str);
    } else {
      buff[i] = *format;
    }
    format++;
    for (int j = 0; buff[j]; j++, str++) {
      *str = buff[j];
    }
  }
  va_end(args);
  *str = '\0';
  return str - str_start;
}
void parsing_spec_two(char format, char *buff, flags fl, va_list args,
                      char *str_start, char *str) {
  if (format == 'c') {
    parsing_char(fl, buff, args);
  }
  if (format == 'd' || format == 'i') {
    parsing_int(fl, buff, args);
  }
  if (format == 'e' || format == 'E') {
    fl.e_spec = format;
    parsing_e(fl, buff, args);
  }
  if (format == 'f') {
    parsing_float(fl, buff, args);
  }
  if (format == 'g' || format == 'G') {
    fl.e_spec = format;
    parsing_g(fl, buff, args);
  }
  if (format == 'o') {
    parsing_o(fl, buff, args);
  }
  if (format == 's') {
    parsing_string(fl, buff, args);
  }
  if (format == 'u') {
    parsing_u(fl, buff, args);
  }
  if (format == 'x' || format == 'X') {
    fl.e_spec = format;
    parsing_x(fl, buff, args);
  }
  if (format == 'p') {
    pointer_to_string(va_arg(args, void *), buff, fl);
  }
  if (format == 'n') {
    n_to_string(str, str_start, args);
  }
  if (format == '%') {
    *buff++ = '%';
  }
}
int parsing_spec(const char format) {
  int result = 1;
  int number_of_specifiers = 16;
  const char spec[BUFF_SIZE] = {'c', 'd', 'i', 'e', 'E', 'f', 'g', 'G',
                                'o', 's', 'u', 'x', 'X', 'p', 'n', '%'};
  for (int i = 0; i < number_of_specifiers; i++) {
    if (spec[i] == format) {
      result = 0;
      i = number_of_specifiers;
    }
  }
  return result;
}
const char *parsing_flags(flags *fl, const char *format) {
  fl->specifier = ' ';
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '#' ||
         *format == '0') {
    switch (*format) {
      case '-':
        fl->minus = 1;
        break;
      case '+':
        fl->plus = 1;
        break;
      case ' ':
        fl->space = 1;
        break;
      case '#':
        fl->sharp = 1;
        break;
      case '0':
        fl->specifier = '0';
        fl->zero = 1;
        break;
    }
    format++;
  }
  if (fl->minus) {
    fl->specifier = ' ';
  }
  return format;
}
const char *parsing_width(flags *fl, const char *format, va_list args) {
  int result = 0;
  if (*format == '*') {
    result = va_arg(args, int);
    format++;
  }
  if (prov_num(*format)) {
    while (*format && prov_num(*format)) {
      result = result * 10 + (*format - '0');
      format++;
    }
  }
  fl->width = result;
  return format;
}
const char *parsing_precision(flags *fl, const char *format, va_list args) {
  int result = 0;
  if (*format == '.') {
    format++;
    if (prov_num(*format)) {
      while (*format && prov_num(*format)) {
        result = result * 10 + (*format - '0');
        format++;
      }
      if (result == 0) {
        result = -1;
      }
    } else {
      result = -2;
    }
  }
  if (*format == '*') {
    result = va_arg(args, int);
    format++;
  }
  fl->precision = result;
  return format;
}
const char *parsing_length(flags *fl, const char *format) {
  switch (*format) {
    case 'h':
      fl->length = 'h';
      format++;
      break;
    case 'l':
      fl->length = 'l';
      format++;
      break;
    case 'L':
      fl->length = 'L';
      format++;
  }
  return format;
}
void parsing_char(flags fl, char *str, va_list args) {
  if (fl.length == 'l') {
    wchar_t c = va_arg(args, wchar_t);
    wchar_t_to_string(fl, str, c);
  } else {
    char c = (char)va_arg(args, int);
    char_to_string(fl, str, c);
  }
}
void wchar_t_to_string(flags fl, char *str, wchar_t c) {
  if (fl.minus) {
    wcstombs(str, &c, BUFF_SIZE);
    int a = d3_strlen(str);
    str += a;
    for (int i = a; i < fl.width; i++, str++) {
      *str = fl.specifier;
    }
  } else {
    char buff[1024] = {'\0'};
    wcstombs(buff, &c, BUFF_SIZE);
    int gg = fl.width - d3_strlen(buff);
    for (int i = 0; i < gg; i++, str++) {
      *str = fl.specifier;
    }
    wcstombs(str, &c, BUFF_SIZE);
  }
}
void char_to_string(flags fl, char *str, char c) {
  if (fl.minus) {
    *str = c;
    str++;
    for (int i = 1; i < fl.width; i++, str++) {
      *str = fl.specifier;
    }
  } else {
    for (int i = 1; i < fl.width; i++, str++) {
      *str = fl.specifier;
    }
    *str = c;
  }
}
void parsing_int(flags fl, char *str, va_list args) {
  int64_t num = va_arg(args, int64_t);
  switch (fl.length) {
    case 0:
      num = (int32_t)num;
      break;
    case 'h':
      num = (int16_t)num;
  }
  int_to_string(fl, str, num, 10);
}
void int_to_string(flags fl, char *str, int64_t num, int base) {
  char buff[1024];
  int num_count = 0, minus = 0;
  int64_t num_copy = num;
  if (fl.specifier == '0') {
    fl.zero = 1;
  }
  if (num < 0) {
    num *= -1;
    minus = 1;
  }
  if (num_copy == 0 && fl.precision != -1 && fl.precision != -2) {
    buff[num_count++] = '0';
  }
  while (num > 0) {
    int digit = num % base;
    buff[num_count++] = (char)('0' + digit);
    num -= digit;
    num /= base;
  }
  if (minus) {
    if (fl.zero) {
      *str++ = '-';
      fl.width--;
    }
  }
  if (num_copy > 0 && fl.plus) {
    if (fl.zero) {
      *str++ = '+';
      fl.width--;
    }
  }
  if (fl.space && fl.plus == 0 && num_copy >= 0 && fl.precision <= 0) {
    buff[num_count++] = ' ';
  }
  int_write_to_array(fl, num_count, str, buff, minus);
}
void int_write_to_array(flags fl, int num_count, char *str, char *buff,
                        int minus) {
  if (fl.precision) {
    fl.precision -= num_count;
    for (int j = 0; j < fl.precision; j++) {
      buff[num_count++] = '0';
    }
  }

  if (fl.sharp && (fl.e_spec == 'x' || fl.e_spec == 'X')) {
    buff[num_count++] = 'x';
    buff[num_count++] = '0';
  }
  if (minus && fl.zero == 0) {
    buff[num_count++] = '-';
  }
  if (fl.zero == 0 && fl.plus && minus == 0) {
    buff[num_count++] = '+';
  }
  if (fl.minus) {
    char *str_copy = str + num_count;
    for (int j = num_count; j < fl.width; j++) {
      *str_copy = fl.specifier;
      str_copy++;
    }
  }
  if (fl.minus == 0) {
    for (int j = num_count; j < fl.width; j++) {
      buff[num_count++] = fl.specifier;
    }
  }
  for (num_count--; num_count >= 0; num_count--) {
    *str++ = buff[num_count];
  }
  if (fl.sharp) {
    *str = '\0';
  }
}
void parsing_e(flags fl, char *str, va_list args) {
  long double num;
  if (fl.length == 'L') {
    num = va_arg(args, long double);
  } else {
    num = va_arg(args, double);
  }
  e_to_string(fl, str, num);
}
void e_to_string(flags fl, char *str, long double num) {
  int e_count = 0, pos = 0, buff[BUFF_SIZE] = {'\0'}, minus = 0;
  long double num_copy = num;
  if (num < 0 && num != 0) {
    num *= -1;
    minus = 1;
  }
  if (fl.precision == 0) {
    fl.precision = 6;
  }
  if (fl.space && num_copy == 0) {
    *str++ = ' ';
  }
  if (num != 0) {
    e_logic(&fl, num, str, &pos, &e_count, buff, minus);
    str += d3_strlen(str);
    if (fl.sharp && fl.precision < 0) {
      *str++ = '.';
    }
    if (pos > 0) {
      *str++ = '.';
    }
    for (int t = fl.precision; 0 < t; t--) {
      *str++ = buff[t] + '0';
    }
    str += d3_strlen(str);
    *str++ = fl.e_spec;
    if (e_count >= 0) {
      *str++ = '+';
    } else {
      *str++ = '-';
      e_count *= -1;
    }
    *(str + 1) = e_count % 10 + '0';
    e_count /= 10;
    *str++ = e_count % 10 + '0';
    if (fl.minus) {
      str++;
      for (int h = 6 + pos; h <= fl.width; h++) {
        *str++ = fl.specifier;
      }
    }
  } else {
    e_zero(fl, str);
  }
}
void e_logic(flags *fl, long double num, char *str, int *pos, int *e_count,
             int *buff, int minus) {
  long double i = 0;
  int count = 0;
  while (num < 1) {
    num *= 10;
    (*e_count)--;
  }
  while (num >= 10) {
    num /= 10;
    (*e_count)++;
  }
  num = modfl(num, &i);
  if (fl->precision <= 0) {
    i++;
  }
  int gg = 0;
  while (gg <= fl->precision) {
    num *= 10;
    gg++;
  }
  long long int num1 = roundl(num);
  while (count <= fl->precision) {
    buff[count] = num1 % 10;
    num1 -= buff[count];
    num1 /= 10;
    count++;
  }
  *pos = count;
  if (buff[0] > 5 && buff[0] < 9) {
    buff[1] += 1;
  }
  if (buff[0] == 9) {
    buff[1] += 1;
    if (buff[1] == 10) {
      buff[1] = 0;
      buff[2] += 1;
    }
  }
  if (fl->plus && minus == 0) {
    *str++ = '+';
    fl->width--;
  }
  if (minus) {
    if (fl->zero) {
      *str++ = '-';
      fl->width--;
    } else {
      fl->width--;
    }
  }
  if (fl->minus == 0) {
    for (int h = 6 + count; h <= fl->width; h++) {
      *str++ = fl->specifier;
    }
  }
  if (minus && fl->zero == 0) {
    *str++ = '-';
  }
  *str++ = (long long int)i + '0';
}
void e_zero(flags fl, char *str) {
  if (fl.precision > 1) {
    char str_cpy[BUFF_SIZE] = {"0."};
    int zero_count = 2;
    while (zero_count < fl.precision + 2) {
      str_cpy[zero_count] = '0';
      zero_count++;
    }
    str_cpy[zero_count++] = fl.e_spec;
    str_cpy[zero_count++] = '+';
    str_cpy[zero_count++] = '0';
    str_cpy[zero_count++] = '0';
    if (fl.width) {
      int count_space = fl.width - 12;
      d3_memset(str, fl.specifier, count_space);
      str += d3_strlen(str);
    }
    d3_strcpy(str, str_cpy);
  } else {
    char str_cpy[BUFF_SIZE] = {"0e+00"};
    if (fl.e_spec == 'E') {
      str_cpy[1] = fl.e_spec;
    }
    if (fl.width) {
      int count_space = fl.width - 4;
      d3_memset(str, fl.specifier, count_space);
      str += d3_strlen(str);
    }
    d3_strcpy(str, str_cpy);
  }
}
void parsing_float(flags fl, char *str, va_list args) {
  long double num;
  if (fl.length == 'L') {
    num = va_arg(args, long double);
  } else {
    num = va_arg(args, double);
  }
  float_to_string(fl, str, num);
}
void float_to_string(flags fl, char *str, long double num) {
  long double num_copy, fractional;
  long long int whole_num = (long long int)num, num_count, minus = 0;
  char buff[1024];
  if (fl.precision == 0) {
    fl.precision = 6;
  }
  if (fl.specifier == '0') {
    fl.zero = 1;
  }
  if (num < 0) {
    num *= -1;
    whole_num *= -1;
    minus = 1;
  }
  num_copy = modfl(num, &fractional);
  long long int t = num + 0.1;
  if (fl.precision < 4 && t == whole_num + 1 && fl.plus == 0 && fl.minus == 0) {
    whole_num++;
  }
  for (int q = 0; q < fl.precision; q++) {
    num_copy *= 10.0;
  }
  if (fl.precision > -1) {
    num_copy = roundl(num_copy);
  } else {
    if (num_copy > 0.5) {
      num_copy = round(num);
    } else {
      num_copy = (long long int)num;
    }
  }
  if (fl.space && fl.plus == 0 && minus == 0) {
    *str++ = ' ';
    fl.width--;
  }
  if (minus == 0 && fl.plus) {
    if (fl.zero) {
      *str++ = '+';
      fl.width--;
    }
  }
  if (minus) {
    if (fl.zero) {
      *str++ = '-';
      fl.width--;
    }
  }
  if (minus && fl.precision > 0 && whole_num + 1 == num_copy * 10) {
    whole_num++;
  }
  num_count =
      float_write_to_array(fl, num, num_copy, whole_num, buff, str, minus);
  if (num < 1 && -1 < num && (num == 0 || minus == 0)) {
    *str++ = '0';
  }
  for (num_count--; num_count >= 0; num_count--) {
    *str++ = buff[num_count];
  }
}
int float_write_to_array(flags fl, long double num, long double num_copy,
                         long long int whole_num, char *buff, char *str,
                         int minus) {
  int digit, j = 0, num_count = 0;
  for (; j < fl.precision && fl.precision != -1; j++, num_count++) {
    digit = fmodl(num_copy, 10);
    buff[num_count] = (char)('0' + digit);
    num_copy -= digit;
    num_copy /= 10;
  }
  if (fl.precision > 0) {
    buff[num_count++] = '.';
    if (num < 1 && -1 < num && (fl.plus || fl.minus) && num != 0) {
      buff[num_count++] = '1';
    }
    while (whole_num) {
      digit = whole_num % 10;
      buff[num_count++] = (char)('0' + digit);
      whole_num -= digit;
      whole_num /= 10;
    }
  } else {
    if (fl.sharp) {
      buff[num_count++] = '.';
    }
    while (num_copy >= 1) {
      digit = fmodl(roundl(num_copy), 10);
      buff[num_count++] = digit + '0';
      num_copy -= digit;
      num_copy /= 10;
    }
  }
  if (minus && fl.zero == 0) {
    buff[num_count++] = '-';
  }
  if (fl.zero == 0 && fl.plus && minus == 0) {
    buff[num_count++] = '+';
  }
  if (fl.minus == 0) {
    for (whole_num = num_count; whole_num < fl.width;
         whole_num++, num_count++) {
      buff[whole_num] = fl.specifier;
    }
  } else {
    char *str_copy = str + num_count;
    for (whole_num = num_count; whole_num < fl.width; whole_num++, str_copy++) {
      *str_copy = fl.specifier;
    }
  }
  return num_count;
}
void parsing_g(flags fl, char *str, va_list args) {
  long double num;
  if (fl.length == 'L') {
    num = va_arg(args, long double);
  } else {
    num = va_arg(args, double);
  }
  if (fl.precision == 0 && num != 0) {
    fl.precision = 6;
  }
  g_to_string(fl, str, num);
  if (fl.e_spec == 'G') {
    to_upper(str);
  }
}
void g_to_string(flags fl, char *str, long double num) {
  int precision = fl.precision, count = 0;
  long double num_cpy = num;
  while ((int)num_cpy != 0) {
    num_cpy /= 10;
    count++;
  }
  fl.precision -= count;
  if (count < 1) {
    fl.precision = 10;
  }
  if (num > 0.0001 && num != 0) {
    float_to_string(fl, str, num);
  } else {
    if (num != 0) {
      g_two_logic(str, num);
    } else {
      *str++ = '0';
    }
  }
  if (precision > -1) {
    size_t len = d3_strlen(str) - 1;
    str += len;
    while (*str == '0' && num != 0) {
      *str = '\0';
      str--;
    }
  } else {
    str += 2;
    while (*str == '0') {
      str++;
    }
    str++;
    *str = '\0';
  }
}
void g_two_logic(char *str, long double num) {
  int e_count = 0;
  while (num < 1 && num != 0) {
    num *= 10;
    e_count++;
  }
  int num1 = round(num);
  *str++ = num1 + '0';
  *str++ = 'e';
  *str++ = '-';
  *(str + 1) = e_count % 10 + '0';
  e_count /= 10;
  *str++ = e_count % 10 + '0';
}
void parsing_o(flags fl, char *str, va_list args) {
  int64_t num = va_arg(args, int64_t);
  if (fl.sharp && num != 0 && fl.precision <= 0) {
    *str++ = '0';
  }
  if (fl.plus) {
    fl.plus = 0;
  }
  if (fl.space) {
    fl.space = 0;
  }
  int_to_string(fl, str, num, 8);
}
void parsing_string(flags fl, char *str, va_list args) {
  if (fl.length == 'l') {
    wchar_t *c = va_arg(args, wchar_t *);
    wchar_t_string_to_string(fl, str, c);
  } else {
    char *c = va_arg(args, char *);
    string_to_string(fl, str, c);
  }
}
void wchar_t_string_to_string(flags fl, char *str, wchar_t *c) {
  char buff[BUFF_SIZE];
  wcstombs(buff, c, BUFF_SIZE);
  if (fl.precision) {
    buff[fl.precision] = '\0';
  }
  int a = d3_strlen(buff);
  if (fl.minus) {
    wcstombs(str, c, BUFF_SIZE);
    d3_strcpy(str, buff);
    str += a;
    for (int i = a; i < fl.width; i++, str++) {
      *str = fl.specifier;
    }
  } else {
    for (int i = a; i < fl.width; i++, str++) {
      *str = fl.specifier;
    }
    wcstombs(str, c, BUFF_SIZE);
    d3_strcpy(str, buff);
  }
}
void string_to_string(flags fl, char *str, char *c) {
  char buff[BUFF_SIZE];
  d3_strcpy(buff, c);
  if (fl.precision) {
    buff[fl.precision] = '\0';
  }
  int a = d3_strlen(buff);
  if (fl.precision < 0) {
    fl.width = a + fl.width;
  }
  if (fl.minus) {
    if (fl.precision != -2) {
      d3_strcpy(str, buff);
    }
    str += a;
    for (int i = a; i < fl.width; i++, str++) {
      *str = fl.specifier;
    }
  } else {
    for (int i = a; i < fl.width; i++, str++) {
      *str = fl.specifier;
    }
    if (fl.precision >= 0) {
      d3_strcpy(str, buff);
    }
  }
}
void parsing_u(flags fl, char *str, va_list args) {
  uint64_t num = va_arg(args, uint64_t);
  switch (fl.length) {
    case 'h':
      num = (uint16_t)num;
      break;
    case 'l':
      num = (uint64_t)num;
      break;
    case 0:
      num = (uint32_t)num;
  }
  uint_to_string(fl, str, num, 10);
}
void uint_to_string(flags fl, char *str, unsigned long num, int base) {
  if (base != 0) {
    char buff[1024];
    int num_count = 0;
    unsigned long num_copy = num;
    if (num_copy == 0 && fl.precision > -1) {
      buff[num_count++] = '0';
    }
    if (num == 0 || base == 8) {
      fl.sharp = 0;
    }
    if (fl.plus) {
      fl.plus = 0;
    }
    while (num) {
      int digit = num % base;
      buff[num_count++] = "0123456789abcdef"[digit];
      num -= digit;
      num /= base;
    }
    if (fl.specifier == '0' || fl.precision > 0) {
      fl.zero = 1;
    }
    int_write_to_array(fl, num_count, str, buff, 0);
  }
}
void parsing_x(flags fl, char *str, va_list args) {
  uint64_t num = va_arg(args, uint64_t);
  switch (fl.length) {
    case 'h':
      num = (uint16_t)num;
      break;
    case 'l':
      num = (uint64_t)num;
      break;
    case 0:
      num = (uint32_t)num;
  }
  uint_to_string(fl, str, num, 16);
  if (fl.e_spec == 'X') {
    to_upper(str);
  }
}
void to_upper(char *str) {
  while (*str) {
    if (*str >= 'a' && *str <= 'z') {
      *str = *str - 'a' + 'A';
    }
    str++;
  }
}
void pointer_to_string(void *ptr, char *str, flags fl) {
  uintptr_t num = (uintptr_t)ptr;
  char buff[1024];
  int i = 0, g = 0;
  if (num == 0 && fl.precision != -2) {
    buff[i] = '0';
    i = 1;
  } else {
    while (num != 0) {
      int digit = num % 16;
      if (digit < 10) {
        buff[i] = (char)('0' + digit);
      } else {
        buff[i] = (char)('a' + digit - 10);
      }
      num /= 16;
      i++;
    }
  }
  if (fl.precision > 0) {
    while (i < fl.precision) {
      buff[i++] = '0';
    }
  }
  buff[i++] = 'x';
  buff[i++] = '0';
  if (fl.minus == 0) {
    for (g = i; g < fl.width; g++) {
      buff[g] = fl.specifier;
      i++;
    }
  } else {
    char *str_copy = str + i;
    for (g = i; g < fl.width; g++) {
      *str_copy++ = fl.specifier;
    }
  }
  for (i--; i >= 0; i--, str++) {
    *str = buff[i];
  }
}
void n_to_string(const char *str, const char *str2, va_list args) {
  int *c = va_arg(args, int *);
  *c = str - str2;
}
int prov_num(const char format) { return (format >= '0' && format <= '9'); }