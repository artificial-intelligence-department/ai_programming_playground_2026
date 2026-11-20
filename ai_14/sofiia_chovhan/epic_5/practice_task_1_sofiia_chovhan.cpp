
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

bool validWord(const char *word) {
    int length = (int)strlen(word);
    if (length == 0 || length > 31) return false;

    for (int i = 0; i < length; i++) {
        char c = word[i];
        if (!((c >= 'A' && c <= 'Z') ||
              (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9'))) {
            return false;
        }
    }
    return true;
}

bool validText(const char *text) {
    int length = (int)strlen(text);

    if (length < 2 || length > 255 || text[length - 1] != '.') {
        return false;
    }

    if (text[length - 2] == ' ') return false;

    bool hasWord = false;

    for (int i = 0; i < length - 1; i++) {
        char c = text[i];

        if ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9')) {
            hasWord = true;
        } else if (c != ' ') {
            return false;
        }
    }

    return hasWord;
}

char **splitWords(const char *text, int &count) {
    char copy[256];
    strcpy(copy, text);
    copy[strlen(copy) - 1] = '\0';

    char **words = new char*[256];
    count = 0;

    char *word = strtok(copy, " ");

    while (word != NULL) {
        words[count] = new char[strlen(word) + 1];
        strcpy(words[count], word);

        count++;
        word = strtok(NULL, " ");
    }

    return words;
}

void freeWords(char **words, int count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }

    delete[] words;
}

void countChars(const char *text, int &letters,
                int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;

    const char *p = text;

    while (*p != '\0') {
        unsigned char c = (unsigned char)*p;

        if (isalpha(c)) letters++;
        else if (isdigit(c)) digits++;
        else if (isspace(c)) spaces++;

        p++;
    }
}

bool readWord(char word[32]) {
    char line[256];

    if (fgets(line, 256, stdin) == NULL) return false;

    int length = (int)strlen(line);

    if (strchr(line, '\n') == NULL && length == 255) {
        int ch = getchar();

        while (ch != '\n' && ch != EOF) {
            ch = getchar();
        }

        return false;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    if (!validWord(line)) return false;

    strcpy(word, line);
    return true;
}

void showStatistics(const char *text, int count) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);

    int length = (int)strlen(text);

    printf("\nText:\t\"%s\"\n", text);
    printf("Characters: %d\n", length);
    printf("Words: %d\n", count);

    printf("Letters: %d (%.1f%%)\n",
           letters, letters * 100.0 / length);

    printf("Digits: %d (%.1f%%)\n",
           digits, digits * 100.0 / length);

    printf("Spaces: %d (%.1f%%)\n",
           spaces, spaces * 100.0 / length);
}

void showTable(char **words, int count) {
    int longest = 0;
    int shortest = 0;
    int sum = 0;
    int width = 20;

    for (int i = 0; i < count; i++) {
        int len = (int)strlen(words[i]);
        sum += len;

        if (len > (int)strlen(words[longest])) {
            longest = i;
        }

        if (len < (int)strlen(words[shortest])) {
            shortest = i;
        }

        if (len > width) width = len;
    }

    printf("\n--- WORD TABLE ---\n");
    printf("%3s | %-*s | %6s\n",
           "No.", width, "Word", "Length");

    for (int i = 0; i < count; i++) {
        printf("%3d | %-*s | %6zu\n",
               i + 1, width, words[i], strlen(words[i]));
    }

    printf("Longest word: %s\n", words[longest]);
    printf("Shortest word: %s\n", words[shortest]);

    printf("Average word length: %.2f\n",
           (double)sum / count);

    char **sorted = new char*[256];

    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) {
                char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("\nWords in alphabetical order:\n");

    for (int i = 0; i < count; i++) {
        printf("%s\n", sorted[i]);
    }

    int mostFrequent = 0;
    int maxFrequency = 0;
    int i = 0;

    while (i < count) {
        int frequency = 1;

        while (i + frequency < count &&
               strcmp(sorted[i], sorted[i + frequency]) == 0) {
            frequency++;
        }

        if (frequency > maxFrequency) {
            maxFrequency = frequency;
            mostFrequent = i;
        }

        i += frequency;
    }

    printf("Most frequent word: %s (%d times)\n",
           sorted[mostFrequent], maxFrequency);

    delete[] sorted;
}

void replaceWord(char text[256], char **&words, int &count) {
    char from[32], to[32];

    printf("Word to replace (max 31 characters): ");

    if (!readWord(from)) {
        printf("Invalid search word. Text unchanged.\n");
        return;
    }

    printf("New word (max 31 characters): ");

    if (!readWord(to)) {
        printf("Invalid replacement word. Text unchanged.\n");
        return;
    }

    string updated = text;
    string oldWord = from;
    string newWord = to;

    int replacements = 0;
    size_t pos = updated.find(oldWord);

    while (pos != string::npos) {
        size_t end = pos + oldWord.length();

        bool left = (pos == 0 ||
                     updated[pos - 1] == ' ');

        bool right = (end == updated.length() - 1 ||
                      (end < updated.length() &&
                       updated[end] == ' '));

        if (left && right) {
            updated.replace(pos, oldWord.length(), newWord);
            replacements++;

            pos = updated.find(oldWord,
                               pos + newWord.length());
        } else {
            pos = updated.find(oldWord, pos + 1);
        }
    }

    if (updated.length() > 255) {
        printf("Error: result exceeds 255 characters. Text unchanged.\n");
        return;
    }

    printf("Replacements: %d\n", replacements);
    printf("Before: %s\n", text);
    printf("After: %s\n", updated.c_str());
    printf("New length: %zu\n", updated.length());

    strcpy(text, updated.c_str());

    freeWords(words, count);
    words = splitWords(text, count);
}

void compareWords() {
    char a[32], b[32];

    printf("First word (max 31 characters): ");

    if (!readWord(a)) {
        printf("Invalid first word.\n");
        return;
    }

    printf("Second word (max 31 characters): ");

    if (!readWord(b)) {
        printf("Invalid second word.\n");
        return;
    }

    int result = strcmp(a, b);

    if (result < 0) {
        printf("strcmp: -1 (first comes before second)\n");
    } else if (result > 0) {
        printf("strcmp: 1 (first comes after second)\n");
    } else {
        printf("strcmp: 0 (words are equal)\n");
    }

    string first = a;
    string second = b;

    if (first == second) {
        printf("string ==: equal\n");
    } else {
        printf("string ==: different\n");
    }

    char lowA[32], lowB[32];
    strcpy(lowA, a);
    strcpy(lowB, b);

    for (int i = 0; lowA[i] != '\0'; i++) {
        lowA[i] = (char)tolower((unsigned char)lowA[i]);
    }

    for (int i = 0; lowB[i] != '\0'; i++) {
        lowB[i] = (char)tolower((unsigned char)lowB[i]);
    }

    if (strcmp(lowA, lowB) == 0) {
        printf("Case-insensitive: equal\n");
    } else {
        printf("Case-insensitive: different\n");
    }

    printf("First length: %zu\n", first.length());
    printf("Second length: %zu\n", second.length());

    string joined = first + " & " + second;

    printf("Concatenation: %s\n", joined.c_str());
    printf("Concatenation length: %zu\n", joined.length());
}

void characterInfo(const char *text) {
    char c;

    printf("Enter one character (space is allowed): ");

    if (scanf("%c", &c) != 1) {
        printf("Invalid character.\n");
        return;
    }

    if (c == '\n') {
        printf("Enter exactly one ASCII character.\n");
        return;
    }

    int ch = getchar();

    if (ch == '\r') ch = getchar();

    if (c == '\r' || (ch != '\n' && ch != EOF) ||
        (unsigned char)c > 127) {

        while (ch != '\n' && ch != EOF) {
            ch = getchar();
        }

        printf("Enter exactly one ASCII character.\n");
        return;
    }

    unsigned char code = (unsigned char)c;

    printf("Character: '%c'\n", c);
    printf("Decimal: %u\n", (unsigned int)code);
    printf("Hexadecimal: %X\n", (unsigned int)code);
    printf("Octal: %o\n", (unsigned int)code);

    printf("Binary: ");

    for (int bit = 7; bit >= 0; bit--) {
        printf("%d", (code >> bit) & 1);
    }

    printf("\n");

    if (isupper(code)) {
        printf("Type: uppercase letter\n");
        printf("Opposite case: %c\n", tolower(code));
        printf("Next character: %c\n", c + 1);

    } else if (islower(code)) {
        printf("Type: lowercase letter\n");
        printf("Opposite case: %c\n", toupper(code));
        printf("Next character: %c\n", c + 1);

    } else if (isdigit(code)) {
        printf("Type: digit\n");
        printf("Numeric value: %d\n", c - '0');

    } else if (isspace(code)) {
        printf("Type: whitespace\n");

    } else {
        printf("Type: other character\n");
    }

    int occurrences = 0;
    const char *p = text;

    while (*p != '\0') {
        if (*p == c) occurrences++;
        p++;
    }

    printf("Occurrences: %d\n", occurrences);

    const char *first = strchr(text, c);

    if (first != NULL) {
        printf("First position: %d\n",
               (int)(first - text) + 1);
    } else {
        printf("Character not found in text.\n");
    }
}

void enterNewSentence(char text[256],
                      char **&words, int &count) {
    printf("Enter a new sentence (end with a period):\n");

    string sentence = "";
    string word;

    int readCount = 0;
    bool finished = false;
    bool tooLong = false;

    while (cin >> word) {
        readCount++;

        if (sentence.length() + word.length() +
            (sentence.length() == 0 ? 0 : 1) > 255) {
            tooLong = true;
        }

        if (!tooLong) {
            if (sentence.length() > 0) {
                sentence += " ";
            }

            sentence += word;
        }

        if (word[word.length() - 1] == '.') {
            finished = true;
            break;
        }
    }

    if (finished) {
        int ch = cin.get();

        while (ch != '\n' && ch != EOF) {
            ch = cin.get();
        }
    }

    if (!finished || tooLong ||
        !validText(sentence.c_str())) {

        printf("Invalid new sentence. Text unchanged.\n");
        return;
    }

    strcpy(text, sentence.c_str());

    freeWords(words, count);
    words = splitWords(text, count);

    printf("Words read: %d\n", readCount);
    printf("New text: %s\n", text);
    printf("New length: %zu\n", sentence.length());
}

int main() {
    char text[256];

    printf("Enter a message (max 255 characters, ending with a period):\n");

    if (fgets(text, 256, stdin) == NULL) {
        printf("Invalid text.\n");
        return 1;
    }

    int length = (int)strlen(text);

    if (strchr(text, '\n') == NULL && length == 255) {
        int ch = getchar();

        if (ch == '\r') ch = getchar();

        if (ch != '\n' && ch != EOF) {
            printf("Invalid text: more than 255 characters.\n");
            return 1;
        }
    }

    if (length > 0 && text[length - 1] == '\n') {
        text[--length] = '\0';
    }

    if (length > 0 && text[length - 1] == '\r') {
        text[--length] = '\0';
    }

    if (!validText(text)) {
        printf("Invalid text. Use Latin letters, digits, spaces and a final period.\n");
        return 1;
    }

    int count = 0;
    char **words = splitWords(text, count);

    int choice = -1;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Show text and statistics\n");
        printf("2. Show word table\n");
        printf("3. Replace a word\n");
        printf("4. Compare two words\n");
        printf("5. Character information\n");
        printf("6. Enter a new sentence\n");
        printf("0. Exit\n");
        printf("Choose an option: ");

        int result = scanf("%1d", &choice);
        bool extra = false;
        int ch = getchar();

        while (ch != '\n' && ch != EOF) {
            if (ch != ' ' && ch != '\t' && ch != '\r') {
                extra = true;
            }

            ch = getchar();
        }

        if (result == EOF) break;

        if (result != 1 || extra ||
            choice < 0 || choice > 6) {
            printf("Invalid option.\n");
            continue;
        }

        switch (choice) {
            case 1:
                showStatistics(text, count);
                break;

            case 2:
                showTable(words, count);
                break;

            case 3:
                replaceWord(text, words, count);
                break;

            case 4:
                compareWords();
                break;

            case 5:
                characterInfo(text);
                break;

            case 6:
                enterNewSentence(text, words, count);
                break;

            case 0:
                printf("Goodbye!\n");
                break;
        }

    } while (choice != 0);

    freeWords(words, count);
    return 0;
}
