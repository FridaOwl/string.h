#include "d3_tests.h"

START_TEST(d3_strcpy_test) {
  char test_1[] = "Namysyn bermegen Qazagym myqty";
  char test_2[] = "     ";
  char test_3[] = "Gup\0";
  char test_4[] = "rept\0Qazagym";
  char test_5[128] = "";
  char test_6[] = "Qazahi 11 and Qazahi 22";
  char test_7[] = "";
  char test_8[] = "1";
  ck_assert_str_eq(d3_strcpy(test_1, test_2), strcpy(test_1, test_2));
  ck_assert_str_eq(d3_strcpy(test_2, test_3), strcpy(test_2, test_3));
  ck_assert_str_eq(d3_strcpy(test_4, test_5), strcpy(test_4, test_5));
  ck_assert_str_eq(d3_strcpy(test_5, test_4), strcpy(test_5, test_4));
  ck_assert_str_eq(d3_strcpy(test_6, test_5), strcpy(test_6, test_5));
  ck_assert_str_eq(d3_strcpy(test_7, test_5), strcpy(test_7, test_5));
  ck_assert_str_eq(d3_strcpy(test_8, test_5), strcpy(test_8, test_5));
}
END_TEST

Suite *suite_strcpy(void) {
  Suite *s = suite_create("suite_strcpy");
  TCase *tc = tcase_create("strcpy_tc");

  tcase_add_test(tc, d3_strcpy_test);

  suite_add_tcase(s, tc);
  return s;
}
