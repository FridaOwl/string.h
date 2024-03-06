#include "d3_tests.h"

START_TEST(d3_strchr_test) {
  char str1[] = "Aqto";
  ck_assert_str_eq(d3_strchr(str1, 'q'), "qto");

  char str2[] = "Aqto";
  char *ach2 = strchr(str2, 'q');
  ck_assert_ptr_eq(d3_strchr(str2, 'q'), ach2);
  ck_assert_str_eq(str1, str2);

  char str3[] = "Abcdefg";
  ck_assert_ptr_eq(d3_strchr(str3, '\0'), strchr(str3, '\0'));
}
END_TEST

Suite *suite_strchr(void) {
  Suite *s = suite_create("suite_strchr");
  TCase *tc = tcase_create("strchr_tc");

  tcase_add_test(tc, d3_strchr_test);

  suite_add_tcase(s, tc);
  return s;
}
