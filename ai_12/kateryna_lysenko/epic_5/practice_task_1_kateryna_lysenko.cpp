/*
Задача: Редактор текстового повідомлення
Автор:   Катерирна Лисенко
Група:   ШІ-12
*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

const int TEXT_SIZE = 256;      // char text[256]: до 255 символів + '\0'
const int MAX_LEN = 255;
const int WORD_MAX = 31;        // максимальна довжина слова для заміни/порівняння


// Пропускає залишок поточного рядка вводу (до '\n' або кінця файлу).
void clearLine() {
    char c;
    while (scanf("%c", &c) == 1 && c != '\n') {
    }
}

// Виводить символ у лапках (для службових символів - пояснення).
void printCharRepr(unsigned char c) {
    if (c == '\t') printf("'\\t'");
    else if (isprint(c)) printf("'%c'", c);
    else printf("(недрукований символ)");
}


// Розбиває текст на слова (strtok), повертає динамічний масив рядків.
char **splitWords(const char *text, int &count) {
    char *buf = new char[strlen(text) + 1];
    strcpy(buf, text);
    count = 0;
    for (char *t = strtok(buf, " ."); t != nullptr; t = strtok(nullptr, " .")) {
        count++;
    }
    char **words = (count > 0) ? new char *[count] : nullptr;
    strcpy(buf, text);
    int i = 0;
    for (char *t = strtok(buf, " ."); t != nullptr; t = strtok(nullptr, " .")) {
        words[i] = new char[strlen(t) + 1];
        strcpy(words[i], t);
        i++;
    }
    delete[] buf;
    return words;
}

// Звільняє масив слів.
void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

// Рахує літери, цифри та пробіли (обхід вказівником).
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = digits = spaces = 0;
    for (const char *p = text; *p != '\0'; p++) {
        unsigned char c = (unsigned char)*p;
        if (isalpha(c)) letters++;
        else if (isdigit(c)) digits++;
        else if (c == ' ') spaces++;
    }
}


void showTextStats(const char *text) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int total = (int)strlen(text);
    int wordCount;
    char **w = splitWords(text, wordCount);
    for (int i = 0; i < wordCount; i++) delete[] w[i];
    delete[] w;

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %d\n", total);
    printf("Слів: %d\n", wordCount);
    printf("Літер: %d (%5.1f%%)\n", letters, 100.0 * letters / total);
    printf("Цифр: %d (%5.1f%%)\n", digits, 100.0 * digits / total);
    printf("Пробілів: %d (%5.1f%%)\n", spaces, 100.0 * spaces / total);
}


int digitsIn(int n) {
    int d = 1;
    while (n >= 10) {
        n /= 10;
        d++;
    }
    return d;
}

void printBorder(int w1, int w2, int w3) {
    putchar('+');
    for (int i = 0; i < w1 + 2; i++) putchar('-');
    putchar('+');
    for (int i = 0; i < w2 + 2; i++) putchar('-');
    putchar('+');
    for (int i = 0; i < w3 + 2; i++) putchar('-');
    printf("+\n");
}

void wordsTable(char **words, int count) {
    int maxLen = 0, minLen = 0, maxIdx = 0, minIdx = 0;
    long sum = 0;
    for (int i = 0; i < count; i++) {
        int len = (int)strlen(words[i]);
        sum += len;
        if (i == 0 || len > maxLen) { maxLen = len; maxIdx = i; }   // перше найдовше
        if (i == 0 || len < minLen) { minLen = len; minIdx = i; }   // перше найкоротше
    }
    int w1 = digitsIn(count);
    if (w1 < 1) w1 = 1;
    int w2 = maxLen < 5 ? 5 : maxLen;           // "Слово" - 5 символів
    int w3 = digitsIn(maxLen) < 5 ? 5 : digitsIn(maxLen);   // "Довж." - 5 символів

    printBorder(w1, w2, w3);
    // заголовок вирівнюємо вручну: кирилиця в UTF-8 займає по 2 байти
    printf("| %*s | Слово%*s | Довж. |\n", w1, "N", w2 - 5, "");
    printBorder(w1, w2, w3);
    for (int i = 0; i < count; i++) {
        printf("| %*d | %-*s | %*d |\n", w1, i + 1, w2, words[i], w3, (int)strlen(words[i]));
    }
    printBorder(w1, w2, w3);

    printf("Найдовше слово: %s (%d)\n", words[maxIdx], maxLen);
    printf("Найкоротше слово: %s (%d)\n", words[minIdx], minLen);
    printf("Середня довжина: %.2f\n", (double)sum / count);

    // копія вказівників: порядок слів у words не змінюється
    char **sorted = new char *[count];
    for (int i = 0; i < count; i++) sorted[i] = words[i];
    // сортування обміном: кожен елемент порівнюємо з наступними
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(sorted[j], sorted[i]) < 0) {
                char *temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    printf("За абеткою:");
    for (int i = 0; i < count; i++) printf(" %s", sorted[i]);
    printf("\n");

    // найчастіше слово: серед однакових слів, що стоять підряд
    int bestCount = 0, bestIdx = 0, i = 0;
    while (i < count) {
        int j = i;
        while (j < count && strcmp(sorted[j], sorted[i]) == 0) j++;
        if (j - i > bestCount) {                // строго більше: перше за абеткою
            bestCount = j - i;
            bestIdx = i;
        }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[bestIdx], bestCount);
    delete[] sorted;                            // самі слова не видаляємо
}

void replaceWord(char *text, char **&words, int &count) {
    char from[WORD_MAX + 2], to[WORD_MAX + 2];
    bool wordOk;

    printf("Замінити слово: ");
    if (scanf("%32s", from) != 1) return;
    clearLine();
    wordOk = (strlen(from) > 0 && strlen(from) <= WORD_MAX);
    for (const char *p = from; wordOk && *p != '\0'; p++) {
        if (!isalnum((unsigned char)*p)) wordOk = false;
    }
    if (!wordOk) {
        printf("Помилка: слово має містити лише латинські літери й цифри (до %d символів).\n", WORD_MAX);
        return;
    }
    printf("На слово: ");
    if (scanf("%32s", to) != 1) return;

    clearLine();
    wordOk = (strlen(to) > 0 && strlen(to) <= WORD_MAX);
    for (const char *p = to; wordOk && *p != '\0'; p++) {
        if (!isalnum((unsigned char)*p)) wordOk = false;
    }
    if (!wordOk) {
        printf("Помилка: нове слово має містити лише латинські літери й цифри (до %d символів).\n", WORD_MAX);
        return;
    }

    std::string s(text);
    std::string before = s;
    std::string f(from), t(to);
    int replaced = 0;
    size_t pos = s.find(f);
    while (pos != std::string::npos) {
        size_t end = pos + f.length();
        bool leftOk = (pos == 0 || s[pos - 1] == ' ');
        bool rightOk = (end == s.length() || s[end] == ' ' || s[end] == '.');
        if (leftOk && rightOk) {
            s.replace(pos, f.length(), t);
            replaced++;
            pos = s.find(f, pos + t.length());
        } else {
            pos = s.find(f, pos + 1);
        }
    }
    if (s.length() > (size_t)MAX_LEN) {
        printf("Помилка: після заміни текст перевищив би %d символів. Текст не змінено.\n", MAX_LEN);
        return;
    }

    strcpy(text, s.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Замін виконано: %d\n", replaced);
    printf("Було: \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)s.length());
}


void compareWords() {
    char a[WORD_MAX + 2], b[WORD_MAX + 2];
    bool wordOk;

    printf("Перше слово: ");
    if (scanf("%32s", a) != 1) return;
    clearLine();
    wordOk = (strlen(a) > 0 && strlen(a) <= WORD_MAX);
    for (const char *p = a; wordOk && *p != '\0'; p++) {
        if (!isalnum((unsigned char)*p)) wordOk = false;
    }
    if (!wordOk) {
        printf("Помилка: слово має містити лише латинські літери й цифри (до %d символів).\n", WORD_MAX);
        return;
    }
    printf("Друге слово: ");
    if (scanf("%32s", b) != 1) return;
    clearLine();
    wordOk = (strlen(b) > 0 && strlen(b) <= WORD_MAX);
    for (const char *p = b; wordOk && *p != '\0'; p++) {
        if (!isalnum((unsigned char)*p)) wordOk = false;
    }
    if (!wordOk) {
        printf("Помилка: слово має містити лише латинські літери й цифри (до %d символів).\n", WORD_MAX);
        return;
    }

    int r = strcmp(a, b);
    int sign = (r < 0) ? -1 : (r > 0 ? 1 : 0);
    if (sign < 0) printf("strcmp: -1 -> перше слово менше\n");
    else if (sign > 0) printf("strcmp: 1 -> перше слово більше\n");
    else printf("strcmp: 0 -> слова однакові\n");

    std::string sa(a), sb(b);
    printf("Рівні (==): %s\n", (sa == sb) ? "так" : "ні");

    bool equalIgnoreCase = (sa.length() == sb.length());
    for (size_t i = 0; equalIgnoreCase && i < sa.length(); i++) {
        if (tolower((unsigned char)sa[i]) != tolower((unsigned char)sb[i])) equalIgnoreCase = false;
    }
    printf("Рівні без урахування регістру: %s\n", equalIgnoreCase ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)sa.length(), (int)sb.length());
    std::string joined = sa + " & " + sb;
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}


void charInfo(const char *text) {
    char line[16];
    printf("Введіть символ: ");
    if (fgets(line, sizeof(line), stdin) == nullptr) return;
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[--len] = '\0';
    } else {
        clearLine();                            // рядок був довшим за буфер
    }
    if (len > 0 && line[len - 1] == '\r') line[--len] = '\0';
    if (len != 1) {
        printf("Помилка: введіть рівно один символ.\n");
        return;
    }
    unsigned char c = (unsigned char)line[0];

    printf("Символ: ");
    printCharRepr(c);
    printf("\n");
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", c, c, c);
    for (int i = 7; i >= 0; i--) {              // двійковий код побітово
        printf("%d", (c >> i) & 1);
    }
    printf(")\n");

    if (isupper(c)) printf("Тип: велика літера\n");
    else if (islower(c)) printf("Тип: мала літера\n");
    else if (isdigit(c)) printf("Тип: цифра\n");
    else if (c == ' ' || (c >= '\t' && c <= '\r')) printf("Тип: пробільний символ\n");
    else printf("Тип: інший символ\n");

    if (isalpha(c)) {
        unsigned char other = isupper(c) ? (unsigned char)(c + ('a' - 'A'))
                                         : (unsigned char)(c - ('a' - 'A'));
        printf("Інший регістр: ");
        printCharRepr(other);
        printf("\n");
    }
    if (c < 255) {
        printf("Наступний символ: ");
        printCharRepr((unsigned char)(c + 1));
        printf("\n");
    }

    int occurrences = 0;
    for (const char *p = text; *p != '\0'; p++) {
        if ((unsigned char)*p == c) occurrences++;
    }
    const char *first = strchr(text, c);
    if (first == nullptr) {
        printf("Символ у тексті не зустрічається.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, (int)(first - text) + 1);
    }
}

void newSentence(char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");
    std::string sentence, word;
    int read = 0;
    bool endsWithDot = false, tooLong = false;
    while (std::cin >> word) {
        read++;
        if (!sentence.empty()) sentence += ' ';
        if (sentence.length() + word.length() > (size_t)MAX_LEN + 1) {
            tooLong = true;                     // не накопичуємо зайве, але читаємо до крапки
        } else {
            sentence += word;
        }
        if (word[word.length() - 1] == '.') {
            endsWithDot = true;
            break;
        }
    }
    if (!endsWithDot) std::cin.clear();         // кінець вводу без крапки
    else clearLine();                           // решта рядка після крапки

    if (tooLong || sentence.length() > (size_t)MAX_LEN) {
        printf("Помилка: речення перевищує %d символів. Текст не змінено.\n", MAX_LEN);
        return;
    }
    // перевірка речення: латинські літери, цифри, пробіли, крапка після останнього слова
    bool ok = endsWithDot;
    size_t n = sentence.length();
    if (n < 2 || sentence[n - 1] != '.' || !isalnum((unsigned char)sentence[n - 2])) {
        ok = false;
    }
    for (size_t i = 0; ok && i + 1 < n; i++) {
        unsigned char c = (unsigned char)sentence[i];
        if (!isalnum(c) && c != ' ') ok = false;
    }
    if (!ok) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою. Текст не змінено.\n");
        return;
    }
    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Прочитано слів: %d\n", read);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

void printMenu() {
    printf("\n=== Меню ===\n");
    printf("1. Показати текст і статистику\n");
    printf("2. Таблиця слів\n");
    printf("3. Замінити слово\n");
    printf("4. Порівняти два слова\n");
    printf("5. Інформація про символ\n");
    printf("6. Ввести нове речення\n");
    printf("0. Вийти\n");
    printf("Ваш вибір: ");
}

int main() {
    char text[TEXT_SIZE];

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, sizeof(text), stdin) == nullptr) {
        printf("Помилка: текст не введено.\n");
        return 1;
    }
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[--len] = '\0';
    } else {
        char next;                              // рядок заповнив весь буфер?
        if (scanf("%c", &next) == 1 && next != '\n') {
            printf("Помилка: текст перевищує %d символів.\n", MAX_LEN);
            return 1;
        }
    }
    if (len > 0 && text[len - 1] == '\r') text[--len] = '\0';
    // перевірка тексту: латинські літери, цифри, пробіли, крапка після останнього слова
    bool textOk = true;
    if (len < 2 || len > MAX_LEN || text[len - 1] != '.' || !isalnum((unsigned char)text[len - 2])) {
        textOk = false;
    }
    for (size_t i = 0; textOk && i + 1 < len; i++) {
        unsigned char c = (unsigned char)text[i];
        if (!isalnum(c) && c != ' ') textOk = false;
    }
    if (!textOk) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int count = 0;
    char **words = splitWords(text, count);

    int choice = -1;
    do {
        printMenu();
        int r = scanf("%d", &choice);
        if (r < 0) break;
        if (r == 0) {                           // нечислове введення
            clearLine();
            printf("Помилка: введіть номер пункту меню.\n");
            choice = -1;
            continue;
        }
        bool extra = false;                     // зайві символи після числа, наприклад "3abc"
        char c;
        while (scanf("%c", &c) == 1 && c != '\n') {
            if (c != ' ' && c != '\t' && c != '\r') extra = true;
        }
        if (extra) {
            printf("Помилка: введіть номер пункту меню.\n");
            choice = -1;
            continue;
        }
        switch (choice) {
            case 1: showTextStats(text); break;
            case 2: wordsTable(words, count); break;
            case 3: replaceWord(text, words, count); break;
            case 4: compareWords(); break;
            case 5: charInfo(text); break;
            case 6: newSentence(text, words, count); break;
            case 0: printf("Завершення роботи.\n"); break;
            default: printf("Помилка: пункту %d немає в меню.\n", choice); break;
        }
    } while (choice != 0);

    freeWords(words, count);
    return 0;
}
