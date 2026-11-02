/*
 * Task: Algotester 0213 - Oaks and Birches
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <iostream>

int main() {
  int studs, types;
  std::cin >> studs >> types;

  int tree[77][77] = {}, max[77] = {};

  for (int i = 0; i < studs; ++i) {
    for (int j = 0; j < types; ++j) {
      std::cin >> tree[i][j];
    }
  }

  for (int i = 0; i < types; ++i) {
    for (int j = 0; j < studs; ++j) {
      if (max[i] < tree[j][i]) {
        max[i] = tree[j][i];
      }
    }
  }

  int sum = 0;
  for (int i = 0; i < types; ++i) {
    sum += max[i];
  }
  std::cout << sum;

  return 0;
}
