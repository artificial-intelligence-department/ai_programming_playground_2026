/*
 * Task: Algotester 0613 - Andriyko and Strings
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <iostream>
#include <string>

int main() {
  int n, k;
  std::cin >> n >> k;

  if (n < k || (k == 1 && n > 1)) {
    std::cout << -1 << "\n";
    return 0;
  }

  if (k == 1 && n == 1) {
    std::cout << "a\n";
    return 0;
  }

  std::string res;
  res.reserve(n);

  // Alternate 'a' and 'b' to minimize lexicographical order
  int prefix_len = n - (k - 2);
  for (int i = 0; i < prefix_len; ++i) {
    res.push_back((i % 2 == 0) ? 'a' : 'b');
  }

  // Append the remaining (k - 2) distinct letters: 'c', 'd', ...
  for (int i = 0; i < k - 2; ++i) {
    res.push_back(static_cast<char>('c' + i));
  }

  std::cout << res << "\n";
  return 0;
}
