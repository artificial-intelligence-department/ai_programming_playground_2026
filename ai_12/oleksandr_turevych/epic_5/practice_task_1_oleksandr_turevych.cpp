/*
Епік 5. Практичне завдання: Редактор текстового повідомлення
Автор: Туревич Олександр
Група: ШІ-12
*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;


bool isValidText(const char *text) 
{
    int len = strlen(text);
    if (len < 2) 
    {
        return false;
    }
    if (text[len - 1] != '.') 
    {
        return false;
    }

    bool hasWordChar = false;
    for (int i = 0; i < len - 1; ++i) 
    {
        unsigned char ch = (unsigned char)text[i];
        if (isalpha(ch) || isdigit(ch)) 
        {
            hasWordChar = true;
        } 
        else if (ch != ' ') 
        {
            return false;
        }
    }

    return hasWordChar;
}

char** splitWords(const char *text, int &count) 
{
    char temp[256];
    strcpy(temp, text);

    char **words = new char*[128];
    count = 0;

    char *token = strtok(temp, " .");
    while (token != nullptr) {
        words[count] = new char[strlen(token) + 1];
        strcpy(words[count], token);
        count++;
        token = strtok(nullptr, " .");
    }

    return words;
}

void freeWords(char **&words, int &count) 
{
    if (words != nullptr) {
        for (int i = 0; i < count; ++i) 
        {
            delete[] words[i];
        }
        delete[] words;
        words = nullptr;
    }
    count = 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;

    const char *p = text;
    while (*p != '\0') 
    {
        if (isalpha(*p)) 
        {
            letters++;
        } 
        else if (isdigit(*p))
        {
            digits++;
        } 
        else if (*p == ' ') 
        {
            spaces++;
        }
        p++;
    }


}

// Пункт 1
void showStats(const char *text, int wordCount) {
    int totalLen = strlen(text);
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);

    double lettersPct = 0.0;
    double digitsPct = 0.0;
    double spacesPct = 0.0;
    
    lettersPct = letters * 100.0 / totalLen;
    digitsPct = digits * 100.0 / totalLen;
    spacesPct = spaces * 100.0 / totalLen;
    

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:  %4d\n", totalLen);
    printf("Слів:      %4d\n", wordCount);
    printf("Літер:     %4d (%5.1f%%)\n", letters, lettersPct);
    printf("Цифр:      %4d (%5.1f%%)\n", digits, digitsPct);
    printf("Пробілів:  %4d (%5.1f%%)\n", spaces, spacesPct);
}

// Пункт 2
void showWordTable(char **words, int count) 
{
    if (count == 0) {
        printf("Слів немає.\n");

        return;
    }

    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");

    int maxLen = strlen(words[0]);
    int minLen = strlen(words[0]);
    int maxIdx = 0;
    int minIdx = 0;
    int sumLen = 0;

    for (int i = 0; i < count; ++i) {
        int len = strlen(words[i]);
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);

        sumLen += len;
        if (len > maxLen) 
        {
            maxLen = len;

            maxIdx = i;
        }

        if (len < minLen) 
        {
            minLen = len;
            minIdx = i;
        }
    }
    printf("+----+-----------------+-------+\n");

    double avgLen = (double)sumLen / count;
    printf("Найдовше слово: %s (%d)\n", words[maxIdx], maxLen);
    printf("Найкоротше слово: %s (%d)\n", words[minIdx], minLen);
    printf("Середня довжина: %.2f\n", avgLen);

    char *sorted[128];
    for (int i = 0; i < count; ++i) 
    {
        sorted[i] = words[i];
    }

    for (int i = 0; i < count - 1; ++i) 
    {
        for (int j = 0; j < count - 1 - i; ++j) 
        {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) 
            {

                char *temp = sorted[j];

                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("За абеткою:");

    for (int i = 0; i < count; ++i) {

        printf(" %s", sorted[i]);
    }
    printf("\n");

    char *bestWord = sorted[0];
    int bestFreq = 1;
    int curFreq = 1;

    for (int i = 1; i < count; ++i) {
        if (strcmp(sorted[i], sorted[i - 1]) == 0) 
        {
            curFreq++;
        } 
        else 
        {
            curFreq = 1;
        }
        if (curFreq > bestFreq) 
        {
            bestFreq = curFreq;
            bestWord = sorted[i];
        }
    }

    printf("Найчастіше слово: %s (%d)\n", bestWord, bestFreq);
}

bool isValidWord(const char *w) 
{
    int len = strlen(w);
    if (len == 0) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if (!isalpha(w[i]) && !isdigit(w[i])) {
            return false;
        }
    }
    return true;
}

void clearInputLine() 
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

// Пункт 3
void replaceWord(char *text, char **&words, int &wordCount) 
{
    char from[32];
    char to[32];

    printf("Замінити слово: ");
    scanf("%31s", from);
    clearInputLine();

    printf("На слово: ");
    scanf("%31s", to);
    clearInputLine();

    if (!isValidWord(from) || !isValidWord(to)) {
        printf("Помилка: слова мають складатися лише з латинських літер і цифр.\n");

        return;
    }

    string s = text;
    string oldW = from;
    string newW = to;

    int replacements = 0;
    int startPos = 0;

    while (true) {
        int pos = s.find(oldW, startPos);
        if (pos == string::npos) 
        {
            break;
        }

        bool leftOk = false;
        if (pos == 0 || s[pos - 1] == ' ') 
        {
            leftOk = true;
        }

        int endPos = pos + oldW.length();
        bool rightOk = false;
        if (endPos == s.length() || s[endPos] == ' ' || s[endPos] == '.') 
        {
            rightOk = true;
        }

        if (leftOk && rightOk) 
        {
            s.replace(pos, oldW.length(), newW);
            replacements++;
            startPos = pos + newW.length();
        } 
        else 
        {
            startPos = pos + 1;
        }
    }

    if (s.length() > 255) {
        printf("Помилка: довжина тексту після заміни перевищує 255 символів.\n");
        
        return;
    }

    printf("Замін виконано: %d\n", replacements);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", s.c_str());
    printf("Нова довжина: %zu\n", s.length());

    strcpy(text, s.c_str());

    freeWords(words, wordCount);

    words = splitWords(text, wordCount);
}

// Пункт 4
void compareWords() {
    char a[32];
    char b[32];

    printf("Перше слово: ");
    scanf("%31s", a);
    clearInputLine();

    printf("Друге слово: ");
    scanf("%31s", b);
    clearInputLine();

    if (!isValidWord(a) || !isValidWord(b)) 
    {
        printf("Помилка: слова мають складатися лише з латинських літер і цифр.\n");
        return;
    }

    int cmp = strcmp(a, b);
    if (cmp < 0) 
    {
        printf("strcmp: -1 -> перше слово менше\n");
    } 
    else if (cmp > 0) 
    {
        printf("strcmp: 1 -> перше слово більше\n");
    } 
    else 
    {
        printf("strcmp: 0 -> слова однакові\n");
    }

    string sa = a;
    string sb = b;

    if (sa == sb) 
    {
        printf("Рівні (==): так\n");
    } 
    else {
        printf("Рівні (==): ні\n");
    }

    bool sameIgnoreCase = true;
    if (sa.length() != sb.length()) {
        sameIgnoreCase = false;
    } 
    else {
        for (int i = 0; i < sa.length(); ++i)
        {
            if (tolower(sa[i]) != tolower(sb[i])) 
            {

                sameIgnoreCase = false;
                break;
            }
        }
    }

    if (sameIgnoreCase) {
        printf("Рівні без урахування регістру: так\n");
    } 
    else {
        printf("Рівні без урахування регістру: ні\n");
    }

    printf("Довжини: %zu і %zu\n", sa.length(), sb.length());

    string combined = sa + " & " + sb;
    printf("Конкатенація: \"%s\" (%zu)\n", combined.c_str(), combined.length());
}

// Пункт 5
void charInfo(const char *text) {
    char c;
    printf("Введіть символ: ");
    scanf(" %c", &c);
    clearInputLine();

    int code = c;
    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", code, code, code);

    for (int i = 7; i >= 0; --i) {
        if ((code >> i) & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf(")\n");


    
    if (isupper(c)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(c));
    } 
    else if (islower(c)) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(c));
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

    printf("Наступний символ: '%c'\n", c + 1);

    const char *first = strchr(text, c);
    if (first == nullptr) {
        printf("У тексті не зустрічається.\n");
    } 
    else 
    {
        int firstPos = (first - text) + 1;
        int count = 0;
        const char *p = first;
        while (p != nullptr) {
            count++;
            p = strchr(p + 1, c);
        }
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, firstPos);
    }
}

// Пункт 6
void inputNewSentence(char *text, char **&words, int &wordCount) {
    printf("Введіть речення (крапка після останнього слова):\n");

    string word;
    string newText = "";
    int readWords = 0;
    bool endedWithDot = false;

    while (cin >> word) 
    {
        if (newText.length() > 0) {
            newText += " ";
        }
        newText += word;
        readWords++;

        if (word[word.length() - 1] == '.') {
            endedWithDot = true;
            break;
        }
    }

    clearInputLine();

    if (!endedWithDot || newText.length() > 255 || !isValidText(newText.c_str())) 
    {
        printf("Помилка: речення має складатися з латинських літер, цифр і пробілів, не перевищувати 255 символів та завершуватися крапкою.\n");
        return;
    }

    strcpy(text, newText.c_str());
    freeWords(words, wordCount);
    words = splitWords(text, wordCount);

    printf("Прочитано слів: %d\n", readWords);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", strlen(text));
}

int main() 
{
    char text[256];

    printf("Введіть текст (до 255 символів, крапка в кінці): ");
    if (fgets(text, sizeof(text), stdin) == nullptr) {
        printf("Помилка вводу.\n");
        return 1;
    }

    // Прибираємо символ '\n', який додає fgets
    text[strcspn(text, "\n")] = '\0';

    if (!isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int wordCount = 0;
    char **words = splitWords(text, wordCount);

    int choice;
    do {
        printf("\nМеню:\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\n");
        printf("Ваш вибір: ");

        if (scanf("%d", &choice) != 1) {
            printf("Помилка: введіть номер пункту меню.\n");
            // Очищаємо буфер вводу від некоректних символів до кінця рядка
            clearInputLine();
            choice = -1;
            continue;
        }


        switch (choice) {
            case 1:
                showStats(text, wordCount);
                break;
            case 2:
                showWordTable(words, wordCount);
                break;
            case 3:

                replaceWord(text, words, wordCount);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                charInfo(text);
                break;
            case 6:
                inputNewSentence(text, words, wordCount);
                break;
            case 0:
                printf("Вихід з програми.\n");

                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);
                break;
        }
    } while (choice != 0);

    freeWords(words, wordCount);

    return 0;
}
