
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

const int MAX_LEN = 255;
const int MAX_WORD = 31;

int readLine(char *buf, int size) {
    if (!fgets(buf, size, stdin)) return 0;
    char *nl = strchr(buf, '\n');
    if (nl) {
        *nl = '\0';
        return 1;
    }
    int ch = getchar();
    if (ch == '\n' || ch == EOF) return 1;
    while (ch != '\n' && ch != EOF) ch = getchar();
    return 2;
}

bool isLatinOrDigit(char c) {
    unsigned char u = (unsigned char)c;
    return isalpha(u) || isdigit(u);
}

bool isValidText(const char *text) {
    int len = (int)strlen(text);
    if (len < 2 || len > MAX_LEN) return false;
    if (text[len - 1] != '.') return false;
    if (!isLatinOrDigit(text[len - 2])) return false;
    for (const char *p = text; p < text + len - 1; p++)
        if (!isLatinOrDigit(*p) && *p != ' ') return false;
    return true;
}

bool readWord(const char *prompt, std::string &out) {
    char line[MAX_LEN + 1], a[MAX_LEN + 1], b[MAX_LEN + 1];
    printf("%s", prompt);
    int st = readLine(line, sizeof(line));
    if (st == 0) {
        printf("Помилка: вхідні дані закінчились.\n");
        return false;
    }
    if (st == 2) {
        printf("Помилка: слово має бути не довшим за %d символів.\n", MAX_WORD);
        return false;
    }
    int n = sscanf(line, "%255s %255s", a, b);
    if (n < 1) {
        printf("Помилка: слово не може бути порожнім.\n");
        return false;
    }
    if (n > 1) {
        printf("Помилка: потрібно ввести одне слово без пробілів.\n");
        return false;
    }
    if ((int)strlen(a) > MAX_WORD) {
        printf("Помилка: слово має бути не довшим за %d символів.\n", MAX_WORD);
        return false;
    }
    for (const char *p = a; *p; p++) {
        if (!isLatinOrDigit(*p)) {
            printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
            return false;
        }
    }
    out = a;
    return true;
}

void printRepeat(char c, int n) {
    for (int i = 0; i < n; i++) putchar(c);
}

char **splitWords(const char *text, int &count) {
    char buf[MAX_LEN + 1];
    strcpy(buf, text);
    count = 0;
    for (char *t = strtok(buf, " ."); t; t = strtok(nullptr, " ."))
        count++;

    char **words = new char *[count];
    strcpy(buf, text);
    int i = 0;
    for (char *t = strtok(buf, " ."); t; t = strtok(nullptr, " .")) {
        words[i] = new char[strlen(t) + 1];
        strcpy(words[i], t);
        i++;
    }
    return words;
}

void freeWords(char **&words, int &count) {
    if (words) {
        for (int i = 0; i < count; i++) delete[] words[i];
        delete[] words;
    }
    words = nullptr;
    count = 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = digits = spaces = 0;
    for (const char *p = text; *p; p++) {
        unsigned char c = (unsigned char)*p;
        if (isalpha(c)) letters++;
        else if (isdigit(c)) digits++;
        else if (c == ' ') spaces++;
    }
}

char **sortedCopy(char **words, int count) {
    char **copy = new char *[count];
    for (int i = 0; i < count; i++) copy[i] = words[i];
    for (int i = 0; i < count - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < count; j++)
            if (strcmp(copy[j], copy[minIdx]) < 0) minIdx = j;
        if (minIdx != i) {
            char *tmp = copy[i];
            copy[i] = copy[minIdx];
            copy[minIdx] = tmp;
        }
    }
    return copy;
}

void showTextInfo(const char *text, int wordsCount) {
    int len = (int)strlen(text);
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:  %3d\n", len);
    printf("Слів:      %3d\n", wordsCount);
    printf("Літер:     %3d (%5.1f%%)\n", letters, letters * 100.0 / len);
    printf("Цифр:      %3d (%5.1f%%)\n", digits, digits * 100.0 / len);
    printf("Пробілів:  %3d (%5.1f%%)\n", spaces, spaces * 100.0 / len);
}

void showWordTable(char **words, int count) {
    int maxLen = 0, minLen = 0, maxIdx = 0, minIdx = 0, total = 0;
    for (int i = 0; i < count; i++) {
        int len = (int)strlen(words[i]);
        total += len;
        if (i == 0) {
            maxLen = minLen = len;
        } else {
            if (len > maxLen) { maxLen = len; maxIdx = i; }
            if (len < minLen) { minLen = len; minIdx = i; }
        }
    }
    int width = maxLen > 16 ? maxLen : 16;

    printf("+----+");  printRepeat('-', width + 2);  printf("+-------+\n");
    printf("| N  | Слово");  printRepeat(' ', width - 5);  printf(" | Довж. |\n");
    printf("+----+");  printRepeat('-', width + 2);  printf("+-------+\n");
    for (int i = 0; i < count; i++) {
        int len = (int)strlen(words[i]);
        printf("| %2d | %s", i + 1, words[i]);
        printRepeat(' ', width - len);
        printf(" | %5d |\n", len);
    }
    printf("+----+");  printRepeat('-', width + 2);  printf("+-------+\n");

    printf("Найдовше слово: %s (%d)\n", words[maxIdx], maxLen);
    printf("Найкоротше слово: %s (%d)\n", words[minIdx], minLen);
    printf("Середня довжина: %.2f\n", (double)total / count);

    char **sorted = sortedCopy(words, count);
    printf("За абеткою:");
    for (int i = 0; i < count; i++) printf(" %s", sorted[i]);
    printf("\n");

    int best = 0, bestIdx = 0;
    int i = 0;
    while (i < count) {
        int j = i;
        while (j < count && strcmp(sorted[i], sorted[j]) == 0) j++;
        if (j - i > best) {
            best = j - i;
            bestIdx = i;
        }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[bestIdx], best);
    delete[] sorted;
}

void replaceWord(char *text, char **&words, int &count) {
    std::string from, to;
    if (!readWord("Замінити слово: ", from)) return;
    if (!readWord("На слово: ", to)) return;

    std::string s(text);
    int replaced = 0;
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != std::string::npos) {
        size_t end = pos + from.length();
        bool leftOk = (pos == 0 || s[pos - 1] == ' ');
        bool rightOk = (end == s.length() || s[end] == ' ' || s[end] == '.');
        if (leftOk && rightOk) {
            s.replace(pos, from.length(), to);
            replaced++;
            pos += to.length();
        } else {
            pos++;
        }
    }

    if ((int)s.length() > MAX_LEN) {
        printf("Помилка: результат перевищує %d символів, текст не змінено.\n", MAX_LEN);
        return;
    }

    printf("Замін виконано: %d\n", replaced);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", s.c_str());
    printf("Нова довжина: %d\n", (int)s.length());

    strcpy(text, s.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
}

void compareWords() {
    std::string a, b;
    if (!readWord("Перше слово: ", a)) return;
    if (!readWord("Друге слово: ", b)) return;

    int cmp = strcmp(a.c_str(), b.c_str());
    int sign = cmp < 0 ? -1 : (cmp > 0 ? 1 : 0);
    const char *explain = sign < 0 ? "перше слово менше"
                        : (sign > 0 ? "перше слово більше" : "слова однакові");
    printf("strcmp: %d -> %s\n", sign, explain);
    printf("Рівні (==): %s\n", a == b ? "так" : "ні");

    std::string la = a, lb = b;
    for (size_t i = 0; i < la.length(); i++) la[i] = (char)tolower((unsigned char)la[i]);
    for (size_t i = 0; i < lb.length(); i++) lb[i] = (char)tolower((unsigned char)lb[i]);
    printf("Рівні без урахування регістру: %s\n", la == lb ? "так" : "ні");

    printf("Довжини: %d і %d\n", (int)a.length(), (int)b.length());
    std::string cat = a + " & " + b;
    printf("Конкатенація: \"%s\" (%d)\n", cat.c_str(), (int)cat.length());
}

void charInfo(const char *text) {
    char line[MAX_LEN + 1];
    printf("Введіть символ: ");
    int st = readLine(line, sizeof(line));
    if (st == 0) {
        printf("Помилка: вхідні дані закінчились.\n");
        return;
    }
    if (st == 2 || strlen(line) != 1 || !isprint((unsigned char)line[0])) {
        printf("Помилка: потрібно ввести рівно один друкований символ.\n");
        return;
    }

    unsigned char c = (unsigned char)line[0];
    int code = c;
    printf("Символ: '%c'\n", c);

    printf("Код: %d (hex 0x%x, oct 0%o, bin ", code, code, code);
    for (int bit = 7; bit >= 0; bit--) printf("%d", (code >> bit) & 1);
    printf(")\n");

    const char *type;
    if (isupper(c)) type = "велика літера";
    else if (islower(c)) type = "мала літера";
    else if (isdigit(c)) type = "цифра";
    else if (isspace(c)) type = "пробільний символ";
    else type = "інший символ";
    printf("Тип: %s\n", type);

    if (isupper(c)) printf("Інший регістр: '%c'\n", c + ('a' - 'A'));
    else if (islower(c)) printf("Інший регістр: '%c'\n", c - ('a' - 'A'));

    int next = code + 1;
    if (isprint(next)) printf("Наступний символ: '%c'\n", next);
    else printf("Наступний символ: код %d (недрукований)\n", next);

    int occurrences = 0, first = 0, position = 0;
    for (const char *p = text; *p; p++) {
        position++;
        if (*p == line[0]) {
            occurrences++;
            if (first == 0) first = position;
        }
    }
    if (occurrences > 0)
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, first);
    else
        printf("Входжень у тексті: 0, символ у тексті відсутній\n");
}

void enterSentence(char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");

    std::string sentence, w;
    bool ok = true, ended = false;
    int n = 0;
    while (std::cin >> w) {
        int len = (int)w.length();
        bool last = (w[len - 1] == '.');
        int core = last ? len - 1 : len;
        if (core == 0) ok = false;
        for (int i = 0; i < core; i++)
            if (!isLatinOrDigit(w[i])) ok = false;
        if (n > 0) sentence += ' ';
        sentence += w.substr(0, core);
        n++;
        if (last) {
            ended = true;
            break;
        }
    }
    if (!ended) ok = false;

    if (ended) {
        int ch;
        while ((ch = std::cin.get()) != '\n' && ch != EOF) {}
    } else {
        std::cin.clear();
    }

    if (ok) {
        sentence += '.';
        if ((int)sentence.length() > MAX_LEN) ok = false;
    }
    if (!ok) {
        printf("Помилка: речення має складатися з латинських літер, цифр і пробілів, "
               "завершуватися крапкою та містити не більше %d символів. "
               "Поточний текст не змінено.\n", MAX_LEN);
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

void printMenu() {
    printf("\nМеню:\n");
    printf("1  Показати текст і статистику\n");
    printf("2  Таблиця слів\n");
    printf("3  Замінити слово\n");
    printf("4  Порівняти два слова\n");
    printf("5  Інформація про символ\n");
    printf("6  Ввести нове речення\n");
    printf("0  Вийти\n");
}

int parseChoice(const char *line) {
    char a[MAX_LEN + 1], b[MAX_LEN + 1];
    int n = sscanf(line, "%255s %255s", a, b);
    bool digitsOnly = (n == 1);
    for (const char *p = a; digitsOnly && *p; p++)
        if (!isdigit((unsigned char)*p)) digitsOnly = false;
    if (!digitsOnly) {
        printf("Помилка: введіть номер пункту меню.\n");
        return -1;
    }
    int value = 0;
    if (strlen(a) > 3) value = 999;
    else
        for (const char *p = a; *p; p++) value = value * 10 + (*p - '0');
    if (value > 6) {
        printf("Помилка: пункту %s немає в меню.\n", a);
        return -1;
    }
    return value;
}

int main() {
    char text[MAX_LEN + 1];

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    int st = readLine(text, sizeof(text));
    if (st != 1 || !isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр "
               "і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int count = 0;
    char **words = splitWords(text, count);

    while (true) {
        printMenu();
        printf("Ваш вибір: ");
        char line[MAX_LEN + 1];
        int s = readLine(line, sizeof(line));
        if (s == 0) break;
        if (s == 2) {
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }
        int choice = parseChoice(line);
        if (choice < 0) continue;
        if (choice == 0) break;

        switch (choice) {
            case 1: showTextInfo(text, count); break;
            case 2: showWordTable(words, count); break;
            case 3: replaceWord(text, words, count); break;
            case 4: compareWords(); break;
            case 5: charInfo(text); break;
            case 6: enterSentence(text, words, count); break;
        }
    }

    freeWords(words, count);
    printf("Роботу завершено.\n");
    return 0;
}

