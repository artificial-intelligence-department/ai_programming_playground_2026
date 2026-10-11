/*
 * Algotester: 0182 Зуби
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <iostream>
int main() {
  int n, k, a_j, amount = 0, temp_amount = 0;
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    std::cin >> a_j;
    if (a_j >= k) {
      temp_amount++;
      if (temp_amount > amount) {
        amount++;
      }
    } else {
      temp_amount = 0;
    }
  }
  std::cout << amount;
  return 0;
}
