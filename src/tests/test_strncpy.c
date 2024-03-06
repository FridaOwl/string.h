#include "d3_tests.h"

START_TEST(d3_strncpy_test) {
  char str1[] = "Rembo4 public society";
  char dest1[15] = "";

  char str2[] = "Rembo \0";
  char dest2[10] = "";

  char str3[] = "Rembo ";
  char dest3[] = "pulllRequest";

  char str4[] = "R";
  char dest4[2] = "";

  char str5[] = " ";
  char dest5[2] = "";

  ck_assert_str_eq(d3_strncpy(dest1, str1, 6), "Rembo4");
  ck_assert_str_eq(d3_strncpy(dest2, str2, 4), "Remb");
  ck_assert_str_eq(d3_strncpy(dest3, str3, 10), "Rembo ");
  ck_assert_str_eq(d3_strncpy(dest4, str4, 1), "R");
  ck_assert_str_eq(d3_strncpy(dest5, str5, 1), " ");
}

END_TEST

Suite *suite_strncpy(void) {
  Suite *s = suite_create("suite_strncpy");
  TCase *tc = tcase_create("strncpy_tc");

  tcase_add_test(tc, d3_strncpy_test);
  suite_add_tcase(s, tc);
  return s;
}