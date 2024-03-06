#include "d3_tests.h"

START_TEST(d3_memcmp_test) {
  char test1[] = "Altyn kun aspany";
  char test2[] = "Altyn dan dalasy";
  char test3[] = "\0";
  char test4[] = "Grep\0 perg";
  char test5[] = "Grep\0 perg";
  char test_8[] = "";
  char test_9[] = "";
  char test_10[] = "1";
  char test_11[] = "1";

  ck_assert_int_eq(d3_memcmp(test1, test2, 14), memcmp(test1, test2, 14));
  ck_assert_int_eq(d3_memcmp(test1, test3, 2), memcmp(test1, test3, 2));
  ck_assert_int_eq(d3_memcmp(test2, test3, 2), memcmp(test2, test3, 2));
  ck_assert_int_eq(d3_memcmp(test4, test1, 9), memcmp(test4, test1, 9));
  ck_assert_int_eq(d3_memcmp(test4, test5, 7), memcmp(test4, test5, 7));
  ck_assert_int_eq(d3_memcmp(test_8, test_9, 1), memcmp(test_8, test_9, 1));
  ck_assert_int_eq(d3_memcmp(test_10, test_11, 1), memcmp(test_10, test_11, 1));
}
END_TEST

Suite *suite_memcmp(void) {
  Suite *s = suite_create("suite_memcmp");
  TCase *tc = tcase_create("memcmp_tc");

  tcase_add_test(tc, d3_memcmp_test);

  suite_add_tcase(s, tc);
  return s;
}
