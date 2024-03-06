#include "d3_tests.h"

START_TEST(d3_strcspn_test) {
  char test1[] = "NamysynBermegen,";
  char test2[] = "Namysyn";
  char test3[] = "Bizdin Elim ";
  char test4[] = "elim";
  char test5[] = "0/";
  ck_assert_uint_eq(d3_strcspn(test1, test2), strcspn(test1, test2));
  ck_assert_uint_eq(d3_strcspn(test3, test4), strcspn(test3, test4));
  ck_assert_uint_eq(d3_strcspn(test3, test5), strcspn(test3, test5));
}
END_TEST

Suite *suite_strcspn(void) {
  Suite *s = suite_create("suite_strcspn");
  TCase *tc = tcase_create("strcspn_tc");

  tcase_add_test(tc, d3_strcspn_test);
  suite_add_tcase(s, tc);
  return s;
}
