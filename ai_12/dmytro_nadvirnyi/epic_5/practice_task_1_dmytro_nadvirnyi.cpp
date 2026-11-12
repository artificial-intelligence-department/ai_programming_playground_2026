#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <cstdio>

const size_t MAX_WORD_LEN = 31;
const size_t WORD_BUF_SIZE = MAX_WORD_LEN + 1; // 32 байти (31 символ + '\0')

// Допоміжна функція: перевірка, чи є символ латинською літерою або цифрою (DRY)
bool isLatinAlnum(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}

// Зчитування тексту через fgets із захистом від переповнення та очищенням потоку
bool readText(char *buf, size_t size) {
    printf("Введіть текст (до 255 символів, крапка в кінці): ");
    if (fgets(buf, (int)size, stdin) == NULL) {
        printf("Помилка зчитування або кінець файлу (EOF).\n");
        return false;
    }

    // 1. Обробка завершення рядка та переповнення (> 255)
    char *newline = strchr(buf, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else {
        size_t len = strlen(buf);
        if (len == size - 1) {
            int nextChar = getchar();
            if (nextChar == '\r') {
                nextChar = getchar();
            }
            if (nextChar != '\n' && nextChar != EOF) {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {
                    // вичищаємо залишки у потоці
                }
                printf("Помилка: довжина тексту перевищує 255 символів.\n");
                return false;
            }
        }
    }

    // 2. Безпечно прибираємо '\r' у кінці, якщо він лишився (для Windows CRLF)
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\r') {
        buf[len - 1] = '\0';
    }

    return true;
}

/*
 * Правила валідації тексту (для блок-схеми та захисту):
 * 1. Текст не може бути порожнім.
 * 2. Текст обов'язково завершується крапкою '.'.
 * 3. Крапка дозволена ТІЛЬКИ в кінці; крапки в середині речення заборонені.
 * 4. До крапки дозволені виключно латинські літери ('a'..'z', 'A'..'Z'), цифри ('0'..'9') та пробіли (' ').
 * 5. Пробіли допустимі на початку тексту, між словами (у будь-якій кількості) та перед крапкою (наприклад "cat .").
 * 6. Текст повинен містити хоча б одне слово (хоча б одну літеру чи цифру). Рядки "." або "   ." — некоректні.
 */
bool isValidText(const char *text) {
    if (text == nullptr || *text == '\0') {
        return false;
    }

    size_t len = strlen(text);
    if (text[len - 1] != '.') {
        return false;
    }

    bool hasWord = false;
    const char *p = text;
    const char *end = text + len - 1; // вказівник на завершальну крапку

    while (p < end) {
        if (isLatinAlnum(*p)) {
            hasWord = true;
        } else if (*p == ' ') {
            // Пробіл дозволений
        } else {
            return false;
        }
        ++p;
    }

    return hasWord;
}

// Підрахунок символів за допомогою вказівника та посилань
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;

    const char *p = text;
    while (*p != '\0') {
        if (std::isalpha((unsigned char)*p)) {
            ++letters;
        } else if (std::isdigit((unsigned char)*p)) {
            ++digits;
        } else if (*p == ' ') {
            ++spaces;
        }
        ++p;
    }
}

// Розбиття тексту на слова у 2 проходи із виділенням динамічної пам'яті
char **splitWords(const char *text, int &count) {
    count = 0;
    size_t len = strlen(text) + 1;

    // Прохід 1: підрахунок кількості слів
    char *copy1 = new char[len];
    strcpy(copy1, text);

    char *token = strtok(copy1, " .");
    while (token != nullptr) {
        ++count;
        token = strtok(nullptr, " .");
    }
    delete[] copy1;

    if (count == 0) {
        return nullptr;
    }

    // Виділяємо масив вказівників
    char **words = new char *[count];

    // Прохід 2: копіювання кожного слова в окрему пам'ять
    char *copy2 = new char[len];
    strcpy(copy2, text);

    int i = 0;
    token = strtok(copy2, " .");
    while (token != nullptr) {
        words[i] = new char[strlen(token) + 1];
        strcpy(words[i], token);
        ++i;
        token = strtok(nullptr, " .");
    }
    delete[] copy2;

    return words;
}

// Звільнення динамічної пам'яті масиву слів
void freeWords(char **&words, int &count) {
    if (words == nullptr) {
        return;
    }

    for (int i = 0; i < count; ++i) {
        delete[] words[i];
    }
    delete[] words;

    words = nullptr;
    count = 0;
}

void printMenu() {
    printf("\n--- Меню ---\n");
    printf("1. Показати текст і статистику\n");
    printf("2. Таблиця слів\n");
    printf("3. Замінити слово\n");
    printf("4. Порівняти два слова\n");
    printf("5. Інформація про символ\n");
    printf("6. Ввести нове речення\n");
    printf("0. Вийти\n");
}

/*
 * Правила валідації вибору пункту меню:
 * 1. Очікується ціле число від 0 до 6.
 * 2. Будь-які нечислові символи або рядок із літерами після числа ("3abc")
 *    відхиляються ("Помилка: введіть номер пункту меню.").
 * 3. Число поза межами 0..6 відхиляється ("Помилка: пункту N немає в меню.").
 * 4. Залишок рядка обов'язково вичищається з потоку stdin.
 * 5. При досягненні EOF повертається 0 (коректне завершення роботи).
 */
int readMenuChoice() {
    int choice;
    while (true) {
        printf("Ваш вибір: ");
        int res = scanf("%d", &choice);

        if (res == EOF) {
            return 0;
        }

        if (res == 0) {
            printf("Помилка: введіть номер пункту меню.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            continue;
        }

        bool hasExtraChars = false;
        int nextChar = getchar();
        while (nextChar != '\n' && nextChar != EOF) {
            if (!std::isspace((unsigned char)nextChar)) {
                hasExtraChars = true;
            }
            nextChar = getchar();
        }

        if (hasExtraChars) {
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }

        if (choice < 0 || choice > 6) {
            printf("Помилка: пункту %d немає в меню.\n", choice);
            continue;
        }

        return choice;
    }
}

// Допоміжні функції для Пункту 2
void printTableBorder(int numColWidth, int wordColWidth) {
    printf("+");
    for (int i = 0; i < numColWidth + 2; ++i) putchar('-');
    printf("+");
    for (int i = 0; i < wordColWidth + 2; ++i) putchar('-');
    printf("+-------+\n");
}

void sortWordPointers(char **arr, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void findExtremes(char **words, int count, int &longestIdx, int &shortestIdx, int &totalLength) {
    longestIdx = 0;
    shortestIdx = 0;
    size_t maxLen = strlen(words[0]);
    size_t minLen = strlen(words[0]);
    totalLength = 0;

    for (int i = 0; i < count; ++i) {
        size_t len = strlen(words[i]);
        totalLength += (int)len;

        if (len > maxLen) {
            maxLen = len;
            longestIdx = i;
        }
        if (len < minLen) {
            minLen = len;
            shortestIdx = i;
        }
    }
}

void findMostFrequentWord(char **sorted, int count, const char *&bestWord, int &bestFreq) {
    bestWord = sorted[0];
    bestFreq = 1;
    int currentFreq = 1;

    for (int i = 1; i < count; ++i) {
        if (strcmp(sorted[i], sorted[i - 1]) == 0) {
            ++currentFreq;
        } else {
            if (currentFreq > bestFreq) {
                bestFreq = currentFreq;
                bestWord = sorted[i - 1];
            }
            currentFreq = 1;
        }
    }
    if (currentFreq > bestFreq) {
        bestFreq = currentFreq;
        bestWord = sorted[count - 1];
    }
}

/*
 * Правила зчитування та валідації окремого слова:
 * 1. Формат зчитування формується динамічно через snprintf (наприклад "%31s"),
 *    що гарантує захист від виходу за межі буфера bufSize.
 * 2. Якщо після (bufSize - 1) символів є продовження слова (не пробіл/Enter),
 *    це фіксується як перевищення ліміту довжини.
 * 3. В одному рядку дозволено лише ОДНЕ слово ("cat tiger" відхиляється).
 * 4. Залишок рядка обов'язково вичищається з потоку stdin до Enter або EOF.
 * 5. Слово має містити виключно латинські літери та цифри (isLatinAlnum).
 * 6. Натискання Enter на початку ігнорується (поведінка специфікатора %s у scanf).
 * 7. При досягненні EOF повертається false для чистого виходу.
 */
bool readWord(const char *prompt, char *buf, size_t bufSize) {
    printf("%s", prompt);

    char fmt[16];
    snprintf(fmt, sizeof(fmt), "%%%zus", bufSize - 1);

    int res = scanf(fmt, buf);

    if (res == EOF) {
        return false;
    }
    if (res == 0) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        printf("Помилка: не вдалося зчитати слово.\n");
        return false;
    }

    int nextChar = getchar();
    bool overflow = false;
    bool extraWords = false;

    if (nextChar != '\n' && nextChar != EOF && !std::isspace((unsigned char)nextChar)) {
        overflow = true;
    }

    while (nextChar != '\n' && nextChar != EOF) {
        if (!std::isspace((unsigned char)nextChar)) {
            extraWords = true;
        }
        nextChar = getchar();
    }

    if (overflow) {
        printf("Помилка: слово має бути не довшим за %zu символів.\n", bufSize - 1);
        return false;
    }

    if (extraWords) {
        printf("Помилка: введіть лише одне слово в рядку.\n");
        return false;
    }

    for (const char *p = buf; *p != '\0'; ++p) {
        if (!isLatinAlnum(*p)) {
            printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
            return false;
        }
    }

    return true;
}

// Допоміжні функції для заміни слів (Пункт 3)
bool isWholeWord(const std::string &s, size_t pos, size_t len) {
    bool leftOk = (pos == 0) || !isLatinAlnum(s[pos - 1]);
    bool rightOk = (pos + len == s.length()) || !isLatinAlnum(s[pos + len]);
    return leftOk && rightOk;
}

std::string replaceAllWholeWords(const std::string &src, const std::string &from, const std::string &to, int &replacements) {
    replacements = 0;
    if (from.empty()) {
        return src;
    }

    std::string result = src;
    size_t pos = 0;
    size_t fromLen = from.length();
    size_t toLen = to.length();

    while ((pos = result.find(from, pos)) != std::string::npos) {
        if (isWholeWord(result, pos, fromLen)) {
            result.replace(pos, fromLen, to);
            ++replacements;
            pos += toLen; // перестрибуємо замінене слово для уникнення зациклення
        } else {
            pos += 1;     // збіг всередині слова (наприклад cat у cats)
        }
    }

    return result;
}

// Спільна функція для оновлення text і перебудови words (Пункти 3 і 6, DRY)
bool applyNewText(char *text, size_t maxLen, const std::string &newText, char **&words, int &count) {
    if (newText.length() >= maxLen) {
        printf("Помилка: довжина тексту перевищує 255 символів.\n");
        return false;
    }

    strcpy(text, newText.c_str());

    freeWords(words, count);
    words = splitWords(text, count);

    return true;
}

// Допоміжна функція: порівняння без урахування регістру (Пункт 4)
bool equalsIgnoreCase(const std::string &s1, const std::string &s2) {
    if (s1.length() != s2.length()) {
        return false;
    }
    for (size_t i = 0; i < s1.length(); ++i) {
        if (std::tolower((unsigned char)s1[i]) != std::tolower((unsigned char)s2[i])) {
            return false;
        }
    }
    return true;
}

// Допоміжна функція: безпечне зчитування одного символу (Пункт 5)
bool readSingleChar(const char *prompt, char &target) {
    printf("%s", prompt);

    int ch = getchar();

    if (ch == EOF) {
        return false;
    }
    if (ch == '\n') {
        printf("Помилка: введіть один символ.\n");
        return false;
    }

    // Відхиляємо код 0 (Ctrl+@) та будь-які не-ASCII символи (> 127)
    if (ch <= 0 || ch > 127) {
        int rest;
        while ((rest = getchar()) != '\n' && rest != EOF) {}
        printf("Помилка: дозволені лише символи ASCII.\n");
        return false;
    }

    target = (char)ch;

    int next = getchar();
    if (next == '\r') {
        int afterCr = getchar();
        if (afterCr == '\n') {
            next = '\n';
        } else {
            ungetc(afterCr, stdin);
        }
    }

    bool hasExtra = false;
    while (next != '\n' && next != EOF) {
        hasExtra = true;
        next = getchar();
    }

    if (hasExtra) {
        printf("Помилка: введіть лише один символ.\n");
        return false;
    }

    return true;
}

// === ФУНКЦІЇ ПУНКТІВ МЕНЮ 1-6 ===

void item1_showStats(const char *text, int wordCount) {
    int letters = 0, digits = 0, spaces = 0;
    countChars(text, letters, digits, spaces);

    int totalLen = (int)strlen(text);

    double lettersPct = (totalLen > 0) ? ((double)letters * 100.0 / totalLen) : 0.0;
    double digitsPct  = (totalLen > 0) ? ((double)digits * 100.0 / totalLen) : 0.0;
    double spacesPct  = (totalLen > 0) ? ((double)spaces * 100.0 / totalLen) : 0.0;

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %5d\n", totalLen);
    printf("Слів:     %5d\n", wordCount);
    printf("Літер:    %5d (%5.1f%%)\n", letters, lettersPct);
    printf("Цифр:     %5d (%5.1f%%)\n", digits, digitsPct);
    printf("Пробілів: %5d (%5.1f%%)\n", spaces, spacesPct);
}

/*
 * Пункт 2: Таблиця слів, статистика, сортування та найчастіше слово.
 * Рішення та правила:
 * 1. Адаптивна ширина: колонка N розширюється при count >= 100, колонка слова — за найдовшим словом (не менше 15).
 * 2. Строге порівняння (> та <) для екстремумів гарантує вибір першого слова за появою.
 * 3. Порядок у words не змінюється: сортується окрема поверхнева копія вказівників sorted.
 * 4. Безпека пам'яті: звільняється ТІЛЬКИ delete[] sorted (рядки належать words).
 * 5. Найчастіше слово шукається за один прохід; строге '>' обирає перше за абеткою при однаковій кількості.
 */
void item2_wordTable(char **words, int count) {
    if (words == nullptr || count <= 0) {
        printf("Текст не містить слів.\n");
        return;
    }

    int longestIdx = 0, shortestIdx = 0, totalLength = 0;
    findExtremes(words, count, longestIdx, shortestIdx, totalLength);

    size_t maxLen = strlen(words[longestIdx]);
    int numColWidth = (count >= 100) ? 3 : 2;
    int wordColWidth = (maxLen > 15) ? (int)maxLen : 15;

    printTableBorder(numColWidth, wordColWidth);

    printf("| %-*s | Слово", numColWidth, "N");
    for (int s = 0; s < wordColWidth - 5; ++s) putchar(' ');
    printf(" | Довж. |\n");

    printTableBorder(numColWidth, wordColWidth);

    for (int i = 0; i < count; ++i) {
        printf("| %*d | %-*s | %5d |\n", numColWidth, i + 1, wordColWidth, words[i], (int)strlen(words[i]));
    }

    printTableBorder(numColWidth, wordColWidth);

    double avgLen = (count > 0) ? ((double)totalLength / count) : 0.0;
    printf("Найдовше слово: %s (%d)\n", words[longestIdx], (int)maxLen);
    printf("Найкоротше слово: %s (%d)\n", words[shortestIdx], (int)strlen(words[shortestIdx]));
    printf("Середня довжина: %.2f\n", avgLen);

    char **sorted = new char*[count];
    for (int i = 0; i < count; ++i) sorted[i] = words[i];
    sortWordPointers(sorted, count);

    printf("За абеткою: ");
    for (int i = 0; i < count; ++i) {
        printf("%s%s", sorted[i], (i == count - 1) ? "" : " ");
    }
    printf("\n");

    const char *mostFreqWord = nullptr;
    int maxFreq = 0;
    findMostFrequentWord(sorted, count, mostFreqWord, maxFreq);
    printf("Найчастіше слово: %s (%d)\n", mostFreqWord, maxFreq);

    delete[] sorted;
}

/*
 * Пункт 3: Заміна цілих слів у тексті.
 * Рішення та правила:
 * 1. Ввід слів from і to контролюється readWord (до 31 символу, лише латиниця й цифри).
 * 2. Заміна здійснюється тільки для цілих слів із урахуванням регістру через replaceAllWholeWords.
 * 3. Перевірка ліміту 255 символів виконується ДО будь-яких змін через applyNewText.
 * 4. Рішення щодо нуля замін: якщо замін не було, текст не змінився, перебудова words не виконується.
 * 5. Заміна слова на саме себе (cat -> cat) валідна, кількість рахується, зациклення відсутнє завдяки pos += toLen.
 */
void item3_replaceWord(char *text, size_t maxLen, char **&words, int &count) {
    char fromBuf[WORD_BUF_SIZE];
    char toBuf[WORD_BUF_SIZE];

    if (!readWord("Замінити слово: ", fromBuf, sizeof(fromBuf))) {
        return;
    }
    if (!readWord("На слово: ", toBuf, sizeof(toBuf))) {
        return;
    }

    std::string textStr(text);
    std::string fromStr(fromBuf);
    std::string toStr(toBuf);

    int replacements = 0;
    std::string updated = replaceAllWholeWords(textStr, fromStr, toStr, replacements);

    if (replacements > 0) {
        if (!applyNewText(text, maxLen, updated, words, count)) {
            return;
        }
    }

    printf("Замін виконано: %d\n", replacements);
    printf("Було:  \"%s\"\n", textStr.c_str());
    printf("Стало: \"%s\"\n", updated.c_str());
    printf("Нова довжина: %zu\n", updated.length());
}

/*
 * Пункт 4: Порівняння двох слів.
 * Рішення та правила:
 * 1. Обидва слова валідуються через readWord (до 31 символу, лише латиниця й цифри).
 * 2. Результат strcmp нормалізується до строгого -1, 0 або 1 із текстовим поясненням.
 * 3. Рівність за вмістом перевіряється оператором == для std::string (а не на рівність адрес char*).
 * 4. Регістронезалежне порівняння через equalsIgnoreCase виконується без зміни оригіналів.
 * 5. Конкатенація формується через оператор + у std::string (довжина береться через length()).
 */
void item4_compareWords() {
    char first[WORD_BUF_SIZE];
    char second[WORD_BUF_SIZE];

    if (!readWord("Перше слово: ", first, sizeof(first))) {
        return;
    }
    if (!readWord("Друге слово: ", second, sizeof(second))) {
        return;
    }

    int cmp = strcmp(first, second);
    int sign = 0;
    const char *explanation = "";

    if (cmp < 0) {
        sign = -1;
        explanation = "перше слово менше";
    } else if (cmp > 0) {
        sign = 1;
        explanation = "перше слово більше";
    } else {
        sign = 0;
        explanation = "слова однакові";
    }
    printf("strcmp: %d -> %s\n", sign, explanation);

    std::string s1(first);
    std::string s2(second);
    printf("Рівні (==): %s\n", (s1 == s2) ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", equalsIgnoreCase(s1, s2) ? "так" : "ні");
    printf("Довжини: %zu і %zu\n", s1.length(), s2.length());

    std::string concatenated = s1 + " & " + s2;
    printf("Конкатенація: \"%s\" (%zu)\n", concatenated.c_str(), concatenated.length());
}

/*
 * Пункт 5: Інформація про символ.
 * Рішення та правила:
 * 1. Зчитується один символ ASCII (код 1..127); код 0 (Ctrl+@), кирилиця та кілька символів у рядку відхиляються.
 * 2. Двійковий код формується через побітові операції (>> та & 1), hex і oct через %x та 0%o.
 * 3. Тип визначається функціями <cctype>; інший регістр ('a' - 'A') і наступний символ (c + 1) — лише для літер.
 * 4. Перша позиція визначається через strchr (різниця вказівників + 1), загальна кількість — проходом по тексту.
 */
void item5_charInfo(const char *text) {
    char c = '\0';
    if (!readSingleChar("Введіть символ: ", c)) {
        return;
    }

    unsigned char ucode = (unsigned char)c;

    char binStr[9];
    for (int i = 7; i >= 0; --i) {
        binStr[7 - i] = ((ucode >> i) & 1) ? '1' : '0';
    }
    binStr[8] = '\0';

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n", (int)ucode, (int)ucode, (int)ucode, binStr);

    const char *typeName = "";
    if (std::isupper(ucode)) {
        typeName = "велика літера";
    } else if (std::islower(ucode)) {
        typeName = "мала літера";
    } else if (std::isdigit(ucode)) {
        typeName = "цифра";
    } else if (std::isspace(ucode)) {
        typeName = "пробільний символ";
    } else {
        typeName = "інший символ";
    }
    printf("Тип: %s\n", typeName);

    if (std::isalpha(ucode)) {
        char otherCase = '\0';
        if (std::islower(ucode)) {
            otherCase = (char)(c - ('a' - 'A'));
        } else {
            otherCase = (char)(c + ('a' - 'A'));
        }
        char nextChar = (char)(c + 1);

        printf("Інший регістр: '%c'\n", otherCase);
        printf("Наступний символ: '%c'\n", nextChar);
    }

    int occurrences = 0;
    int firstPos = 0;

    const char *firstFound = strchr(text, c);
    if (firstFound != nullptr) {
        firstPos = (int)(firstFound - text) + 1;
    }

    const char *p = text;
    while (*p != '\0') {
        if (*p == c) {
            ++occurrences;
        }
        ++p;
    }

    if (occurrences > 0) {
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, firstPos);
    } else {
        printf("Символ у тексті відсутній.\n");
    }
}

/*
 * Пункт 6: Введення нового речення через cin >>
 * Рішення та правила:
 * 1. Читання по словах оператором cin >> у циклі while, доки чергове слово не закінчиться на '.'.
 * 2. Багаторядковий ввід підтримується автоматично, слова з'єднуються через рівно один пробіл.
 * 3. Якщо ввід містить слово-крапку ("a b ."), вона стає завершенням речення ("a b ."),
 *    що валідується за правилами закінчення на крапку.
 * 4. Залишок рядка після слова з крапкою вичищається до Enter (\n).
 * 5. Якщо потік завершився до крапки (EOF) — виводиться повідомлення про помилку.
 * 6. Оновлення text і words виконується атомарно через applyNewText.
 */
void item6_newSentence(char *text, size_t maxLen, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");

    std::string word;
    std::string newSentence;
    int wordsRead = 0;
    bool finishedWithDot = false;

    while (std::cin >> word) {
        ++wordsRead;

        if (!newSentence.empty()) {
            newSentence += " ";
        }
        newSentence += word;

        if (!word.empty() && word.back() == '.') {
            finishedWithDot = true;
            break;
        }
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}

    if (!finishedWithDot) {
        printf("Помилка: речення має завершуватися крапкою.\n");
        return;
    }

    if (!isValidText(newSentence.c_str())) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }

    if (!applyNewText(text, maxLen, newSentence, words, count)) {
        return;
    }

    printf("Прочитано слів: %d\n", wordsRead);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", strlen(text));
}

int main() {
    char text[256];

    if (!readText(text, sizeof(text))) {
        return 1;
    }

    if (!isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int wordCount = 0;
    char **words = splitWords(text, wordCount);

    int choice = 0;
    do {
        printMenu();
        choice = readMenuChoice();

        switch (choice) {
            case 1:
                item1_showStats(text, wordCount);
                break;
            case 2:
                item2_wordTable(words, wordCount);
                break;
            case 3:
                item3_replaceWord(text, sizeof(text), words, wordCount);
                break;
            case 4:
                item4_compareWords();
                break;
            case 5:
                item5_charInfo(text);
                break;
            case 6:
                item6_newSentence(text, sizeof(text), words, wordCount);
                break;
            case 0:
                printf("Вихід із програми.\n");
                break;
        }
    } while (choice != 0);

    freeWords(words, wordCount);

    return 0;
}