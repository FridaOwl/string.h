#include "d3_tests.h"

START_TEST(d3_to_lower_test) {
  char str1[] = "I'M JUST a Mangilik EVERY DAy";
  char str2[] = "QAZAQFOREVER";
  char str3[] = "";
  char str4[] = "A";

  char *result1 = d3_to_lower(str1);
  ck_assert_str_eq(result1, "i'm just a mangilik every day");
  free(result1);

  char *result2 = d3_to_lower(str2);
  ck_assert_str_eq(result2, "qazaqforever");
  free(result2);

  char *result3 = d3_to_lower(str3);
  ck_assert_str_eq(result3, "");
  free(result3);

  char *result4 = d3_to_lower(str4);
  ck_assert_str_eq(result4, "a");
  free(result4);
}
END_TEST

Suite *suite_to_lower(void) {
  Suite *s = suite_create("suite_to_lower");
  TCase *tc = tcase_create("to_lower_tc");

  tcase_add_test(tc, d3_to_lower_test);
  suite_add_tcase(s, tc);
  return s;
}
