#include "d3_tests.h"

START_TEST(d3_strrchr_test) {
  char test1[] = "9876 54326 10";
  char test2[] = "a;b;c;d;e;f;g;h;i;j;h";
  char test3[] = " $ ! @ # $ ^ & * ( $ ) $ ";
  char test4[] = "$";

  ck_assert_ptr_eq(d3_strrchr(test1, '6'), strrchr(test1, '6'));
  ck_assert_ptr_eq(d3_strrchr(test1, ' '), strrchr(test1, ' '));
  ck_assert_ptr_eq(d3_strrchr(test1, '6'), strrchr(test1, '6'));
  ck_assert_ptr_eq(d3_strrchr(test2, 'h'), strrchr(test2, 'h'));
  ck_assert_ptr_eq(d3_strrchr(test3, '$'), strrchr(test3, '$'));
  ck_assert_ptr_eq(d3_strrchr(test2, ';'), strrchr(test2, ';'));
  ck_assert_ptr_eq(d3_strrchr(test3, ' '), strrchr(test3, ' '));
  ck_assert_ptr_eq(d3_strrchr(test2, '\0'), strrchr(test2, '\0'));
  ck_assert_ptr_eq(d3_strrchr(test4, '$'), strrchr(test4, '$'));
}

END_TEST

Suite *suite_strrchr(void) {
  Suite *s = suite_create("suite_strrchr");
  TCase *tc = tcase_create("strrchr_tc");

  tcase_add_test(tc, d3_strrchr_test);
  suite_add_tcase(s, tc);
  return s;
}
