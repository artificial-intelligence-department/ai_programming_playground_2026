/*
Редактор текстового повідомлення
Зубак Тетяна
ШІ-12
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

const int max_chars = 255;
const int max_text = 256;
const int max_word = 31;
const int max_words = 128;

//введення і перевірка
void clearLine() {
    scanf("%*[^\n]");
    scanf("%*c");
}

bool readInt(int &value) {
    char token[32];
    if (scanf("%31s", token) != 1) {
        return false;
    }

    int len = strlen(token);
    for (int i = 0; i < len; i++) {
        if (token[i] < '0' || token[i] > '9') {
            clearLine();
            return false;
        }
    }

    if (len > 9) {
        clearLine();
        return false;
    }

    bool extra = false;
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (!isspace(ch)) extra = true;
    }
    if (extra) {
        return false;
    }

    value = 0;
    for (int i = 0; i < len; i++) {
        value = value * 10 + (token[i] - '0');
    }

    return true;
}

bool readLine(char *text, int size) {
    if (fgets(text, size, stdin) == NULL) {
        return false;
    }

    bool full = (strchr(text, '\n') == NULL);
    text[strcspn(text, "\n")] = '\0';

    if (full) {
        char rest[64];
        bool extra = false;
        while (fgets(rest, sizeof(rest), stdin) != NULL) {
            if (rest[0] != '\n') extra = true;
            if (strchr(rest, '\n') != NULL) break;
        }
        if (extra) {
            printf("Помилка: текст довший за %d символів.\n", size - 1);
            return false;
        }
    }
    return true;
}

bool isLetter(char c) {
    return (unsigned char)c < 128 && isalpha((unsigned char)c);
}

bool isWordChar(char c) {
    return isLetter(c) || isdigit((unsigned char)c);
}

bool validText(const char *text) {
    int len = strlen(text);
    if (len == 0 || text[len - 1] != '.') {
        return false;
    }

    bool hasWord = false;
    for (const char *p = text; p < text + len - 1; p++) {
        if (isWordChar(*p)) {
            hasWord = true;
        }
        else if (*p != ' ') {
            return false;
        }
    }
    return hasWord;
}

bool readWord(char *word) {
    if (scanf("%32s", word) != 1) {
        return false;
    }

    if ((int)strlen(word) > max_word) {
        printf("Помилка: слово має містити не більше %d символів.\n", max_word);
        clearLine();
        return false;
    }

    for (const char *p = word; *p != '\0'; p++) {
        if (!isWordChar(*p)) {
            printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
            clearLine();
            return false;
        }
    }
    return true;
}

//слова
char **splitWords(const char *text, int &count) {
    char buf[max_text];
    strcpy(buf, text);
    buf[strlen(buf) - 1] = '\0';

    char **words = new char*[max_words];
    count = 0;

    char *t = strtok(buf, " ");
    while (t != NULL) {
        words[count] = new char[strlen(t) + 1];
        strcpy(words[count], t);
        count++;
        t = strtok(NULL, " ");
    }
    return words;
}

void freeWords(char **&words, int &count) {
    if (words == nullptr) return;
    for (int i = 0; i < count; i++) {
        delete[] words[i];
        words[i] = nullptr;
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;

    for (const char *p = text; *p != '\0'; p++) {
        if (isLetter(*p)) letters++;
        else if (isdigit((unsigned char)*p)) digits++;
        else if (*p == ' ') spaces++;
    }
}

//1. текст і статистика
void show(const char *text, int count) {
    int letters = 0, digits = 0, spaces = 0;
    countChars(text, letters, digits, spaces);
    int total = strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:%6d\n", total);
    printf("Слів:%10d\n", count);
    printf("Літер:%9d (%5.1f%%)\n", letters, letters * 100.0 / total);
    printf("Цифр:%10d (%5.1f%%)\n", digits, digits * 100.0 / total);
    printf("Пробілів:%6d (%5.1f%%)\n", spaces, spaces * 100.0 / total);
}

//2. таблиця слів
void printLine(int nw, int col) {
    printf("+");
    for (int i = 0; i < nw + 2; i++) printf("-");
    printf("+");
    for (int i = 0; i < col + 2; i++) printf("-");
    printf("+-------+\n");
}

void findExtremes(char **words, int count, int &maxIdx, int &minIdx) {
    maxIdx = 0;
    minIdx = 0;

    for (int i = 1; i < count; i++) {
        char *w = *(words + i);
        if ((int)strlen(w) > (int)strlen(words[maxIdx])) maxIdx = i;
        if ((int)strlen(w) < (int)strlen(words[minIdx])) minIdx = i;
    }
}

void swapWords(char *&a, char *&b) {
    char *t = a;
    a = b;
    b = t;
}

void sortWords(char **sorted, int count) {
    for (int i = 1; i < count; i++) {
        for (int j = 1; j < count; j++) {
            if (strcmp(sorted[j - 1], sorted[j]) > 0) swapWords(sorted[j - 1], sorted[j]);
        }
    }
}

char *popular(char **sorted, int count, int &best) {
    char *res = sorted[0];
    int run = 0;
    best = 0;

    for (int i = 0; i < count; i++) {
        if (i > 0 && strcmp(sorted[i], sorted[i - 1]) == 0) run++;
        else run = 1;

        if (run > best) {
            best = run;
            res = sorted[i];
        }
    }
    return res;
}

void table(char **words, int count) {
    int col = 15;
    int nw = 2;
    int sum = 0;

    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        sum += len;
        if (len > col) col = len;
    }
    if (count > 99) nw = 3;

    printLine(nw, col);
    printf("│ %-*s │ Слово%*s │ Довж. │\n", nw, "N", col - 5, "");
    printLine(nw, col);
    for (int i = 0; i < count; i++) {
        printf("│ %*d │ %-*s │ %5d │\n", nw, i + 1, col, words[i], (int)strlen(words[i]));
    }
    printLine(nw, col);

    int maxIdx = 0, minIdx = 0;
    findExtremes(words, count, maxIdx, minIdx);
    printf("Найдовше слово: %s (%d)\n", words[maxIdx], (int)strlen(words[maxIdx]));
    printf("Найкоротше слово: %s (%d)\n", words[minIdx], (int)strlen(words[minIdx]));
    printf("Середня довжина: %.2f\n", (double)sum / count);

    char **sorted = new char*[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }
    sortWords(sorted, count);

    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    int best = 0;
    char *top = popular(sorted, count, best);
    printf("Найчастіше слово: %s (%d)\n", top, best);

    delete[] sorted;
    sorted = nullptr;
}

//3. заміна слова
void replaceWord(char *text, char **&words, int &count) {
    char from[max_word + 2];
    char to[max_word + 2];

    printf("Замінити слово: ");
    if (!readWord(from)) return;
    printf("На слово: ");
    if (!readWord(to)) return;

    string s(text);
    string f(from);
    string t(to);
    int num = 0;

    size_t pos = s.find(f);
    while (pos != string::npos) {
        bool left = (pos == 0 || !isWordChar(s[pos - 1]));
        bool right = (pos + f.length() == s.length() || !isWordChar(s[pos + f.length()]));

        if (left && right) {
            s.replace(pos, f.length(), t);
            pos += t.length();
            num++;
        }
        else {
            pos++;
        }
        pos = s.find(f, pos);
    }

    if ((int)s.length() > max_chars) {
        printf("Помилка: результат перевищує %d символів, текст не змінено.\n", max_chars);
        return;
    }

    printf("Замін виконано: %d\n", num);
    printf("Було:  \"%s\"\n", text);
    strcpy(text, s.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));

    if (num > 0) {
        freeWords(words, count);
        words = splitWords(text, count);
    }
}

//4. порівняння слів
bool equalNoCase(const string &a, const string &b) {
    if (a.length() != b.length()) return false;
    for (int i = 0; i < (int)a.length(); i++) {
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])) return false;
    }
    return true;
}

const char *yesNo(bool value) {
    if (value) return "так";
    return "ні";
}

void compare() {
    char a[max_word + 2];
    char b[max_word + 2];

    printf("Перше слово: ");
    if (!readWord(a)) return;
    printf("Друге слово: ");
    if (!readWord(b)) return;

    int res = strcmp(a, b);
    if (res < 0) res = -1;
    else if (res > 0) res = 1;

    string s1(a);
    string s2(b);

    printf("strcmp: %d -> ", res);
    if (res < 0) printf("перше слово менше\n");
    else if (res > 0) printf("перше слово більше\n");
    else printf("слова однакові\n");

    printf("Рівні (==): %s\n", yesNo(s1 == s2));
    printf("Рівні без урахування регістру: %s\n", yesNo(equalNoCase(s1, s2)));
    printf("Довжини: %d і %d\n", (int)s1.length(), (int)s2.length());

    string both = s1 + " & " + s2;
    printf("Конкатенація: \"%s\" (%d)\n", both.c_str(), (int)both.length());
}

//5. інформація про символ
void symbol(const char *text) {
    char c = 0;

    printf("Введіть символ: ");
    scanf("%*[\n]");
    if (scanf("%c", &c) != 1) return;
    clearLine();

    int code = (unsigned char)c;
    if (code < 32 || code > 126) {
        printf("Помилка: введіть один видимий символ ASCII.\n");
        return;
    }

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", code, code, code);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (code >> i) & 1);
    }
    printf(")\n");

    printf("Тип: ");
    if (isLetter(c)) {
        if (tolower(code) == code) printf("мала літера\n");
        else printf("велика літера\n");
    }
    else if (isdigit(code)) printf("цифра\n");
    else if (isspace(code)) printf("пробільний символ\n");
    else printf("інший символ\n");

    if (isLetter(c)) {
        if (tolower(code) == code) printf("Інший регістр: '%c'\n", toupper(code));
        else printf("Інший регістр: '%c'\n", tolower(code));
        printf("Наступний символ: '%c'\n", c + 1);
    }

    int num = 0;
    const char *first = strchr(text, c);
    const char *p = first;
    while (p != NULL) {
        num++;
        p = strchr(p + 1, c);
    }

    if (first == NULL) printf("Символ у тексті не зустрічається.\n");
    else printf("Входжень у тексті: %d, перше на позиції %d\n", num, (int)(first - text) + 1);
}

//6. нове речення
void newText(char *text, char **&words, int &count) {
    string word;
    string sentence = "";
    int n = 0;
    bool ended = false;

    printf("Введіть речення (крапка після останнього слова): ");
    fflush(stdout);
    while (cin >> word) {
        if (n > 0) sentence += " ";
        sentence += word;
        n++;
        if (word[word.length() - 1] == '.') {
            ended = true;
            break;
        }
    }

    if (!ended) {
        printf("Помилка: речення не завершено крапкою.\n");
        return;
    }
    clearLine();

    if ((int)sentence.length() > max_chars) {
        printf("Помилка: речення довше за %d символів, текст не змінено.\n", max_chars);
        return;
    }

    if (!validText(sentence.c_str())) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

//меню
bool status(char *text, char **&words, int &count, int &def) {
    int menu = 0;

    printf("\n1 - Показати текст і статистику\n"
        "2 - Таблиця слів\n"
        "3 - Замінити слово\n"
        "4 - Порівняти два слова\n"
        "5 - Інформація про символ\n"
        "6 - Ввести нове речення\n"
        "0 - Вийти\n");
    printf("Ваш вибір: ");

    if (!readInt(menu)) {
        if (feof(stdin)) return false;
        printf("Помилка: введіть номер пункту меню.\n");
        return true;
    }

    switch (menu) {
        case 1:
            show(text, count);
            break;
        case 2:
            table(words, count);
            break;
        case 3:
            replaceWord(text, words, count);
            break;
        case 4:
            compare();
            break;
        case 5:
            symbol(text);
            break;
        case 6:
            newText(text, words, count);
            break;
        case 0:
            def = 1;
            break;
        default:
            printf("Помилка: пункту %d немає в меню.\n", menu);
    }
    return true;
}

int main() {
    int def = 0;
    int count = 0;
    char text[max_text];

    printf("Введіть текст (до 255 символів, крапка в кінці): ");
    if (!readLine(text, max_text)) return 0;

    if (!validText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 0;
    }

    char **words = splitWords(text, count);

    do {
        if (!status(text, words, count, def)) {
            freeWords(words, count);
            return 0;
        }
    } while (def != 1);

    freeWords(words, count);
    return 0;
}