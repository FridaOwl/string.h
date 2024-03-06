#include "d3_tests.h"

const char *d3_strpbrk(const char *str1, const char *str2);

START_TEST(d3_strpbrk_test) {
  const char str_for_strpbrk[] = "stetic Asian";
  const char str_oneof[] = "asit";
  ck_assert_str_eq(d3_strpbrk(str_for_strpbrk, str_oneof), "stetic Asian");

  const char str_for_strpbrk2[] = "hello world";
  const char str_oneof2[] = "zxq";
  ck_assert_pstr_eq(d3_strpbrk(str_for_strpbrk2, str_oneof2), d3_NULL);
}
END_TEST

Suite *suite_strpbrk(void) {
  Suite *s = suite_create("suite_strpbrk");
  TCase *tc = tcase_create("strpbrk_tc");

  tcase_add_test(tc, d3_strpbrk_test);
  suite_add_tcase(s, tc);
  return s;
}
