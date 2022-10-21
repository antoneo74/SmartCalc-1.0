#include <check.h>

#include "calc.h"

START_TEST(calc1) {
  char string[256] = "19+3^2*((4*2+5-1)-(14+4*4)/(4+2*3))";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);

  ck_assert_double_eq(result, 100);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc2) {
  char string[256] =
      "((5.6- 8.9 + 18 * 5 / 3 ^ 4 ^ 0.5) mod 2.8 - 2.5 ) / 7 * 2 ^ (15 mod "
      "4) + 9 + 16/10";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);

  ck_assert_double_eq(result, 9);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc3) {
  char string[256] = "(tan(sin( log( sqrt9 * sqrt9 ) ) ) + cos(ln(10))+1)";
  double result1 = 0;
  double x = 0;
  int error = push_button_equal(string, &result1, x);

  double result2 = (tan(sin(log10(sqrt(9) * sqrt(9)))) + cos(log(10)) + 1);
  ck_assert_double_eq(result1, result2);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc4) {
  char string[256] = "atan(1) + asin(1) + acos(-1)";
  double result1 = 0;
  double x = 0;
  int error = push_button_equal(string, &result1, x);

  double result2 = atan(1) + asin(1) + acos(-1);
  ck_assert_double_eq(result1, result2);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc5) {
  char string[256] = "(X+X-3)*X+X*X";
  double result1 = 0;
  double x = 5;
  int error = push_button_equal(string, &result1, x);

  double result2 = (5 + 5 - 3) * 5 + 5 * 5;
  ck_assert_double_eq(result1, result2);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc6) {
  char string[256] =
      "sin(cos(23/454))+tan(23)+asin(0.2525)+acos(0.5353453)+atan(0.3453455)";
  double result1 = 0;
  double x = 0;
  int error = push_button_equal(string, &result1, x);

  ck_assert_ldouble_eq_tol(result1, 4.0225954, EPS);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc7) {
  char string[256] = "2/-5+2*-5+2-5+2mod-5";
  double result1 = 0;
  double x = 0;
  int error = push_button_equal(string, &result1, x);

  ck_assert_ldouble_eq_tol(result1, -11.4, EPS);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc8) {
  char string[256] = "3+4*2/(1-5)^2";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq(result, 3.5);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc9) {
  char string[256] = "1+2+3+4*5*6^7";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_int_eq((int)result, 5598726);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc10) {
  char string[256] = "123.456+2*3^4";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq(result, 285.456);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc11) {
  char string[256] = "(8+2*5)/(1+3*2-4)";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq(result, 6);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc12) {
  char string[256] =
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq(result, 10);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc13) {
  char string[256] = "cos(1*2)-1";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, -1.41614683655, 1e-06);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc14) {
  char string[256] =
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, -1.83907152908, 1e-06);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc15) {
  char string[256] = "sin(cos(5))";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 0.27987335076, 1e-06);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc16) {
  char string[256] = "2.33mod1";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 0.33, 1e-06);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc17) {
  char string[256] = "3+4*2/1-5+2^2";
  double result = 0;
  double x = 10;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 10, 1e-06);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc18) {
  char string[256] = "3+4*2/1-5+2^2";
  double result = 0;
  double x = 10;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 10, 1e-06);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc19) {
  char string[256] = "asin(2*X)";
  double result = 0;
  double x = 0.0003;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 0.0006, 1e-06);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc20) {
  char string[256] = "acos(2*X)";
  double result = 0;
  double x = 0.0019;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 1.567, 1e-03);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc21) {
  char string[256] = "atan(2*X)";
  double result = 0;
  double x = 0.0019;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 0.00379998, 1e-06);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc22) {
  char string[256] = "tan(2*X)";
  double result = 0;
  double x = 0.004;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 0.00800017, 1e-06);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc23) {
  char string[256] = "sqrt(2*X)";
  double result = 0;
  double x = 25;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 7.07107, 1e-05);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc24) {
  char string[256] = "ln(10*X)";
  double result = 0;
  double x = 2;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 2.99573, 1e-05);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc25) {
  char string[256] = "log(10*X)";
  double result = 0;
  double x = 2;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 1.30103, 1e-05);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc26) {
  char string[256] = "()";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 0, 1e-06);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc27) {
  char string[256] = "3-(-3)";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 6, 1e-06);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc28) {
  char string[256] = "3-(+3)";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_double_eq_tol(result, 0, 1e-06);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(calc29) {
  char string[256] = "3.1.2-(+3)";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(calc30) {
  char string[256] = "31.2-(+3))";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(calc31) {
  char string[256] = "((31.2-(+3))";
  double result = 0;
  double x = 0;
  int error = push_button_equal(string, &result, x);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(calc32) {
  double dohod = 57000;
  double CBR = 4.25;
  double NDFL = 13;
  double result = Tax(dohod, CBR, NDFL);
  ck_assert_double_eq(result, 1885);
}
END_TEST

START_TEST(calc33) {
  int days = 47;
  int daysOfYear = 365;
  double deposit = 10000;
  double percent = 13;
  double result = Accrued_interest(deposit, percent, days, daysOfYear);
  ck_assert_double_eq_tol(result, 167.4, 1e-02);
}
END_TEST

START_TEST(calc34) {
  double deposit = 124875;
  double percent = 17;
  double result = Monthly_percent_payment(deposit, percent);
  ck_assert_double_eq_tol(result, 1769.06, 1e-02);
}
END_TEST

START_TEST(calc35) {
  double deposit = 124875;
  double period = 2;
  double percent = 17;
  double result = Anuitet(deposit, period, percent);
  ck_assert_double_eq_tol(result, 63767.41, 1e-02);
}
END_TEST

START_TEST(calc36) {
  double deposit = 124875;
  double anuitet = 63767.41;
  double period = 2;
  double result = Pereplata(deposit, anuitet, period);
  ck_assert_double_eq_tol(result, 2659.82, 1e-02);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Suite");
  TCase *tc1_1 = tcase_create("tests");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, calc1);
  tcase_add_test(tc1_1, calc2);
  tcase_add_test(tc1_1, calc3);
  tcase_add_test(tc1_1, calc4);
  tcase_add_test(tc1_1, calc5);
  tcase_add_test(tc1_1, calc6);
  tcase_add_test(tc1_1, calc7);
  tcase_add_test(tc1_1, calc8);
  tcase_add_test(tc1_1, calc9);
  tcase_add_test(tc1_1, calc10);
  tcase_add_test(tc1_1, calc11);
  tcase_add_test(tc1_1, calc12);
  tcase_add_test(tc1_1, calc13);
  tcase_add_test(tc1_1, calc14);
  tcase_add_test(tc1_1, calc15);
  tcase_add_test(tc1_1, calc16);
  tcase_add_test(tc1_1, calc17);
  tcase_add_test(tc1_1, calc18);
  tcase_add_test(tc1_1, calc19);
  tcase_add_test(tc1_1, calc20);
  tcase_add_test(tc1_1, calc21);
  tcase_add_test(tc1_1, calc22);
  tcase_add_test(tc1_1, calc23);
  tcase_add_test(tc1_1, calc24);
  tcase_add_test(tc1_1, calc25);
  tcase_add_test(tc1_1, calc26);
  tcase_add_test(tc1_1, calc27);
  tcase_add_test(tc1_1, calc28);
  tcase_add_test(tc1_1, calc29);
  tcase_add_test(tc1_1, calc30);
  tcase_add_test(tc1_1, calc31);
  tcase_add_test(tc1_1, calc32);
  tcase_add_test(tc1_1, calc33);
  tcase_add_test(tc1_1, calc34);
  tcase_add_test(tc1_1, calc35);
  tcase_add_test(tc1_1, calc36);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}