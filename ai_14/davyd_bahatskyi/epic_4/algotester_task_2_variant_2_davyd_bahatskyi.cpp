/*
 * Task: Algotester Lab 2 - Variant 2
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <iostream>
#include <print>

int main() {
  int n;
  std::cin >> n;

  int *r = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> r[i];
  }

  int a, b, c;
  std::cin >> a >> b >> c;

  int k = 0;
  for (int i = 0; i < n; ++i) {
    if (r[i] != a && r[i] != b && r[i] != c) {
      r[k++] = r[i];
    }
  }

  if (k <= 1) {
    std::println("0");
  } else {
    std::println("{}", k - 1);
    for (int i = 0; i < k - 1; ++i) {
      std::print("{} ", r[i] + r[i + 1]);
    }
  }
  delete[] r;
  return 0;
}
