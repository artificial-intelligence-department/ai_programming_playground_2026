/*Редактор текстового повідомлення
Artem Mnikh
AI-14
*/

#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

bool isValidText(const char* text);
bool isValidWord(const char* word);
char** splitWords(const char* text, int& count);
void freeWords(char**& words, int& count);
void countChars(const char* text, int& letters, int& digits, int& spaces);
void showStats(const char* text, int wordCount);
void showWordTable(char** words, int count);
void replaceWord(char* text, char**& words, int& count);
void compareWords();
void showCharInfo(const char* text);
void enterNewSentence(char* text, char**& words, int& count);

int main()
{
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");

    if (!fgets(text, sizeof(text), stdin))
    {
        return 0;
    }
    text[strcspn(text, "\n")] = '\0';

    if (!isValidText(text))
    {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int count = 0;
    char** words = splitWords(text, count);

    bool isActive = true;
    int userInput;

    do
    {
        printf("\n========== Меню ==========\n");
        printf("1 - Показати текст і статистику\n");
        printf("2 - Таблиця слів\n");
        printf("3 - Замінити слово\n");
        printf("4 - Порівняти два слова\n");
        printf("5 - Інформація про символ\n");
        printf("6 - Ввести нове речення\n");
        printf("0 - Вийти\n");
        printf("Ваш вибір: ");

        if (scanf("%d", &userInput) != 1)
        {
            printf("Помилка: введіть номер пункту меню.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (userInput < 0 || userInput > 6)
        {
            printf("Помилка: пункту %d немає в меню.\n", userInput);
            continue;
        }

        switch (userInput)
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
                showCharInfo(text);
                break;
            case 6:
                enterNewSentence(text, words, count);
                break;
            case 0:
                isActive = false;
                break;
        }
    } while (isActive);

    freeWords(words, count);
    return 0;
}

bool isValidText(const char* text)
{
    int len = (int)strlen(text);
    if (len < 2 || text[len - 1] != '.')
    {
        return false;
    }

    bool hasWord = false;
    for (int i = 0; i < len - 1; ++i)
    {
        char ch = text[i];
        if (isalpha(ch) || isdigit(ch))
        {
            hasWord = true;
        }
        else if (ch != ' ')
        {
            return false;
        }
    }

    return hasWord;
}

bool isValidWord(const char* word)
{
    int len = (int)strlen(word);
    if (len < 1 || len > 31)
    {
        return false;
    }

    for (int i = 0; i < len; ++i)
    {
        char ch = word[i];
        if (!isalpha(ch) && !isdigit(ch))
        {
            return false;
        }
    }

    return true;
}

char** splitWords(const char* text, int& count)
{
    char temp[256];
    strcpy(temp, text);

    count = 0;
    char* token = strtok(temp, " .");
    while (token != nullptr)
    {
        ++count;
        token = strtok(nullptr, " .");
    }

    char** words = new char*[count];

    strcpy(temp, text);
    int index = 0;
    token = strtok(temp, " .");
    while (token != nullptr)
    {
        words[index] = new char[strlen(token) + 1];
        strcpy(words[index], token);
        ++index;
        token = strtok(nullptr, " .");
    }

    return words;
}

void freeWords(char**& words, int& count)
{
    if (words != nullptr)
    {
        for (int i = 0; i < count; ++i)
        {
            delete[] words[i];
        }
        delete[] words;
        words = nullptr;
    }
    count = 0;
}

void countChars(const char* text, int& letters, int& digits, int& spaces)
{
    letters = 0;
    digits = 0;
    spaces = 0;

    for (int i = 0; text[i] != '\0'; ++i)
    {
        char ch = text[i];
        if (isalpha(ch))
        {
            ++letters;
        }
        else if (isdigit(ch))
        {
            ++digits;
        }
        else if (ch == ' ')
        {
            ++spaces;
        }
    }
}

void showStats(const char* text, int wordCount)
{
    int totalChars = (int)strlen(text);
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:\t%2d\n", totalChars);
    printf("Слів:\t\t%2d\n", wordCount);
    printf("Літер:\t\t%2d (%5.1f%%)\n", letters, letters * 100.0 / totalChars);
    printf("Цифр:\t\t%2d (%5.1f%%)\n", digits, digits * 100.0 / totalChars);
    printf("Пробілів:\t%2d (%5.1f%%)\n", spaces, spaces * 100.0 / totalChars);
}

void showWordTable(char** words, int count)
{
    int maxLen = 0;
    int minLen = (int)strlen(words[0]);
    int longestIndex = 0;
    int shortestIndex = 0;
    int totalWordChars = 0;

    for (int i = 0; i < count; ++i)
    {
        int len = (int)strlen(words[i]);
        totalWordChars += len;
        if (len > maxLen)
        {
            maxLen = len;
            longestIndex = i;
        }
        if (len < minLen)
        {
            minLen = len;
            shortestIndex = i;
        }
    }
    int colWidth = 13;
    if (maxLen > 13) colWidth = maxLen;

    printf("+----+");
    for (int i = 0; i < colWidth + 2; ++i) printf("-");
    printf("+------+\n");

    printf("|  N | %-*s | Довж.|\n", colWidth + 5, "Слово");

    printf("+----+");
    for (int i = 0; i < colWidth + 2; ++i) printf("-");
    printf("+------+\n");

    for (int i = 0; i < count; ++i)
    {
        printf("| %2d | %-*s | %4d |\n", i + 1, colWidth, words[i], (int)strlen(words[i]));
    }

    printf("+----+");
    for (int i = 0; i < colWidth + 2; ++i) printf("-");
    printf("+------+\n");

    printf("Найдовше слово: %s (%d)\n", words[longestIndex], maxLen);
    printf("Найкоротше слово: %s (%d)\n", words[shortestIndex], minLen);
    printf("Середня довжина: %.2f\n", totalWordChars * 1.0 / count);

    const char** sorted = new const char*[count];
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
                const char* temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("За абеткою:");
    for (int i = 0; i < count; ++i)
    {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    const char* mostFrequent = sorted[0];
    int maxFreq = 1;
    int currentFreq = 1;

    for (int i = 1; i < count; ++i)
    {
        if (strcmp(sorted[i], sorted[i - 1]) == 0)
        {
            ++currentFreq;
            if (currentFreq > maxFreq)
            {
                maxFreq = currentFreq;
                mostFrequent = sorted[i];
            }
        }
        else
        {
            currentFreq = 1;
        }
    }

    printf("Найчастіше слово: %s (%d)\n", mostFrequent, maxFreq);
    delete[] sorted;
}

void replaceWord(char* text, char**& words, int& count)
{
    char fromBuf[256];
    char toBuf[256];

    printf("Замінити слово: ");
    if (!fgets(fromBuf, sizeof(fromBuf), stdin)) return;
    fromBuf[strcspn(fromBuf, "\n")] = '\0';

    if (!isValidWord(fromBuf))
    {
        printf("Помилка: слово має містити від 1 до 31 латинських літер або цифр.\n");
        return;
    }

    printf("На слово: ");
    if (!fgets(toBuf, sizeof(toBuf), stdin)) return;
    toBuf[strcspn(toBuf, "\n")] = '\0';

    if (!isValidWord(toBuf))
    {
        printf("Помилка: слово має містити від 1 до 31 латинських літер або цифр.\n");
        return;
    }

    string before(text);
    string str = before;
    string oldWord(fromBuf);
    string newWord(toBuf);

    int replacements = 0;
    size_t pos = 0;
    while ((pos = str.find(oldWord, pos)) != string::npos)
    {
        bool leftOk = (pos == 0 || str[pos - 1] == ' ');
        size_t endPos = pos + oldWord.length();
        bool rightOk = (endPos < str.length() && (str[endPos] == ' ' || str[endPos] == '.'));

        if (leftOk && rightOk)
        {
            str.replace(pos, oldWord.length(), newWord);
            ++replacements;
            pos += newWord.length();
        }
        else
        {
            pos += 1;
        }
    }

    if (str.length() > 255)
    {
        printf("Помилка: довжина тексту після заміни перевищує 255 символів.\n");
        return;
    }

    if (replacements > 0 && !(oldWord == newWord))
    {
        strcpy(text, str.c_str());
        freeWords(words, count);
        words = splitWords(text, count);
    }

    printf("Замін виконано: %d\n", replacements);
    printf("Було: \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", str.c_str());
    printf("Нова довжина: %d\n", (int)str.length());
}

void compareWords()
{
    char firstBuf[256];
    char secondBuf[256];

    printf("Перше слово: ");
    if (!fgets(firstBuf, sizeof(firstBuf), stdin)) return;
    firstBuf[strcspn(firstBuf, "\n")] = '\0';

    if (!isValidWord(firstBuf))
    {
        printf("Помилка: слово має містити від 1 до 31 латинських літер або цифр.\n");
        return;
    }

    printf("Друге слово: ");
    if (!fgets(secondBuf, sizeof(secondBuf), stdin)) return;
    secondBuf[strcspn(secondBuf, "\n")] = '\0';

    if (!isValidWord(secondBuf))
    {
        printf("Помилка: слово має містити від 1 до 31 латинських літер або цифр.\n");
        return;
    }

    int cmp = strcmp(firstBuf, secondBuf);
    if (cmp < 0)
    {
        cmp = -1;
        printf("strcmp: %d -> перше слово менше\n", cmp);
    }
    else if (cmp > 0)
    {
        cmp = 1;
        printf("strcmp: %d -> перше слово більше\n", cmp);
    }
    else
    {
        printf("strcmp: 0 -> слова рівні\n");
    }

    string strA(firstBuf);
    string strB(secondBuf);

    printf("Рівні (==): %s\n", (strA == strB) ? "так" : "ні");

    string lowerA = strA;
    string lowerB = strB;
    for (size_t i = 0; i < lowerA.length(); ++i)
    {
        lowerA[i] = (char)tolower(lowerA[i]);
    }
    for (size_t i = 0; i < lowerB.length(); ++i)
    {
        lowerB[i] = (char)tolower(lowerB[i]);
    }

    printf("Рівні без урахування регістру: %s\n", (lowerA == lowerB) ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)strA.length(), (int)strB.length());

    string concat = strA + " & " + strB;
    printf("Конкатенація: \"%s\" (%d)\n", concat.c_str(), (int)concat.length());
}

void showCharInfo(const char* text)
{
    char buf[64];
    printf("Введіть символ: ");
    if (!fgets(buf, sizeof(buf), stdin)) return;
    buf[strcspn(buf, "\n")] = '\0';

    if (strlen(buf) != 1)
    {
        printf("Помилка: потрібно ввести рівно один символ.\n");
        return;
    }

    unsigned char c = (unsigned char)buf[0];

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", (int)c, (int)c, (int)c);
    for (int bit = 7; bit >= 0; --bit)
    {
        printf("%d", (c >> bit) & 1);
    }
    printf(")\n");

    if (isupper(c))
    {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", (char)tolower(c));
    }
    else if (islower(c))
    {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", (char)toupper(c));
    }
    else if (isdigit(c))
    {
        printf("Тип: цифра\n");
    }
    else if (isspace(c))
    {
        printf("Тип: пробільний символ\n");
    }
    else
    {
        printf("Тип: інший символ\n");
    }

    printf("Наступний символ: '%c'\n", (char)(c + 1));

    const char* firstMatch = strchr(text, c);
    if (firstMatch == nullptr)
    {
        printf("У тексті не зустрічається\n");
    }
    else
    {
        int occurrences = 0;
        for (int i = 0; text[i] != '\0'; ++i)
        {
            if (text[i] == c)
            {
                ++occurrences;
            }
        }
        int firstPos = (int)(firstMatch - text) + 1;
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, firstPos);
    }
}

void enterNewSentence(char* text, char**& words, int& count)
{
    printf("Введіть речення (крапка після останнього слова):\n");
    string newSentence;
    string token;
    int readWords = 0;
    bool endedWithDot = false;
    bool overflow = false;

    while (cin >> token)
    {
        if (token == ".")
        {
            if (!overflow)
            {
                newSentence = newSentence + ".";
                if (newSentence.length() > 255) overflow = true;
            }
            endedWithDot = true;
            break;
        }

        if (!overflow)
        {
            if (readWords > 0)
                newSentence = newSentence + " " + token;
            else
                newSentence = token;

            if (newSentence.length() > 255) overflow = true;
        }
        ++readWords;

        if (!token.empty() && token[token.length() - 1] == '.')
        {
            endedWithDot = true;
            break;
        }
    }

    cin.clear();
    cin.ignore(10000, '\n');

    if (!endedWithDot || overflow || !isValidText(newSentence.c_str()))
    {
        printf("Помилка: некоректне речення, поточний текст не змінено.\n");
        return;
    }

    strcpy(text, newSentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", readWords);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}