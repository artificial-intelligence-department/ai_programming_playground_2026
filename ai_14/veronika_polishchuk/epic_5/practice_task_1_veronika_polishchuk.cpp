// Редактор текстового повідомлення

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

const int MAX_TEXT = 255;   // найбільша довжина тексту (символів)
const int TEXT_SIZE = 256;  // розмір масиву text (255 символів + '\0')
const int WORD_SIZE = 32;   // розмір масиву для слова (31 символ + '\0')

// Зчитує й викидає решту рядка до кінця (до '\n').
// Повертає true, якщо серед викинутих символів були не лише пробіли.
bool clearLine()
{
    bool extra = false;
    int c = getchar();
    while (c != '\n' && c != EOF)
    {
        if (!isspace(c))
            extra = true;
        c = getchar();
    }
    return extra;
}

// Слово правильне, якщо воно не порожнє й містить лише латинські літери та цифри
bool isWordValid(const char* word)
{
    if (*word == '\0')
        return false;
    for (const char* p = word; *p != '\0'; p++)
    {
        unsigned char ch = (unsigned char)*p;
        if (ch >= 128 || !isalnum(ch))
            return false;
    }
    return true;
}

// Текст правильний, якщо: закінчується крапкою, перед нею лише
// латинські літери, цифри та пробіли, і є хоча б одне слово
bool isTextValid(const char* text)
{
    int len = (int)strlen(text);
    if (len == 0 || text[len - 1] != '.')
        return false;

    bool hasWord = false;
    for (const char* p = text; p < text + len - 1; p++)   // обхід вказівником
    {
        unsigned char ch = (unsigned char)*p;
        if (ch < 128 && isalnum(ch))
            hasWord = true;
        else if (ch != ' ')
            return false;
    }
    return hasWord;
}

// Порівняння двох слів без урахування регістру
bool equalIgnoreCase(const char* a, const char* b)
{
    while (*a != '\0' && *b != '\0')
    {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return false;
        a++;
        b++;
    }
    return *a == *b;   // обидва рядки мають закінчитися разом
}

// Рахує літери, цифри й пробіли (обхід тексту вказівником)
void countChars(const char* text, int& letters, int& digits, int& spaces)
{
    letters = 0;
    digits = 0;
    spaces = 0;
    while (*text != '\0')
    {
        unsigned char ch = (unsigned char)*text;
        if (isalpha(ch))
            letters++;
        else if (isdigit(ch))
            digits++;
        else if (ch == ' ')
            spaces++;
        text++;
    }
}

// Читає початковий текст через fgets. Повертає false, якщо читати не вдалося
bool readText(char* text)
{
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, TEXT_SIZE, stdin) == NULL)
        return false;

    char* nl = strchr(text, '\n');
    if (nl != NULL)
    {
        *nl = '\0';
    }
    else if ((int)strlen(text) == MAX_TEXT)
    {
        // у масив влізло 255 символів, а '\n' не прочитано: перевіряємо, чи є ще символи
        int c = getchar();
        if (c != '\n' && c != EOF)
        {
            clearLine();
            printf("Помилка: текст довший за 255 символів.\n");
            return false;
        }
    }

    // прибираємо '\r' в кінці (якщо файл із Windows)
    int len = (int)strlen(text);
    if (len > 0 && text[len - 1] == '\r')
        text[len - 1] = '\0';
    return true;
}

// Читає одне слово (до 31 символу) через scanf і перевіряє його.
// Повертає false, якщо введення некоректне (помилка вже виведена).
bool readWord(const char* prompt, char* word)
{
    printf("%s", prompt);
    if (scanf("%31s", word) != 1)
        return false;                       // кінець вводу
    if (clearLine())                        // у рядку є ще щось, крім слова
    {
        printf("Помилка: потрібно ввести одне слово до 31 символу.\n");
        return false;
    }
    if (!isWordValid(word))
    {
        printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
        return false;
    }
    return true;
}

// Читає номер пункту меню через scanf.
// Повертає: 1 - число прочитано, 0 - введено не число, -1 - кінець вводу
int readChoice(int& choice)
{
    printf("Ваш вибір: ");
    int r = scanf("%d", &choice);
    if (r == EOF)
        return -1;
    if (r == 0)                 // ввели не число, наприклад "abc"
    {
        clearLine();
        return 0;
    }
    if (clearLine())            // після числа є зайві символи, наприклад "3abc"
        return 0;
    return 1;
}

// ======================================================================
//                       ДИНАМІЧНИЙ МАСИВ СЛІВ
// ======================================================================

// Розбиває текст на слова. Кожне слово зберігається в окремому динамічному рядку
char** splitWords(const char* text, int& count)
{
    // робимо копію тексту, бо strtok псує рядок
    char* copy = new char[strlen(text) + 1];
    strcpy(copy, text);
    char* dot = strchr(copy, '.');          // завершальна крапка не входить у слово
    if (dot != NULL)
        *dot = '\0';

    // перший прохід: рахуємо слова
    count = 0;
    for (char* w = strtok(copy, " "); w != NULL; w = strtok(NULL, " "))
        count++;

    char** words = new char*[count];

    // другий прохід: копіюємо слова
    strcpy(copy, text);
    dot = strchr(copy, '.');
    if (dot != NULL)
        *dot = '\0';

    int i = 0;
    for (char* w = strtok(copy, " "); w != NULL; w = strtok(NULL, " "))
    {
        words[i] = new char[strlen(w) + 1];
        strcpy(words[i], w);
        i++;
    }

    delete[] copy;
    return words;
}

// Звільняє масив слів
void freeWords(char**& words, int& count)
{
    for (int i = 0; i < count; i++)
        delete[] words[i];
    delete[] words;
    words = NULL;
    count = 0;
}

// Замінює масив слів на новий, який відповідає тексту
void rebuildWords(const char* text, char**& words, int& count)
{
    freeWords(words, count);
    words = splitWords(text, count);
}

// ======================================================================
//                         ПУНКТИ МЕНЮ
// ======================================================================

// ----- 1. Показати текст і статистику -----
void showStats(const char* text, int wordCount)
{
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int total = (int)strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:%6d\n", total);
    printf("Слів:%10d\n", wordCount);
    printf("Літер:%9d (%5.1f%%)\n", letters, letters * 100.0 / total);
    printf("Цифр:%10d (%5.1f%%)\n", digits, digits * 100.0 / total);
    printf("Пробілів:%6d (%5.1f%%)\n", spaces, spaces * 100.0 / total);
}

// ----- 2. Таблиця слів -----
void printDashes(int n)
{
    for (int i = 0; i < n; i++)
        putchar('-');
}

void printBorder(int numWidth, int wordWidth)
{
    printf("+");
    printDashes(numWidth + 2);
    printf("+");
    printDashes(wordWidth + 2);
    printf("+");
    printDashes(7);
    printf("+\n");
}

void showWordTable(char** words, int count)
{
    // ширина колонок (підлаштовується під довгі слова)
    int wordWidth = 15;
    for (int i = 0; i < count; i++)
    {
        int len = (int)strlen(words[i]);
        if (len > wordWidth)
            wordWidth = len;
    }
    int numWidth = 2;
    if (count >= 100)
        numWidth = 3;

    // таблиця
    printBorder(numWidth, wordWidth);
    printf("| N%*s | Слово%*s | Довж. |\n", numWidth - 1, "", wordWidth - 5, "");
    printBorder(numWidth, wordWidth);
    for (int i = 0; i < count; i++)
        printf("| %*d | %-*s | %5d |\n", numWidth, i + 1, wordWidth, words[i], (int)strlen(words[i]));
    printBorder(numWidth, wordWidth);

    // найдовше, найкоротше слово і середня довжина
    int longest = 0, shortest = 0, sum = 0;
    for (int i = 0; i < count; i++)
    {
        int len = (int)strlen(words[i]);
        if (len > (int)strlen(words[longest]))
            longest = i;                    // строге порівняння: лишається перше
        if (len < (int)strlen(words[shortest]))
            shortest = i;
        sum += len;
    }
    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)sum / count);

    // сортування КОПІЇ вказівників (порядок у масиві words не змінюється)
    char** sorted = new char*[count];
    for (int i = 0; i < count; i++)
        sorted[i] = words[i];

    // сортування вибором
    for (int i = 0; i < count - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(sorted[j], sorted[min]) < 0)
                min = j;
        }
        char* tmp = sorted[i];
        sorted[i] = sorted[min];
        sorted[min] = tmp;
    }

    printf("За абеткою:");
    for (int i = 0; i < count; i++)
        printf(" %s", sorted[i]);
    printf("\n");

    // найчастіше слово: в упорядкованому масиві однакові слова стоять поруч
    const char* bestWord = sorted[0];
    int bestCount = 0;
    int i = 0;
    while (i < count)
    {
        int j = i;
        while (j < count && strcmp(sorted[j], sorted[i]) == 0)
            j++;
        if (j - i > bestCount)              // строго більше: лишається перше за абеткою
        {
            bestCount = j - i;
            bestWord = sorted[i];
        }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", bestWord, bestCount);

    delete[] sorted;   // слова не видаляємо, вони ще потрібні в масиві words
}

// ----- 3. Замінити слово -----
void replaceWord(char* text, char**& words, int& count)
{
    char from[WORD_SIZE], to[WORD_SIZE];
    if (!readWord("Замінити слово: ", from))
        return;
    if (!readWord("На слово: ", to))
        return;

    string oldText(text);
    string result = oldText;
    string fromStr(from);
    string toStr(to);
    int replaced = 0;

    size_t pos = result.find(fromStr);
    while (pos != string::npos)
    {
        size_t end = pos + fromStr.length();
        // слово ціле, якщо перед ним початок тексту або пробіл,
        // а після нього пробіл, крапка або кінець
        bool startOk = (pos == 0 || result[pos - 1] == ' ');
        bool endOk = (end == result.length() || result[end] == ' ' || result[end] == '.');

        if (startOk && endOk)
        {
            result.replace(pos, fromStr.length(), toStr);
            replaced++;
            pos = pos + toStr.length();     // перестрибуємо через нове слово
        }
        else
        {
            pos = pos + 1;
        }
        pos = result.find(fromStr, pos);
    }

    if ((int)result.length() > MAX_TEXT)
    {
        printf("Помилка: після заміни текст перевищить 255 символів. Текст не змінено.\n");
        return;
    }

    strcpy(text, result.c_str());
    rebuildWords(text, words, count);       // масив слів відповідає новому тексту

    printf("Замін виконано: %d\n", replaced);
    printf("Було: \"%s\"\n", oldText.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)result.length());
}

// ----- 4. Порівняти два слова -----
void compareWords()
{
    char a[WORD_SIZE], b[WORD_SIZE];
    if (!readWord("Перше слово: ", a))
        return;
    if (!readWord("Друге слово: ", b))
        return;

    // strcmp може повернути будь-яке число, тому зводимо до -1, 0 або 1
    int r = strcmp(a, b);
    int sign = 0;
    if (r < 0)
        sign = -1;
    else if (r > 0)
        sign = 1;

    printf("strcmp: %d -> ", sign);
    if (sign < 0)
        printf("перше слово менше\n");
    else if (sign > 0)
        printf("перше слово більше\n");
    else
        printf("слова рівні\n");

    string sa(a);
    string sb(b);
    printf("Рівні (==): %s\n", (sa == sb) ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", equalIgnoreCase(a, b) ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)strlen(a), (int)strlen(b));

    string joined = sa + " & " + sb;
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}

// ----- 5. Інформація про символ -----
void charInfo(const char* text)
{
    char c;
    printf("Введіть символ: ");
    if (scanf("%c", &c) != 1)
        return;                             // кінець вводу
    if (c == '\n')
    {
        printf("Помилка: потрібно ввести один символ.\n");
        return;
    }
    if (clearLine())
    {
        printf("Помилка: потрібно ввести лише один символ.\n");
        return;
    }
    if ((unsigned char)c > 127)
    {
        printf("Помилка: введіть символ із таблиці ASCII.\n");
        return;
    }

    int code = (unsigned char)c;

    if (isprint(code))
        printf("Символ: '%c'\n", c);
    else
        printf("Символ: недрукований\n");

    // код у різних системах числення
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", code, code, code);
    for (int bit = 7; bit >= 0; bit--)
        printf("%d", (code >> bit) & 1);    // побітові операції
    printf(")\n");

    // тип символу
    printf("Тип: ");
    if (isupper(code))
        printf("велика літера\n");
    else if (islower(code))
        printf("мала літера\n");
    else if (isdigit(code))
        printf("цифра\n");
    else if (isspace(code))
        printf("пробільний символ\n");
    else
        printf("інший символ\n");

    // для літери: інший регістр і наступний символ (арифметика над кодами)
    if (isalpha(code))
    {
        int other;
        if (isupper(code))
            other = code + ('a' - 'A');
        else
            other = code - ('a' - 'A');
        printf("Інший регістр: '%c'\n", other);
        printf("Наступний символ: '%c'\n", code + 1);
    }

    // входження в тексті
    int occurrences = 0;
    const char* first = strchr(text, c);
    const char* p = first;
    while (p != NULL)
    {
        occurrences++;
        p = strchr(p + 1, c);
    }

    if (first == NULL)
        printf("У тексті символ не зустрічається.\n");
    else
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, (int)(first - text) + 1);
}

// ----- 6. Ввести нове речення -----
void newSentence(char* text, char**& words, int& count)
{
    printf("Введіть речення (крапка після останнього слова):\n");

    string word;
    string sentence;
    int wordsRead = 0;
    bool finished = false;

    // читаємо по одному слову, доки слово не закінчиться крапкою
    while (!finished && cin >> word)
    {
        if (wordsRead > 0)
            sentence = sentence + " ";
        sentence = sentence + word;
        wordsRead++;

        if (word[word.length() - 1] == '.')
            finished = true;
    }
    cin.clear();                // скидаємо стан cin (на випадок кінця вводу)
    cin.ignore(10000, '\n');    // викидаємо залишок рядка, щоб не заважав scanf

    if ((int)sentence.length() > MAX_TEXT)
    {
        printf("Помилка: речення довше за 255 символів. Текст не змінено.\n");
        return;
    }
    if (!isTextValid(sentence.c_str()))
    {
        printf("Помилка: речення має складатися з латинських літер, цифр\n");
        printf("і пробілів та завершуватися крапкою. Текст не змінено.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    rebuildWords(text, words, count);

    printf("Прочитано слів: %d\n", wordsRead);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}


void printMenu()
{
    printf("\n=========== Меню ===========\n");
    printf("1. Показати текст і статистику\n");
    printf("2. Таблиця слів\n");
    printf("3. Замінити слово\n");
    printf("4. Порівняти два слова\n");
    printf("5. Інформація про символ\n");
    printf("6. Ввести нове речення\n");
    printf("0. Вийти\n");
    printf("============================\n");
}

int main()
{
    char text[TEXT_SIZE];

    // 1) читаємо текст і перевіряємо його
    if (!readText(text))
        return 0;

    if (!isTextValid(text))
    {
        printf("Помилка: текст має складатися з латинських літер, цифр\n");
        printf("і пробілів та завершуватися крапкою.\n");
        return 0;
    }

    // 2) розбиваємо текст на слова
    int count = 0;
    char** words = splitWords(text, count);

    // 3) меню (цикл do-while)
    int choice = -1;
    do
    {
        printMenu();

        int status = readChoice(choice);
        if (status == -1)           // кінець вводу - виходимо
            break;
        if (status == 0)            // введено не число
        {
            printf("Помилка: введіть номер пункту меню.\n");
            choice = -1;            // щоб цикл не завершився
            continue;
        }

        switch (choice)
        {
        case 1:
            showStats(text, count);
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
            newSentence(text, words, count);
            break;
        case 0:
            break;
        default:
            printf("Помилка: пункту %d немає в меню.\n", choice);
        }
    } while (choice != 0);

    // 4) звільняємо пам'ять
    freeWords(words, count);
    return 0;
}