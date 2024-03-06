#include "d3_tests.h"

START_TEST(d3_to_upper_test) {
  char str1[] = "eatminin gulin egileminy eatte it's gulin";
  char str2[] = "qazaqforever";
  char str3[] = "";
  char str4[] = "a";

  char *str = d3_to_upper(str1);
  ck_assert_str_eq(str, "EATMININ GULIN EGILEMINY EATTE IT'S GULIN");
  free(str);

  str = d3_to_upper(str2);
  ck_assert_str_eq(str, "QAZAQFOREVER");
  free(str);

  str = d3_to_upper(str3);
  ck_assert_str_eq(str, "");
  free(str);

  str = d3_to_upper(str4);
  ck_assert_str_eq(str, "A");
  free(str);
}
END_TEST

Suite *suite_to_upper(void) {
  Suite *s = suite_create("suite_to_upper");
  TCase *tc = tcase_create("to_upper_tc");

  tcase_add_test(tc, d3_to_upper_test);
  suite_add_tcase(s, tc);
  return s;
}
