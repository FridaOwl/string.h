#include "d3_tests.h"

START_TEST(d3_trim_test) {
  char *result;

  result = d3_trim("   Hello, World!   ", " ");
  ck_assert_str_eq(result, "Hello, World!");
  free(result);

  result = d3_trim("----abc123----", "-");
  ck_assert_str_eq(result, "abc123");
  free(result);

  result = d3_trim("   ", " ");
  ck_assert_str_eq(result, "");
  free(result);

  result = d3_trim("", " ");
  ck_assert_str_eq(result, "");
  free(result);

  result = d3_trim("12345", "");
  ck_assert_str_eq(result, "12345");
  free(result);
}
END_TEST

Suite *suite_trim(void) {
  Suite *s = suite_create("suite_trim");
  TCase *tc = tcase_create("trim_tc");

  tcase_add_test(tc, d3_trim_test);
  suite_add_tcase(s, tc);
  return s;
}
