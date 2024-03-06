#include "d3_tests.h"

START_TEST(d3_strncat_test) {
  char str1[50] = "Hello";
  char str2[50] = "Hello";
  char str3[50] = " World";
  ck_assert_str_eq(strcat(str1, str3), d3_strncat(str2, str3, sizeof(str2)));

  char str4[50] = "";
  char str5[50] = "";
  ck_assert_str_eq(strcat(str4, str5), d3_strncat(str4, str5, sizeof(str4)));

  char str6[50] = "Hello";
  char str7[50] = "";
  ck_assert_str_eq(strcat(str6, str7), d3_strncat(str6, str7, sizeof(str6)));
}
END_TEST

Suite *suite_strncat(void) {
  Suite *s = suite_create("suite_strncat");
  TCase *tc = tcase_create("strncat_tc");

  tcase_add_test(tc, d3_strncat_test);
  suite_add_tcase(s, tc);
  return s;
}
