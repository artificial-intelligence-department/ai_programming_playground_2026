/*
Practice Task
Лисюк Андріана
ШІ-13
*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

const int MAX_TEXT = 256;
const int MAX_WORD = 32;

void clearInput()
{
    int ch = getchar();
    while (ch != '\n' && ch != EOF)
        ch = getchar();
}

bool readLine(char *buf, int size)
{
    if (fgets(buf, size, stdin) == NULL)
        return false;

    char *nl = strchr(buf, '\n');
    if (nl != NULL) {
        *nl = '\0';
        return true;
    }

    int ch = getchar();
    if (ch == '\n' || ch == EOF)
        return true;

    clearInput();
    return false;
}

bool isLatinOrDigit(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

bool isGoodWord(const char *w)
{
    if (strlen(w) == 0)
        return false;
    for (int i = 0; w[i] != '\0'; i++)
        if (!isLatinOrDigit(w[i]))
            return false;
    return true;
}

bool isGoodText(const char *text)
{
    int len = strlen(text);
    if (len < 2 || len > MAX_TEXT - 1)
        return false;
    if (text[len - 1] != '.' || !isLatinOrDigit(text[len - 2]))
        return false;
    for (int i = 0; i < len - 1; i++)
        if (!isLatinOrDigit(text[i]) && text[i] != ' ')
            return false;
    return true;
}

bool readWord(const char *prompt, char *word)
{
    char line[MAX_TEXT];
    printf("%s", prompt);

    if (!readLine(line, MAX_TEXT)) {
        printf("Помилка: занадто довгий ввід.\n");
        return false;
    }

    char *start = line;
    while (*start == ' ')
        start++;
    int len = strlen(start);
    while (len > 0 && start[len - 1] == ' ')
        start[--len] = '\0';

    if (len == 0) {
        printf("Помилка: слово не введено.\n");
        return false;
    }
    if (len > MAX_WORD - 1) {
        printf("Помилка: слово довше за %d символ.\n", MAX_WORD - 1);
        return false;
    }
    if (!isGoodWord(start)) {
        printf("Помилка: слово може містити лише латинські літери і цифри.\n");
        return false;
    }

    strcpy(word, start);
    return true;
}

char toLower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    return c;
}

bool equalsNoCase(const char *a, const char *b)
{
    if (strlen(a) != strlen(b))
        return false;
    for (int i = 0; a[i] != '\0'; i++)
        if (toLower(a[i]) != toLower(b[i]))
            return false;
    return true;
}

char **splitWords(const char *text, int &count)
{
    char copy[MAX_TEXT];
    strcpy(copy, text);
    copy[strlen(copy) - 1] = '\0';

    count = 0;
    bool inWord = false;
    for (const char *p = copy; *p != '\0'; p++) {
        if (*p != ' ' && !inWord)
            count++;
        inWord = (*p != ' ');
    }

    char **words = new char *[count];
    int i = 0;
    char *token = strtok(copy, " ");
    while (token != NULL) {
        words[i] = new char[strlen(token) + 1];
        strcpy(words[i], token);
        i++;
        token = strtok(NULL, " ");
    }
    return words;
}

void freeWords(char **&words, int &count)
{
    for (int i = 0; i < count; i++)
        delete[] words[i];
    delete[] words;
    words = NULL;
    count = 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces)
{
    letters = digits = spaces = 0;
    for (const char *p = text; *p != '\0'; p++) {
        if (isalpha(*p))
            letters++;
        else if (isdigit(*p))
            digits++;
        else if (*p == ' ')
            spaces++;
    }
}

void sortWords(char **arr, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char *tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

void showStats(const char *text, int wordCount)
{
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int total = strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %5d\n", total);
    printf("Слів:     %5d\n", wordCount);
    printf("Літер:    %5d (%5.1f%%)\n", letters, 100.0 * letters /total);
    printf("Цифр:     %5d (%5.1f%%)\n", digits, 100.0 * digits / total);
    printf("Пробілів: %5d (%5.1f%%)\n", spaces, 100.0 * spaces / total);
}

void showTable(char **words, int count)
{
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");

    int longest = 0, shortest = 0, sum = 0;
    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);
        sum += len;
        if (len > (int)strlen(words[longest]))
            longest = i;
        if (len < (int)strlen(words[shortest]))
            shortest = i;
    }
    printf("+----+-----------------+-------+\n");

    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)sum / count);

    char **sorted = new char *[count];
    for (int i = 0; i < count; i++)
        sorted[i] = words[i];
    sortWords(sorted, count);

    printf("За абеткою:");
    for (int i = 0; i < count; i++)
        printf(" %s", sorted[i]);
    printf("\n");

    int best = 0, bestCount = 0;
    for (int i = 0; i < count; ) {
        int j = i;
        while (j < count && strcmp(sorted[j], sorted[i]) == 0)
            j++;
        if (j - i > bestCount) {
            bestCount = j - i;
            best = i;
        }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[best], bestCount);

    delete[] sorted;
}

void replaceWord(char *text, char **&words, int &count)
{
    char from[MAX_WORD], to[MAX_WORD];
    if (!readWord("Замінити слово: ", from) || !readWord("На слово: ", to)) {
        printf("Текст не змінено.\n");
        return;
    }

    string oldText = text;
    string s = text;
    string a = from, b = to;
    int replaced = 0;

    size_t pos = s.find(a);
    while (pos != string::npos) {
        size_t end = pos + a.length();
        bool leftOk = (pos == 0 || s[pos - 1] == ' ');
        bool rightOk = (s[end] == ' ' || s[end] == '.');
        if (leftOk && rightOk) {
            s.replace(pos, a.length(), b);
            replaced++;
            pos = s.find(a, pos + b.length());
        } else {
            pos = s.find(a, pos + 1);
        }
    }

    if (s.length() > MAX_TEXT - 1) {
        printf("Помилка: після заміни текст буде довший за %d символів.\n", MAX_TEXT - 1);
        printf("Текст не змінено.\n");
        return;
    }

    printf("Замін виконано: %d\n", replaced);
    if (replaced == 0)
        return;

    strcpy(text, s.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Було:  \"%s\"\n", oldText.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));
}

void compareWords()
{
    char a[MAX_WORD], b[MAX_WORD];
    if (!readWord("Перше слово: ", a) || !readWord("Друге слово: ", b))
        return;

    int cmp = strcmp(a, b);
    if (cmp < 0)
        printf("strcmp: -1 -> перше слово менше\n");
    else if (cmp > 0)
        printf("strcmp: 1 -> перше слово більше\n");
    else
        printf("strcmp: 0 -> слова однакові\n");

    string s1 = a, s2 = b;
    printf("Рівні (==): %s\n", s1 == s2 ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", equalsNoCase(a, b) ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)s1.length(), (int)s2.length());

    string both = s1 + " & " + s2;
    printf("Конкатенація: \"%s\" (%d)\n", both.c_str(), (int)both.length());
}

void charInfo(const char *text)
{
    char c = '\n';
    printf("Введіть символ: ");
    scanf("%c", &c);

    if (c == '\n') {
        printf("Помилка: символ не введено.\n");
        return;
    }
    if (getchar() != '\n') {
        clearInput();
        printf("Помилка: треба ввести один символ.\n");
        return;
    }
    if (c <= 0) {
        printf("Помилка: підтримуються лише латинські символи.\n");
        return;
    }

    char bin[9];
    for (int i = 0; i < 8; i++)
        bin[i] = ((c >> (7 - i)) & 1) ? '1' : '0';
    bin[8] = '\0';

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n", c, c, c, bin);

    if (isupper(c)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", c - 'A' + 'a');
    } else if (islower(c)) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", c - 'a' + 'A');
    } else if (isdigit(c)) {
        printf("Тип: цифра\n");
    } else if (isspace(c)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }

    if (isprint(c + 1))
        printf("Наступний символ: '%c'\n", c + 1);
    else
        printf("Наступний символ: код %d\n", c + 1);

    const char *first = strchr(text, c);
    if (first == NULL) {
        printf("Символ у тексті не зустрічається.\n");
        return;
    }

    int times = 0;
    for (const char *p = first; p != NULL; p = strchr(p + 1, c))
        times++;
    printf("Входжень у тексті: %d, перше на позиції %d\n", times, (int)(first - text) + 1);
}

void newSentence(char *text, char **&words, int &count)
{
    printf("Введіть речення (крапка після останнього слова):\n");

    string sentence, word;
    int n = 0;
    bool done = false;

    while (cin >> word) {
        n++;
        if (sentence.length() < MAX_TEXT) {
            if (n > 1)
                sentence += " ";
            sentence += word;
        }
        if (word[word.length() - 1] == '.') {
            done = true;
            break;
        }
    }
    clearInput();

    printf("Прочитано слів: %d\n", n);

    if (!done || !isGoodText(sentence.c_str())) {
        printf("Помилка: речення має складатися з латинських літер, цифр\n"
               "і пробілів, мати до %d символів і закінчуватися крапкою.\n", MAX_TEXT - 1);
        printf("Текст не змінено.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

void printMenu()
{
    printf("\n1 - Показати текст і статистику\n");
    printf("2 - Таблиця слів\n");
    printf("3 - Замінити слово\n");
    printf("4 - Порівняти два слова\n");
    printf("5 - Інформація про символ\n");
    printf("6 - Ввести нове речення\n");
    printf("0 - Вийти\n");
    printf("Ваш вибір: ");
}

bool readChoice(int &choice)
{
    int ok = scanf("%d", &choice);
    bool extra = false;
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        if (ch != ' ')
            extra = true;
    return ok == 1 && !extra;
}

int main()
{
    char text[MAX_TEXT];

    printf("Введіть текст (до %d символів, крапка в кінці):\n", MAX_TEXT - 1);
    if (!readLine(text, MAX_TEXT) || !isGoodText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n"
               "і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int count;
    char **words = splitWords(text, count);

    int choice = -1;
    while (choice != 0) {
        printMenu();
        if (!readChoice(choice)) {
            if (feof(stdin))
                break;
            printf("Помилка: введіть номер пункту меню.\n");
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1: showStats(text, count); break;
        case 2: showTable(words, count); break;
        case 3: replaceWord(text, words, count); break;
        case 4: compareWords(); break;
        case 5: charInfo(text); break;
        case 6: newSentence(text, words, count); break;
        case 0: break;
        default: printf("Помилка: пункту %d немає в меню.\n", choice);
        }
    }

    freeWords(words, count);
    return 0;
}