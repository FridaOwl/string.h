#include "d3_tests.h"

START_TEST(test_d3_strtok) {
  char *token;

  token = d3_strtok(NULL, "/");
  ck_assert_ptr_null(token);

  char str1[] = "";
  token = d3_strtok(str1, "/");
  ck_assert_ptr_null(token);

  char str2[] = "Hello";
  token = d3_strtok(str2, "/");
  ck_assert_str_eq(token, "Hello");

  token = d3_strtok(NULL, "/");
  ck_assert_ptr_null(token);

  char str3[] = "Hello/World/Check";
  token = d3_strtok(str3, "/");
  ck_assert_str_eq(token, "Hello");

  token = d3_strtok(NULL, "/");
  ck_assert_str_eq(token, "World");

  token = d3_strtok(NULL, "/");
  ck_assert_str_eq(token, "Check");

  token = d3_strtok(NULL, "/");
  ck_assert_ptr_null(token);

  char str4[] = "Hello World";
  char delim1[] = "";

  token = d3_strtok(str4, delim1);
  ck_assert_str_eq(token, "Hello World");

  char str5[] = "Hello World";
  char delim2[] = ",";

  token = d3_strtok(str5, delim2);
  ck_assert_str_eq(token, "Hello World");

  token = d3_strtok(NULL, delim2);
  ck_assert_ptr_null(token);
}
END_TEST

Suite *suite_strtok(void) {
  Suite *s = suite_create("suite_strtok");
  TCase *tc = tcase_create("strtok_tc");

  tcase_add_test(tc, test_d3_strtok);

  suite_add_tcase(s, tc);
  return s;
}
