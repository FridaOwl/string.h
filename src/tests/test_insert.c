#include "d3_tests.h"

START_TEST(d3_insert_test) {
  char *src = "Altynda!";
  char *str = ", Erliktindas";
  char *new_str = d3_insert(src, str, 7);
  ck_assert_str_eq(new_str, "Altynda, Erliktindas!");
  free(new_str);

  new_str = d3_insert(src, "", 9);
  ck_assert(new_str == d3_NULL);
  free(new_str);

  new_str = d3_insert("Altynda!", ", Erliktindas!!", 7);
  ck_assert_str_eq(new_str, "Altynda, Erliktindas!!!");
  free(new_str);

  new_str = d3_insert("Altynda!", ", Erliktindas!!", 35);
  ck_assert(new_str == d3_NULL);
  free(new_str);

  new_str = d3_insert("", "", 0);
  ck_assert_str_eq(new_str, "");
  free(new_str);

  char *src1 = "1";
  char *str1 = "1";
  char *new_str2 = d3_insert(src1, str1, 1);
  ck_assert_str_eq(new_str2, "11");
  free(new_str2);
}

END_TEST

START_TEST(insert_str_null) {
  char *str = NULL;
  char src[] = "Pudge  ";
  d3_size_t index = 6;
  char expected[] = "Pudge  ";
  char *got = (char *)d3_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, d3_insert_test);
  tcase_add_test(tc, insert_str_null);
  suite_add_tcase(s, tc);
  return s;
}