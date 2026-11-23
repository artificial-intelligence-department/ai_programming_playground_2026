#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;

int readLine(char* buf, int size) {
    if (fgets(buf, size, stdin) == NULL) {
        return 0;
    }

    int len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
        return 1;
    }

    int extra = 0;
    int c = getchar();
    while (c != '\n' && c != EOF) {
        extra = 1;
        c = getchar();
    }

    if (extra) {
        return -1;
    }

    return 1;
}

bool isValidText(char* text) {
    int len = strlen(text);
    if (len < 2) {
        return false;
    }

    if (text[len - 1] != '.') {
        return false;
    }

    if (!isalnum((unsigned char)text[len - 2])) {
        return false;
    }

    int words = 0;
    bool inWord = false;
    for (int i = 0; i < len - 1; i++) {
        unsigned char ch = text[i];
        if (ch == ' ') {
            inWord = false;
        } else if (isalnum(ch)) {
            if (!inWord) {
                words++;
                inWord = true;
            }
        } else {
            return false;
        }
    }

    return words > 0;
}

bool isValidWord(char* w) {
    int len = strlen(w);
    if (len < 1 || len > 31) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (!isalnum((unsigned char)w[i])) {
            return false;
        }
    }

    return true;
}

bool parseSingleWord(char* line, char* word) {
    char* p = line;
    int len = 0;
    while (*p == ' ') {
        p++;
    }

    while (*p != '\0' && *p != ' ') {
        if (len >= 31) {
            return false;
        }
        word[len] = *p;
        len++;
        p++;
    }
    word[len] = '\0';
    while (*p == ' ') {
        p++;
    }

    if (*p != '\0') {
        return false;
    }

    return len > 0;
}

bool readWord(char* word) {
    char line[256];
    if (readLine(line, 256) != 1) {
        return false;
    }

    if (!parseSingleWord(line, word)) {
        return false;
    }

    return isValidWord(word);
}

// Розбиває текст на слова за допомогою strtok. Крапка в кінці не входить до слів.
char** splitWords(char* text, int &count) {
    int len = strlen(text);
    char* work = new char[len + 1];

    strcpy(work, text);
    work[len - 1] = '\0';
    count = 0;
    char* tok = strtok(work, " ");
    while (tok != NULL) {
        count++;
        tok = strtok(NULL, " ");
    }

    char** words = new char*[count];

    strcpy(work, text);
    work[len - 1] = '\0';
    int idx = 0;
    tok = strtok(work, " ");
    while (tok != NULL) {
        words[idx] = new char[strlen(tok) + 1];
        strcpy(words[idx], tok);
        idx++;
        tok = strtok(NULL, " ");
    }

    delete[] work;
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

// Рахує літери, цифри й пробіли, обходячи текст вказівником.
void countChars(char* text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    for (char* p = text; *p != '\0'; p++) {
        unsigned char ch = *p;
        if (isalpha(ch)) {
            letters++;
        } else if (isdigit(ch)) {
            digits++;
        } else if (ch == ' ') {
            spaces++;
        }
    }
}


void showStats(char* text, int wordCount) {
    int len = strlen(text);
    int letters = 0;
    int digits = 0;
    int spaces = 0;
    countChars(text, letters, digits, spaces);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:  %4d\n", len);
    printf("Слів:      %4d\n", wordCount);
    printf("Літер:     %4d (%5.1f%%)\n", letters, 100.0 * letters / len);
    printf("Цифр:      %4d (%5.1f%%)\n", digits, 100.0 * digits / len);
    printf("Пробілів:  %4d (%5.1f%%)\n", spaces, 100.0 * spaces / len);
}


void showWordTable(char** words, int count) {
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for (int i = 0; i < count; i++) {
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], (int)strlen(words[i]));
    }

    printf("+----+-----------------+-------+\n");

    int longest = 0;
    int shortest = 0;
    long total = 0;
    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        total += len;
        if (len > (int)strlen(words[longest])) {
            longest = i;
        }
        if (len < (int)strlen(words[shortest])) {
            shortest = i;
        }
    }

    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)total / count);

    
    char** sorted = new char*[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(sorted[j], sorted[i]) < 0) {
                char* tmp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = tmp;
            }
        }
    }

    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }

    printf("\n");

    int bestIndex = 0;
    int bestCount = 0;
    int i = 0;
    while (i < count) {
        int run = 1;
        while (i + run < count && strcmp(sorted[i], sorted[i + run]) == 0) {
            run++;
        }
        if (run > bestCount) {
            bestCount = run;
            bestIndex = i;
        }
        i += run;
    }

    printf("Найчастіше слово: %s (%d)\n", sorted[bestIndex], bestCount);

    delete[] sorted;
}
void replaceWord(const char* text) {
    char oldWord[32];
    char newWord[32];

    printf("Замінити слово: ");
    if (!readWord(oldWord)) {
        printf("Помилка: слово має складатися лише з латинських літер і цифр (до 31 символу).\n");
        return;
    }

    printf("На слово: ");
    if (!readWord(newWord)) {
        printf("Помилка: слово має складатися лише з латинських літер і цифр (до 31 символу).\n");
        printf("Текст не змінено.\n");
        return;
    }

    string source = text;
    string target = oldWord;
    string replacement = newWord;
    int replaced = 0;

    size_t pos = source.find(target);
    while (pos != string::npos) {
        size_t end = pos + target.length();
        bool startOk = (pos == 0) || (source[pos - 1] == ' ');
        bool endOk = (end == source.length()) || (source[end] == ' ') || (source[end] == '.');
        if (startOk && endOk) {
            source.replace(pos, target.length(), replacement);
            replaced++;
            pos += replacement.length();
        } else {
            pos++;
        }
        pos = source.find(target, pos);
    }

    if (replaced == 0) {
        printf("Замін виконано: 0. Текст не змінено.\n");
        return;
    }

    if (source.length() > 255) {
        printf("Помилка: результат перевищує 255 символів, текст не змінено.\n");
        return;
    }

    printf("Замін виконано: %d\n", replaced);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", source.c_str());
    printf("Нова довжина: %d\n", (int)source.length());
}
void comparePair() {
    char first[32];
    char second[32];

    printf("Перше слово: ");
    if (!readWord(first)) {
        printf("Помилка: слово має складатися лише з латинських літер і цифр (до 31 символу).\n");
        return;
    }

    printf("Друге слово: ");
    if (!readWord(second)) {
        printf("Помилка: слово має складатися лише з латинських літер і цифр (до 31 символу).\n");
        return;
    }

    int result = strcmp(first, second);
    int sign = 0;
    if (result < 0) {
        sign = -1;
    } else if (result > 0) {
        sign = 1;
    }

    printf("strcmp: %d -> ", sign);
    if (sign < 0) {
        printf("перше слово менше\n");
    } else if (sign > 0) {
        printf("перше слово більше\n");
    } else {
        printf("слова рівні\n");
    }

    string s1 = first;
    string s2 = second;
    printf("Рівні (==): %s\n", (s1 == s2) ? "так" : "ні");

    bool equalNoCase = (strlen(first) == strlen(second));
    for (int i = 0; equalNoCase && first[i] != '\0'; i++) {
        if (tolower((unsigned char)first[i]) != tolower((unsigned char)second[i])) {
            equalNoCase = false;
        }
    }

    printf("Рівні без урахування регістру: %s\n", equalNoCase ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)strlen(first), (int)strlen(second));

    string joined = s1 + " & " + s2;
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}

void charInfo(char* text) {
    char line[256];

    printf("Введіть символ: ");
    if (readLine(line, 256) != 1 || strlen(line) != 1) {
        printf("Помилка: введіть рівно один символ.\n");
        return;
    }

    unsigned char code = line[0];
    printf("Символ: '%c'\n", code);
    printf("Код: %d (hex 0x%02x, oct 0%o, bin ", code, code, code);
    int number = code;
    int bits[8];


    for (int i = 0; i < 8; i++) {
        bits[i] = number % 2;
        number = number / 2;
    }

    for (int i = 7; i >= 0; i--) {
        printf("%d", bits[i]);
    }
        printf(")\n");

    printf("Тип: ");
    if (isupper(code)) {
        printf("велика літера\n");
    } else if (islower(code)) {
        printf("мала літера\n");
    } else if (isdigit(code)) {
        printf("цифра\n");
    } else if (isspace(code)) {
        printf("пробільний символ\n");
    } else {
        printf("інший символ\n");
    }

    if (isalpha(code)) {
        char other = isupper(code) ? tolower(code) : toupper(code);
        printf("Інший регістр: '%c'\n", other);
        printf("Наступний символ: '%c'\n", code + 1);
    }

    int occurrences = 0;
    int firstPos = 0;
    int position = 0;
    for (char* p = text; *p != '\0'; p++) {
        position++;
        if (*p == line[0]) {
            occurrences++;
            if (firstPos == 0) {
                firstPos = position;
            }
        }
    }

    if (occurrences == 0) {
        printf("Символ у тексті відсутній.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, firstPos);
    }
}


void newSentence(char* text, char** &words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");

    string sentence = "";
    string token;
    int wordCount = 0;
    bool finished = false;

    while (!finished && (cin >> token)) {
        if (token[token.length() - 1] == '.') {
            finished = true;
            token = token.substr(0, token.length() - 1);
        }
        if (!token.empty()) {
            if (!sentence.empty()) {
                sentence += " ";
            }
            sentence += token;
            wordCount++;
        }
    }
    cin.ignore(1000, '\n');

    if (!finished) {
        printf("Помилка: речення має завершуватися крапкою. Текст не змінено.\n");
        return;
    }

    string candidate = sentence + ".";
    if (candidate.length() > 255) {
        printf("Помилка: речення перевищує 255 символів. Текст не змінено.\n");
        return;
    }

    char buf[256];
    strcpy(buf, candidate.c_str());
    if (!isValidText(buf)) {
        printf("Помилка: речення має складатися лише з латинських літер, цифр і пробілів\n");
        printf("та містити хоча б одне слово. Текст не змінено.\n");
        return;
    }

    printf("Прочитано слів: %d\n", wordCount);
    printf("Новий текст: \"%s\"\n", buf);
    printf("Довжина: %d\n", (int)candidate.length());

    strcpy(text, buf);
    freeWords(words, count);
    words = splitWords(text, count);
}

int main() {
    char text[256];
    int wordCount = 0;
    char** words = nullptr;

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    int status = readLine(text, 256);
    if (status == 0) {
        printf("Помилка: текст не введено.\n");
        return 1;
    }

    if (status < 0) {
        printf("Помилка: текст довший за 255 символів.\n");
        return 1;
    }

    if (!isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n");
        printf("і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    words = splitWords(text, wordCount);

    bool running = true;
    while (running) {
        printf("\n=== МЕНЮ ===\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вихід\n");

        char menu[16];
        printf("Ваш вибір: ");
        if (scanf("%15s", menu) != 1) {
            break;
        }

        int extra = getchar();
        while (extra != '\n' && extra != EOF) {
            extra = getchar();
        }

        int len = strlen(menu);
        bool digitsOnly = (len > 0);
        for (int i = 0; i < len; i++) {
            if (!isdigit((unsigned char)menu[i])) {
                digitsOnly = false;
            }
        }
        if (!digitsOnly) {
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }
        if (len != 1 || menu[0] > '6') {
            printf("Помилка: пункту %s немає в меню.\n", menu);
            continue;
        }

        switch (menu[0] - '0') {
            case 0:
                printf("Вихід з програми.\n");
                running = false;
                break;
            case 1:
                showStats(text, wordCount);
                break;
            case 2:
                showWordTable(words, wordCount);
                break;
            case 3:
                replaceWord(text);
                break;
            case 4:
                comparePair();
                break;
            case 5:
                charInfo(text);
                break;
            case 6:
                newSentence(text, words, wordCount);
                break;
        }
    }

    freeWords(words, wordCount);
    return 0;
}