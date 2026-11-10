/*
 * Task: Algotester 0631 - Kolobok
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORDS 505
#define MAX_WORD_LEN 1005

// Static buffer to hold unique words safely
static char unique_words[MAX_WORDS][MAX_WORD_LEN];

int main() {
  char line[2048];

  // Read the single line of input (completes immediately on Enter)
  if (fgets(line, sizeof(line), stdin) == NULL) {
    return 0;
  }

  int unique_count = 0;
  char *token = strtok(line, " \t\r\n");

  while (token != NULL) {
    // Convert token to lowercase for case-insensitivity
    for (int i = 0; token[i] != '\0'; ++i) {
      token[i] = (char)tolower((unsigned char)token[i]);
    }

    // Check if the lowercase word is already recorded
    int exists = 0;
    for (int i = 0; i < unique_count; ++i) {
      if (strcmp(unique_words[i], token) == 0) {
        exists = 1;
        break;
      }
    }

    // Add if unique
    if (!exists && unique_count < MAX_WORDS) {
      strcpy(unique_words[unique_count], token);
      unique_count++;
    }

    token = strtok(NULL, " \t\r\n");
  }

  printf("%d\n", unique_count);
  return 0;
}
