#include "d3_tests.h"

START_TEST(all_std_errors) {
  for (int i = 0; i < 150; i++) {
    ck_assert_str_eq(d3_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(negative_err_code) {
  ck_assert_str_eq(d3_strerror(-1), strerror(-1));
}
END_TEST

Suite *suite_strerror(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("suite_strerror");
  tc = tcase_create("strerror_tc");
  tcase_add_test(tc, all_std_errors);
  tcase_add_test(tc, negative_err_code);

  suite_add_tcase(s, tc);
  return s;
}
