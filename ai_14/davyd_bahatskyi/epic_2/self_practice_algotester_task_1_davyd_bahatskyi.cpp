/*
 * Algotester: 0011 Marichka and Cookies (Self Practice)
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <iostream>

int main() {
  long long i, sum = 0, a;
  for (std::cin >> i; i--;) {
    std::cin >> a;
    sum += a;
    if (a != 0) {
      sum--;
    }
  };
  std::cout << sum;
  return 0;
}
