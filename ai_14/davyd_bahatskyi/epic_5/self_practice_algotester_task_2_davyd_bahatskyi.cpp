/*
 * Task: Algotester 0541 - Dzidzio and His Song
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <cstdio>
#include <cstring>

int main() {
  char s[128];
  fgets(s, sizeof(s), stdin);

  // Strip trailing newline
  size_t len = strlen(s);
  if (len > 0 && s[len - 1] == '\n') {
    s[len - 1] = '\0';
    len--;
  }

  if (len == 0) {
    printf("0\n");
    return 0;
  }

  // Count contiguous blocks of identical characters
  int blocks = 1;
  for (size_t i = 1; i < len; ++i) {
    if (s[i] != s[i - 1]) {
      blocks++;
    }
  }

  printf("%d\n", blocks);
  return 0;
}
