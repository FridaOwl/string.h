#include "d3_tests.h"

START_TEST(d3_strncmp_test) {
  char str1[] = "Tugan qarasy";
  char str2[] = "Yrpaqqa jol";
  char str3[] = "Yrpaqqa jol\0";
  char str4[] = "";
  char str5[] = "";

  ck_assert_int_eq(d3_strncmp(str1, str2, 5) == 0,
                   strncmp(str1, str2, 5) == 0);
  ck_assert_int_eq(d3_strncmp(str1, str2, 6) > 0, strncmp(str1, str2, 6) > 0);
  ck_assert_int_eq(d3_strncmp(str1, str3, 10) > 0,
                   strncmp(str1, str3, 10) > 0);
  ck_assert_int_eq(d3_strncmp(str4, str5, 1) == 0,
                   strncmp(str4, str5, 1) == 0);
}
END_TEST

Suite *suite_strncmp(void) {
  Suite *s = suite_create("suite_strncmp");
  TCase *tc = tcase_create("strncmp_tc");

  tcase_add_test(tc, d3_strncmp_test);

  suite_add_tcase(s, tc);
  return s;
}
