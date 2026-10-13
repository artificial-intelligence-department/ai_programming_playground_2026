/*
 * Lab 3. Task 1. Variant 9
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <cmath>
#include <iomanip>
#include <ios>
#include <iostream>
int main() {
  const double a = 0.1, b = 0.8, k = 10, eps = 0.0001;
  double h = (b - a) / k;

  // main loop
  for (int i = 0; i <= k; i++) {
    // X calculations
    long double x = a + i * h;
    long double SN = 0, SE = 0;

    // SN loop
    for (int n = 0; n <= 3; n++) {
      SN += pow(x, 4.0 * n + 1) / (4.0 * n + 1);
    }

    // SE loop
    long double x_n = x;
    for (int n = 0; x_n >= eps; n++) {
      x_n = pow(x, 4.0 * n + 1) / (4.0 * n + 1);
      SE += x_n;
    }

    // Y calculations
    long double Y = 0.25 * std::log((1.0 + x) / (1.0 - x)) + 0.5 * std::atan(x);

    // final table output
    std::cout << std::fixed << std::setw(3) << std::setprecision(2) << "X=" << x
              << std::setw(7) << std::setprecision(8) << "SN=" << SN
              << std::setw(7) << "SE=" << SE << std::setw(7) << "Y=" << Y
              << "\n";
  }
  return 0;
}
