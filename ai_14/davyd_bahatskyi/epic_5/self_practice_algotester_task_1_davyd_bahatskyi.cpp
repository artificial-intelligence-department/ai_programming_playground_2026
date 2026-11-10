/*
 * Task: Algotester 0081 - Will He Help or Blow It Off?
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <iostream>
#include <string>

int main() {
  int k;
  std::cin >> k;

  std::string s;
  std::cin >> s;

  const std::string target = "TOILET";
  int count = 0;
  size_t pos = 0;

  while ((pos = s.find(target, pos)) != std::string::npos) {
    count++;
    pos += target.length();
    if (count >= k)
      break;
  }

  if (count >= k) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }

  return 0;
}
