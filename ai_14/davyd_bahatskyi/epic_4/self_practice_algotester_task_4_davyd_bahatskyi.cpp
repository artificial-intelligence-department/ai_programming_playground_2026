/*
 * Task: Algotester 0281 - Field of Wonders
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <iostream>

int main() {
  char s[105];
  std::cin >> s;

  bool seen[26] = {false};
  bool *p_seen = seen;
  char *ptr = s;

  int unique_letters = 0;
  while (*ptr != '\0') {
    int idx = *ptr - 'A';
    if (!(*(p_seen + idx))) {
      *(p_seen + idx) = true;
      unique_letters++;
    }
    ptr++;
  }

  std::cout << unique_letters << "\n";
  return 0;
}
