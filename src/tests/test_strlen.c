#include "d3_tests.h"

START_TEST(d3_strlen_test) {
  char test_1[] = "QazaqRepub";
  char test_2[] = "Salam";
  char test_3[] = "1\0";
  char test_4[] = " ";
  char test_5[] = "123\0456";
  char test_6[] = "qqq\\\0";
  char test_8[] = "";
  char test_10[] = "1";

  ck_assert_int_eq(d3_strlen(test_1), strlen(test_1));
  ck_assert_int_eq(d3_strlen(test_2), strlen(test_2));
  ck_assert_int_eq(d3_strlen(test_3), strlen(test_3));
  ck_assert_int_eq(d3_strlen(test_4), strlen(test_4));
  ck_assert_int_eq(d3_strlen(test_5), strlen(test_5));
  ck_assert_int_eq(d3_strlen(test_6), strlen(test_6));
  ck_assert_int_eq(d3_strlen(test_8), strlen(test_8));
  ck_assert_int_eq(d3_strlen(test_10), strlen(test_10));
}
END_TEST

Suite *suite_strlen(void) {
  Suite *s = suite_create("suite_strlen");
  TCase *tc = tcase_create("strlen_tc");

  tcase_add_test(tc, d3_strlen_test);
  suite_add_tcase(s, tc);
  return s;
}
