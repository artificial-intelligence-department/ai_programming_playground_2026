/*
 * Task: Algotester Lab 4_1
 * Variant 3
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <print>
#include <vector>

int main() {
  std::vector<int> rem0, rem1, rem2;
  size_t size;
  std::cin >> size;

  for (size_t i = 0; i < size; ++i) {
    int temp;
    std::cin >> temp;
    if (temp % 3 == 0) {
      rem0.push_back(temp);
    } else if (temp % 3 == 1) {
      rem1.push_back(temp);
    } else {
      rem2.push_back(temp);
    }
  }

  std::sort(rem0.begin(), rem0.end());
  std::sort(rem1.begin(), rem1.end(), std::greater<>());
  std::sort(rem2.begin(), rem2.end());

  std::vector<int> result;

  result.insert(result.end(), rem0.begin(), rem0.end());
  result.insert(result.end(), rem1.begin(), rem1.end());
  result.insert(result.end(), rem2.begin(), rem2.end());

  auto it = std::unique(result.begin(), result.end());
  result.erase(it, result.end());

  std::println("{}", result.size());
  for (int x : result) {
    std::print("{} ", x);
  }
  return 0;
}
