//Проскурня Дмитро ШІ-13
//Редактор текстового повідомлення

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

bool isValidText(const char* text);
char** splitWords(const char* text, int& count);
void freeWords(char**& words, int& count);
void countChars(const char* text, int& letters, int& digits, int& spaces);
void sortWords(const char** arr, int n);
bool equalIgnoreCase(const char* x, const char* y);
bool readWord(char* buf);
int readMenuChoice();
void clearLine();

void showStatistics(const char* text, int count);
void showWordTable(char** words, int count);
void replaceWord(char* text, char**& words, int& count);
void compareWords();
void charInfo(const char* text);
void enterSentence(char* text, char**& words, int& count);

// Головна функція: зчитує й перевіряє початковий текст, будує масив слів,
// у циклі показує меню та викликає потрібний пункт, при виході звільняє пам'ять
int main() {
    char text[256];

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    if (!isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n");
        printf("і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int count = 0;
    char** words = splitWords(text, count);

    do {
        printf("\n1 Показати текст і статистику\n");
        printf("2 Таблиця слів\n");
        printf("3 Замінити слово\n");
        printf("4 Порівняти два слова\n");
        printf("5 Інформація про символ\n");
        printf("6 Ввести нове речення\n");
        printf("0 Вийти\n");

        int action;
        while (true) {
            printf("Ваш вибір: ");
            action = readMenuChoice();
            if (action == -1) {
                printf("Помилка: введіть номер пункту меню.\n");
            } else if (action > 6) {
                printf("Помилка: пункту %d немає в меню.\n", action);
            } else {
                break;
            }
        }
        printf("\n");

        switch (action)
        {
        case 1:
            showStatistics(text, count);
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
            charInfo(text);
            break;

        case 6:
            enterSentence(text, words, count);
            break;

        case 0:
            freeWords(words, count);
            printf("Роботу завершено\n");
            return 0;
        }
    } while (true);
}

// ---------- допоміжні функції ----------

// Перевіряє, що текст коректний: є хоча б одне слово, лише латинські літери,
// цифри й пробіли, а в кінці стоїть крапка. Повертає true або false
bool isValidText(const char* text) {
    int len = strlen(text);
    if (len == 0 || text[len - 1] != '.') {
        return false;
    }

    bool hasWord = false;
    for (int i = 0; i < len - 1; i++) {
        if (isalnum(text[i])) {
            hasWord = true;
        } else if (text[i] != ' ') {
            return false;
        }
    }
    return hasWord;
}

// Розбиває текст на слова: відкидає завершальну крапку, ділить рядок через strtok
// по пробілах і створює динамічний масив рядків. Кількість слів повертає через count
char** splitWords(const char* text, int& count) {
    char copy[256];
    strcpy(copy, text);
    *strchr(copy, '.') = '\0';           // прибираємо завершальну крапку

    char* tokens[128];                   // у тексті до 255 символів не більше 127 слів
    count = 0;
    for (char* tok = strtok(copy, " "); tok != nullptr; tok = strtok(nullptr, " ")) {
        tokens[count++] = tok;
    }

    char** words = new char* [count];
    for (int i = 0; i < count; i++) {
        words[i] = new char[strlen(tokens[i]) + 1];
        strcpy(words[i], tokens[i]);
    }
    return words;
}

// Звільняє пам'ять масиву слів і обнуляє words та count,
// щоб їх не можна було використати випадково
void freeWords(char**& words, int& count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

// Обходить текст вказівником і рахує літери, цифри та пробіли.
// Результати повертає через посилання
void countChars(const char* text, int& letters, int& digits, int& spaces) {
    letters = 0, digits = 0, spaces = 0;
    for (const char* p = text; *p != '\0'; p++) {
        if (isalpha(*p)) {
            letters++;
        } else if (isdigit(*p)) {
            digits++;
        } else if (*p == ' ') {
            spaces++;
        }
    }
}

// Сортуємо масив
void sortWords(const char** arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[i], arr[j]) > 0) {
                const char* tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

// Порівнює два рядки без урахування регістру: символи по черзі приводяться
// до нижнього регістру. Рядки рівні, якщо закінчилися одночасно
bool equalIgnoreCase(const char* x, const char* y) {
    while (*x != '\0' && *y != '\0') {
        if (tolower(*x) != tolower(*y)) {
            return false;
        }
        x++;
        y++;
    }
    return *x == *y;
}

// Викидає залишок поточного рядка вводу, щоб він не потрапив у наступне читання
void clearLine() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

// Зчитує слово (до 31 символу) і перевіряє, що воно не порожнє та складається
// лише з літер і цифр. При помилці виводить повідомлення й повертає false
bool readWord(char* buf) {
    buf[0] = '\0';
    scanf("%31s", buf);
    clearLine();

    for (const char* p = buf; *p != '\0'; p++) {
        if (!isalnum(*p)) {
            printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
            return false;
        }
    }
    if (buf[0] == '\0') {
        printf("Помилка: слово не введено.\n");
        return false;
    }
    return true;
}

// Зчитує вибір меню рядком і розбирає його вручну.
// Повертає -1, якщо введено не число, інакше номер пункту
int readMenuChoice() {
    char line[64];
    fgets(line, sizeof(line), stdin);

    if (line[0] == '\n' || line[0] == '\0') {
        return -1;
    }

    int value = 0;
    for (const char* p = line; *p != '\0' && *p != '\n'; p++) {
        if (!isdigit(*p)) {
            return -1;
        }
        if (value < 1000) value = value * 10 + (*p - '0');
    }
    return value;
}

// ---------- пункти меню ----------

// Пункт 1: виводить текст у лапках, кількість символів і слів,
// а також кількість і відсоток літер, цифр та пробілів
void showStatistics(const char* text, int count) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int len = strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:%6d\n", len);
    printf("Слів:%10d\n", count);
    printf("Літер:%9d (%5.1f%%)\n", letters, 100.0 * letters / len);
    printf("Цифр:%10d (%5.1f%%)\n", digits, 100.0 * digits / len);
    printf("Пробілів:%6d (%5.1f%%)\n", spaces, 100.0 * spaces / len);
}

// Пункт 2: виводить таблицю слів (номер, слово, довжина), найдовше й найкоротше
// слово, середню довжину, слова за абеткою та найчастіше слово
void showWordTable(char** words, int count) {
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");

    int maxLen = strlen(words[0]), minLen = maxLen;
    int longest = 0, shortest = 0, total = 0;
    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);
        total += len;
        if (len > maxLen) {
            maxLen = len;
            longest = i;
        }
        if (len < minLen) {
            minLen = len;
            shortest = i;
        }
    }
    printf("+----+-----------------+-------+\n");

    printf("Найдовше слово: %s (%d)\n", words[longest], maxLen);
    printf("Найкоротше слово: %s (%d)\n", words[shortest], minLen);
    printf("Середня довжина: %.2f\n", 1.0 * total / count);

    const char** sorted = new const char* [count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }
    sortWords(sorted, count);

    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    // найчастіше слово: групи однакових слів підряд у відсортованому масиві
    int bestIndex = 0, bestCount = 0;
    for (int i = 0; i < count; ) {
        int j = i;
        while (j < count && strcmp(sorted[i], sorted[j]) == 0) j++;
        if (j - i > bestCount) {
            bestCount = j - i;
            bestIndex = i;
        }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[bestIndex], bestCount);

    delete[] sorted;
}

// Пункт 3: замінює цілі слова з урахуванням регістру за допомогою std::string.
// Якщо результат довший за 255 символів, текст не змінюється. Після заміни
// оновлює текст і масив слів, виводить кількість замін, текст до й після та довжину
void replaceWord(char* text, char**& words, int& count) {
    char from[32], to[32];

    printf("Замінити слово: ");
    if (!readWord(from)) return;
    printf("На слово: ");
    if (!readWord(to)) return;

    std::string result(text);
    std::string src(from), dst(to);
    int replaced = 0;

    int pos = 0;
    while ((pos = result.find(src, pos)) != -1) {
        int end = pos + src.length();
        bool leftOk = (pos == 0) || !isalnum(result[pos - 1]);
        bool rightOk = (end == result.length()) || !isalnum(result[end]);

        if (leftOk && rightOk) {
            result.replace(pos, src.length(), dst);
            pos += dst.length();
            replaced++;
        } else {
            pos++;
        }
    }

    int newLen = result.length();
    if (newLen > 255) {
        printf("Помилка: після заміни текст перевищує 255 символів. Текст не змінено.\n");
        return;
    }

    printf("Замін виконано: %d\n", replaced);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", result.c_str());
    printf("Нова довжина: %d\n", newLen);

    strcpy(text, result.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
}

// Пункт 4: порівнює два слова через strcmp, оператор == та без урахування регістру,
// виводить їхні довжини й конкатенацію через " & " разом з довжиною результату.
void compareWords() {
    char a[32], b[32];

    printf("Перше слово: ");
    if (!readWord(a)) return;
    printf("Друге слово: ");
    if (!readWord(b)) return;

    int cmp = strcmp(a, b);
    if (cmp < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    } else if (cmp > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    } else {
        printf("strcmp: 0 -> слова рівні\n");
    }

    std::string sa(a), sb(b);
    printf("Рівні (==): %s\n", (sa == sb) ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", equalIgnoreCase(a, b) ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)sa.length(), (int)sb.length());

    std::string joined = sa + " & " + sb;
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}

// Пункт 5: зчитує символ і виводить його код у десятковій, шістнадцятковій,
// вісімковій та двійковій системах, тип символу, для літери інший регістр
// і наступний символ, а також кількість входжень у тексті та позицію першого.
void charInfo(const char* text) {
    char c = 0;
    printf("Введіть символ: ");
    scanf(" %c", &c);
    clearLine();

    unsigned char code = c;
    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%02x, oct 0%o, bin ", code, code, code);
    for (int bit = 7; bit >= 0; bit--) {
        printf("%d", (code >> bit) & 1);
    }
    printf(")\n");

    const char* type;
    if (isupper(code))      type = "велика літера";
    else if (islower(code)) type = "мала літера";
    else if (isdigit(code)) type = "цифра";
    else if (isspace(code)) type = "пробільний символ";
    else                    type = "інший символ";
    printf("Тип: %s\n", type);

    if (isalpha(code)) {
        char other = isupper(code) ? tolower(code) : toupper(code);
        printf("Інший регістр: '%c'\n", other);
        printf("Наступний символ: '%c'\n", code + 1);
    }

    int occurrences = 0, first = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == c) {
            if (occurrences == 0) first = i + 1;
            occurrences++;
        }
    }

    if (occurrences == 0) {
        printf("Символ у тексті не зустрічається\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, first);
    }
}

// Пункт 6: читає нове речення по словах через cin >> до слова з крапкою
// (можна в кількох рядках), склеює слова через один пробіл і перевіряє довжину
// та коректність. При успіху замінює текст і масив слів, виводить кількість слів,
// новий текст і його довжину. Інакше виводить помилку й текст не змінює.
void enterSentence(char* text, char**& words, int& count) {
    printf("Введіть речення (крапка після останнього слова):\n");

    std::string word, sentence;
    while (std::cin >> word) {
        if (!sentence.empty()) sentence += " ";
        sentence += word;
        if (word.back() == '.') break;
    }
    clearLine();

    if (sentence.length() > 255 || !isValidText(sentence.c_str())) {
        printf("Помилка: речення має містити до 255 символів, складатися з латинських\n");
        printf("літер, цифр і пробілів та завершуватися крапкою. Текст не змінено.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}