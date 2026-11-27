#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
using namespace std;
char** splitWords(const char* text, int &count) {
    char copy[256];
    strcpy(copy, text);
    count = 0;
    char* word = strtok(copy, " .");
    while (word != nullptr) {
        count++;
        word = strtok(nullptr, " .");
    }
    char** words = new char*[count];
    strcpy(copy, text);
    word = strtok(copy, " .");
    for (int i = 0; i < count; i++) {
        int length = strlen(word);
        words[i] = new char[length + 1];
        strcpy(words[i], word);
        word = strtok(nullptr, " .");
    }
    return words;
}
void freeWords(char** &words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}
void countChars(const char* text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    const char* p = text;
    while (*p != '\0') {
        if (isalpha(*p)) {
            letters++;
        }
        else if (isdigit(*p)) {
            digits++;
        }
        else if (*p == ' ') {
            spaces++;
        }
        p++;
    }
}

void showStats(const char* text, int count) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int length = strlen(text);
    printf("Text:\t\"%s\"\n", text);
    printf("%-12s %3d\n", "Characters:", length);
    printf("%-12s %3d\n", "Words:", count);
    printf("%-12s %3d (%5.1f%%)\n", "Letters:", letters, letters * 100.0 / length);
    printf("%-12s %3d (%5.1f%%)\n", "Digits:", digits, digits * 100.0 / length);
    printf("%-12s %3d (%5.1f%%)\n", "Spaces:", spaces, spaces * 100.0 / length);
}
void printLine(int width) {
    printf("+-----+");
    for (int i = 0; i < width + 2; i++) {
        printf("-");
    }
    printf("+--------+\n");
}
void showWordTable(char** words, int count) {
    int longest = 0;
    int shortest = 0;
    int total = 0;
    int width = 16;
    int longestLength = 0;
    int shortestLength = 256;
    for (int i = 0; i < count; i++) {
        int length = strlen(words[i]);
        total += length;
        if (length > longestLength) {
            longest = i;
            longestLength = length;
        }
        if (length < shortestLength) {
            shortest = i;
            shortestLength = length;
        }
        if (length > width) {
            width = length;
        }
    }
    printLine(width);
    printf("|   N | %-*s | %6s |\n", width, "Word", "Length");
    printLine(width);
    for (int i = 0; i < count; i++) {
        int length = strlen(words[i]);
        printf("| %3d | %-*s | %6d |\n", i + 1, width, words[i], length);
    }
    printLine(width);
    printf("Longest word: %s (%d)\n", words[longest], longestLength);
    printf("Shortest word: %s (%d)\n", words[shortest], shortestLength);
    printf("Average length: %.2f\n", (double)total / count);
    char** sortedWords = new char*[count];
    for (int i = 0; i < count; i++) {
        sortedWords[i] = words[i];
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(sortedWords[j], sortedWords[j + 1]) > 0) {
                char* temp = sortedWords[j];
                sortedWords[j] = sortedWords[j + 1];
                sortedWords[j + 1] = temp;
            }
        }
    }
    printf("Alphabetical order: ");
    for (int i = 0; i < count; i++) {
        printf("%s", sortedWords[i]);
        if (i < count - 1) {
            printf(" ");
        }
    }
    printf("\n");
    int maxCount = 0;
    char* commonWord = sortedWords[0];
    for (int i = 0; i < count;) {
        int times = 1;
        while (i + times < count && strcmp(sortedWords[i], sortedWords[i + times]) == 0) {
            times++;
        }
        if (times > maxCount) {
            maxCount = times;
            commonWord = sortedWords[i];
        }
        i += times;
    }
    printf("Most frequent word: %s (%d)\n", commonWord, maxCount);
    delete[] sortedWords;
}
bool validWord(const char* word) {
    if (word[0] == '\0') {
        return false;
    }
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        bool letter = false;
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            letter = true;
        }
        bool digit = false;
        if (c >= '0' && c <= '9') {
            digit = true;
        }
        if (!letter && !digit) {
            return false;
        }
    }
    return true;
}
bool validText(const char* text) {
    int length = strlen(text);
    if (length < 2 || length > 255 || text[length - 1] != '.') {
        return false;
    }
    if (text[length - 2] == ' ') {
        return false;
    }
    bool found = false;
    for (int i = 0; i < length - 1; i++) {
        char c = text[i];
        bool letter = false;
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            letter = true;
        }
        bool digit = false;
        if (c >= '0' && c <= '9') {
            digit = true;
        }
        if (letter || digit) {
            found = true;
        }
        else if (c != ' ') {
            return false;
        }
    }
    return found;
}
bool readWord(char word[32]) {
    if (scanf("%31s", word) != 1) {
        return false;
    }
    char c;
    if (scanf("%c", &c) != 1) {
        return true;
    }
    if (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
        return true;
    }
    while (c != ' ' && c != '\n' && c != '\t' && c != '\r') {
        if (scanf("%c", &c) != 1) {
            break;
        }
    }
    return false;
}
void replaceWord(char text[256], char** &words, int &count) {
    char from[32], to[32];
    printf("Replace word: ");
    if (!readWord(from) || !validWord(from)) {
        printf("Error: invalid word to replace.\n");
        return;
    }
    printf("With word: ");
    if (!readWord(to) || !validWord(to)) {
        printf("Error: invalid replacement word.\n");
        return;
    }
    char oldText[256];
    strcpy(oldText, text);
    string newText = text;
    string oldWord = from;
    string newWord = to;
    int oldLength = oldWord.length();
    int newLength = newWord.length();
    unsigned int position = 0;
    int changes = 0;
    unsigned int length = newText.length();
    while (position + oldLength <= length) {
        if (newText.find(oldWord, position) == position) {
            unsigned int end = position + oldLength;
            bool startsWord = position == 0 || newText[position - 1] == ' ';
            bool endsWord = end == length || newText[end] == ' ' || newText[end] == '.';
            if (startsWord && endsWord) {
                if (length - oldLength + newLength > 255) {
                    printf("Error: text would exceed 255 characters.\n");
                    return;
                }
                newText.replace(position, oldLength, newWord);
                changes++;
                length = newText.length();
                position += newLength;
            }
            else {
                position++;
            }
        }
        else {
            position++;
        }
    }
    if (changes > 0) {
        for (unsigned int i = 0; i < length; i++) {
            text[i] = newText[i];
        }
        text[length] = '\0';
        freeWords(words, count);
        words = splitWords(text, count);
    }
    printf("Replacements: %d\n", changes);
    printf("Before: \"%s\"\n", oldText);
    printf("After: \"%s\"\n", text);
    printf("New length: %d\n", (int)strlen(text));
}
void compareWords() {
    char a[32], b[32];
    printf("First word: ");
    if (!readWord(a) || !validWord(a)) {
        printf("Error: invalid first word.\n");
        return;
    }
    printf("Second word: ");
    if (!readWord(b) || !validWord(b)) {
        printf("Error: invalid second word.\n");
        return;
    }
    int compare = strcmp(a, b);
    if (compare < 0) {
        compare = -1;
    }
    else if (compare > 0) {
        compare = 1;
    }
    printf("strcmp: %d", compare);
    if (compare < 0) {
        printf(" -> first word is smaller\n");
    }
    else if (compare > 0) {
        printf(" -> first word is greater\n");
    }
    else {
        printf(" -> words are equal\n");
    }
    string first = a;
    string second = b;
    if (first == second) {
        printf("Equal (==): yes\n");
    }
    else {
        printf("Equal (==): no\n");
    }
    bool same = strlen(a) == strlen(b);
    if (same) {
        for (int i = 0; a[i] != '\0'; i++) {
            if (tolower(a[i]) != tolower(b[i])) {
                same = false;
                break;
            }
        }
    }
    if (same) {
        printf("Equal ignoring case: yes\n");
    }
    else {
        printf("Equal ignoring case: no\n");
    }
    printf("Lengths: %d and %d\n", (int)strlen(a), (int)strlen(b));
    string joined = first + " & " + second;
    printf("Concatenation: \"");
    int joinedLength = joined.length();
    for (int i = 0; i < joinedLength; i++) {
        printf("%c", joined[i]);
    }
    printf("\" (%d)\n", joinedLength);
}
void characterInfo(const char* text) {
    char c;
    printf("Enter character: ");
    if (scanf("%c", &c) != 1) {
        printf("Error: character input failed.\n");
        return;
    }
    char extra;
    bool valid = true;
    if (c != '\n') {
        while (scanf("%c", &extra) == 1 && extra != '\n') {
            if (extra != ' ' && extra != '\t' && extra != '\r') {
                valid = false;
            }
        }
    }
    if (!valid) {
        printf("Error: enter one character.\n");
        return;
    }
    unsigned int code = (unsigned char)c;
    printf("Character: '%c'\n", c);
    printf("Code: %u (hex 0x%02x, oct 0%o, bin ", code, code, code);
    for (int bit = 7; bit >= 0; bit--) {
        printf("%u", (code >> bit) & 1);
    }
    printf(")\n");
    if (isupper(code)) {
        printf("Type: uppercase letter\n");
        printf("Other case: '%c'\n", tolower(code));
    }
    else if (islower(code)) {
        printf("Type: lowercase letter\n");
        printf("Other case: '%c'\n", toupper(code));
    }
    else if (isdigit(code)) {
        printf("Type: digit\n");
    }
    else if (isspace(code)) {
        printf("Type: whitespace\n");
    }
    else {
        printf("Type: other character\n");
    }
    if (code == 255) {
        printf("Next character: not available\n");
    }
    else if (isprint(code + 1)) {
        printf("Next character: '%c'\n", code + 1);
    }
    else {
        printf("Next character: non-printable (code %u)\n", code + 1);
    }
    int times = 0;
    int first = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if ((unsigned char)text[i] == code) {
            times++;
            if (first == 0) {
                first = i + 1;
            }
        }
    }
    if (times > 0) {
        printf("Occurrences: %d, first at position %d\n", times, first);
    }
    else {
        printf("This character does not appear in the text.\n");
    }
}
void newSentence(char text[256], char** &words, int &count) {
    char sentence[256] = "";
    char word[256];
    int readCount = 0;
    bool valid = true;
    bool finished = false;
    printf("Enter a sentence (period after last word):\n");
    while (!finished) {
        cin.width(256);
        if (!(cin >> word)) {
            printf("Error: sentence input failed.\n");
            return;
        }
        readCount++;
        int length = strlen(word);
        if (length > 0 && word[length - 1] == '.') {
            finished = true;
        }
        if (valid) {
            int current = strlen(sentence);
            int space = 0;
            if (readCount > 1) {
                space = 1;
            }
            if (current + space + length > 255) {
                valid = false;
            }
            else {
                if (space == 1) {
                    strcat(sentence, " ");
                }
                strcat(sentence, word);
            }
        }
    }
    if (!valid || !validText(sentence)) {
        printf("Error: invalid sentence or text exceeds 255 characters.\n");
        return;
    }
    int newCount = 0;
    char** newWords = splitWords(sentence, newCount);
    freeWords(words, count);
    strcpy(text, sentence);
    words = newWords;
    count = newCount;
    printf("Words read: %d\n", readCount);
    printf("New text: \"%s\"\n", text);
    printf("Length: %d\n", (int)strlen(text));
}
int main() {
    char text[256];
    printf("Enter text (up to 255 characters, ending with a period):\n");
    if (fgets(text, 256, stdin) == nullptr) {
        printf("Error: input failed.\n");
        return 1;
    }
    char* newline = strchr(text, '\n');
    if (newline != nullptr) {
        *newline = '\0';
    }
    else if (strlen(text) == 255) {
        char extra;
        if (scanf("%c", &extra) == 1 && extra != '\n') {
            printf("Error: text is too long.\n");
            return 1;
        }
    }
    if (!validText(text)) {
        printf("Error: invalid text.\n");
        return 1;
    }
    int count = 0;
    char** words = splitWords(text, count);
    int choice;
    while (true) {
        printf("\n1. Text statistics\n");
        printf("2. Word table\n");
        printf("3. Replace word\n");
        printf("4. Compare words\n");
        printf("5. Character information\n");
        printf("6. New sentence\n");
        printf("0. Exit\n");
        printf("Your choice: ");
        int input = scanf("%d", &choice);
        if (input == EOF) {
            break;
        }
        bool valid = input == 1;
        char extra;
        while (scanf("%c", &extra) == 1 && extra != '\n') {
            if (extra != ' ' && extra != '\t' && extra != '\r') {
                valid = false;
            }
        }
        if (!valid) {
            printf("Error: enter a menu number.\n");
            continue;
        }
        if (choice == 0) {
            break;
        }
        switch (choice) {
            case 1:
                showStats(text, count);
                break;
            case 2:
                showWordTable(words, count);
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
                newSentence(text, words, count);
                break;
            default:
                printf("Error: option %d does not exist.\n", choice);
        }
    }
    freeWords(words, count);
    return 0;
}
           