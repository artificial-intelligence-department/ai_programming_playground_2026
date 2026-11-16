#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

const int MAX_TEXT = 256;
const int MAX_WORDS = 128;

//допоміжні функції

//прибирає зайве з вводу після scanf
void clearLine() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

// перевірка чи текст коректний (є слово, лише латиниця, цифри, пробіли, у кінці крапка)
bool isValidText(const char *text) {
    int len = strlen(text);
    if (len < 2 || text[len - 1] != '.') {
        return false;
    }
    bool hasWord = false;
    for (int i = 0; i < len - 1; i++) {
        unsigned char c = text[i];
        if (isalpha(c) || isdigit(c)) {
            hasWord = true;
        } else if (c != ' ') {
            return false;
        }
    }
    return hasWord;
}

// перевірка чи слово правильне
bool isValidWord(const char *w) {
    int len = strlen(w);
    if (len < 1 || len > 31) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        unsigned char c = w[i];
        if (!isalpha(c) && !isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Обов'язкові функції

// ділить текст на слова (strtok), кожне слово копіює в купу
char **splitWords(const char *text, int &count) {
    char buf[MAX_TEXT];
    strcpy(buf, text);
    buf[strlen(buf) - 1] = '\0';  //прибирає завершальну крапку

    char **words = new char *[MAX_WORDS];
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

// рахує літери, цифри й пробіли
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    for (const char *p = text; *p != '\0'; p++) {
        unsigned char c = *p;
        if (isalpha(c)) {
            letters++;
        } else if (isdigit(c)) {
            digits++;
        } else if (isspace(c)) {
            spaces++;
        }
    }
}

// звільняє масив слів
void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = NULL;
    count = 0;
}

// Пункти меню

// 1. Текст і статистика
void showStats(const char *text, int wordCount) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int len = strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %6d\n", len);
    printf("Слів:     %6d\n", wordCount);
    printf("Літер:    %6d (%5.1f%%)\n", letters, 100.0 * letters / len);
    printf("Цифр:     %6d (%5.1f%%)\n", digits, 100.0 * digits / len);
    printf("Пробілів: %6d (%5.1f%%)\n", spaces, 100.0 * spaces / len);
}

// 2. Таблиця слів
void showTable(char **words, int count) {
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    int sum = 0;
    int longest = 0, shortest = 0;
    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);
        sum += len;
        if (len > (int)strlen(words[longest])) {
            longest = i;  // строго більше: лишається перше
        }
        if (len < (int)strlen(words[shortest])) {
            shortest = i;
        }
    }
    printf("+----+-----------------+-------+\n");
    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)sum / count);

    // копія адрес слів, щоб не міняти порядок у words
    char *sorted[MAX_WORDS];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }
    // сортування бульбашкою за strcmp
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) {
                char *tmp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = tmp;
            }
        }
    }
    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    // однакові слова стоять поруч, тому рахуємо серії слів, щоб знайти найчастіше слово
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
}

// 3. Замінити слово
void replaceWord(char *text, char **&words, int &count) {
    char from[64], to[64];
    printf("Замінити слово: ");
    scanf("%63s", from);
    printf("На слово: ");
    scanf("%63s", to);
    clearLine();

    if (!isValidWord(from) || !isValidWord(to)) {
        printf("Помилка: слово має містити 1-31 латинську літеру або цифру.\n");
        return;
    }

    string s = text;
    string f = from;
    string t = to;
    int replaced = 0;

    size_t pos = s.find(f);
    while (pos != string::npos) {
        bool leftOk = (pos == 0 || s[pos - 1] == ' ');
        bool rightOk = !isalnum((unsigned char)s[pos + f.length()]);
        if (leftOk && rightOk) {
            s.replace(pos, f.length(), t);
            pos += t.length();
            replaced++;
        } else {
            pos++;
        }
        pos = s.find(f, pos);
    }

    if (s.length() > 255) {
        printf("Помилка: результат довший за 255 символів.\n");
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

// 4. Порівняти два слова
void compareWords() {
    char a[64], b[64];
    printf("Перше слово: ");
    scanf("%63s", a);
    printf("Друге слово: ");
    scanf("%63s", b);
    clearLine();

    if (!isValidWord(a) || !isValidWord(b)) {
        printf("Помилка: слово має містити 1-31 латинську літеру або цифру.\n");
        return;
    }

    int r = strcmp(a, b);
    int sign = 0;
    if (r < 0) {
        sign = -1;
    } else if (r > 0) {
        sign = 1;
    }
    printf("strcmp: %d -> ", sign);
    if (sign < 0) {
        printf("перше слово менше\n");
    } else if (sign > 0) {
        printf("перше слово більше\n");
    } else {
        printf("слова однакові\n");
    }

    string sa = a;
    string sb = b;
    printf("Рівні (==): %s\n", sa == sb ? "так" : "ні");

    string la = sa;
    string lb = sb;
    for (size_t i = 0; i < la.length(); i++) {
        la[i] = tolower((unsigned char)la[i]);
    }
    for (size_t i = 0; i < lb.length(); i++) {
        lb[i] = tolower((unsigned char)lb[i]);
    }
    printf("Рівні без урахування регістру: %s\n", la == lb ? "так" : "ні");

    printf("Довжини: %d і %d\n", (int)sa.length(), (int)sb.length());
    string both = sa + " & " + sb;
    printf("Конкатенація: \"%s\" (%d)\n", both.c_str(), (int)both.length());
}

// 5. Інформація про символ
void charInfo(const char *text) {
    char c;
    printf("Введіть символ: ");
    scanf(" %c", &c);
    clearLine();
    unsigned char code = c;

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", code, code, code);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (code >> i) & 1);  // побітові операції
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
    }
    printf("Наступний символ: '%c'\n", c + 1);

    int total = 0;
    const char *first = strchr(text, c);
    const char *p = first;
    while (p != NULL) {
        total++;
        p = strchr(p + 1, c);
    }
    if (first == NULL) {
        printf("У тексті цей символ не зустрічається.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", total, (int)(first - text) + 1);
    }
}

// 6. Нове речення
void newSentence(char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");
    string word;
    string sentence = "";
    int read = 0;
    while (cin >> word) {
        if (read > 0) {
            sentence += " ";
        }
        sentence += word;
        read++;
        if (word[word.length() - 1] == '.') {
            break;
        }
    }

    if (sentence.length() > 255 || !isValidText(sentence.c_str())) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n");
        printf("і пробілів, завершуватися крапкою та мати до 255 символів.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", read);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}



int main() {
    char text[MAX_TEXT];

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        return 0;
    }
    if (strchr(text, '\n') == NULL && strlen(text) == 255) {
        int next = getchar();  // чи справді текст довший за 255
        if (next != '\n' && next != EOF) {
            printf("Помилка: текст довший за 255 символів.\n");
            return 0;
        }
    }
    text[strcspn(text, "\n")] = '\0';

    if (!isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n");
        printf("і пробілів та завершуватися крапкою.\n");
        return 0;
    }

    int count = 0;
    char **words = splitWords(text, count);

    int choice = -1;
    while (choice != 0) {
        printf("\n1 - Показати текст і статистику\n");
        printf("2 - Таблиця слів\n");
        printf("3 - Замінити слово\n");
        printf("4 - Порівняти два слова\n");
        printf("5 - Інформація про символ\n");
        printf("6 - Ввести нове речення\n");
        printf("0 - Вийти\n");
        printf("Ваш вибір: ");

        int r = scanf("%d", &choice);
        if (r == EOF) {
            break;
        }
        if (r != 1) {
            clearLine();
            choice = -1;
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }
        clearLine();

        if (choice == 1) {
            showStats(text, count);
        } else if (choice == 2) {
            showTable(words, count);
        } else if (choice == 3) {
            replaceWord(text, words, count);
        } else if (choice == 4) {
            compareWords();
        } else if (choice == 5) {
            charInfo(text);
        } else if (choice == 6) {
            newSentence(text, words, count);
        } else if (choice != 0) {
            printf("Помилка: пункту %d немає в меню.\n", choice);
        }
    }

    freeWords(words, count);
    return 0;
}