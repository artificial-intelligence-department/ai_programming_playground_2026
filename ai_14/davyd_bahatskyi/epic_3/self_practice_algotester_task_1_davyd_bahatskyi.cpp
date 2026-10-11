/*
 * Algotester: 0181 Цікава гра
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <iostream>

int main() {
  int n, m;
  std::cin >> n >> m;
  ((n * m) % 2 == 0) ? std::cout << "Dragon" : std::cout << "Imp";

  return 0;
}
