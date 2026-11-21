#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

const int MAX_LEN = 255;
const int MAX_WORD = 31;

void clear() {  // очищає залишок рядка після scanf
    int c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

bool correctsym(char c) { // перевіряє латинська літера або цифра
    bool small = (c >= 'a' && c <= 'z');
    bool big = (c >= 'A' && c <= 'Z');
    bool digit = (c >= '0' && c <= '9');

    return small || big || digit;
}

bool checktext(const char *text) { // перевіряє валідацію тексту
    int len = strlen(text);

    if (len == 0) {
        return false;
    }

    if (text[len - 1] != '.') {
        return false;
    }

    bool slova = false; 

    for (int i = 0; i < len - 1; i++) {
        if (correctsym(text[i])) {
            slova = true;       // знайшли символ слова
        } 
        else if (text[i] != ' ') { 
            return false;       // не літера, не цифра і не пробіл
        }
    }

    return slova;
}

bool checkword(const char *word) { // перевіряє валідацію слова
    int len = strlen(word);

    if (len == 0 || len > MAX_WORD) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (!correctsym(word[i])) {
            return false;
        }
    }

    return true;
}

bool input(char *word) { // перевіряє валідність + довжину

    char buf[MAX_WORD + 2];

    if (scanf("%32s", buf) != 1) {
        return false;
    }
    clear();

    if (!checkword(buf)) {
        printf("Помилка: слово має складатися лише з латинських літер і цифр (до %d символів).\n", MAX_WORD);
        return false;
    }

    strcpy(word, buf);
    return true;
}

char **split(const char *text, int &count) { // текст на слова, повертає масив вказівників на слова

    char copy[MAX_LEN + 1];

    strcpy(copy, text); // шукаємо кількість слів
    count = 0;
    char *word = strtok(copy, " .");
    while (word != nullptr) {
        count++; 
        word = strtok(nullptr, " .");
    }

    char **words = new char *[count]; // робимо масив з кількості слів

    strcpy(copy, text); 
    int i = 0;
    word = strtok(copy, " .");
    while (word != nullptr) {
        words[i] = new char[strlen(word) + 1];
        strcpy(words[i], word); // копіюємо слово в масив
        i++;
        word = strtok(nullptr, " .");
    }

    return words;
}


void free(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;

    words = nullptr;
    count = 0;
}

void update(const char *text, char **&words, int &count) { // оновлює масив слів після зміни тексту
    free(words, count);
    words = split(text, count);
}

void calculate(const char *text, int &letters, int &digits, int &spaces) { // рахує літери, цифри та пробіли
    letters = 0;
    digits = 0;
    spaces = 0;

    for (const char *p = text; *p != '\0'; p++) {
        if (isalpha(*p)) {
            letters++;
        } 
        else if (isdigit(*p)) {
            digits++;
        } 
        else if (isspace(*p)) {
            spaces++;
        }
    }
}

void stats(const char *text, int wordCount) {
    int letters, digits, spaces;
    calculate(text, letters, digits, spaces);

    int total = strlen(text);

    printf("Текст: \t\"%s\"\n", text);
    printf("Символів: %5d\n", total);
    printf("Слів:     %5d\n", wordCount);
    printf("Літер:    %5d(%.1f%%)\n", letters, 100.0 * letters / total);
    printf("Цифр:     %5d(%.1f%%)\n", digits, 100.0 * digits / total);
    printf("Пробілів: %5d(%.1f%%)\n", spaces, 100.0 * spaces / total);
}

void table(char **words, int count) {
    printf("+-----+---------------------------------+-------+\n");
    printf("|  N  | Слово                           | Довж. |\n");
    printf("+-----+---------------------------------+-------+\n");

    for (int i = 0; i < count; i++) {
        printf("| %2d  | %-32s| %5d |\n", i + 1, words[i], (int)strlen(words[i]));
    }

    printf("+-----+---------------------------------+-------+\n");
}

void lengths(char **words, int count) {
    int longest = 0;
    int shortest = 0;
    int sum = 0;

    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        sum += len;

        if (len > (int)strlen(words[longest])) {
            longest = i;
        }
        if (len < (int)strlen(words[shortest])) {
            shortest = i;
        }
    }

    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)sum / count);
}

void sorting(char **words, int count) {
    char **sorted = new char *[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) {
                char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
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

    int start = 0;
    while (start < count) {
        int end = start;
        while (end < count && strcmp(sorted[end], sorted[start]) == 0) {
            end++;
        }

        if (end - start > bestCount) {
            bestCount = end - start;
            bestIndex = start;
        }
        start = end;
    }

    printf("Найчастіше слово: %s (%d)\n", sorted[bestIndex], bestCount);

    delete[] sorted;
}

void report(char **words, int count) {
    table(words, count);
    lengths(words, count);
    sorting(words, count);
}

void change(char *text, char **&words, int &count) {
    char fromBuf[MAX_WORD + 1];
    char toBuf[MAX_WORD + 1];

    printf("Замінити слово: ");
    if (!input(fromBuf)) {
        return;
    }
    printf("На слово: ");
    if (!input(toBuf)) {
        return;
    }

    string from = fromBuf;
    string to = toBuf;
    string before = text;
    string after = text;

    int replaced = 0;

    size_t pos = after.find(from);
    while (pos != string::npos) {
        bool leftOk = (pos == 0 || after[pos - 1] == ' ');

        size_t end = pos + from.length();

        bool rightOk = (end < after.length() && (after[end] == ' ' || after[end] == '.'));

        if (leftOk && rightOk) {
            after.replace(pos, from.length(), to);
            replaced++;
            pos = after.find(from, pos + to.length());
        } 
        else {
            pos = after.find(from, pos + 1);
        }
    }

    if ((int)after.length() > MAX_LEN) {
        printf("Помилка: результат довший за %d символів, текст не змінено.\n", MAX_LEN);
        return;
    }

    printf("Замін виконано: %d\n", replaced);

    if (replaced == 0) {
        return;
    }

    strcpy(text, after.c_str());       // с_стр - записати у правильному форматі
    update(text, words, count);

    printf("Було:  \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)after.length());
}

void compare() {
    char aBuf[MAX_WORD + 1];
    char bBuf[MAX_WORD + 1];

    printf("Перше слово: ");
    if (!input(aBuf)) {
        return;
    }
    printf("Друге слово: ");
    if (!input(bBuf)) {
        return;
    }

    string a = aBuf;
    string b = bBuf;

    int cmp = strcmp(aBuf, bBuf);
    if (cmp < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    } 
    else if (cmp > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    } 
    else {
        printf("strcmp: 0 -> слова рівні\n");
    }

    if (a == b) {
        printf("Рівні (==): так\n");
    } 
    else {
        printf("Рівні (==): ні\n");
    }

    bool same = (a.length() == b.length());
    for (size_t i = 0; same && i < a.length(); i++) {
        if (tolower(a[i]) != tolower(b[i])) {
            same = false;
        }
    }
    if (same) {
        printf("Рівні без урахування регістру: так\n");
    } 
    else {
        printf("Рівні без урахування регістру: ні\n");
    }

    printf("Довжини: %d і %d\n", (int)a.length(), (int)b.length());

    string joined = a + " & " + b;
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}

void symbol(const char *text) {
    char c;

    printf("Введіть символ: ");
    if (scanf("%c", &c) != 1) {
        return;
    }

    if (c == '\n') {
        printf("Помилка: потрібно ввести рівно один символ.\n");
        return;
    }

    int next = getchar();
    if (next != '\n' && next != EOF) {
        clear();   // прибираємо решту рядка
        printf("Помилка: потрібно ввести рівно один символ.\n");
        return;
    }

    if (c <= 0) {
        printf("Помилка: підтримуються лише символи ASCII.\n");
        return;
    }

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%02x, oct 0%o, bin ", c, c, c);
    for (int bit = 7; bit >= 0; bit--) {
        printf("%d", (c >> bit) & 1);
    }
    printf(")\n");

    if (isupper(c)) {
        printf("Тип: велика літера\n");
    } 
    else if (islower(c)) {
        printf("Тип: мала літера\n");
    } 
    else if (isdigit(c)) {
        printf("Тип: цифра\n");
    } 
    else if (isspace(c)) {
        printf("Тип: пробільний символ\n");
    } 
    else {
        printf("Тип: інший символ\n");
    }

    if (isalpha(c)) {
        char other;
        if (isupper(c)) {
            other = c + ('a' - 'A'); // різниця 32
        } 
        else {
            other = c - ('a' - 'A');
        }
        printf("Інший регістр: '%c'\n", other);
        printf("Наступний символ: '%c'\n", c + 1);
    }

    int found = 0;
    int firstPos = 0;

    const char *p = strchr(text, c);
    while (p != nullptr) {
        if (found == 0) {
            firstPos = (p - text) + 1;
        }
        found++;
        p = strchr(p + 1, c);
    }

    if (found == 0) {
        printf("У тексті не зустрічається.\n");
    } 
    else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", found, firstPos);
    }
}

void enter(char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");

    string sentence;
    string word;
    int wordCount = 0;
    bool correct = true;
    bool finished = false;

    while (cin >> word) {
        bool isLast = (word[word.length() - 1] == '.');
        if (isLast) {
            word.erase(word.length() - 1);   // прибираємо крапку зі слова
        }

        for (size_t i = 0; i < word.length(); i++) {
            if (!correctsym(word[i])) {
                correct = false;
            }
        }

        if (!word.empty()) {
            if ((int)sentence.length() <= MAX_LEN) {
                if (wordCount > 0) {
                    sentence += " ";
                }
                sentence += word;
            }
            wordCount++;
        }

        if (isLast) {
            finished = true;
            break;
        }
    }

    if (!finished) {
        printf("Помилка: речення не завершено крапкою.\n");
        return;
    }

    clear();

    sentence += ".";

    if (!correct || wordCount == 0) {
        printf("Помилка: речення має містити хоча б одне слово з латинських літер і цифр.\n");
        return;
    }
    if ((int)sentence.length() > MAX_LEN) {
        printf("Помилка: речення довше за %d символів, текст не змінено.\n", MAX_LEN);
        return;
    }

    strcpy(text, sentence.c_str());
    update(text, words, count);

    printf("Прочитано слів: %d\n", wordCount);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

void menu() {
    printf("\nМеню:\n");
    printf("1. Показати текст і статистику\n");
    printf("2. Таблиця слів\n");
    printf("3. Замінити слово\n");
    printf("4. Порівняти два слова\n");
    printf("5. Інформація про символ\n");
    printf("6. Ввести нове речення\n");
    printf("0. Вийти\n");
}

int main() {
    char text[MAX_LEN + 1];

    printf("Введіть текст (до %d символів, крапка в кінці):\n", MAX_LEN);

    if (fgets(text, sizeof(text), stdin) == nullptr) {
        printf("Помилка: текст не введено.\n");
        return 1;
    }

    char *newline = strchr(text, '\n'); // замінюємо '\n' на '\0', якщо є
    if (newline != nullptr) {
        *newline = '\0';
    } 
    else if (strlen(text) == MAX_LEN) {
        int next = getchar(); 
        if (next != '\n' && next != EOF) { // перевіряємо чи часом останній символ не '\n'
            printf("Помилка: текст довший за %d символів.\n", MAX_LEN);
            return 1;
        }
    }

    if (!checktext(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int count;
    char **words = split(text, count);

    int choice = -1;

    while (choice != 0) {
        menu();
        printf("Ваш вибір: ");

        char buf[3];
        if (scanf("%2s", buf) != 1) {
            break;   // кінець введення
        }
        clear();

        if (strlen(buf) == 1 && isdigit(buf[0])) {
            choice = buf[0] - '0';   // переводимо із символа в число
        } 
        else {
            choice = -1;
        }

        switch (choice) {
            case 0:
                break; 
            case 1:
                stats(text, count);
                break;
            case 2:
                report(words, count);
                break;
            case 3:
                change(text, words, count);
                break;
            case 4:
                compare();
                break;
            case 5:
                symbol(text);
                break;
            case 6:
                enter(text, words, count);
                break;
            default:
                printf("Помилка: введіть число від 0 до 6.\n");
                break;
        }
    }

    free(words, count);
    printf("До побачення!\n");
    return 0;
}
