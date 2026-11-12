#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cctype>
using namespace std;

char **splitWords(const char *text, int &count)
{
    char copy[256];
    strcpy(copy, text);
    count = 0;

    char *word = strtok(copy, " .");
    while (word != NULL)
    {
        count++;
        word = strtok(NULL, " .");
    }
    char **words = new char *[count];

    strcpy(copy, text);
    word = strtok(copy, " .");
    int i = 0;

    while (word != NULL)
    {
        words[i] = new char[strlen(word) + 1];
        strcpy(words[i], word);
        i++;
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
    words = NULL;
    count = 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces)
{
    letters = 0;
    digits = 0;
    spaces = 0;

    const char *p = text;
    while (*p != '\0')
    {
        if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z'))
        {
            letters++;
        }
        else if (*p >= '0' && *p <= '9')
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

void showStatistics(const char *text, int count)
{
    int letters = 0;
    int digits = 0;
    int spaces = 0;

    countChars(text, letters, digits, spaces);
    int len = strlen(text);

    double percentLetters = (double)letters / len * 100;
    double percentDigits = (double)digits / len * 100;
    double percentSpaces = (double)spaces / len * 100;

    printf("Текст: \t\"%s\"\n", text);
    printf("Символів: %d \n", len);
    printf("Слів: %d \n", count);
    printf("Літер: %d (%.1f %%) \n", letters, percentLetters);
    printf("Цифр: %d (%.1f %%) \n", digits, percentDigits);
    printf("Пробілів: %d (%.1f %%) \n", spaces, percentSpaces);
}

void showWordsTable(char **words, int count)
{
    printf("+----+------------------+-------+\n");
    printf("|  N | Слово            | Довж. |\n");
    printf("+----+------------------+-------+\n");

    int maxLenght = 0;
    string maxWord;
    int minLenght = 255;
    string minWord;
    int sumLength = 0;
    double averageWord;

    for (int i = 0; i < count; i++)
    {
        printf("| %2d | %-16s | %5d |\n", i + 1, words[i], (int)strlen(words[i]));
        if (strlen(words[i]) > maxLenght)
        {
            maxLenght = strlen(words[i]);
            maxWord = words[i];
        }
        if (strlen(words[i]) < minLenght)
        {
            minLenght = strlen(words[i]);
            minWord = words[i];
        }
        sumLength += strlen(words[i]);
    }
    printf("+----+------------------+-------+\n");

    averageWord = (double)sumLength / count;

    char **sorted = new char *[count];

    for (int i = 0; i < count; i++)
    {
        sorted[i] = words[i];
    }
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(sorted[j], sorted[j + 1]) > 0)
            {
                char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    int maxFrequency = 0;
    char *mostFrequent = sorted[0];
    for (int i = 0; i < count; i++)
    {
        int frequency = 0;

        for (int j = 0; j < count; j++)
        {
            if (strcmp(sorted[i], sorted[j]) == 0)
            {
                frequency++;
            }
        }

        if (frequency > maxFrequency)
        {
            maxFrequency = frequency;
            mostFrequent = sorted[i];
        }
    }

    printf("Найдовше слово: %s (%d) \n", maxWord.c_str(), maxLenght);
    printf("Найкоротше слово: %s (%d) \n", minWord.c_str(), minLenght);
    printf("Середня довжина: %.2f \n", averageWord);
    printf("За абеткою: ");

    for (int i = 0; i < count; i++)
    {
        printf("%s ", sorted[i]);
    }

    printf("\n");
    printf("Найчастіше слово: %s (%d)\n", mostFrequent, maxFrequency);

    delete[] sorted;
}

void replaceWord(char *text, char **&words, int &count)
{
    char from[32];
    char to[32];
    string before = text;

    printf("Замінити слово: ");
    scanf("%31s", from);
    printf("На слово: ");
    scanf("%31s", to);
    for (int i = 0; i < strlen(to); i++)
    {
        if (!((to[i] >= 'a' && to[i] <= 'z') ||
              (to[i] >= 'A' && to[i] <= 'Z') ||
              (to[i] >= '0' && to[i] <= '9')))
        {
            printf("Помилка! Нове слово містить недопустимі символи. \n");
            return;
        }
    }
    string result = text;
    string oldWord = from;
    string newWord = to;
    size_t pos = result.find(oldWord);
    int replacements = 0;

    while (pos != string::npos)
    {
        bool left = (pos == 0 || result[pos - 1] == ' ');

        bool right = (pos + oldWord.length() == result.length() || result[pos + oldWord.length()] == ' ' || result[pos + oldWord.length()] == '.');

        if (left && right)
        {
            result.replace(pos, oldWord.length(), newWord);
            replacements++;
            pos = result.find(oldWord, pos + newWord.length());
        }
        else
        {
            pos = result.find(oldWord, pos + 1);
        }
    }
    if (result.length() > 255)
    {
        printf("Помилка! Новий текст перевищує 255 символів.\n");
        return;
    }
    strcpy(text, result.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Замін виконано: %d\n", replacements);
    printf("Було: \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %zu\n", result.length());
}

void compareWords()
{
    char a[32];
    char b[32];

    printf("Перше слово: ");
    scanf("%31s", a);

    printf("Друге слово: ");
    scanf("%31s", b);

    int result = strcmp(a, b);
    if (result < 0)
    {
        printf("strcmp: -1 -> перше слово менше\n");
    }
    else if (result > 0)
    {
        printf("strcmp: 1 -> перше слово більше\n");
    }
    else
    {
        printf("strcmp: 0 -> слова однакові\n");
    }

    string first = a;
    string second = b;

    if (first == second)
    {
        printf("Рівні (==): так\n");
    }
    else
    {
        printf("Рівні (==): ні\n");
    }

    string lowerFirst = first;
    string lowerSecond = second;

    for (int i = 0; i < lowerFirst.length(); i++)
    {
        lowerFirst[i] = tolower(lowerFirst[i]);
    }
    for (int i = 0; i < lowerSecond.length(); i++)
    {
        lowerSecond[i] = tolower(lowerSecond[i]);
    }
    if (lowerFirst == lowerSecond)
    {
        printf("Рівні без урахування регістру: так\n");
    }
    else
    {
        printf("Рівні без урахування регістру: ні\n");
    }
    printf("Довжини: %zu і %zu\n", first.length(), second.length());
    string combined = first + " & " + second;
    printf("Конкатенація: \"%s\" (%zu)\n", combined.c_str(), combined.length());
}

void analyzeChar(const char *text)
{
    char symbol;

    printf("Введіть символ: ");
    scanf(" %c", &symbol);
    printf("Символ: '%c' ", symbol);
    unsigned char code = (unsigned char)symbol;
    printf("Код: %d (hex 0x%x, oct 0%o, ", code, code, code);
    printf("bin ");
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (code >> i) & 1);
    }

    printf(")\n");

    if (isupper(symbol))
    {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(symbol));
    }
    else if (islower(symbol))
    {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(symbol));
    }
    else if (isdigit(symbol))
    {
        printf("Тип: число\n");
    }
    else if (isspace(symbol))
    {
        printf("Тип: пробел\n");
    }
    else
    {
        printf("Тип: інший символ\n");
    }
    printf("Наступний символ: '%c'\n", symbol + 1);

    int countSymbols = 0;
    int firstPosition = -1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == symbol)
        {
            countSymbols++;
            if (firstPosition == -1)
            {
                firstPosition = i + 1;
            }
        }
    }

    if (countSymbols > 0)
    {
        printf("Входжень у тексті: %d, перше на позиції %d\n", countSymbols, firstPosition);
    }
    else
    {
        printf("Символ у тексті не зустрічається.\n");
    }
}

void inputNewSentence(char *text, char **&words, int &count)
{
    string sentence = "";
    string word;
    printf("Введіть нове речення (крапка після останнього слова):\n");
    while (cin >> word)
    {
        if (sentence.length() > 0)
        {
            sentence += " ";
        }
        sentence += word;
        if (sentence[sentence.length() - 1] == '.')
        {
            break;
        }
    }
    if (sentence.length() > 255)
    {
        printf("Помилка! Текст перевищує 255 символів.\n");
        return;
    }
    if (sentence.length() < 2)
    {
        printf("Помилка! Речення не може бути порожнім.\n");
        return;
    }
    for (int i = 0; i < sentence.length() - 1; i++)
    {
        if (!((sentence[i] >= 'a' && sentence[i] <= 'z') ||
              (sentence[i] >= 'A' && sentence[i] <= 'Z') ||
              (sentence[i] >= '0' && sentence[i] <= '9') ||
              sentence[i] == ' '))
        {
            printf("Помилка! Недопустимий символ.\n");
            return;
        }
    }
    bool hasWord = false;

    for (int i = 0; i < sentence.length() - 1; i++)
    {
        if ((sentence[i] >= 'a' && sentence[i] <= 'z') ||
            (sentence[i] >= 'A' && sentence[i] <= 'Z'))
        {
            hasWord = true;
            break;
        }
    }

    if (!hasWord)
    {
        printf("Помилка! Речення має містити хоча б одне слово.\n");
        return;
    }
    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Прочитано слів: %d\n", count);
    printf("Нове речення: %s\n", text);
    printf("Довжина: %zu\n", strlen(text));
}

int main()
{
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці): \n");
    if (fgets(text, 256, stdin) == NULL)
    {
        printf("Помилка зчитування тексту.\n");
        return 1;
    }
    int len = strlen(text);

    if (len > 0 && text[len - 1] != '\n')
    {
        int c = getchar();

        if (c != '\n')
        {
            printf("Помилка! Текст перевищує 255 символів.\n");
            return 1;
        }
    }
    if (len > 0 && text[len - 1] == '\n')
    {
        text[len - 1] = '\0';
        len--;
    }
    if (len == 0)
    {
        printf("Помилка! Текст не може бути порожнім. \n");
        return 1;
    }
    if (text[len - 1] != '.')
    {
        printf("Помилка! Текст має закінчуватися крапкою. \n");
        return 1;
    }
    bool hasWord = false;
    for (int i = 0; i < len - 1; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') ||
            (text[i] >= 'A' && text[i] <= 'Z'))
        {
            hasWord = true;
            break;
        }
    }
    if (hasWord == false)
    {
        printf("Помилка! Текст має містити хоча б одне слово. \n");
        return 1;
    }

    for (int i = 0; i < len - 1; i++)
    {
        if (!((text[i] >= 'a' && text[i] <= 'z') ||
              (text[i] >= 'A' && text[i] <= 'Z') ||
              (text[i] >= '0' && text[i] <= '9') ||
              text[i] == ' '))
        {
            printf("Помилка! Недопустимий символ. \n");
            return 1;
        }
    }

    int count = 0;
    char **words = splitWords(text, count);

    int choice = -1;

    do
    {
        printf("\n============ МЕНЮ ============\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\n");

        printf("Ваш вибір: ");
        if (!(scanf("%d", &choice)) || choice < 0 || choice > 6)
        {
            printf("Помилка! Введіть номер пункту меню. \n");
            int c = getchar();

            while (c != '\n' && c != EOF)
            {
                c = getchar();
            }
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("========== Статистика тексту ==========\n");
            showStatistics(text, count);
            break;

        case 2:
            printf("========== Таблиця слів ==========\n");
            showWordsTable(words, count);
            break;

        case 3:
            printf("========== Заміна слова ==========\n");
            replaceWord(text, words, count);
            break;

        case 4:
            printf("========== Порівняння слів ==========\n");
            compareWords();
            break;

        case 5:
            printf("========== Інформація про символ ==========\n");
            analyzeChar(text);
            break;

        case 6:
            printf("========== Нове речення ==========\n");
            inputNewSentence(text, words, count);
            break;

        case 0:
            printf("========== Завершення програми. ==========\n");
            break;

        default:
            printf("Помилка! Такого пункту немає.\n");
        }

    } while (choice != 0);

    freeWords(words, count);
    return 0;
}
