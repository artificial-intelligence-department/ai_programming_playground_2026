/*
    Лабораторна робота. Редактор текстового повідомлення.
    Гончаренко Семен
    ШІ-11
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>
using namespace std;

const int MAX_LEN = 255;

bool isValidText(const char *s) {
    int len = strlen(s);
    if (len < 2 || len > MAX_LEN) {
        return 0;
    }
    if (s[len - 1] != '.') {
        return 0;
    }
    bool hasWord = 0;
    for (const char *p = s; p < s + len - 1; p++) {
        if (isalnum((unsigned char)*p) != 0) {
            hasWord = 1;
        }
        else if (*p != ' ') {
            return 0;
        }
    }
    return hasWord;
}

bool isValidWord(const char *w) {
    int len = strlen(w);
    if (len == 0 || len > 31) {
        return 0;
    }
    for (const char *p = w; *p != '\0'; p++) {
        if (isalnum((unsigned char)*p) == 0) {
            return 0;
        }
    }
    return 1;
}

void readText(char *text) {
    if (fgets(text, MAX_LEN + 1, stdin) == NULL) {
        text[0] = '\0';
        return;
    }
    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }
    else if (len == MAX_LEN) {
        int ch = getchar();
        if (ch != EOF && ch != '\n') {
            while (ch != EOF && ch != '\n') {
                ch = getchar();
            }
            text[0] = '\0';
            return;
        }
    }
    len = strlen(text);
    if (len > 0 && text[len - 1] == '\r') {
        text[len - 1] = '\0';
    }
}

bool readWord(const char *prompt, char *out) {
    char line[128];
    char buf[64];
    printf("%s", prompt);
    if (fgets(line, sizeof(line), stdin) == NULL || sscanf(line, "%63s", buf) != 1) {
        printf("Помилка: слово не введено.\n");
        return 0;
    }
    if (isValidWord(buf) == 0) {
        printf("Помилка: слово має містити латинські літери та цифри й бути довжиною до 31 символу.\n");
        return 0;
    }
    strcpy(out, buf);
    return 1;
}

char **splitWords(const char *text, int &count) {
    char buf[MAX_LEN + 1];
    strcpy(buf, text);
    int len = strlen(buf);
    if (len > 0 && buf[len - 1] == '.') {
        buf[len - 1] = '\0';
    }

    count = 0;
    for (char *t = strtok(buf, " "); t != NULL; t = strtok(NULL, " ")) {
        count++;
    }

    char **words = new char *[count];

    strcpy(buf, text);
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '.') {
        buf[len - 1] = '\0';
    }

    int i = 0;
    for (char *t = strtok(buf, " "); t != NULL; t = strtok(NULL, " ")) {
        words[i] = new char[strlen(t) + 1];
        strcpy(words[i], t);
        i++;
    }
    return words;
}

void freeWords(char **&words, int &count) {
    if (words != NULL) {
        for (int i = 0; i < count; i++) {
            delete[] words[i];
        }
        delete[] words;
        words = NULL;
    }
    count = 0;
}

void rebuildWords(const char *text, char **&words, int &count) {
    freeWords(words, count);
    words = splitWords(text, count);
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    for (const char *p = text; *p != '\0'; p++) {
        if (isalpha((unsigned char)*p) != 0) {
            letters++;
        }
        else if (isdigit((unsigned char)*p) != 0) {
            digits++;
        }
        else if (*p == ' ') {
            spaces++;
        }
    }
}

void printStats(const char *text, int wordCount) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int len = strlen(text);
    printf("Текст: \"%s\"\n", text);
    printf("Символів: %d\n", len);
    printf("Слів: %d\n", wordCount);
    printf("Літер: %d (%5.1f%%)\n", letters, 100.0 * letters / len);
    printf("Цифр: %d (%5.1f%%)\n", digits, 100.0 * digits / len);
    printf("Пробілів: %d (%5.1f%%)\n", spaces, 100.0 * spaces / len);
}

void sortPointers(const char **arr, int n) {
    for (int i = 1; i < n; i++) {
        const char *key = arr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printTable(char **words, int count) {
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    int total = 0;
    int longest = 0;
    int shortest = 0;
    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);
        total += len;
        if (len > (int)strlen(words[longest])) {
            longest = i;
        }
        if (len < (int)strlen(words[shortest])) {
            shortest = i;
        }
    }
    printf("+----+-----------------+-------+\n");
    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)total / count);

    const char **sorted = new const char *[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }
    sortPointers(sorted, count);

    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    // після сортування однакові слова стоять поруч
    int bestIndex = 0;
    int bestCount = 0;
    int i = 0;
    while (i < count) {
        int j = i;
        while (j < count && strcmp(sorted[j], sorted[i]) == 0) {
            j++;
        }
        if (j - i > bestCount) {
            bestCount = j - i;
            bestIndex = i;
        }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[bestIndex], bestCount);
    delete[] sorted;
}

void replaceWord(char *text, char **&words, int &count) {
    char from[64];
    char to[64];
    if (readWord("Замінити слово: ", from) == 0) {
        return;
    }
    if (readWord("На слово: ", to) == 0) {
        return;
    }

    string s(text);
    string f(from);
    string t(to);
    int replaced = 0;
    size_t pos = 0;
    while ((pos = s.find(f, pos)) != string::npos) {
        size_t end = pos + f.length();
        bool leftOk = (pos == 0 || isalnum((unsigned char)s[pos - 1]) == 0);
        bool rightOk = (end == s.length() || isalnum((unsigned char)s[end]) == 0);
        if (leftOk == 1 && rightOk == 1) {
            s.replace(pos, f.length(), t);
            pos += t.length();
            replaced++;
        }
        else {
            pos += f.length();
        }
    }

    if (replaced == 0) {
        printf("Такого слова немає в тексті, текст не змінено.\n");
        return;
    }
    if ((int)s.length() > MAX_LEN) {
        printf("Помилка: результат перевищує 255 символів, текст не змінено.\n");
        return;
    }

    printf("Замін виконано: %d\n", replaced);
    printf("Було: \"%s\"\n", text);
    printf("Стало: \"%s\"\n", s.c_str());
    printf("Нова довжина: %d\n", (int)s.length());

    strcpy(text, s.c_str());
    rebuildWords(text, words, count);
}

string toLowerStr(const string &s) {
    string r = s;
    for (size_t i = 0; i < r.length(); i++) {
        r[i] = tolower((unsigned char)r[i]);
    }
    return r;
}

void compareWords() {
    char a[64];
    char b[64];
    if (readWord("Перше слово: ", a) == 0) {
        return;
    }
    if (readWord("Друге слово: ", b) == 0) {
        return;
    }

    int c = strcmp(a, b);
    int sign = 0;
    const char *meaning = "слова однакові";
    if (c < 0) {
        sign = -1;
        meaning = "перше слово менше";
    }
    else if (c > 0) {
        sign = 1;
        meaning = "перше слово більше";
    }
    printf("strcmp: %d -> %s\n", sign, meaning);

    string sa(a);
    string sb(b);
    if (sa == sb) {
        printf("Рівні (==): так\n");
    }
    else {
        printf("Рівні (==): ні\n");
    }
    if (toLowerStr(sa) == toLowerStr(sb)) {
        printf("Рівні без урахування регістру: так\n");
    }
    else {
        printf("Рівні без урахування регістру: ні\n");
    }
    printf("Довжини: %d і %d\n", (int)sa.length(), (int)sb.length());
    string joined = sa + " & " + sb;
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}

void charInfo(const char *text) {
    char line[128];
    printf("Введіть символ: ");
    if (fgets(line, sizeof(line), stdin) == NULL || line[0] == '\n' || line[0] == '\0') {
        printf("Помилка: символ не введено.\n");
        return;
    }
    unsigned char c = (unsigned char)line[0];

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", c, c, c);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (c >> i) & 1);
    }
    printf(")\n");

    if (isupper(c) != 0) {
        printf("Тип: велика літера\n");
    }
    else if (islower(c) != 0) {
        printf("Тип: мала літера\n");
    }
    else if (isdigit(c) != 0) {
        printf("Тип: цифра\n");
    }
    else if (isspace(c) != 0) {
        printf("Тип: пробільний символ\n");
    }
    else {
        printf("Тип: інший символ\n");
    }

    if (isalpha(c) != 0) {
        int other = toupper(c);
        if (isupper(c) != 0) {
            other = tolower(c);
        }
        printf("Інший регістр: '%c'\n", other);
        printf("Наступний символ: '%c'\n", c + 1);
    }

    int occurrences = 0;
    for (const char *p = text; *p != '\0'; p++) {
        if ((unsigned char)*p == c) {
            occurrences++;
        }
    }
    if (occurrences == 0) {
        printf("У тексті не зустрічається\n");
    }
    else {
        int first = strchr(text, c) - text + 1;
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, first);
    }
}

void newSentence(char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");
    string result;
    string w;
    int n = 0;
    while (cin >> w) {
        if (n > 0) {
            result += ' ';
        }
        result += w;
        n++;
        if (w[w.length() - 1] == '.') {
            break;
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');

    if ((int)result.length() > MAX_LEN || isValidText(result.c_str()) == 0) {
        printf("Помилка: речення некоректне, текст не змінено.\n");
        return;
    }
    strcpy(text, result.c_str());
    rebuildWords(text, words, count);
    printf("Прочитано слів: %d\n", n);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

void printMenu() {
    printf("\n=====РЕДАКТОР ТЕКСТОВОГО ПОВІДОМЛЕННЯ=====\n");
    printf("1 - Показати текст і статистику\n");
    printf("2 - Таблиця слів\n");
    printf("3 - Замінити слово\n");
    printf("4 - Порівняти два слова\n");
    printf("5 - Інформація про символ\n");
    printf("6 - Ввести нове речення\n");
    printf("0 - Вийти\n");
    printf("========================================\n");
    printf("Ваш вибір: ");
}

int main() {
    char text[MAX_LEN + 1];
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    readText(text);
    if (isValidText(text) == 0) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 0;
    }

    int count = 0;
    char **words = splitWords(text, count);

    int choice = 0;
    char line[64];
    do {
        printMenu();
        choice = -1;
        if (fgets(line, sizeof(line), stdin) == NULL) {
            choice = 0;
        }
        else if (sscanf(line, "%d", &choice) != 1) {
            choice = -1;
        }

        switch (choice) {
            case 0:
                printf("Завершення програми...\n");
                break;
            case 1:
                printStats(text, count);
                break;
            case 2:
                printTable(words, count);
                break;
            case 3:
                replaceWord(text, words, count);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                charInfo(text);
                break;
            case 6:
                newSentence(text, words, count);
                break;
            default:
                printf("Помилка: введіть номер пункту меню від 0 до 6.\n");
                break;
        }
    } while (choice != 0);
    freeWords(words, count);

    return 0;
}