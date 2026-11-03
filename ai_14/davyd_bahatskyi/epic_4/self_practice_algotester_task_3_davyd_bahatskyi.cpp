/*
 * Task: Algotester 0331 - Make Palindrome
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <iostream>

int main() {
  char s[100005];
  std::cin >> s;

  int freq[26] = {};
  int *p_freq = freq;
  const char *p_str = s;

  while (*p_str != '\0') {
    int idx = *p_str - 'a';
    if (idx >= 0 && idx < 26) {
      (*(p_freq + idx))++; // pointer arithmetic for frequency table
    }
    p_str++;
  }

  int odd_count = 0;
  for (int i = 0; i < 26; ++i) {
    if (*(p_freq + i) % 2 != 0) {
      odd_count++;
    }
  }

  if (odd_count <= 1) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }

  return 0;
}
