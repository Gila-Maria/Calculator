#include <check.h>

#include "SmartCalc.h"

START_TEST(DEPOSIT_CALCULATOR1) {
  double deposit = 500;
  int time = 365;
  double rate = 30;
  double nalog_rate = 35;
  int period_payment = 1;
  int capitalization = 0;
  double add_deposit = 0;
  double remove_deposit = 0;
  int month = 7;
  double profit = 0;
  double deposit_end = 0;
  double tax = 0;

  deposit_count(deposit, time, rate, nalog_rate, period_payment, capitalization,
                add_deposit, remove_deposit, month, &profit, &tax,
                &deposit_end);

  ck_assert_ldouble_eq_tol(profit, 150.00, 1e-2);
  ck_assert_ldouble_eq_tol(deposit_end, 500.00, 1e-2);
  ck_assert_ldouble_eq_tol(tax, 52.5, 1e-2);
}
END_TEST

START_TEST(DEPOSIT_CALCULATOR2) {
  double deposit = 1000000;
  int time = 365;
  double rate = 30;
  double nalog_rate = 35;
  int period_payment = 2;
  int capitalization = 1;
  double add_deposit = 0;
  double remove_deposit = 0;
  int month = 7;
  double profit = 0;
  double deposit_end = 0;
  double tax = 0;

  deposit_count(deposit, time, rate, nalog_rate, period_payment, capitalization,
                add_deposit, remove_deposit, month, &profit, &tax,
                &deposit_end);

  ck_assert_ldouble_eq_tol(profit, 340093.66, 1e-2);
  ck_assert_ldouble_eq_tol(deposit_end, 1340093.66, 1e-2);
  ck_assert_ldouble_eq_tol(tax, 119032.78, 1e-2);
}
END_TEST

START_TEST(DEPOSIT_CALCULATOR3) {
  double deposit = 62312;
  int time = 1800;
  double rate = 11;
  double nalog_rate = 35;
  int period_payment = 4;
  int capitalization = 0;
  double add_deposit = 0;
  double remove_deposit = 0;
  int month = 7;
  double profit = 0;
  double deposit_end = 0;
  double tax = 0;

  deposit_count(deposit, time, rate, nalog_rate, period_payment, capitalization,
                add_deposit, remove_deposit, month, &profit, &tax,
                &deposit_end);

  ck_assert_double_eq_tol(profit, 33802.13, 1e-2);
  ck_assert_double_eq_tol(deposit_end, 62312.00, 1e-2);
  ck_assert_double_eq(tax, 0);
}
END_TEST

START_TEST(CREDIT_CALCULATOR_ANNUITY1) {
  double credit_amount = 89124.34;
  int time = 9;
  double rate = 17;
  double monthly_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
  annuity_credit(credit_amount, time, rate, &monthly_payment, &overpayment,
                 &total_payment);

  ck_assert_double_eq_tol(monthly_payment, 10617.3, 1e-2);
  ck_assert_double_eq_tol(overpayment, 6431.36, 1e-2);
  ck_assert_double_eq_tol(total_payment, 95555.70, 1e-2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_ANNUITY2) {
  double credit_amount = 439809.32;
  int time = 1;
  double rate = 1;
  double monthly_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
  annuity_credit(credit_amount, time, rate, &monthly_payment, &overpayment,
                 &total_payment);

  ck_assert_double_eq_tol(monthly_payment, 440175.83, 1e-2);
  ck_assert_double_eq_tol(overpayment, 366.51, 1e-2);
  ck_assert_double_eq_tol(total_payment, 440175.83, 1e-2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_ANNUITY3) {
  double credit_amount = 439809.32;
  int time = 1;
  double rate = 0.01;
  double monthly_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
  annuity_credit(credit_amount, time, rate, &monthly_payment, &overpayment,
                 &total_payment);

  ck_assert_double_eq_tol(monthly_payment, 439812.99, 1e-2);
  ck_assert_double_eq_tol(overpayment, 3.67, 1e-2);
  ck_assert_double_eq_tol(total_payment, 439812.99, 1e-2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_ANNUITY4) {
  double credit_amount = 100;
  int time = 600;
  double rate = 15;
  double monthly_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
  annuity_credit(credit_amount, time, rate, &monthly_payment, &overpayment,
                 &total_payment);

  ck_assert_double_eq_tol(monthly_payment, 1.25, 1e2);
  ck_assert_double_eq_tol(overpayment, 650, 1e2);
  ck_assert_double_eq_tol(total_payment, 750, 1e2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_ANNUITY5) {
  double credit_amount = 324812.24;
  int time = 600;
  double rate = 15;
  double monthly_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
  annuity_credit(credit_amount, time, rate, &monthly_payment, &overpayment,
                 &total_payment);

  ck_assert_double_eq_tol(monthly_payment, 4062.51, 1e2);
  ck_assert_double_eq_tol(overpayment, 2112693.76, 1e2);
  ck_assert_double_eq_tol(total_payment, 2437506.00, 1e2);
}
END_TEST

START_TEST(CREDIT_CALCULATOR_DIFFERENTIATED1) {
  double credit_amount = 89124.34;
  int time = 9;
  double rate = 17;
  double max_payment = 0;
  double min_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
  credit_differentiated(credit_amount, time, rate, &max_payment, &min_payment,
                        &overpayment, &total_payment);
  ck_assert_double_eq_tol(max_payment, 11165.30, 1e2);
  ck_assert_double_eq_tol(min_payment, 10042.99, 1e2);
  ck_assert_double_eq_tol(overpayment, 6312.97, 1e2);
  ck_assert_double_eq_tol(total_payment, 95437.31, 1e2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_DIFFERENTIATED2) {
  double credit_amount = 439809.32;
  int time = 1;
  double rate = 1;
  double max_payment = 0;
  double min_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
  credit_differentiated(credit_amount, time, rate, &max_payment, &min_payment,
                        &overpayment, &total_payment);

  ck_assert_double_eq_tol(max_payment, 440175.83, 1e2);
  ck_assert_double_eq_tol(min_payment, 440175.83, 1e2);
  ck_assert_double_eq_tol(overpayment, 366.51, 1e2);
  ck_assert_double_eq_tol(total_payment, 440175.83, 1e2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_DIFFERENTIATED3) {
  double credit_amount = 439809.32;
  int time = 1;
  double rate = 0.01;
  double max_payment = 0;
  double min_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
  credit_differentiated(credit_amount, time, rate, &max_payment, &min_payment,
                        &overpayment, &total_payment);

  ck_assert_double_eq_tol(max_payment, 439812.99, 1e2);
  ck_assert_double_eq_tol(min_payment, 439812.99, 1e2);
  ck_assert_double_eq_tol(overpayment, 3.67, 1e2);
  ck_assert_double_eq_tol(total_payment, 439812.99, 1e2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_DIFFERENTIATED4) {
  double credit_amount = 100;
  int time = 600;
  double rate = 15;
  double max_payment = 0;
  double min_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
  credit_differentiated(credit_amount, time, rate, &max_payment, &min_payment,
                        &overpayment, &total_payment);
  ck_assert_double_eq_tol(max_payment, 1.42, 1e2);
  ck_assert_double_eq_tol(min_payment, 0.17, 1e2);
  ck_assert_double_eq_tol(overpayment, 375.63, 1e2);
  ck_assert_double_eq_tol(total_payment, 475.63, 1e2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_DIFFERENTIATED5) {
  double credit_amount = 324812.24;
  int time = 600;
  double rate = 15;
  double max_payment = 0;
  double min_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
  credit_differentiated(credit_amount, time, rate, &max_payment, &min_payment,
                        &overpayment, &total_payment);

  ck_assert_double_eq_tol(max_payment, 4601.51, 1e2);
  ck_assert_double_eq_tol(min_payment, 548.12, 1e2);
  ck_assert_double_eq_tol(overpayment, 1220075.98, 1e3);
  ck_assert_double_eq_tol(total_payment, 1544888.22, 1e3);
}
END_TEST

START_TEST(process_NUMBERS1) {
  double result = 0;
  int RESULT_CODE = process("2 + 3 / 4", 0, &result);  // 2 3 4 / +

  ck_assert_double_eq_tol(result, 2.7500000, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS2) {
  double result = 0;
  int RESULT_CODE = process("-3 - 4", 0, &result);  // -3 4 -

  ck_assert_double_eq_tol(result, -7.0000000, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS3) {
  double result = 0;
  int RESULT_CODE = process("5", 0, &result);  // 5

  ck_assert_double_eq(result, 5.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS4) {
  double result = 0;
  int RESULT_CODE = process("(2 + 3 / 4)", 0, &result);  // 2 3 4 / +

  ck_assert_double_eq(result, 2.7500000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS5) {
  double result = 0;
  int RESULT_CODE = process("2 - (-3)", 0, &result);  // 2 -3 -

  ck_assert_double_eq(result, 5.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS6) {
  double result = 0;
  int RESULT_CODE = process("+2 + 3", 0, &result);  // 2 3 +

  ck_assert_double_eq_tol(result, 5.0000000, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS7) {
  double result = 0;
  int RESULT_CODE = process("-(1 - 152)", 0, &result);

  ck_assert_double_eq(result, 151.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS8) {
  double result = 0;
  int RESULT_CODE = process("-1 * (-1) * (-1 * (-1))", 0, &result);

  ck_assert_double_eq(result, 1.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS9) {
  double result = 0;
  int RESULT_CODE = process("-1 * (-1) * (-1)", 0, &result);

  ck_assert_double_eq(result, -1.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS10) {
  double result = 0;
  int RESULT_CODE = process("-1 * (10 - (-15))", 0, &result);

  ck_assert_double_eq(result, -25.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS11) {
  double result = 0;
  int RESULT_CODE = process("1 - 3 * (-1) + 2 / (-2) ^ 3", 0, &result);

  ck_assert_double_eq(result, 3.7500000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS12) {
  double result = 0;
  int RESULT_CODE =
      process("(1 - 5) + (2 * (3 - 5) + (2 * (4 / 8)))", 0, &result);

  ck_assert_double_eq(result, -7.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS13) {
  double result = 0;
  int RESULT_CODE = process("9124.234 + 3849.1239", 0, &result);

  ck_assert_double_eq(result, 12973.3579000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS14) {
  double result = 0;
  int RESULT_CODE = process("0.1 / 0.1", 0, &result);

  ck_assert_double_eq(result, 1.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS15) {
  double result = 0;
  int RESULT_CODE = process("1 / 0", 0, &result);
  ck_assert_double_eq(result, INFINITY);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS16) {
  double result = 0;
  int RESULT_CODE = process("0/0", 0, &result);
  ck_assert_ldouble_nan(result);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS17) {
  double result = 0;
  int RESULT_CODE =
      process("-0.9 / (-0.3) + (((((128 / 16) * 2) + 3) - 4) / 8)", 0, &result);

  ck_assert_double_eq_tol(result, 4.8750000, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS18) {
  double result = 0;
  int RESULT_CODE = process("1 - (-4)", 0, &result);

  ck_assert_double_eq(result, 5.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS19) {
  double result = 0;
  int RESULT_CODE = process("5 mod 3", 0, &result);

  ck_assert_double_eq(result, 2.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS20) {
  double result = 0;
  int RESULT_CODE = process("442 mod 35 * 28", 0, &result);

  ck_assert_double_eq(result, 616.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS21) {
  double result = 0;
  int RESULT_CODE = process("442 mod 35 ^ 3", 0, &result);

  ck_assert_double_eq(result, 442.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS22) {
  double result = 0;
  int RESULT_CODE = process("2893.124 mod 129.324 mod 1.32", 0, &result);

  ck_assert_double_eq_tol(result, 0.4760000, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS23) {
  double result = 0;
  int RESULT_CODE = process("+", 0, &result);

  ck_assert_int_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_NUMBERS24) {
  double result = 0;
  int RESULT_CODE = process("-", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_NUMBERS25) {
  double result = 0;
  int RESULT_CODE = process("*", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_NUMBERS26) {
  double result = 0;
  int RESULT_CODE = process("mod", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_NUMBERS27) {
  double result = 0;
  int RESULT_CODE = process("mod 3", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_NUMBERS28) {
  double result = 0;
  int RESULT_CODE = process("* 3", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_NUMBERS29) {
  double result = 0;
  int RESULT_CODE = process("3*", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_NUMBERS30) {
  double result = 0;
  int RESULT_CODE = process("- 3", 0, &result);

  ck_assert_double_eq(result, -3.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS31) {
  double result = 0;
  int RESULT_CODE = process("1.1.2 / 2.1", 0, &result);

  ck_assert_double_eq_tol(result, 0.0000000, 7);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_NUMBERS32) {
  double result = 0;
  int RESULT_CODE = process("x", 2.5, &result);

  ck_assert_double_eq_tol(result, 2.5000000, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS33) {
  double result = 0;
  int RESULT_CODE = process("x + x", 2.5, &result);

  ck_assert_double_eq_tol(result, 5.0000000, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS34) {
  double result = 0;
  int RESULT_CODE = process("x / x", 2.5, &result);

  ck_assert_double_eq_tol(result, 1.0000000, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS35) {
  double result = 0;
  int RESULT_CODE = process("45 * (*28 + 31)", 0, &result);

  ck_assert_double_eq_tol(result, 0.0000000, 7);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_NUMBERS36) {
  double result = 0;
  int RESULT_CODE = process("(-2)^2", 0, &result);

  ck_assert_double_eq_tol(result, 4.0000000, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS37) {
  double result = 0;
  int RESULT_CODE = process("2^2^3", 0, &result);

  ck_assert_double_eq(result, 64.0000000);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS38) {
  double result = 0;
  int RESULT_CODE = process("3.5*2.8", 0, &result);

  ck_assert_double_eq_tol(result, 9.8000000, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_NUMBERS39) {
  double result = 0;
  int RESULT_CODE = process("3----", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_NUMBERS40) {
  double result = 0;
  int RESULT_CODE = process("**", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_NUMBERS41) {
  double result = 0;
  int RESULT_CODE = process("-^+", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_NUMBERS42) {
  double result = 0;
  int RESULT_CODE = process("^*", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_FUNCTIONS1) {
  double result = 0;
  int RESULT_CODE = process("cos(1)", 0, &result);

  ck_assert_double_eq_tol(result, 0.5403023, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS2) {
  double result = 0;
  int RESULT_CODE =
      process("cos(1 + cos(cos(3 + 4 * 5) + 10) / 2)", 0, &result);

  ck_assert_double_eq_tol(result, 0.8773672, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS3) {
  double result = 0;
  int RESULT_CODE = process("cos(x)", 1.5, &result);

  ck_assert_double_eq_tol(result, 0.0707372, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS4) {
  double result = 0;
  int RESULT_CODE = process("cos(125 + 90328 / sin(185))", 0, &result);

  ck_assert_double_eq_tol(result, 0.9990858, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS5) {
  double result = 0;
  int RESULT_CODE = process("tan(9009142.324)", 0, &result);

  ck_assert_double_eq_tol(result, 0.2161690, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS6) {
  double result = 0;
  int RESULT_CODE = process("atan(3892.1247032)", 0, &result);

  ck_assert_double_eq_tol(result, 1.5705394, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS7) {
  double result = 0;
  int RESULT_CODE = process("log(3941.1348983123)", 0, &result);

  ck_assert_double_eq_tol(result, 3.5956213, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS8) {
  double result = 0;
  int RESULT_CODE = process("sqrt(930124.1324903)", 0, &result);

  ck_assert_double_eq_tol(result, 964.4294336, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS9) {
  double result = 0;
  int RESULT_CODE = process("ln(2089349.12740)", 0, &result);

  ck_assert_double_eq_tol(result, 14.5523632, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS10) {
  double result = 0;
  int RESULT_CODE = process("-cos(1)", 0, &result);

  ck_assert_double_eq_tol(result, -0.5403023, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS11) {
  double result = 0;
  int RESULT_CODE = process("acos(0.92304912)", 0, &result);

  ck_assert_double_eq_tol(result, 0.3948635, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS12) {
  double result = 0;
  int RESULT_CODE = process("asin(0.998329140)", 0, &result);

  ck_assert_double_eq_tol(result, 1.5129800, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS13) {
  double result = 0;
  int RESULT_CODE = process("cos(-)", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_FUNCTIONS14) {
  double result = 0;
  int RESULT_CODE = process("cos(-1)", 0, &result);

  ck_assert_double_eq_tol(result, 0.5403023, 7);
  ck_assert_int_eq(RESULT_CODE, 0);
}
END_TEST

START_TEST(process_FUNCTIONS15) {
  double result = 0;
  int RESULT_CODE = process("cos(*)", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_FUNCTIONS16) {
  double result = 0;
  int RESULT_CODE = process("cos(*/+-)", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_FUNCTIONS17) {
  double result = 0;
  int RESULT_CODE = process("cos(cos(1.1.2))", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

START_TEST(process_FUNCTIONS18) {
  double result = 0;
  int RESULT_CODE = process("cos(2x)", 0, &result);

  ck_assert_double_eq(result, 0.0000000);
  ck_assert_int_eq(RESULT_CODE, 1);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int a;
  suite_add_tcase(s1, tc);
  tcase_add_test(tc, DEPOSIT_CALCULATOR1);
  tcase_add_test(tc, DEPOSIT_CALCULATOR2);
  tcase_add_test(tc, DEPOSIT_CALCULATOR3);

  tcase_add_test(tc, CREDIT_CALCULATOR_ANNUITY1);
  tcase_add_test(tc, CREDIT_CALCULATOR_ANNUITY2);
  tcase_add_test(tc, CREDIT_CALCULATOR_ANNUITY3);
  tcase_add_test(tc, CREDIT_CALCULATOR_ANNUITY4);
  tcase_add_test(tc, CREDIT_CALCULATOR_ANNUITY5);

  tcase_add_test(tc, CREDIT_CALCULATOR_DIFFERENTIATED1);
  tcase_add_test(tc, CREDIT_CALCULATOR_DIFFERENTIATED2);
  tcase_add_test(tc, CREDIT_CALCULATOR_DIFFERENTIATED3);
  tcase_add_test(tc, CREDIT_CALCULATOR_DIFFERENTIATED4);
  tcase_add_test(tc, CREDIT_CALCULATOR_DIFFERENTIATED5);

  tcase_add_test(tc, process_NUMBERS1);   // 2 + 3 / 4
  tcase_add_test(tc, process_NUMBERS2);   // -3 - 4
  tcase_add_test(tc, process_NUMBERS3);   // 5
  tcase_add_test(tc, process_NUMBERS4);   // (2 + 3 / 4)
  tcase_add_test(tc, process_NUMBERS5);   // 2 - -3
  tcase_add_test(tc, process_NUMBERS6);   // +2 + 3
  tcase_add_test(tc, process_NUMBERS7);   // -(1 - 152)
  tcase_add_test(tc, process_NUMBERS8);   // -1 * -1 * (-1 * -1)
  tcase_add_test(tc, process_NUMBERS9);   // -1 * -1 * -1
  tcase_add_test(tc, process_NUMBERS10);  // -1 * (10 - -15)
  tcase_add_test(tc, process_NUMBERS11);  // 1 - 3 * -1 + 2 / -2^3
  tcase_add_test(tc, process_NUMBERS12);
  // (1 - 5) + (2 * (3 - 5) + (2 * (4 / 8)))
  tcase_add_test(tc, process_NUMBERS13);  // 9124.234 + 3849.1239
  tcase_add_test(tc, process_NUMBERS14);  // .1 / .1
  tcase_add_test(tc, process_NUMBERS15);  // 1 / 0
  tcase_add_test(tc, process_NUMBERS16);  // 0 / 0
  tcase_add_test(tc, process_NUMBERS17);
  // -.9 / -0.3 + (((((128 /16) * 2) + 3) - 4) / 8)
  tcase_add_test(tc, process_NUMBERS18);  // 1 - (-4)
  tcase_add_test(tc, process_NUMBERS19);  // 5 mod 3
  tcase_add_test(tc, process_NUMBERS20);  // 442 mod 35 * 28
  tcase_add_test(tc, process_NUMBERS21);  // 442 mod 35 ^ 3
  tcase_add_test(tc, process_NUMBERS22);
  // 2893.124 mod 129.324 mod 1.32
  tcase_add_test(tc, process_NUMBERS23);  // +
  tcase_add_test(tc, process_NUMBERS24);  // -
  tcase_add_test(tc, process_NUMBERS25);  // *
  tcase_add_test(tc, process_NUMBERS26);  // mod
  tcase_add_test(tc, process_NUMBERS27);  // mod 3
  tcase_add_test(tc, process_NUMBERS28);  // * 3
  tcase_add_test(tc, process_NUMBERS29);  // 3 *
  tcase_add_test(tc, process_NUMBERS30);  // - 3
  tcase_add_test(tc, process_NUMBERS31);  // 1.1.2 / 2.1
  tcase_add_test(tc, process_NUMBERS32);  // x  &  x == 2.5
  tcase_add_test(tc, process_NUMBERS33);  // x + x  & x == 2.5
  tcase_add_test(tc, process_NUMBERS34);  // x / x  & x == 2.5
  tcase_add_test(tc, process_NUMBERS35);  // 45 * (*28 + 31)
  tcase_add_test(tc, process_NUMBERS36);  // -2^2
  tcase_add_test(tc, process_NUMBERS37);  // 2^2^3
  tcase_add_test(tc, process_NUMBERS38);  // 3,5 * 2,8
  tcase_add_test(tc, process_NUMBERS39);  // 3----
  tcase_add_test(tc, process_NUMBERS40);  // **
  tcase_add_test(tc, process_NUMBERS41);  // -^*
  tcase_add_test(tc, process_NUMBERS42);  // ^*

  tcase_add_test(tc, process_FUNCTIONS1);  // cos(1)
  tcase_add_test(tc, process_FUNCTIONS2);
  // cos(1 + cos(cos(3 + 4 * 5) + 10) / 2)
  tcase_add_test(tc, process_FUNCTIONS3);  // cos(x) x = 1.5
  tcase_add_test(tc, process_FUNCTIONS4);
  // cos(125 + 90328 / sin(185))
  tcase_add_test(tc, process_FUNCTIONS5);   // tan(9009142.324)
  tcase_add_test(tc, process_FUNCTIONS6);   // atan(3892.1247032)
  tcase_add_test(tc, process_FUNCTIONS7);   // log(3941.1348983123)
  tcase_add_test(tc, process_FUNCTIONS8);   // sqrt(930124.1324903)
  tcase_add_test(tc, process_FUNCTIONS9);   // ln(2089349.12740)
  tcase_add_test(tc, process_FUNCTIONS10);  // -cos(1)
  tcase_add_test(tc, process_FUNCTIONS11);  // acos(0.92304912)
  tcase_add_test(tc, process_FUNCTIONS12);  // asin(0.998329140)
  tcase_add_test(tc, process_FUNCTIONS13);  // cos(-)
  tcase_add_test(tc, process_FUNCTIONS14);  // cos(-1)
  tcase_add_test(tc, process_FUNCTIONS15);  // cos(*)
  tcase_add_test(tc, process_FUNCTIONS16);  // cos(*/+-)
  tcase_add_test(tc, process_FUNCTIONS17);  // cos(cos(1.1.2))
  tcase_add_test(tc, process_FUNCTIONS18);  // cos(2x)

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  a = srunner_ntests_failed(sr);
  srunner_free(sr);
  return a == 0 ? 0 : 1;
}
