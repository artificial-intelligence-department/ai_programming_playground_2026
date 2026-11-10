/*
 * Task: Lab 6 - C-style Strings
 * Variant: 2
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

bool has_vowels(const char *word) {
  const char *vowels = "aeiouyAEIOUY";
  size_t len = strlen(word);

  for (size_t i = 0; i < len; ++i) {
    if (strchr(vowels, word[i]) != NULL) {
      return 1;
    }
  }
  return 0;
}

int main(void) {
  char str[MAX_LEN];

  puts("Input text (up to 255 chars, words separated by spaces, ends with "
       "dot):");

  if (fgets(str, sizeof(str), stdin) == NULL) {
    return 0;
  }

  // Remove trailing newline if present
  size_t len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }

  puts("\nWords without vowels:");

  int count = 0;
  // Tokenize by spaces, tabs, and terminal dot
  char *token = strtok(str, " \t.");

  while (token != NULL) {
    if (!has_vowels(token)) {
      printf("- %s\n", token);
      count++;
    }
    token = strtok(NULL, " \t.");
  }

  if (count == 0) {
    puts("(No words without vowels found)");
  } else {
    printf("\nTotal matching words: %d\n", count);
  }

  return 0;
}
