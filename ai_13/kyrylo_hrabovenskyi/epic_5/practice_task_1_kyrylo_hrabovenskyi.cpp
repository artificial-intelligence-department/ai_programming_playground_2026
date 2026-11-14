#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

// Прототипи підпрограм
bool isValidText(const char* text);
char** splitWords(const char* text, int& count);
void freeWords(char**& words, int& count);
void countChars(const char* text, int& letters, int& digits, int& spaces);
void printMenu();
void clearInputBuffer();

void handleItem1(const char* text, int wordCount);
void handleItem2(char** words, int count);
void handleItem3(char* text, char**& words, int& count);
void handleItem4();
void handleItem5(const char* text);
void handleItem6(char* text, char**& words, int& count);

int main() {
    char text[256];
    printf("Enter text (up to 255 characters, ends with a period):\n");
    if (!fgets(text, sizeof(text), stdin)) return 0;

    // Видалення \n на кінці
    int len = (int)strlen(text);
    if (len > 0 && text[len - 1] == '\n') text[--len] = '\0';

    if (!isValidText(text)) {
        printf("Error: Text must consist of Latin letters, digits, spaces, and end with a period.\n");
        return 0;
    }

    int wordCount = 0;
    char** words = splitWords(text, wordCount);

    int choice = -1;
    while (choice != 0) {
        printMenu();
        printf("Your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Error: Please enter a valid menu number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
        case 1: handleItem1(text, wordCount); break;
        case 2: handleItem2(words, wordCount); break;
        case 3: handleItem3(text, words, wordCount); break;
        case 4: handleItem4(); break;
        case 5: handleItem5(text); break;
        case 6: handleItem6(text, words, wordCount); break;
        case 0: break;
        default: printf("Error: Option %d does not exist in the menu.\n", choice); break;
        }
    }

    freeWords(words, wordCount);
    return 0;
}

// Очищення буфера введення
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Перевірка коректності тексту
bool isValidText(const char* text) {
    int len = (int)strlen(text);
    if (len == 0 || text[len - 1] != '.') return false;
    int wordLen = 0, words = 0;
    for (int i = 0; i < len - 1; ++i) {
        char c = text[i];
        if (isalnum((unsigned char)c)) wordLen++;
        else if (c == ' ') {
            if (wordLen > 0) { words++; wordLen = 0; }
        }
        else return false;
    }
    if (wordLen > 0) words++;
    return words > 0;
}

// Розбиття тексту на масив слів
char** splitWords(const char* text, int& count) {
    char temp[256];
    strcpy(temp, text);
    int len = (int)strlen(temp);
    if (len > 0 && temp[len - 1] == '.') temp[len - 1] = '\0';

    count = 0;
    char* token = strtok(temp, " ");
    while (token) {
        count++;
        token = strtok(NULL, " ");
    }

    if (count == 0) return NULL;

    char** words = new char* [count];
    strcpy(temp, text);
    if (len > 0) temp[len - 1] = '\0';

    token = strtok(temp, " ");
    int i = 0;
    while (token) {
        words[i] = new char[strlen(token) + 1];
        strcpy(words[i], token);
        i++;
        token = strtok(NULL, " ");
    }
    return words;
}

// Звільнення динамічної пам'яті масиву слів
void freeWords(char**& words, int& count) {
    if (!words) return;
    for (int i = 0; i < count; ++i) {
        delete[] words[i];
    }
    delete[] words;
    words = NULL;
    count = 0;
}

// Підрахунок типів символів
void countChars(const char* text, int& letters, int& digits, int& spaces) {
    letters = digits = spaces = 0;
    const char* p = text;
    while (*p) {
        if (isalpha((unsigned char)*p)) letters++;
        else if (isdigit((unsigned char)*p)) digits++;
        else if (*p == ' ') spaces++;
        p++;
    }
}

// Вивід головного меню
void printMenu() {
    printf("\n--- MENU ---\n");
    printf("1. Show text and statistics\n");
    printf("2. Word table\n");
    printf("3. Replace a word\n");
    printf("4. Compare two words\n");
    printf("5. Character information\n");
    printf("6. Enter new sentence\n");
    printf("0. Exit\n");
}

// Пункт 1: Текст та статистика
void handleItem1(const char* text, int wordCount) {
    int total = (int)strlen(text);
    if (total == 0) return;

    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);

    printf("Text: \"%s\"\n", text);
    printf("Characters: %d\nWords: %d\n", total, wordCount);
    printf("Letters: %d (%.1f%%)\n", letters, (letters * 100.0) / total);
    printf("Digits: %d (%.1f%%)\n", digits, (digits * 100.0) / total);
    printf("Spaces: %d (%.1f%%)\n", spaces, (spaces * 100.0) / total);
}

// Пункт 2: Таблиця слів та аналіз
void handleItem2(char** words, int count) {
    if (count == 0 || !words) {
        printf("Text contains no words.\n");
        return;
    }
    printf("+----+--------------------------------+-------+\n");
    printf("| #  | Word                           | Len.  |\n");
    printf("+----+--------------------------------+-------+\n");
    int totalLen = 0;
    int minLen = (int)strlen(words[0]), maxLen = (int)strlen(words[0]);
    int minIdx = 0, maxIdx = 0;

    for (int i = 0; i < count; ++i) {
        int l = (int)strlen(words[i]);
        totalLen += l;
        printf("| %-2d | %-30s | %5d |\n", i + 1, words[i], l);
        if (l < minLen) { minLen = l; minIdx = i; }
        if (l > maxLen) { maxLen = l; maxIdx = i; }
    }
    printf("+----+--------------------------------+-------+\n");
    printf("Longest word: %s (%d)\n", words[maxIdx], maxLen);
    printf("Shortest word: %s (%d)\n", words[minIdx], minLen);
    printf("Average length: %.2f\n", (double)totalLen / count);

    // Сортування за абеткою
    char** sorted = new char* [count];
    for (int i = 0; i < count; ++i) {
        sorted[i] = new char[strlen(words[i]) + 1];
        strcpy(sorted[i], words[i]);
    }

    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) {
                char* tmp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = tmp;
            }
        }
    }

    printf("Alphabetical order: ");
    for (int i = 0; i < count; ++i) {
        printf("%s ", sorted[i]);
    }
    printf("\n");

    // Пошук найчастішого слова
    int maxFreq = 0;
    char mostFreq[256] = "";
    for (int i = 0; i < count; ++i) {
        int freq = 0;
        for (int j = 0; j < count; ++j) {
            if (strcmp(words[i], words[j]) == 0) freq++;
        }
        if (freq > maxFreq) {
            maxFreq = freq;
            strcpy(mostFreq, words[i]);
        }
    }
    printf("Most frequent word: %s (%d)\n", mostFreq, maxFreq);

    // Звільнення тимчасового відсортованого масиву
    for (int i = 0; i < count; ++i) {
        delete[] sorted[i];
    }
    delete[] sorted;
}

// Пункт 3: Заміна слова
void handleItem3(char* text, char**& words, int& count) {
    char from[32], to[32];
    printf("Replace word: "); scanf("%31s", from);
    printf("With word: "); scanf("%31s", to);
    clearInputBuffer();

    for (int i = 0; to[i]; ++i) {
        if (!isalnum((unsigned char)to[i])) {
            printf("Error: The new word must contain only Latin letters and digits.\n");
            return;
        }
    }

    std::string strText(text);
    std::string strFrom(from);
    std::string strTo(to);

    int replacements = 0;
    size_t pos = 0;
    while ((pos = strText.find(strFrom, pos)) != std::string::npos) {
        bool leftBound = (pos == 0 || !isalnum((unsigned char)strText[pos - 1]));
        bool rightBound = (pos + strFrom.length() == strText.length() || !isalnum((unsigned char)strText[pos + strFrom.length()]));

        if (leftBound && rightBound) {
            strText.replace(pos, strFrom.length(), strTo);
            pos += strTo.length();
            replacements++;
        }
        else {
            pos += strFrom.length();
        }
    }

    if (strText.length() > 255) {
        printf("Error: Length of the new text exceeds 255 characters.\n");
        return;
    }

    printf("Replacements made: %d\n", replacements);
    printf("Before: \"%s\"\n", text);
    strcpy(text, strText.c_str());
    printf("After: \"%s\"\n", text);
    printf("New length: %d\n", (int)strText.length());

    freeWords(words, count);
    words = splitWords(text, count);
}

// Пункт 4: Порівняння двох слів
void handleItem4() {
    char a[32], b[32];
    printf("First word: "); scanf("%31s", a);
    printf("Second word: "); scanf("%31s", b);
    clearInputBuffer();

    int cmp = strcmp(a, b);
    printf("strcmp: %d -> %s\n", cmp, cmp < 0 ? "first word is smaller" : (cmp > 0 ? "first word is larger" : "words are equal"));

    std::string strA(a), strB(b);
    printf("Equal (==): %s\n", strA == strB ? "yes" : "no");

    bool ciEq = (strA.length() == strB.length());
    if (ciEq) {
        for (size_t i = 0; i < strA.length(); ++i) {
            if (tolower((unsigned char)strA[i]) != tolower((unsigned char)strB[i])) {
                ciEq = false; break;
            }
        }
    }
    printf("Equal case-insensitive: %s\n", ciEq ? "yes" : "no");
    printf("Lengths: %d %d\n", (int)strA.length(), (int)strB.length());

    std::string concat = strA + " & " + strB;
    printf("Concatenation: \"%s\" (%d)\n", concat.c_str(), (int)concat.length());
}

// Пункт 5: Інформація про символ
void handleItem5(const char* text) {
    char c;
    printf("Enter a character: ");
    scanf(" %c", &c);
    clearInputBuffer();

    unsigned char uc = (unsigned char)c;
    printf("Character: '%c'\n", c);
    printf("Code: %d (hex 0x%x, oct 0%o, bin ", uc, uc, uc);
    for (int i = 7; i >= 0; --i) printf("%d", (uc >> i) & 1);
    printf(")\n");

    if (isupper(uc)) printf("Type: uppercase letter\nOther case: '%c'\n", tolower(uc));
    else if (islower(uc)) printf("Type: lowercase letter\nOther case: '%c'\n", toupper(uc));
    else if (isdigit(uc)) printf("Type: digit\n");
    else if (isspace(uc)) printf("Type: space character\n");
    else printf("Type: other character\n");

    printf("Next character: '%c'\n", c + 1);

    int count = 0, firstPos = -1;
    int len = (int)strlen(text);
    for (int i = 0; i < len; ++i) {
        if (text[i] == c) {
            count++;
            if (firstPos == -1) firstPos = i + 1;
        }
    }

    if (count > 0) printf("Occurrences in text: %d, first at position %d\n", count, firstPos);
    else printf("Does not occur in text.\n");
}

// Пункт 6: Введення нового речення
void handleItem6(char* text, char**& words, int& count) {
    printf("Enter a new sentence (up to 255 characters, ends with a period):\n");
    clearInputBuffer();

    char newBuf[256];
    if (!fgets(newBuf, sizeof(newBuf), stdin)) return;

    int len = (int)strlen(newBuf);
    if (len > 0 && newBuf[len - 1] == '\n') newBuf[--len] = '\0';

    if (!isValidText(newBuf)) {
        printf("Error: Text must consist of Latin letters, digits, spaces, and end with a period.\n");
        return;
    }

    strcpy(text, newBuf);
    freeWords(words, count);
    words = splitWords(text, count);

    printf("New text successfully saved: \"%s\"\n", text);
    printf("Word count: %d\n", count);
}