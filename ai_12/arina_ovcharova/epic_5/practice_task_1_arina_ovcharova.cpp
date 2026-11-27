// Epic 5, Class Practice - редактор текстового повідомлення
// у Windows перед запуском треба написати в консолі chcp 65001, бо інакше українські букви криві

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

const int TEXT_SIZE = 256;  // 255 символів + '\0'
const int MAX_TEXT_LEN = 255;
const int WORD_SIZE = 32;   // 31 символ + '\0'
const int MAX_WORD_LEN = 31;
const int LINE_SIZE = 64;   // буфер для рядка меню / символу

// --- Допоміжні функції вводу ---

// читаю рядок через fgets і прибираю '\n' (і '\r' з Windows)
// якщо рядок не вліз у буфер - дочитую решту і ставлю tooLong = true
bool readLine(char *buf, int size, bool &tooLong) {
    tooLong = false;
    if (fgets(buf, size, stdin) == NULL) {
        return false;
    }
    char *newline = strchr(buf, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else {
        // '\n' не вліз, отже рядок задовгий, дочитую залишок
        int c = getchar();
        if (c != '\n' && c != EOF) {
            tooLong = true;
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
        }
    }
    int len = (int)strlen(buf);
    if (len > 0 && buf[len - 1] == '\r') {
        buf[len - 1] = '\0';
    }
    return true;
}

// викидаю все до кінця рядка (після scanf і cin там лишається '\n')
void skipRestOfLine() {
    int c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

// одне слово через scanf, ширина поля 63, щоб не вилізти за масив
// lastChar - символ після слова, щоб знати, чи рядок вже закінчився
bool readWord(char *buf, bool &tooLong, int &lastChar) {
    char tmp[LINE_SIZE];
    tooLong = false;
    if (scanf("%63s", tmp) != 1) {
        lastChar = EOF;
        return false;
    }
    lastChar = getchar();
    if (lastChar != EOF && !isspace(lastChar)) {
        // слово довше за 63 символи - дочитую його
        tooLong = true;
        while (lastChar != EOF && !isspace(lastChar)) {
            lastChar = getchar();
        }
    }
    if (strlen(tmp) > (size_t)MAX_WORD_LEN) {
        tooLong = true;
    }
    if (!tooLong) {
        strcpy(buf, tmp);
    } else {
        buf[0] = '\0';
    }
    return true;
}

// --- Перевірки ---

// тільки латинська буква або цифра (кирилиця не підходить)
bool isLatinAlnum(char ch) {
    unsigned char c = (unsigned char)ch;
    return c < 128 && isalnum(c);
}

// текст правильний: є хоч одне слово, тільки латиниця, цифри і пробіли,
// а в кінці крапка
bool isValidText(const char *text) {
    int len = (int)strlen(text);
    if (len < 2 || len > MAX_TEXT_LEN || text[len - 1] != '.') {
        return false;
    }
    bool hasWord = false;
    for (int i = 0; i < len - 1; i++) {
        if (isLatinAlnum(text[i])) {
            hasWord = true;
        } else if (text[i] != ' ') {
            return false;
        }
    }
    return hasWord;
}

// слово для заміни/порівняння: не порожнє, до 31 символу, тільки букви і цифри
bool isValidWord(const char *word) {
    int len = (int)strlen(word);
    if (len == 0 || len > MAX_WORD_LEN) {
        return false;
    }
    for (const char *p = word; *p != '\0'; p++) {
        if (!isLatinAlnum(*p)) {
            return false;
        }
    }
    return true;
}

// --- Робота з динамічним масивом слів ---

// розбиваю текст на слова, масив слів динамічний
// кількість слів повертаю через посилання count
char **splitWords(const char *text, int &count) {
    char buffer[TEXT_SIZE];
    strcpy(buffer, text); // strtok псує рядок, тому працюю з копією

    // спочатку рахую слова, щоб знати, скільки пам'яті виділити
    count = 0;
    char *token = strtok(buffer, " .");
    while (token != NULL) {
        count++;
        token = strtok(NULL, " .");
    }

    char **words = new char *[count];

    strcpy(buffer, text);
    int i = 0;
    token = strtok(buffer, " .");
    while (token != NULL && i < count) {
        words[i] = new char[strlen(token) + 1];
        strcpy(words[i], token);
        i++;
        token = strtok(NULL, " .");
    }
    return words;
}

// звільняю пам'ять: спочатку кожне слово, потім сам масив
void freeWords(char **&words, int &count) {
    if (words != NULL) {
        for (int i = 0; i < count; i++) {
            delete[] words[i];
        }
        delete[] words;
    }
    words = NULL;
    count = 0;
}

// новий текст -> старі слова видаляю і розбиваю заново
void setText(char *text, const char *newText, char **&words, int &count) {
    strcpy(text, newText);
    freeWords(words, count);
    words = splitWords(text, count);
}

// сортування вставками (як в попередніх епіках)
// сортую тільки вказівники, сам масив words не чіпаю
void insertionSort(char **arr, int n) {
    for (int i = 1; i < n; i++) {
        char *key = arr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// --- Пункт 1. Текст і статистика ---

// рахую букви, цифри і пробіли, йду по тексту вказівником
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    for (const char *p = text; *p != '\0'; p++) {
        unsigned char c = (unsigned char)*p;
        if (isalpha(c)) {
            letters++;
        } else if (isdigit(c)) {
            digits++;
        } else if (c == ' ') {
            spaces++;
        }
    }
}

void showStatistics(const char *text, int count) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int total = (int)strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:\t%d\n", total);
    printf("Слів:\t\t%d\n", count);
    printf("Літер:\t\t%d (%5.1f%%)\n", letters, 100.0 * letters / total);
    printf("Цифр:\t\t%d (%5.1f%%)\n", digits, 100.0 * digits / total);
    printf("Пробілів:\t%d (%5.1f%%)\n", spaces, 100.0 * spaces / total);
}

// --- Пункт 2. Таблиця слів ---

void printTableLine(int wordWidth) {
    printf("+----+");
    for (int i = 0; i < wordWidth + 2; i++) {
        printf("-");
    }
    printf("+-------+\n");
}

void showWordTable(char **words, int count) {
    // ширина колонки - мінімум 15, або довжина найдовшого слова
    int wordWidth = 15;
    for (int i = 0; i < count; i++) {
        int len = (int)strlen(words[i]);
        if (len > wordWidth) {
            wordWidth = len;
        }
    }

    printTableLine(wordWidth);
    // "Слово" в UTF-8 займає 10 байт, а не 5, тому %-15s криво вирівнює,
    // доповнюю пробілами сама
    printf("| %2s | Слово%*s | Довж. |\n", "N", wordWidth - 5, "");
    printTableLine(wordWidth);

    int longest = 0, shortest = 0, totalLen = 0;
    for (int i = 0; i < count; i++) {
        int len = (int)strlen(words[i]);
        printf("| %2d | %-*s | %5d |\n", i + 1, wordWidth, words[i], len);
        totalLen += len;
        if (len > (int)strlen(words[longest])) {
            longest = i;
        }
        if (len < (int)strlen(words[shortest])) {
            shortest = i;
        }
    }
    printTableLine(wordWidth);

    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)totalLen / count);

    // копія вказівників, щоб порядок у words не змінився
    char **sorted = new char *[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }
    insertionSort(sorted, count);

    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    // після сортування однакові слова стоять поруч, рахую групи
    // ">" а не ">=", щоб при однаковій кількості лишилось перше за абеткою
    int bestIndex = 0, bestCount = 0;
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

// --- Пункт 3. Заміна слова (засобами std::string) ---

// межа слова - пробіл, крапка або кінець рядка
bool isWordBorder(char ch) {
    return ch == ' ' || ch == '.' || ch == '\0';
}

void replaceWord(char *text, char **&words, int &count) {
    char from[WORD_SIZE], to[WORD_SIZE];
    bool tooLongFrom, tooLongTo;
    int lastChar;

    printf("Замінити слово: ");
    if (!readWord(from, tooLongFrom, lastChar)) {
        return;
    }
    printf("На слово: ");
    if (!readWord(to, tooLongTo, lastChar)) {
        return;
    }
    if (lastChar != '\n' && lastChar != EOF) {
        skipRestOfLine();
    }

    if (tooLongFrom || tooLongTo) {
        printf("Помилка: слово має бути не довшим за %d символ. Текст не змінено.\n",
               MAX_WORD_LEN);
        return;
    }
    if (!isValidWord(from)) {
        printf("Помилка: слово \"%s\" має складатися лише з латинських літер і цифр.\n", from);
        return;
    }
    if (!isValidWord(to)) {
        printf("Помилка: нове слово \"%s\" має складатися лише з латинських літер і цифр. "
               "Текст не змінено.\n", to);
        return;
    }

    std::string result(text);
    std::string oldWord(from);
    std::string newWord(to);
    int replacements = 0;

    size_t pos = result.find(oldWord);
    while (pos != std::string::npos) {
        // міняю тільки ціле слово: зліва початок або пробіл,
        // справа пробіл, крапка або кінець (щоб cat в cats не замінилось)
        bool leftOk = (pos == 0) || result[pos - 1] == ' ';
        size_t end = pos + oldWord.length();
        bool rightOk = (end >= result.length()) || isWordBorder(result[end]);

        if (leftOk && rightOk) {
            result.replace(pos, oldWord.length(), newWord);
            replacements++;
            pos = result.find(oldWord, pos + newWord.length());
        } else {
            pos = result.find(oldWord, pos + 1);
        }
    }

    if (result.length() > (size_t)MAX_TEXT_LEN) {
        printf("Помилка: після заміни текст мав би %d символів (максимум %d). "
               "Текст не змінено.\n", (int)result.length(), MAX_TEXT_LEN);
        return;
    }

    printf("Замін виконано: %d\n", replacements);
    printf("Було:\t\"%s\"\n", text);
    if (replacements > 0) {
        setText(text, result.c_str(), words, count);
    }
    printf("Стало:\t\"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));
}

// --- Пункт 4. Порівняння двох слів ---

// порівнюю без регістру через tolower
bool equalsIgnoreCase(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return false;
        }
        a++;
        b++;
    }
    return *a == *b; // якщо одне слово довше - вони різні
}

void compareWords() {
    char a[WORD_SIZE], b[WORD_SIZE];
    bool tooLongA, tooLongB;
    int lastChar;

    printf("Перше слово: ");
    if (!readWord(a, tooLongA, lastChar)) {
        return;
    }
    printf("Друге слово: ");
    if (!readWord(b, tooLongB, lastChar)) {
        return;
    }
    if (lastChar != '\n' && lastChar != EOF) {
        skipRestOfLine();
    }

    if (tooLongA || tooLongB) {
        printf("Помилка: слово має бути не довшим за %d символ.\n", MAX_WORD_LEN);
        return;
    }
    if (!isValidWord(a) || !isValidWord(b)) {
        printf("Помилка: слова мають складатися лише з латинських літер і цифр.\n");
        return;
    }

    int cmp = strcmp(a, b);
    int sign = (cmp < 0) ? -1 : (cmp > 0 ? 1 : 0);
    const char *meaning;
    if (sign < 0) {
        meaning = "перше слово менше";
    } else if (sign > 0) {
        meaning = "перше слово більше";
    } else {
        meaning = "слова однакові";
    }

    std::string first(a);
    std::string second(b);
    std::string joined = first + " & " + second;

    printf("strcmp: %d -> %s\n", sign, meaning);
    printf("Рівні (==): %s\n", (first == second) ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", equalsIgnoreCase(a, b) ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)first.length(), (int)second.length());
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}

// --- Пункт 5. Інформація про символ ---

// двійковий код: беру біти з 7-го по 0-й зсувом >> і & 1
void printBinary(unsigned char code) {
    for (int bit = 7; bit >= 0; bit--) {
        printf("%d", (code >> bit) & 1);
    }
}

// друкую символ в лапках, пробіл і таб окремо, бо їх не видно
void printCharQuoted(unsigned char c) {
    if (c == ' ') {
        printf("' '");
    } else if (c == '\t') {
        printf("'\\t'");
    } else if (isprint(c)) {
        printf("'%c'", c);
    } else {
        printf("(код %d)", c);
    }
}

void charInfo(const char *text) {
    char line[LINE_SIZE];
    bool tooLong;

    printf("Введіть символ: ");
    if (!readLine(line, LINE_SIZE, tooLong)) {
        return;
    }
    if (tooLong || strlen(line) != 1 || (unsigned char)line[0] >= 128) {
        printf("Помилка: введіть рівно один символ латиниці, цифру або розділовий знак.\n");
        return;
    }

    unsigned char c = (unsigned char)line[0];

    printf("Символ: ");
    printCharQuoted(c);
    printf("\n");
    printf("Код: %d (hex %#x, oct %#o, bin ", c, c, c);
    printBinary(c);
    printf(")\n");

    printf("Тип: ");
    if (isupper(c)) {
        printf("велика літера\n");
    } else if (islower(c)) {
        printf("мала літера\n");
    } else if (isdigit(c)) {
        printf("цифра\n");
    } else if (isspace(c)) {
        printf("пробільний символ\n");
    } else {
        printf("інший символ\n");
    }

    if (isalpha(c)) {
        // 'a' - 'A' = 32, так міняю регістр
        unsigned char other = isupper(c) ? (unsigned char)(c + ('a' - 'A'))
                                         : (unsigned char)(c - ('a' - 'A'));
        printf("Інший регістр: '%c'\n", other);
    }
    printf("Наступний символ: ");
    printCharQuoted((unsigned char)(c + 1));
    printf("\n");

    // шукаю через strchr, позицію рахую з 1
    const char *first = strchr(text, c);
    if (first == NULL) {
        printf("Символ у тексті не зустрічається.\n");
        return;
    }
    int occurrences = 0;
    for (const char *p = first; p != NULL; p = strchr(p + 1, c)) {
        occurrences++;
    }
    printf("Входжень у тексті: %d, перше на позиції %d\n",
           occurrences, (int)(first - text) + 1);
}

// --- Пункт 6. Нове речення (по словах через cin >>) ---

void newSentence(char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");
    fflush(stdout);

    std::string sentence;
    std::string word;
    int tokens = 0;
    bool finished = false;

    while (!finished && std::cin >> word) {
        if (tokens > 0) {
            sentence += " ";
        }
        sentence += word;
        tokens++;
        if (word[word.length() - 1] == '.') {
            finished = true;
        }
    }
    if (finished) {
        skipRestOfLine(); // прибираю '\n' після крапки
    } else {
        std::cin.clear();
        printf("\nПомилка: речення не завершено крапкою. Текст не змінено.\n");
        return;
    }

    if (sentence.length() > (size_t)MAX_TEXT_LEN) {
        printf("Помилка: речення довше за %d символів. Текст не змінено.\n", MAX_TEXT_LEN);
        return;
    }
    if (!isValidText(sentence.c_str())) {
        printf("Помилка: речення має складатися з латинських літер, цифр і пробілів "
               "та завершуватися крапкою. Текст не змінено.\n");
        return;
    }

    setText(text, sentence.c_str(), words, count);
    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

// --- Меню ---

void printMenu() {
    printf("\n========== МЕНЮ ==========\n");
    printf(" 1\tПоказати текст і статистику\n");
    printf(" 2\tТаблиця слів\n");
    printf(" 3\tЗамінити слово\n");
    printf(" 4\tПорівняти два слова\n");
    printf(" 5\tІнформація про символ\n");
    printf(" 6\tВвести нове речення\n");
    printf(" 0\tВийти\n");
    printf("==========================\n");
}

// номер пункту меню: -1 якщо ввели щось не те, -2 якщо ввід закінчився
int readMenuChoice() {
    char line[LINE_SIZE];
    bool tooLong;

    printf("Ваш вибір: ");
    if (!readLine(line, LINE_SIZE, tooLong)) {
        return -2;
    }

    // пробіли пропускаю, далі мають бути тільки цифри
    const char *p = line;
    while (*p == ' ' || *p == '\t') {
        p++;
    }
    const char *start = p;
    while (isdigit((unsigned char)*p)) {
        p++;
    }
    const char *end = p;
    while (*p == ' ' || *p == '\t') {
        p++;
    }

    if (tooLong || start == end || *p != '\0' || end - start > 5) {
        printf("Помилка: введіть номер пункту меню.\n");
        return -1;
    }

    int choice = 0;
    sscanf(start, "%d", &choice);
    if (choice > 6) {
        printf("Помилка: пункту %d немає в меню.\n", choice);
        return -1;
    }
    return choice;
}

int main() {
    char text[TEXT_SIZE];
    bool tooLong;

    printf("Введіть текст (до %d символів, крапка в кінці):\n", MAX_TEXT_LEN);
    if (!readLine(text, TEXT_SIZE, tooLong)) {
        printf("Помилка: текст не введено.\n");
        return 1;
    }
    if (tooLong) {
        printf("Помилка: текст довший за %d символів.\n", MAX_TEXT_LEN);
        return 1;
    }
    if (!isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n"
               "і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int count = 0;
    char **words = splitWords(text, count);

    bool running = true;
    while (running) {
        printMenu();
        int choice = readMenuChoice();
        switch (choice) {
            case 1: showStatistics(text, count); break;
            case 2: showWordTable(words, count); break;
            case 3: replaceWord(text, words, count); break;
            case 4: compareWords(); break;
            case 5: charInfo(text); break;
            case 6: newSentence(text, words, count); break;
            case 0:
            case -2: running = false; break;
            default: break; // помилку вже вивела
        }
    }

    freeWords(words, count);
    printf("До побачення!\n");
    return 0;
}
