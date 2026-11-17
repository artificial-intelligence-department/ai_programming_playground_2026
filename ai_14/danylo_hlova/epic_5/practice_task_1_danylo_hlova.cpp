#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

//константи
const int TEXT_SIZE = 256;   
const int MAX_LEN   = 255;   
const int WORD_SIZE = 32;    
const int MAX_WORD  = 31;    

const int TEXT_OK = 0;
const int TEXT_TOO_LONG = 1;
const int TEXT_INVALID = 2;
const int TEXT_NO_WORDS = 3;


//допоміжні функції

// Латинська літера або цифра (тільки ASCII)
bool isLatinAlnum(char c) {
    unsigned char u = (unsigned char)c;
    return u < 128 && isalnum(u) != 0;
}

// Пропустити залишок поточного рядка вводу
void flushLine() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

// Слово лише з латинських літер і цифр (непорожнє)
bool isValidWord(const char *w) {
    if (*w == '\0') return false;
    for (const char *p = w; *p; ++p)
        if (!isLatinAlnum(*p)) return false;
    return true;
}

// Перевірка тексту
int validateText(const char *s) {
    size_t len = strlen(s);
    if (len > (size_t)MAX_LEN) return TEXT_TOO_LONG;
    if (len == 0 || s[len - 1] != '.') return TEXT_INVALID;
    int words = 0;
    bool inWord = false;
    for (const char *p = s; p < s + len - 1; ++p) {
        if (isLatinAlnum(*p)) {
            if (!inWord) { words++; inWord = true; }
        } else if (*p == ' ') {
            inWord = false;
        } else {
            return TEXT_INVALID;   
        }
    }
    return words > 0 ? TEXT_OK : TEXT_NO_WORDS;
}

void printTextError(int st) {
    if (st == TEXT_TOO_LONG) {
        printf("Помилка: текст довший за %d символів.\n", MAX_LEN);
    } else {
        printf("Помилка: текст має складатися з латинських літер, цифр\n"
               "і пробілів та завершуватися крапкою.\n");
        if (st == TEXT_NO_WORDS)
            printf("Текст має містити хоча б одне слово.\n");
    }
}

// Зчитати одне слово до 31 символу
int readWord(char *buf) {
    if (scanf("%31s", buf) != 1) return 1;
    int c = getchar();
    if (c != EOF && !isspace(c)) {   // слово довше за 31 символ
        flushLine();
        return 2;
    }
    if (c != EOF) ungetc(c, stdin);
    return 0;
}

// Прочитати слово з перевіркою
bool inputWord(const char *prompt, char *buf) {
    printf("%s", prompt);
    int r = readWord(buf);
    if (r == 1) {
        printf("\nПомилка: кінець вводу.\n");
        return false;
    }
    if (r == 2) {
        printf("Помилка: слово має бути не довшим за %d символів.\n", MAX_WORD);
        return false;
    }
    if (!isValidWord(buf)) {
        printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
        flushLine();
        return false;
    }
    return true;
}

// робота зі словами

char **splitWords(const char *text, int &count) {
    count = 0;
    char *buf = new char[strlen(text) + 1];
    strcpy(buf, text);
    for (char *t = strtok(buf, " ."); t; t = strtok(NULL, " ."))
        count++;
    if (count == 0) {
        delete[] buf;
        return NULL;
    }
    strcpy(buf, text);               
    char **words = new char *[count];
    int i = 0;
    for (char *t = strtok(buf, " ."); t && i < count; t = strtok(NULL, " .")) {
        words[i] = new char[strlen(t) + 1];
        strcpy(words[i], t);
        i++;
    }
    delete[] buf;
    return words;
}

void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++)
        delete[] words[i];
    delete[] words;
    words = NULL;
    count = 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = digits = spaces = 0;
    for (const char *p = text; *p; ++p) {
        unsigned char u = (unsigned char)*p;
        if (isalpha(u)) letters++;
        else if (isdigit(u)) digits++;
        else if (*p == ' ') spaces++;
    }
}

//  змінює стан лише якщо текст коректний
void applyNewText(const char *newText, char *text, char **&words, int &count) {
    int newCount = 0;
    char **newWords = splitWords(newText, newCount);
    freeWords(words, count);
    strcpy(text, newText);
    words = newWords;
    count = newCount;
}

//пункти меню

// 1. Показати текст і статистику
void showStats(const char *text, int wordCount) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int total = (int)strlen(text);
    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:%*d\n", 6, total);
    printf("Слів:%*d\n", 10, wordCount);
    printf("Літер:%*d (%5.1f%%)\n", 9, letters, 100.0 * letters / total);
    printf("Цифр:%*d (%5.1f%%)\n", 10, digits, 100.0 * digits / total);
    printf("Пробілів:%*d (%5.1f%%)\n", 6, spaces, 100.0 * spaces / total);
}

// Сортування обміном (бульбашка) 
void bubbleSort(const char **arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;                  // чи були обміни за цей прохід
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                const char *t = arr[j];        // третя змінна для обміну
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
                swapped = true;
            }
        }
        if (!swapped) break;                   // масив уже впорядкований
    }
}

void printBorder(int nw, int ww) {
    putchar('+');
    for (int i = 0; i < nw + 2; i++) putchar('-');
    putchar('+');
    for (int i = 0; i < ww + 2; i++) putchar('-');
    printf("+-------+\n");
}

// 2. Таблиця слів
void showWordTable(char **words, int count) {
    int maxLen = 0;
    for (int i = 0; i < count; i++) {
        int l = (int)strlen(words[i]);
        if (l > maxLen) maxLen = l;
    }
    int ww = maxLen > 15 ? maxLen : 15;      // ширина стовпця зі словом
    int nw = count >= 100 ? 3 : 2;           // ширина стовпця з номером

    printBorder(nw, ww);
    printf("| %-*s | Слово%*s | Довж. |\n", nw, "N", ww - 5, "");
    printBorder(nw, ww);
    for (int i = 0; i < count; i++)
        printf("| %*d | %-*s | %5d |\n", nw, i + 1, ww, words[i], (int)strlen(words[i]));
    printBorder(nw, ww);

    int longest = 0, shortest = 0, sum = 0;
    for (int i = 0; i < count; i++) {
        int l = (int)strlen(words[i]);
        sum += l;
        if (l > (int)strlen(words[longest])) longest = i;     // перше з рівних
        if (l < (int)strlen(words[shortest])) shortest = i;
    }
    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)sum / count);

    const char **sorted = new const char *[count];
    for (int i = 0; i < count; i++) sorted[i] = words[i];
    bubbleSort(sorted, count);

    printf("За абеткою:");
    for (int i = 0; i < count; i++) printf(" %s", sorted[i]);
    printf("\n");

    // найчастіше слово: у відсортованому масиві однакові слова йдуть підряд;
    // строге порівняння залишає перше за абеткою
    int bestCount = 0, bestIdx = 0, i = 0;
    while (i < count) {
        int j = i;
        while (j < count && strcmp(sorted[j], sorted[i]) == 0) j++;
        if (j - i > bestCount) { bestCount = j - i; bestIdx = i; }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[bestIdx], bestCount);
    delete[] sorted;
}

// 3. Замінити слово (std::string)
void replaceWord(char *text, char **&words, int &count) {
    char fromBuf[WORD_SIZE], toBuf[WORD_SIZE];
    if (!inputWord("Замінити слово: ", fromBuf)) return;
    if (!inputWord("На слово: ", toBuf)) return;
    flushLine();

    std::string from(fromBuf), to(toBuf);
    std::string s(text);
    int replaced = 0;
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != std::string::npos) {
        size_t end = pos + from.length();
        bool leftOk = (pos == 0) || !isLatinAlnum(s[pos - 1]);
        bool rightOk = (end >= s.length()) || !isLatinAlnum(s[end]);
        if (leftOk && rightOk) {                 // тільки ціле слово, з регістром
            s.replace(pos, from.length(), to);
            pos += to.length();
            replaced++;
        } else {
            pos++;
        }
    }

    if (replaced == 0) {
        printf("Замін виконано: 0\nСлово \"%s\" у тексті не знайдено, текст не змінено.\n", fromBuf);
        return;
    }
    if (s.length() > (size_t)MAX_LEN) {
        printf("Помилка: після заміни текст перевищив би %d символів. Текст не змінено.\n", MAX_LEN);
        return;
    }
    printf("Замін виконано: %d\n", replaced);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", s.c_str());
    printf("Нова довжина: %d\n", (int)s.length());
    applyNewText(s.c_str(), text, words, count);
}

bool equalsIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return false;
        ++a; ++b;
    }
    return *a == *b;
}

// 4. Порівняти два слова
void compareWords() {
    char a[WORD_SIZE], b[WORD_SIZE];
    if (!inputWord("Перше слово: ", a)) return;
    if (!inputWord("Друге слово: ", b)) return;
    flushLine();

    int r = strcmp(a, b);
    int sign = (r > 0) - (r < 0);
    printf("strcmp: %d -> %s\n", sign,
           sign < 0 ? "перше слово менше" : (sign > 0 ? "перше слово більше" : "слова однакові"));

    std::string sa(a), sb(b);
    printf("Рівні (==): %s\n", sa == sb ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", equalsIgnoreCase(a, b) ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)strlen(a), (int)strlen(b));

    std::string joined = sa + " & " + sb;
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}

// Вивести символ у лапках 
void printCharLiteral(char c) {
    if (c == '\t') printf("'\\t'");
    else printf("'%c'", c);
}

// 5. Інформація про символ
void charInfo(const char *text) {
    printf("Введіть символ: ");
    char c;
    if (scanf("%c", &c) != 1) {
        printf("\nПомилка: кінець вводу.\n");
        return;
    }
    if (c == '\n') {
        printf("Помилка: символ не введено.\n");
        return;
    }
    int next = getchar();
    if (next != '\n' && next != EOF) {
        flushLine();
        printf("Помилка: потрібно ввести рівно один символ.\n");
        return;
    }
    unsigned char u = (unsigned char)c;
    if (u > 126 || (u < 32 && c != '\t')) {
        printf("Помилка: потрібен друкований символ ASCII.\n");
        return;
    }

    printf("Символ: ");
    printCharLiteral(c);
    printf("\nКод: %d (hex 0x%02x, oct 0%o, bin ", (int)u, (unsigned)u, (unsigned)u);
    for (int bit = 7; bit >= 0; bit--)
        printf("%d", (u >> bit) & 1);          
    printf(")\n");

    const char *type;
    if (isupper(u)) type = "велика літера";
    else if (islower(u)) type = "мала літера";
    else if (isdigit(u)) type = "цифра";
    else if (isspace(u)) type = "пробільний символ";
    else type = "інший символ";
    printf("Тип: %s\n", type);

    if (isalpha(u)) {
        char other = isupper(u) ? (char)tolower(u) : (char)toupper(u);
        printf("Інший регістр: ");
        printCharLiteral(other);
        printf("\nНаступний символ: ");
        printCharLiteral((char)(c + 1));
        printf("\n");
    }

    int occurrences = 0;
    for (const char *p = text; *p; ++p)
        if (*p == c) occurrences++;
    const char *first = strchr(text, c);       
    if (first != NULL)
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, (int)(first - text) + 1);
    else
        printf("Входжень у тексті: 0, символ у тексті відсутній\n");
}

// 6. Ввести нове речення (cin >> у циклі while)
void newSentence(char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");
    std::string sentence, token;
    bool finished = false, tooLong = false;

    while (!finished && std::cin >> token) {
        if (!tooLong) {
            if (!sentence.empty()) sentence = sentence + " ";
            sentence = sentence + token;
            if (sentence.length() > (size_t)MAX_LEN) tooLong = true;   // захист від переповнення
        }
        if (token[token.length() - 1] == '.') finished = true;
    }
    flushLine();                       // залишок рядка після останнього слова

    if (!finished) {
        printf("Помилка: речення не завершено крапкою.\n");
        return;
    }
    if (tooLong) {
        printTextError(TEXT_TOO_LONG);
        return;
    }
    int st = validateText(sentence.c_str());
    if (st != TEXT_OK) {
        printTextError(st);
        return;
    }
    applyNewText(sentence.c_str(), text, words, count);
    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

// ---------- меню ----------

void printMenu() {
    printf("\n===== Меню =====\n");
    printf("1. Показати текст і статистику\n");
    printf("2. Таблиця слів\n");
    printf("3. Замінити слово\n");
    printf("4. Порівняти два слова\n");
    printf("5. Інформація про символ\n");
    printf("6. Ввести нове речення\n");
    printf("0. Вийти\n");
}

// Зчитує вибір. Повертає false при кінці вводу
bool readChoice(int &choice) {
    char line[64];
    printf("Ваш вибір: ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("\n");
        return false;
    }
    if (strchr(line, '\n') == NULL && strlen(line) == sizeof(line) - 1)
        flushLine();                       // задовгий рядок - відкидаємо залишок

    const char *p = line;
    while (isspace((unsigned char)*p)) ++p;
    bool neg = false;
    if (*p == '-' || *p == '+') { neg = (*p == '-'); ++p; }
    if (!isdigit((unsigned char)*p)) {
        printf("Помилка: введіть номер пункту меню.\n");
        choice = -1000000;
        return true;
    }
    long v = 0;
    while (isdigit((unsigned char)*p)) {
        if (v < 100000000L) v = v * 10 + (*p - '0');
        ++p;
    }
    while (isspace((unsigned char)*p)) ++p;
    if (*p != '\0') {                     
        printf("Помилка: введіть номер пункту меню.\n");
        choice = -1000000;
        return true;
    }
    choice = (int)(neg ? -v : v);
    return true;
}

int main() {
    char text[TEXT_SIZE];

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, TEXT_SIZE, stdin) == NULL) {
        printf("Помилка: текст не введено.\n");
        return 1;
    }
    size_t len = strlen(text);
    if (strchr(text, '\n') == NULL && len == (size_t)MAX_LEN) {
        int c = getchar();                 
        if (c != '\n' && c != EOF) {
            flushLine();
            printTextError(TEXT_TOO_LONG);
            return 1;
        }
    }
    while (len > 0 && isspace((unsigned char)text[len - 1]))   
        text[--len] = '\0';

    int st = validateText(text);
    if (st != TEXT_OK) {
        printTextError(st);
        return 1;
    }

    int count = 0;
    char **words = splitWords(text, count);

    bool running = true;
    while (running) {
        printMenu();
        int choice;
        if (!readChoice(choice)) break;
        if (choice == -1000000) continue;
        switch (choice) {
            case 1: showStats(text, count); break;
            case 2: showWordTable(words, count); break;
            case 3: replaceWord(text, words, count); break;
            case 4: compareWords(); break;
            case 5: charInfo(text); break;
            case 6: newSentence(text, words, count); break;
            case 0: running = false; break;
            default: printf("Помилка: пункту %d немає в меню.\n", choice);
        }
    }

    freeWords(words, count);               // пункт 7: звільнення памʼяті
    printf("Памʼять звільнено. До побачення!\n");
    return 0;
}