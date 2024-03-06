#include "d3_tests.h"

START_TEST(d3_memchr_test) {
  char test1[] = "QazaRepubl";
  char test2 = 'R';
  char test3 = 'a';
  char test4[] = "9762/\0";
  char test5[] = "?";
  char test6 = 'g';
  char test7 = ' ';
  char test8 = '/';
  char test9 = '\0';

  ck_assert_ptr_eq(d3_memchr(test1, test2, 10), memchr(test1, test2, 10));
  ck_assert_ptr_eq(d3_memchr(test1, test3, 10), memchr(test1, test3, 10));
  ck_assert_ptr_eq(d3_memchr(test4, test6, 7), memchr(test4, test6, 7));
  ck_assert_ptr_eq(d3_memchr(test5, test7, 1), memchr(test5, test7, 1));
  ck_assert_ptr_eq(d3_memchr(test4, test8, 7), memchr(test4, test8, 7));
  ck_assert_ptr_eq(d3_memchr(test4, test9, 7), memchr(test4, test9, 7));
}
END_TEST

Suite *suite_memchr(void) {
  Suite *s = suite_create("suite_memchr");
  TCase *tc = tcase_create("memchr_tc");

  tcase_add_test(tc, d3_memchr_test);

  suite_add_tcase(s, tc);
  return s;
}
