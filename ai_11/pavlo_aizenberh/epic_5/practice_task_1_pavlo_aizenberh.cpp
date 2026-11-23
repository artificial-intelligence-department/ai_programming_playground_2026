#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>
using namespace std;

bool isValid(const char text[]) {
    int len = strlen(text);
    if (len < 2 || text[len - 1] != '.') return false;

    bool hasWord = false;
    for (int i = 0; i < len - 1; i++) {
        char c = text[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            hasWord = true;
        } else if (c != ' ') {
            return false;
        }
    }
    return hasWord;
}

char** splitWords(const char* text, int& count) {
    char copy[256];
    strcpy(copy, text);
    count = 0;

    char* token = strtok(copy, " .");
    while (token != NULL) {
        count++;
        token = strtok(NULL, " .");
    }

    char** words = new char*[count];
    strcpy(copy, text);
    token = strtok(copy, " .");

    for (int i = 0; i < count; i++) {
        words[i] = new char[strlen(token) + 1];
        strcpy(words[i], token);
        token = strtok(NULL, " .");
    }
    return words;
}

void freeWords(char**& words, int& count) {
    for (int i = 0; i < count; i++) delete[] words[i];
    delete[] words;
    words = NULL;
    count = 0;
}
 
void countChars(const char* text, int& letters, int& digits, int& spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    for (const char* p = text; *p != '\0'; p++) {
        unsigned char c = *p;
        if (isalpha(c)) letters++;
        else if (isdigit(c)) digits++;
        else if (c == ' ') spaces++;
    }
}

void showStats(const char text[], int count) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int len = strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %d\n", len);
    printf("Слів: %d\n", count);
    printf("Літер: %d (%.1f%%)\n", letters, 100.0 * letters / len);
    printf("Цифр: %d (%.1f%%)\n", digits, 100.0 * digits / len);
    printf("Пробілів: %d (%.1f%%)\n", spaces, 100.0 * spaces / len);
}


void quickSort(char* words[], int left, int right) {
    int i = left;
    int j = right;
    char* pivot = words[(left + right) / 2];

    while (i <= j) {
        while (strcmp(words[i], pivot) < 0) {
            i++;
        }

        while (strcmp(words[j], pivot) > 0) {
            j--;
        }

        if (i <= j) {
            char* temp = words[i];
            words[i] = words[j];
            words[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort(words, left, j);
    }

    if (i < right) {
        quickSort(words, i, right);
    }
}


void showWords(char** words, int count) {
    int longest = 0, shortest = 0, sum = 0;
    printf("+-----+------------------+-------+\n");
    printf("| N   | Слово            | Довж. |\n");
    printf("+-----+------------------+-------+\n");
    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        printf("| %3d | %-16s | %5d |\n", i + 1, words[i], len);
        sum += len;
        if (len > (int)strlen(words[longest])) longest = i;
        if (len < (int)strlen(words[shortest])) shortest = i;
    }
    printf("+-----+------------------+-------+\n");
    printf("Найдовше слово: %s (%zu)\n", words[longest], strlen(words[longest]));
    printf("Найкоротше слово: %s (%zu)\n", words[shortest], strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)sum / count);

    char** sorted = new char*[count];
    for (int i = 0; i < count; i++) sorted[i] = words[i];

    quickSort(sorted, 0, count - 1);

    printf("За абеткою:");
    for (int i = 0; i < count; i++) printf(" %s", sorted[i]);
    printf("\n");

    int best = 0, bestCount = 0;
    for (int i = 0; i < count;) {
        int j = i + 1;
        while (j < count && strcmp(sorted[i], sorted[j]) == 0) j++;
        if (j - i > bestCount) {
            bestCount = j - i;
            best = i;
        }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[best], bestCount);
    delete[] sorted;
}

bool validWord(const char word[]) {
    if (word[0] == '\0') return false;
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) return false;
    }
    return true;
}

void replaceWord(char text[], char**& words, int& count) {
    char from[32], to[32];
    printf("Замінити слово: ");
    if (scanf("%31s", from) != 1) return;
    printf("На слово: ");
    if (scanf("%31s", to) != 1) return;

    if (!validWord(from) || !validWord(to)) {
        printf("Помилка: слово має містити лише латинські літери та цифри.\n");
        return;
    }

    string before = text;
    string after = before;
    size_t pos = 0;
    int replacements = 0;

    while ((pos = after.find(from, pos)) != string::npos) {
        bool leftOk = (pos == 0 || after[pos - 1] == ' ');
        size_t end = pos + strlen(from);
        bool rightOk = (end == after.length() || after[end] == ' ' || after[end] == '.');

        if (leftOk && rightOk) {
            after.replace(pos, strlen(from), to);
            replacements++;
            pos += strlen(to);
        } else {
            pos += strlen(from);
        }
    }

    if (after.length() > 255) {
        printf("Помилка: новий текст довший за 255 символів.\n");
        return;
    }

    strcpy(text, after.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Замін виконано: %d\n", replacements);
    printf("Було: \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %zu\n", after.length());
}

void compareWords() {
    char first[32], second[32];
    printf("Перше слово: ");
    if (scanf("%31s", first) != 1) return;
    printf("Друге слово: ");
    if (scanf("%31s", second) != 1) return;

    if (!validWord(first) || !validWord(second)) {
        printf("Помилка: некоректне слово.\n");
        return;
    }

    int result = strcmp(first, second);
    if (result < 0) result = -1;
    else if (result > 0) result = 1;

    string a = first, b = second;
    string lowerA = a, lowerB = b;
    for (int i = 0; i < (int)a.length(); i++) lowerA[i] = tolower((unsigned char)a[i]);
    for (int i = 0; i < (int)b.length(); i++) lowerB[i] = tolower((unsigned char)b[i]);
    string combined = a + " & " + b;

    printf("strcmp: %d -> %s\n", result, result < 0 ? "перше слово менше" : result > 0 ? "перше слово більше" : "слова рівні");
    printf("Рівні (==): %s\n", a == b ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", lowerA == lowerB ? "так" : "ні");
    printf("Довжини: %zu і %zu\n", a.length(), b.length());
    printf("Конкатенація: \"%s\" (%zu)\n", combined.c_str(), combined.length());
}

void showCharacter(const char text[]) {
    char c;
    printf("Введіть символ: ");
    if (scanf("%c", &c) != 1) return;
    unsigned char code = c;

    printf("Символ: '%c'\n", c);
    printf("Код: %u (hex 0x%x, oct 0%o, bin ", code, code, code);
    for (int i = 7; i >= 0; i--) printf("%d", (code >> i) & 1);
    printf(")\n");

    if (isupper(code)) printf("Тип: велика літера\n");
    else if (islower(code)) printf("Тип: мала літера\n");
    else if (isdigit(code)) printf("Тип: цифра\n");
    else if (isspace(code)) printf("Тип: пробільний символ\n");
    else printf("Тип: інший символ\n");

    if (isalpha(code)) {
        printf("Інший регістр: '%c'\n", isupper(code) ? tolower(code) : toupper(code));
    }
    if (code < 127) printf("Наступний символ: '%c'\n", code + 1);
    else printf("Наступний символ: немає в ASCII\n");

    int amount = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == c) amount++;
    }
    const char* first = strchr(text, c);
    if (first != NULL) printf("Входжень у тексті: %d, перше на позиції %td\n", amount, first - text + 1);
    else printf("У тексті символ відсутній.\n");
}

void newSentence(char text[], char**& words, int& count) {
    string sentence, word;
    int readCount = 0;
    bool finished = false;

    printf("Введіть речення (крапка після останнього слова):\n");
    while (cin >> word) {
        if (!sentence.empty()) sentence += " ";
            sentence += word;
            readCount++;
        if (word[word.length() - 1] == '.') {
            finished = true;
            break;
        }
    }

    if (!finished || sentence.length() > 255 || !isValid(sentence.c_str())) {
        printf("Помилка: некоректне речення.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", readCount);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", sentence.length());
}


int main() {
    char text[256];

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");

    if (fgets(text, sizeof(text), stdin) == NULL) return 1;

    char* newline = strchr(text, '\n');
    if (newline != NULL) *newline = '\0';

    if (!isValid(text)) {
        printf("Помилка: некоректний текст.\n");
        return 1;
    }

    int count = 0;
    char** words = splitWords(text, count);
    int choice;

    while (true) {
        printf("\n1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\n");
        printf("Ваш вибір: ");

        int result = scanf("%d", &choice);

        if (result == EOF) break;

        if (result != 1) {
            printf("Помилка: введіть номер пункту меню.\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}

            continue;
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}

        switch (choice) {
            case 0:
                freeWords(words, count);
                return 0;

            case 1:
                showStats(text, count);
                break;

            case 2:
                showWords(words, count);
                break;

            case 3:
                replaceWord(text, words, count);
                break;

            case 4:
                compareWords();
                break;

            case 5:
                showCharacter(text);
                break;

            case 6:
                newSentence(text, words, count);
                break;

            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);
                break;
        }
    }

    freeWords(words, count);

    return 0;
}
