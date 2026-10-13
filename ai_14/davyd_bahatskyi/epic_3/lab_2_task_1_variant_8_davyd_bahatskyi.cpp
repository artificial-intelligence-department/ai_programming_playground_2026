/*
 * Lab 2. Task 1. Variant 8
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <iostream>

double func(double n) { return (2.0 * n + 1.0) / (4.0 * n - 2.0); }

int main() {
  const double eps = 0.0001;
  double a_n = 0.5;
  double sum = 0.5;

  std::cout << a_n << "\n";

  for (int n = 1; a_n >= eps; n++) {
    a_n *= func(n);
    sum += a_n;
    std::cout << a_n << "\n";
  }
  std::cout << "the sum is " << sum << "\n";
  return 0;
}
