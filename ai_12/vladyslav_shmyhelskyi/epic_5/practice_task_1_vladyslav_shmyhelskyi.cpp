#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cctype>
#include <string>

using namespace std;
void clearInput()
{
    int c = getchar();

    while (c != '\n' && c != EOF) // забираємо по одному символу з потоку введення, що очистити його
    {
        c = getchar();
    }
}
bool validWordcase3(const char word[])
{
    int length = strlen(word);

    if (length == 0 || length > 31)
    {
        return false;
    }

    for (int i = 0; i < length; i++)
    {
        char c = word[i];

        bool letter = (c >= 'a' && c <= 'z') ||
                      (c >= 'A' && c <= 'Z'); // перебираємо всі букви

        bool digit = (c >= '0' && c <= '9');

        if (!letter && !digit)
        {
            return false;
        }
    }

    return true;
}
char **splitWords(const char *text, int &count)
{
    count = 0;

    char copy[256];
    strcpy(copy, text);

    char **words = new char *[256];

    char *word = strtok(copy, " .");

    while (word != NULL)
    {
        words[count] = new char[strlen(word) + 1];
        strcpy(words[count], word);

        count++;
        word = strtok(NULL, " .");
    }

    return words;
}
void freeWords(char **&words, int &count)
{
    for (int i = 0; i < count; i++)
    {
        delete[] words[i];
    }

    delete[] words;

    words = nullptr;
    count = 0;
}
void countChars(const char *text, int &letters, int &digits, int &spaces)
{
    letters = 0;
    digits = 0;
    spaces = 0;

    while (*text != '\0')
    {
        if ((*text >= 'a' && *text <= 'z') ||
            (*text >= 'A' && *text <= 'Z'))
        {
            letters++;
        }

        if (*text >= '0' && *text <= '9')
        {
            digits++;
        }

        if (*text == ' ')
        {
            spaces++;
        }

        text++;
    }
}
void case1(char text[])
{
    int words = 0;
    int symbols = strlen(text);
    int letters = 0;
    int digits = 0;
    int spaces = 0;

    // Рахуємо літери, цифри та пробіли
    countChars(text, letters, digits, spaces);

    char copy[256];
    strcpy(copy, text); // створюємо копію, щоб не змінювати оригінальний масив

    char *word = strtok(copy, " \n");

    while (word != NULL)
    {
        words++;
        word = strtok(NULL, " \n");
    }

    double letterPercent = 0;
    double digitPercent = 0;
    double spacePercent = 0;

    if (symbols > 0)
    {
        letterPercent = letters * 100.0 / symbols; //рахуємо відсотки
        digitPercent = digits * 100.0 / symbols;
        spacePercent = spaces * 100.0 / symbols;
    }

    printf("Текст:\t\t\"%s\"\n", text);
    printf("Символів:\t%d\n", symbols);
    printf("Слів:\t\t%d\n", words);
    printf("Літер:\t\t%d (%.1f%%)\n", letters, letterPercent);
    printf("Цифр:\t\t%d (%.1f%%)\n", digits, digitPercent);
    printf("Пробілів:\t%d (%.1f%%)\n", spaces, spacePercent);
}
bool validation(const char text[])
{
    int length = strlen(text);

    if (length < 2 || length > 255) // перевірка на допустиму довжину
    {
        return false;
    }
    if (text[0] == ' ') // перевірка пробілу на початку 
    {
        return false;
    }
    if (text[length - 1] != '.') // перевірка на наявнісьть крапки вкінці
    {
        return false;
    }
    if (text[length - 2] == ' ') // чи не стоїть пробіл перед крапкою
    {
        return false;
    }

    bool hasWord = false;

    for (int i = 0; i < length - 1; i++)
    {
        char c = text[i];

        bool letter = (c >= 'a' && c <= 'z') ||
                      (c >= 'A' && c <= 'Z');

        bool digit = (c >= '0' && c <= '9');

        if (!letter && !digit && c != ' ') // якщо не буква, цифра, або пробіл то слів немає.
        {
            return false;
        }

        if (letter == true || digit == true)
        {
            hasWord = true;
        }
    }

    return hasWord;
}
void case2(char **words, int count)
{
    printf("+----+--------------------+------+\n");
    printf("| N  | Слово              | Довж.|\n");
    printf("+----+--------------------+------+\n");
    char longest[256] = "";
    int maxLength = 0;
    char shortest[256] = "";
    int minLength = 300;
    int totalLength = 0;
    for (int i = 0; i < count; i++)
    {
        int length = strlen(words[i]);

        printf("| %2d | %-18s | %4d |\n",
               i + 1, words[i], length);

        if (length > maxLength) //шукаємо найдовше слово
        {
            maxLength = length;
            strcpy(longest, words[i]);
        }

        if (length < minLength) // шукаємо найкоротше слово
        {
            minLength = length;
            strcpy(shortest, words[i]);
        }

        totalLength += length;
    }

    double average = 0;

    if (count > 0)
    {
        average = (double)totalLength / count; //середня довжина
    }
    printf("+----+--------------------+------+\n");
    printf("Найдовше слово: %s (%d)\n", longest, maxLength);
    printf("Найкоротше слово: %s (%d)\n", shortest, minLength);
    printf("Середня довжина: %.2f\n", average);
    char **sorted = new char *[count]; // створюємо масив для виводу за абеткою

    for (int i = 0; i < count; i++)
    {
        sorted[i] = words[i];
    }
    for (int i = 0; i < count - 1; i++) // сортуємо за алфавітом
    {
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(sorted[i], sorted[j]) > 0)
            {
                char *temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    printf("За абеткою: ");

    for (int i = 0; i < count; i++)
    {
        printf("%s", sorted[i]);

        if (i < count - 1)
        {
            printf(" ");
        }
    }
    printf("\n");
    char mostCommon[256] = "";
    int commonCount = 0;
    for (int i = 0; i < count; i++)
    {
        int repeat = 0;

        for (int j = 0; j < count; j++)
        {
            if (strcmp(sorted[i], sorted[j]) == 0)
            {
                repeat++;
            }
        }

        if (repeat > commonCount)
        {
            commonCount = repeat;
            strcpy(mostCommon, sorted[i]);
        }
    }

    printf("Найчастіше слово: %s (%d)\n", mostCommon, commonCount);
    delete[] sorted;
}

void case3(char text[], char **&words, int &count)
{
    char startedword[256];
    char newWord[256];
    printf("Замінити слово: ");
    if (scanf("%255s", startedword) != 1 || !validWordcase3(startedword))
    {
        printf("Помилка: некоректне слово \n");
        clearInput();
        return;
    }

    printf("На слово: ");

    if (scanf("%255s", newWord) != 1 || !validWordcase3(newWord))
    {
        printf("Помилка: некоректне нове слово\n");
        clearInput();
        return;
    }

    string changed = text;
    printf("Було:"
           "\"%s\"\n",
           text);

    int replacements = 0;
    size_t pos = 0;

    while ((pos = changed.find(startedword, pos)) != string::npos)
    {
        bool left = (pos == 0 || changed[pos - 1] == ' ');

        size_t end = pos + strlen(startedword);

        bool right = (end < changed.length() &&
                      (changed[end] == ' ' || changed[end] == '.'));

        if (left && right)
        {
            changed.replace(pos, strlen(startedword), newWord);

            replacements++;
            pos += strlen(newWord);
        }
        else
        {
            pos += strlen(startedword);
        }
    }
    if (changed.length() > 255)
    {
        printf("Помилка, текст перевищує 255 символів\n");
        return;
    }

    strcpy(text, changed.c_str());

    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %zu\n", changed.length());
    printf("Замін виконано: %d\n", replacements);

    if (replacements > 0)
    {
        freeWords(words, count);
        words = splitWords(text, count);
    }
}
void case4(char text[])
{
    char firstword[256];
    char secondword[256];
    printf("Перше слово: ");

    if (scanf("%255s", firstword) != 1 ||
        !validWordcase3(firstword)) //валідація
    {
        printf("Помилка: некоректне слово\n");
        clearInput(); // очищаємо ввід, що він не впливав на вибір
        return;
    }

    printf("Друге слово: ");

    if (scanf("%255s", secondword) != 1 ||
        !validWordcase3(secondword))
    {
        printf("Помилка: некоректне слово\n");
        clearInput();
        return;
    }
    int compare = strcmp(firstword, secondword);
    if (compare <= -1)
    {
        compare = -1;
        printf("Strcmp: %d -> перше слово менше\n", compare);
    }
    else if (compare > 0)
    {
        compare = 1;
        printf("Strcmp: %d -> перше слово більше\n", compare);
    }
    else if (compare == 0)
    {
        printf("Strcmp: %d -> слова рівні\n", compare);
    }
    string a = firstword;
    string b = secondword;

    printf("Рівні (==): ");

    if (a == b)
    {
        printf("так\n");
    }
    else
    {
        printf("ні\n");
    }
    char copyw1[256];
    char copyw2[256];
    strcpy(copyw1, firstword);
    strcpy(copyw2, secondword);
    for (int i = 0; copyw1[i] != '\0'; i++) // переводимо в нижній реєстр
    {
        copyw1[i] = tolower((unsigned char)copyw1[i]); // Бо tolower приймає тільки unsignedchar і спец. значення
    }

    for (int i = 0; copyw2[i] != '\0'; i++)
    {
        copyw2[i] = tolower((unsigned char)copyw2[i]);
    }

    int compare2 = strcmp(copyw1, copyw2);
    printf("рівні без урахування регістру: ");
    if (compare2 == 0)
        printf("так\n");
    else
        printf("ні\n");

    printf("Довжини: %zu  і %zu\n", strlen(firstword), strlen(secondword)); // strlen повертає zu
    string combined = a + " & " + b;
    printf("Конкатенація: \"%s\" (%zu)\n",
           combined.c_str(), combined.length());
}

void case5(char text[])
{
    unsigned char symbol;
    int bin[8];
    char input[256];

    printf("Введіть символ ");
    if (fgets(input, 256, stdin) == NULL)
    {
        printf("Помилка введення\n");
        return;
    }

    int length = strlen(input);

    if (length > 0 && input[length - 1] == '\n')
    {
        input[length - 1] = '\0';
    }

    if (strlen(input) != 1)
    {
        printf("Помилка: введіть тільки один символ\n");
        return;
    }

    symbol = (unsigned char)input[0];
    printf("'%c'\n", symbol);
    for (int i = 7; i >= 0; i--)
    {
        bin[7 - i] = (symbol >> i) & 1;
    }

    printf("Код: %u ( hex 0x%X, oct 0%o, bin ", symbol, symbol, symbol);
    for (int i = 0; i < 8; i++)
    {
        printf("%d", bin[i]); 
    }
    printf(")\n");
    if (isalpha(symbol))
    {
        if (isupper(symbol))
        {
            printf("Тип: велика літера\n");
        }
        else if (islower(symbol))
        {
            printf("Тип: мала літера\n");
        }
    }
    else if (isdigit(symbol))
    {
        printf("Тип: цифра\n");
    }
    else if (isspace(symbol))
    {
        printf("Тип: пробіл\n");
    }
    else if (ispunct(symbol))
    {
        printf("Тип: знак пунктуації\n");
    }
    else
    {
        printf("Тип: Невідомий\n");
    }
    printf("Інший регістр: ");
    if (isupper(symbol))
    {
        printf("'%c'\n", tolower(symbol));
    }
    else if (islower(symbol))
    {
        printf("'%c'\n", toupper(symbol));
    }
    else
    {
        printf("Немає\n");
    }

    printf("Наступний символ: '%c'\n", symbol + 1);
    int firstIn = 0;
    int count = 0;
    char *first = strchr(text, symbol);

    if (first != NULL)
    {
        firstIn = first - text + 1;
    }
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == symbol)
        {
            count++;
        }
    }
    if (count > 0)
    {
        printf("Входжень у тексті: %d, вперше на позиції %d\n", count, firstIn);
    }
    else
    {
        printf("Входжень у тексті: не було\n");
    }
}
void case6(char text[], char **&words, int &count)
{
    char newText[256] = "";
    string word;
    int wordcount = 0;
    printf("Введіть речення (крапка після останнього слова):");

    while (cin >> word)
    {
        if (word.length() > 255)
        {
            printf("Помилка: слово занадто довге\n");
            cin.ignore(10000, '\n');
            return;
        }
        wordcount++;
        int length = word.length();
        for (int i = 0; i < length; i++)
        {
            char c = word[i];

            bool letter = (c >= 'a' && c <= 'z') ||
                          (c >= 'A' && c <= 'Z');

            bool digit = (c >= '0' && c <= '9');

            bool lastDot = (c == '.' && i == length - 1);

            if (!letter && !digit && !lastDot)
            {
                printf("Помилка: недопустимий символ у реченні\n");
                cin.ignore(10000, '\n');
                return;
            }
        }
        int capacity = strlen(newText) + length;
        if (wordcount > 1)
        {
            capacity++;
        }
        if (capacity > 255)
        {
            printf("Речення завелике.\n");
            cin.ignore(10000, '\n');
            return;
        }
        if (wordcount > 1)
        {
            strcat(newText, " ");
        }
        strcat(newText, word.c_str());
        if (word[length - 1] == '.') // перевіряємо чи закінчується крапкою
        {
            break;
        }
    }
    if (!validation(newText))
    {
        printf("Помилка: некоректне речення\n");
        return;
    }
    printf("Прочитано слів: %d\n", wordcount);
    printf("Новий текст: \"%s\"\n", newText);
    printf("Довжина: %zu\n", strlen(newText));
    if (strcmp(text, newText) == 0)
    {
        printf("Речення однакові. текст не змінюється\n");
        return;
    }
    strcpy(text, newText);
    freeWords(words, count);
    words = splitWords(text, count);
}
void menu(int &option)
{ // функція для виводу меню

    printf("Пункт       Операція \n \n");

    printf("1           Показати текст і статистику \n");
    printf("2           Таблиця слів\n");
    printf("3           Замінити слово\n");
    printf("4           Порівняти два слова\n");
    printf("5           Інформація про символ\n");
    printf("6           Ввести нове речення\n");
    printf("0           Вийти\n");
    printf("Вибір: ");
    char choice[32];

    if (scanf("%31s", choice) != 1)
    {
        option = 0;
        return;
    }

    clearInput();

    if (strlen(choice) != 1 ||
        choice[0] < '0' || choice[0] > '9')
    {
        printf("Помилка: введіть номер пункту меню.\n");
        option = 7;
        return;
    }

    option = choice[0] - '0';

    if (option > 6)
    {
        printf("Помилка: пункту %d немає в меню.\n", option);
    }
}

int main()
{
    char text[256];

    printf("Введіть текст (до 255 символів, крапка в кінці)\n");

    if (fgets(text, 256, stdin) == NULL)
    {
        printf("Помилка введення тексту\n");
        return 0;
    }

    int length = strlen(text);

    if (length == 255 && text[length - 1] != '\n')
    {
        int c = getchar();

        if (c != '\n' && c != EOF)
        {
            printf("Помилка: текст занадто довгий\n");
            return 0;
        }
    }

    text[strcspn(text, "\n")] = '\0';

    if (!validation(text))
    {
        printf("текст має складатися з латинських літер, цифрі пробілів та завершуватися крапкою.\n");
        return 0;
    }
    int count = 0;
    char **words = splitWords(text, count);
    int option;
    do
    {
        menu(option);
        switch (option)
        {

        case 1:
            case1(text);

            break;

        case 2:
            case2(words, count);

            break;

        case 3:
            case3(text, words, count);
            break;

        case 4:
            case4(text);
            break;

        case 5:
            case5(text);
            break;

        case 6:
            case6(text, words, count);
            break;

        case 0:
            printf("Ви вийшли.\n");
            break;
        default:
            break;
        }
    } while (option != 0);
    freeWords(words, count);
    return 0;
}
