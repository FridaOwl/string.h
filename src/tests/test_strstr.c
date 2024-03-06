#include "d3_tests.h"

START_TEST(d3_strstr_test) {
  char test_1[] = "Kazak Han";
  char test_2[] = "Han";
  char test_3[] = "AsianAsianAsian";
  char test_4[] = "Asian";
  char test_5[] = "1234";
  char test_6[] = "";
  char test_7[] = "5123451234512345";
  char test_8[] = "1234";
  char test_9[] = "1";
  char test_10[] = "4";

  ck_assert_ptr_eq(d3_strstr(test_1, test_2), strstr(test_1, test_2));
  ck_assert_ptr_eq(d3_strstr(test_3, test_4), strstr(test_3, test_4));
  ck_assert_ptr_eq(d3_strstr(test_5, test_6), strstr(test_5, test_6));
  ck_assert_ptr_eq(d3_strstr(test_4, test_5), strstr(test_4, test_5));
  ck_assert_ptr_eq(d3_strstr(test_7, test_8), strstr(test_7, test_8));
  ck_assert_ptr_eq(d3_strstr(test_8, test_9), strstr(test_8, test_9));
  ck_assert_ptr_eq(d3_strstr(test_8, test_10), strstr(test_8, test_10));
}
END_TEST

Suite *suite_strstr(void) {
  Suite *s = suite_create("suite_strstr");
  TCase *tc = tcase_create("strstr_tc");

  tcase_add_test(tc, d3_strstr_test);
  suite_add_tcase(s, tc);
  return s;
}
