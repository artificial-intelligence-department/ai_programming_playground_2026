/*
 * Lab 1. Task 1. Variant 16
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <cmath>
#include <iostream>

int main() {
  // (a-b)^3-(a^3-3 a^2 b)/b^3-3ab^2
  // FLOAT CALCULATIONS //
  // float constants
  float a_f = 1000.0f, b_f = 0.0001f;
  // a-b
  float diff_f = a_f - b_f;
  //(a-b)^3
  float diff3_f = pow(diff_f, 3);
  // a^3
  float a3_f = pow(a_f, 3);
  // a^3-3 a^2 b
  float diff2_f = a3_f - 3 * a_f * a_f * b_f;
  //(a-b)^3-(a^3-3 a^2 b)
  float numer_f = diff3_f - diff2_f;

  // b^3
  float b3_f = pow(b_f, 3);
  // b^3-3ab^2
  float denum_f = b3_f - 3 * a_f * b_f * b_f;

  // float result
  float result_f = numer_f / denum_f;
  std::cout << "float calculations result: " << result_f << "\n";

  // FLOAT CALCULATIONS //
  // float constants
  double a_d = 1000.0, b_d = 0.0001;
  // a-b
  double diff_d = a_d - b_d;
  //(a-b)^3
  double diff3_d = pow(diff_d, 3);
  // a^3
  double a3_d = pow(a_d, 3);
  // a^3-3 a^2 b
  double diff2_d = a3_d - 3 * a_d * a_d * b_d;
  //(a-b)^3-(a^3-3 a^2 b)
  double numer_d = diff3_d - diff2_d;

  // b^3
  double b3_d = pow(b_d, 3);
  // b^3-3ab^2
  double denum_d = b3_d - 3 * a_d * b_d * b_d;

  // float result
  double result_d = numer_d / denum_d;
  std::cout << "double calculations result: " << result_d << "\n";

  return 0;
}
