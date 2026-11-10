/*
 * Task: Class Practice Work - Text Message Editor
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

#define MAX_TEXT_LEN 256
#define MAX_WORD_LEN 32

// Validates that text consists only of Latin letters, digits, spaces, ends with
// '.', and contains >= 1 word
bool isValidText(const char *text) {
  size_t len = strlen(text);
  if (len < 2 || text[len - 1] != '.') {
    return false;
  }

  bool hasWord = false;
  for (size_t i = 0; i < len - 1; ++i) {
    unsigned char c = text[i];
    if (isalnum(c)) {
      hasWord = true;
    } else if (c != ' ') {
      return false;
    }
  }
  return hasWord;
}

// Splits the text into a dynamic 2D array of C-strings (words)
char **splitWords(const char *text, int &count) {
  count = 0;
  size_t len = strlen(text);
  if (len == 0)
    return nullptr;

  // First pass: count total words
  bool inWord = false;
  for (size_t i = 0; i < len - 1; ++i) {
    if (text[i] != ' ') {
      if (!inWord) {
        inWord = true;
        count++;
      }
    } else {
      inWord = false;
    }
  }

  if (count == 0)
    return nullptr;

  char **words = new char *[count];
  int wIdx = 0;
  size_t start = 0;
  inWord = false;

  // Second pass: allocate memory and copy each word
  for (size_t i = 0; i < len - 1; ++i) {
    if (text[i] != ' ') {
      if (!inWord) {
        inWord = true;
        start = i;
      }
    } else {
      if (inWord) {
        inWord = false;
        size_t wLen = i - start;
        words[wIdx] = new char[wLen + 1];
        strncpy(words[wIdx], text + start, wLen);
        words[wIdx][wLen] = '\0';
        wIdx++;
      }
    }
  }
  if (inWord) {
    size_t wLen = (len - 1) - start;
    words[wIdx] = new char[wLen + 1];
    strncpy(words[wIdx], text + start, wLen);
    words[wIdx][wLen] = '\0';
  }

  return words;
}

// Completely frees the dynamic 2D array of words and zeroes the pointer
void freeWords(char **&words, int &count) {
  if (words != nullptr) {
    for (int i = 0; i < count; ++i) {
      delete[] words[i];
      words[i] = nullptr;
    }
    delete[] words;
    words = nullptr;
  }
  count = 0;
}

// Counts letters, digits, and spaces by traversing text using a raw pointer
void countChars(const char *text, int &letters, int &digits, int &spaces) {
  letters = 0;
  digits = 0;
  spaces = 0;
  const char *p = text;
  while (*p != '\0') {
    if (isalpha((unsigned char)*p)) {
      letters++;
    } else if (isdigit((unsigned char)*p)) {
      digits++;
    } else if (*p == ' ') {
      spaces++;
    }
    p++;
  }
}

// Menu 1: Show text and character statistics with percentages
void showTextAndStats(const char *text, int wordCount) {
  int letters = 0, digits = 0, spaces = 0;
  countChars(text, letters, digits, spaces);
  int total = (int)strlen(text);

  printf("Text:\t\"%s\"\n", text);
  printf("Characters:  %2d\n", total);
  printf("Words:       %2d\n", wordCount);
  printf("Letters:     %2d (%5.1f%%)\n", letters,
         total > 0 ? (letters * 100.0 / total) : 0.0);
  printf("Digits:      %2d (%5.1f%%)\n", digits,
         total > 0 ? (digits * 100.0 / total) : 0.0);
  printf("Spaces:      %2d (%5.1f%%)\n", spaces,
         total > 0 ? (spaces * 100.0 / total) : 0.0);
}

// Custom QuickSort for string pointers using strcmp
void quickSortWords(const char **arr, int left, int right) {
  if (left >= right)
    return;
  const char *pivot = arr[left + (right - left) / 2];
  int i = left, j = right;

  while (i <= j) {
    while (strcmp(arr[i], pivot) < 0)
      i++;
    while (strcmp(arr[j], pivot) > 0)
      j--;
    if (i <= j) {
      const char *temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
      i++;
      j--;
    }
  }
  quickSortWords(arr, left, j);
  quickSortWords(arr, i, right);
}

// Menu 2: Formatted words table, extremes, averages, and most frequent word
void showWordTable(char **words, int count) {
  if (count == 0) {
    printf("Words array is empty.\n");
    return;
  }

  printf("+----+-----------------+-------+\n");
  printf("| N  | Word            | Len.  |\n");
  printf("+----+-----------------+-------+\n");

  int minLen = 1000, maxLen = -1;
  int minIdx = 0, maxIdx = 0;
  int totalLetters = 0;

  for (int i = 0; i < count; ++i) {
    int wLen = (int)strlen(words[i]);
    printf("| %2d | %-15s | %5d |\n", i + 1, words[i], wLen);
    totalLetters += wLen;

    if (wLen < minLen) {
      minLen = wLen;
      minIdx = i;
    }
    if (wLen > maxLen) {
      maxLen = wLen;
      maxIdx = i;
    }
  }
  printf("+----+-----------------+-------+\n");
  printf("Longest word: %s (%d)\n", words[maxIdx], maxLen);
  printf("Shortest word: %s (%d)\n", words[minIdx], minLen);
  printf("Average length: %.2f\n", (double)totalLetters / count);

  // Create a copy of pointer array to preserve original words sequence
  const char **sorted = new const char *[count];
  for (int i = 0; i < count; ++i) {
    sorted[i] = words[i];
  }
  quickSortWords(sorted, 0, count - 1);

  printf("Alphabetical: ");
  for (int i = 0; i < count; ++i) {
    printf("%s%s", sorted[i], (i + 1 == count ? "" : " "));
  }
  printf("\n");

  // Scan sorted copy to determine the most frequent word
  int maxFreq = 0;
  int bestIdx = 0;
  int curFreq = 1;

  for (int i = 1; i <= count; ++i) {
    if (i < count && strcmp(sorted[i], sorted[i - 1]) == 0) {
      curFreq++;
    } else {
      if (curFreq > maxFreq) {
        maxFreq = curFreq;
        bestIdx = i - 1;
      }
      curFreq = 1;
    }
  }
  printf("Most frequent word: %s (%d)\n", sorted[bestIdx], maxFreq);

  delete[] sorted;
}

// Menu 3: Whole-word case-sensitive replacement using std::string methods
void replaceWord(char *text, char **&words, int &count) {
  char fromBuf[MAX_WORD_LEN], toBuf[MAX_WORD_LEN];
  printf("Word to replace: ");
  if (scanf("%31s", fromBuf) != 1)
    return;
  printf("Replacement word: ");
  if (scanf("%31s", toBuf) != 1)
    return;

  // Validate replacement word: only alphanumeric characters allowed
  for (size_t i = 0; i < strlen(toBuf); ++i) {
    if (!isalnum((unsigned char)toBuf[i])) {
      printf("Error: replacement word must contain only Latin letters and "
             "digits.\n");
      return;
    }
  }

  std::string str(text);
  std::string from(fromBuf);
  std::string to(toBuf);

  int replacements = 0;
  size_t pos = 0;

  // Search and replace whole words only
  while ((pos = str.find(from, pos)) != std::string::npos) {
    bool leftBoundary = (pos == 0 || !isalnum((unsigned char)str[pos - 1]));
    bool rightBoundary = (pos + from.length() >= str.length() ||
                          !isalnum((unsigned char)str[pos + from.length()]));

    if (leftBoundary && rightBoundary) {
      str.replace(pos, from.length(), to);
      replacements++;
      pos += to.length();
    } else {
      pos += 1;
    }
  }

  if (str.length() > MAX_TEXT_LEN - 1) {
    printf("Error: text length exceeds 255 characters after replacement.\n");
    return;
  }

  printf("Replacements made: %d\n", replacements);
  printf("Before: \"%s\"\n", text);
  printf("After:  \"%s\"\n", str.c_str());
  printf("New length: %zu\n", str.length());

  // Update base text buffer and rebuild words array
  strcpy(text, str.c_str());
  freeWords(words, count);
  words = splitWords(text, count);
}

// Menu 4: Compare two words using strcmp, string operator==, and
// case-insensitivity
void compareWords() {
  char a[MAX_WORD_LEN], b[MAX_WORD_LEN];
  printf("First word: ");
  if (scanf("%31s", a) != 1)
    return;
  printf("Second word: ");
  if (scanf("%31s", b) != 1)
    return;

  int cmp = strcmp(a, b);
  int normalizedCmp = (cmp < 0) ? -1 : (cmp > 0 ? 1 : 0);
  const char *cmpDesc =
      (cmp < 0) ? "first word is smaller"
                : (cmp > 0 ? "first word is greater" : "words are equal");

  std::string sa(a), sb(b);
  bool eqExact = (sa == sb);

  // Case-insensitive comparison
  bool eqNoCase = (sa.length() == sb.length());
  if (eqNoCase) {
    for (size_t i = 0; i < sa.length(); ++i) {
      if (tolower((unsigned char)sa[i]) != tolower((unsigned char)sb[i])) {
        eqNoCase = false;
        break;
      }
    }
  }

  std::string concat = sa + " & " + sb;

  printf("strcmp: %d -> %s\n", normalizedCmp, cmpDesc);
  printf("Equal (==): %s\n", eqExact ? "yes" : "no");
  printf("Equal case-insensitive: %s\n", eqNoCase ? "yes" : "no");
  printf("Lengths: %zu and %zu\n", sa.length(), sb.length());
  printf("Concatenation: \"%s\" (%zu)\n", concat.c_str(), concat.length());
}

// Menu 5: Character analysis with bitwise binary output
void charInfo(const char *text) {
  printf("Enter character: ");
  char c;
  if (scanf(" %c", &c) != 1)
    return;

  unsigned char uc = (unsigned char)c;

  // Bitwise binary conversion (8 bits)
  char binStr[9];
  for (int i = 7; i >= 0; --i) {
    binStr[7 - i] = ((uc >> i) & 1) ? '1' : '0';
  }
  binStr[8] = '\0';

  printf("Character: '%c'\n", c);
  printf("Code: %d (hex 0x%02x, oct 0%o, bin %s)\n", uc, uc, uc, binStr);

  if (isupper(uc)) {
    printf("Type: uppercase letter\n"
           "Opposite case: '%c'\n",
           (char)tolower(uc));
  } else if (islower(uc)) {
    printf("Type: lowercase letter\n"
           "Opposite case: '%c'\n",
           (char)toupper(uc));
  } else if (isdigit(uc)) {
    printf("Type: digit\n");
  } else if (isspace(uc)) {
    printf("Type: whitespace character\n");
  } else {
    printf("Type: other character\n");
  }

  printf("Next character: '%c'\n", (char)(uc + 1));

  // Occurrences in text (1-based index)
  int count = 0;
  int firstPos = -1;
  for (int i = 0; text[i] != '\0'; ++i) {
    if (text[i] == c) {
      count++;
      if (firstPos == -1) {
        firstPos = i + 1;
      }
    }
  }

  if (count > 0) {
    printf("Occurrences in text: %d, first at position %d\n", count, firstPos);
  } else {
    printf("Not found in text\n");
  }
}

// Menu 6: Read new sentence word by word via std::cin >>
void inputNewSentence(char *text, char **&words, int &count) {
  printf("Enter sentence (dot after the last word):\n");

  std::string newText = "";
  std::string w;
  int readWords = 0;

  // Read word by word using cin >> until a word ends with '.'
  while (std::cin >> w) {
    readWords++;
    if (!newText.empty()) {
      newText += " ";
    }
    newText += w;

    if (!w.empty() && w.back() == '.') {
      break;
    }
  }

  if (!isValidText(newText.c_str())) {
    printf("Error: text must consist of Latin letters, digits, and spaces, and "
           "end with a dot.\n");
    return;
  }

  if (newText.length() > MAX_TEXT_LEN - 1) {
    printf("Error: text length exceeds 255 characters.\n");
    return;
  }

  printf("Words read: %d\n", readWords);
  printf("New text: \"%s\"\n", newText.c_str());
  printf("Length: %zu\n", newText.length());

  strcpy(text, newText.c_str());
  freeWords(words, count);
  words = splitWords(text, count);
}

// Clears residual newline and whitespace from stdin buffer after scanf
void clearInputBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

int main() {
  char text[MAX_TEXT_LEN];

  printf("Enter text (up to 255 chars, ends with dot):\n");
  if (fgets(text, sizeof(text), stdin) == nullptr) {
    return 0;
  }

  // Strip trailing newline from fgets
  size_t len = strlen(text);
  if (len > 0 && text[len - 1] == '\n') {
    text[len - 1] = '\0';
  }

  if (!isValidText(text)) {
    printf("Error: text must consist of Latin letters, digits, and spaces, and "
           "end with a dot.\n");
    return 0;
  }

  int wordCount = 0;
  char **words = splitWords(text, wordCount);

  while (true) {
    printf("\n--- Menu ---\n"
           "1. Show text and statistics\n"
           "2. Word table\n"
           "3. Replace word\n"
           "4. Compare two words\n"
           "5. Character information\n"
           "6. Enter new sentence\n"
           "0. Exit\n"
           "Your choice: ");

    int choice = -1;
    if (scanf("%d", &choice) != 1) {
      printf("Error: please enter a menu item number.\n");
      clearInputBuffer();
      continue;
    }
    clearInputBuffer();

    switch (choice) {
    case 1:
      // text and stats
      //
      showTextAndStats(text, wordCount);
      break;
    case 2:
      // word table
      // table: number,word,length. words left, numbers right
      // under the table, shortest and longest word
      // most used word (if multiple then first alphabetically)
      showWordTable(words, wordCount);
      break;
    case 3:
      // replace word
      // case sensitive, only complete words
      // show error if errors
      // replace with std::string, if result is longer than 255, show error and
      // dont change text chow amount of replaced words and length before and
      // after replacement
      replaceWord(text, words, wordCount);
      break;
    case 4:
      // compare words
      // strcmp (-1,0,1 with descpription)
      // show length of both words and result of &
      compareWords();
      break;
    case 5:
      // info about char
      // 10,16,8,2 bit representations.
      // is it a big small character, number, space or smth else
      // amount of this character in text and first appearance
      charInfo(text);
      break;
    case 6:
      // input new sentence
      // uses while cin
      // if exists an error, show it and dont change text
      // show amount of words, new text, its length
      inputNewSentence(text, words, wordCount);
      clearInputBuffer();
      break;
    case 0:
      printf("Exiting program...\n");
      freeWords(words, wordCount);
      return 0;
      break;
    default:
      printf("Error: item %d is not in the menu.\n", choice);
      break;
    }
  }

  return 0;
}
