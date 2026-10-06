/*
 * Lab 1. Task 2. Variant 16
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <iostream>

int main() {
  float n = 0, m = 0;
  std::cout << "input n: ";
  std::cin >> n;
  std::cout << "input m: ";
  std::cin >> m;

  std::cout << "value n: " << n << "\nvalue m: " << m
            << "\n++n*++m: " << (++n * ++m) << "\n\n";

  std::cout << "value n: " << n << "\nvalue m: " << m
            << "\nm++<n: " << (m++ < n) << "\n\n";

  std::cout << "value n: " << n << "\nvalue m: " << m
            << "\nn++<m: " << (n++ < m) << "\n";

  return 0;
}
