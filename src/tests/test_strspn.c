#include "d3_tests.h"

START_TEST(d3_strspn_test) {
  char str1[] = "0987654321";
  char str2[] = "012";
  char str3[] = "abcdefg";
  char str4[] = "gda";
  char str5[] = "!@#$^&*()";
  char str6[] = ")(*";
  char str7[] = ")";
  char str8[] = "";

  ck_assert_int_eq(d3_strspn(str1, str2), strspn(str1, str2));
  ck_assert_int_eq(d3_strspn(str2, str1), strspn(str2, str1));
  ck_assert_int_eq(d3_strspn(str3, str4), strspn(str3, str4));
  ck_assert_int_eq(d3_strspn(str5, str6), strspn(str5, str6));
  ck_assert_int_eq(d3_strspn(str5, str7), strspn(str5, str7));
  ck_assert_int_eq(d3_strspn(str5, str8), strspn(str5, str8));
}

Suite *suite_strspn(void) {
  Suite *s = suite_create("suite_strspn");
  TCase *tc = tcase_create("strspn_tc");

  tcase_add_test(tc, d3_strspn_test);
  suite_add_tcase(s, tc);
  return s;
}