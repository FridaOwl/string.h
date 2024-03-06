#include "d3_tests.h"

START_TEST(d3_memset_test) {
  char test1[] = "123456789";
  char test2[] = "123456789";
  ck_assert_str_eq(d3_memset(test1, 'a', 9), memset(test2, 'a', 9));
}
END_TEST

Suite *suite_memset(void) {
  Suite *s = suite_create("suite_memset");
  TCase *tc = tcase_create("memset_tc");

  tcase_add_test(tc, d3_memset_test);

  suite_add_tcase(s, tc);
  return s;
}
