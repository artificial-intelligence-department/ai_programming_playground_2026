/*
    Задача: Редактор текстового повідомлення
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>
using namespace std;
// Перевірка валідності тексту
bool validText(const char* text)
{
    int len = strlen(text); 
    if (len == 0 || text[len - 1] != '.')
    {
        return false;
    }
    bool hasWord = false; 
    for (int i = 0; i < len - 1; i++) 
    {
        if (isalnum(text[i])) 
        {
            hasWord = true;
        } 
        else if (text[i] != ' ') 
        {
            return false;
        }
    }
    return hasWord;
}
// Розбиття тексту на слова
char **splitWords(const char *text, int &count)
{
    count = 0;
    char temp[256];
    strcpy(temp, text); 
    char* word = strtok(temp, " ."); 
    while (word != NULL) 
    {
        count++;
        word = strtok(NULL, " ."); 
    }
    char** words = new char*[count]; 
    strcpy(temp, text);
    word = strtok(temp, " .");
    for (int i = 0; i < count; i++)
    {
        int len = strlen(word); 
        words[i] = new char[len + 1];
        strcpy(words[i], word); 
        word = strtok(NULL, " ."); 
    }
    return words;
}
// Звільнення пам'яті масиву
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
// Підрахунок літер, цифр і пробілів
void countChars(const char *text, int &letters, int &digits, int &spaces)
{
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
//Вивід тексту і статистики
void showStatistics(char *text, int wordCount)
{
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int length = strlen(text);
    double lettersPercent = letters * 100.0 / length;
    double digitsPercent = digits * 100.0 / length;
    double spacesPercent = spaces * 100.0 / length;
    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %6d\n", length);
    printf("Слів: %10d\n", wordCount);
    printf("Літер: %9d (%5.1f%%)\n", letters, lettersPercent);
    printf("Цифр: %10d (%5.1f%%)\n", digits, digitsPercent);
    printf("Пробілів: %6d (%5.1f%%)\n", spaces, spacesPercent);
}
// Вивід таблиці слів та її статистики
void showTable(char **words, int count)
{
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for (int i = 0; i < count; i++)
    {
        int len = strlen(words[i]);
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);
    }
    printf("+----+-----------------+-------+\n");
    int longest = 0;
    int shortest = 0;
    int longestLen = strlen(words[0]);
    int shortestLen = strlen(words[0]);
    double total = 0;
    for (int i = 0; i < count; i++)
    {
        int len = strlen(words[i]);
        total += len;
        if (len > longestLen)
        {
            longestLen = len;
            longest = i;
        }
        if (len < shortestLen)
        {
            shortestLen = len;
            shortest = i;
        }
    }
    double average = total / count;
    printf("Найдовше слово: %s (%d)\n", words[longest], longestLen);
    printf("Найкоротше слово: %s (%d)\n", words[shortest], shortestLen);
    printf("Середня довжина: %.2f\n", average);
    char **sorted = new char*[count];
    for (int i = 0; i < count; i++)
    {
        sorted[i] = words[i]; 
    }
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (strcmp(sorted[j], sorted[j+1]) > 0)
            {
                char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    printf("За абеткою:");
    for (int i = 0; i < count; i++)
    {
        printf(" %s", sorted[i]);
    }
    printf("\n");
    int bestIndex = 0;
    int bestCount = 0;
    int run = 0;
    for (int i = 0; i < count; i++)
    {
        if (i > 0 && strcmp(sorted[i], sorted[i - 1]) == 0)
        {
            run +=1;
        }
        else
        {
            run = 1;
        }
        if (run > bestCount)
        {
            bestCount = run;
            bestIndex = i;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[bestIndex], bestCount);
    delete[] sorted;
}
// Перевірка валідності слова
bool validWord(const char *word)
{
    int len = strlen(word);
    if (len == 0)
    {
        return false;
    }
    for (int i = 0; i < len; i++)
    {
        if (!isalnum(word[i]))
        {
            return false;
        }
    }
    return true;
}
// Заміна слова в тексті
void replaceWord(char *text, char **&words, int &count)
{
    char oldWord[32];
    char newWord[32];
    printf("Замінити слово: ");
    scanf("%31s", oldWord);
    printf("На слово: ");
    scanf("%31s", newWord);
    if (!validWord(oldWord) || !validWord(newWord))
        {
            printf("Помилка: слова мають складатися лише з латинських літер і цифр.\n");
            return;
        }
    string newText = text; 
    string oldString = oldWord; 
    string newString = newWord;
    int replaceCount = 0;
    int position = newText.find(oldString); 
    while (position != string::npos)
    {
       int end = position + oldString.length(); 
       bool wholeWord = true; 
       if (position > 0 && newText[position - 1] != ' ') 
       {
        wholeWord = false;
       }
       if (newText[end] != ' ' && newText[end] != '.') 
       {
        wholeWord = false;
       }
       if (wholeWord)
       {
        newText.replace(position, oldString.length(), newString);
        replaceCount++;
        position += newString.length(); 
       }
        else
        {
            position += oldString.length(); 
        }
        position = newText.find(oldString, position);
    }
    if (newText.length() > 255)
    {
        printf("Помилка: текст перевищить 255 символів, заміну не виконано.\n");
        return;
    }
    printf("Замін виконано: %d\n", replaceCount);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", newText.c_str());
    printf("Нова довжина: %d\n", (int)newText.length());
    strcpy(text, newText.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
}
// Порівняння двох слів
void compareWords(char *firstWord, char *secondWord)
{
    printf("Перше слово: ");
    scanf("%31s", firstWord);
    printf("Друге слово: ");
    scanf("%31s", secondWord);
    if (!validWord(firstWord) || !validWord(secondWord))
    {
        printf("Помилка: слова мають складатися лише з латинських літер і цифр.\n");
        return;
    }
    int compareResult = strcmp(firstWord, secondWord);
    if (compareResult < 0)
    {
        printf("strcmp: -1 -> перше слово менше\n");
    }
    else if (compareResult > 0)
    {
        printf("strcmp: 1 -> перше слово більше\n");
    }
    else 
    {
        printf("strcmp: 0 -> слова рівні\n");
    }
    string first = firstWord;
    string second = secondWord;
    if (first == second)
    {
        printf("Рівні (==): так\n");
    }
    else
    {
        printf("Рівні (==): ні\n");
    }
    string firstLower = first;
    string secondLower = second;
    for (int i = 0; i < firstLower.length(); i++)
    {
        firstLower[i] = tolower(firstLower[i]);
    }
    for (int i = 0; i < secondLower.length(); i++)
    {
        secondLower[i] = tolower(secondLower[i]);
    }
    if (firstLower == secondLower)
    {
        printf("Рівні без урахування регістру: так\n");
    }
    else
    {
        printf("Рівні без урахування регістру: ні\n");
    }
    int firstLength = first.length();
    int secondLength = second.length();
    printf("Довжини: %d і %d\n", firstLength, secondLength);
    string joined = first + " & " + second;
    int joinedLength = joined.length();
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), joinedLength);
}
// Вивід інформації про символ
void showCharInfo(const char *text)
{
    char symbol;
    printf("Введіть символ: ");
    scanf(" %c", &symbol);
    if (symbol < 33 || symbol > 126)
    {
        printf("Помилка: потрібен символ з латинської розкладки.\n");
        return;
    }
    printf("Символ: '%c'\n", symbol);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", symbol, symbol, symbol);
    for (int bit = 7; bit >=0; bit--)
    {
        int bitValue = (symbol >> bit) & 1;
        printf("%d", bitValue);
    }
    printf(")\n");
    bool isLetter = false;
    if (isupper(symbol))
    {
        printf("Тип: велика літера\n");
        isLetter = true;
    }
    else if (islower(symbol))
    {
        printf("Тип: мала літера\n");
        isLetter = true;
    }
    else if (isdigit(symbol))
    {
        printf("Тип: цифра\n");
    }
    else if (isspace(symbol))
    {
        printf("Тип: пробільний символ\n");
    }
    else
    {
        printf("Тип: інший символ\n");
    }
    if (isLetter)
    {
        char otherCase;
        if (isupper(symbol))
        {
            otherCase = tolower(symbol);
        }
        else
        {
            otherCase = toupper(symbol);
        }
        printf("Інший регістр: '%c'\n", otherCase);
        printf("Наступний символ: '%c'\n", symbol + 1);
    }
    int timesFound = 0;
    int firstPos = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == symbol)
        {
            timesFound++;
            if (firstPos == 0)
            {
                firstPos = i + 1;
            }
        }
    }
    if (timesFound == 0)
    {
        printf("Символ '%c' у тексті не зустрічається.\n", symbol);
    }
    else
    {
        printf("Входжень у тексті: %d, перше на позиції %d\n", timesFound, firstPos);
    }
}
// Вивід нового значення
void enterNewSentence(char *text, char **&words, int &count)
{
    string sentence = "";
    string word;
    bool finished = false;
    printf("Введіть речення (крапка після останнього слова): ");
    while (finished == false)
    {
        cin >> word;
        if (sentence != "")
        {
            sentence = sentence + " ";
        }
        sentence += word;
        if (word[word.length() - 1] == '.')
        {
            finished = true;
        }
    }
    if (sentence.length() > 255)
    {
        printf("Помилка: речення довше за 255 символів, текст не змінено.\n");
        return;
    }
    if (!validText(sentence.c_str()))
    {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }
    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    int length = strlen(text);
    printf("Довжина: %d\n", length);
}
int main() {
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці): ");
    fgets(text, 256, stdin); 
    char *n1 = strchr(text, '\n'); 
    if (n1 != NULL) 
    {
        *n1 = '\0';
    }
    if (!validText(text))
    {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 0; 
    }
    int count = 0;
    char** words = splitWords(text, count);
    char firstWord[32];
    char secondWord[32];
    int choice = 1;
    do 
    {
        printf("\n --- Меню --- \n");
        printf("1 - Показати текст і статистику\n");
        printf("2 - Таблиця слів\n");
        printf("3 - Замінити слово\n");
        printf("4 - Порівняти два слова\n");
        printf("5 - Інформація про символ\n");
        printf("6 - Ввести нове речення\n");
        printf("0 - Вийти\n");
        printf("Ваш вибір: ");
        if (scanf("%d", &choice) != 1) 
        {
            printf("Помилка: введіть номер пункту меню.\n");
            while (getchar() != '\n'); 
            choice = 1;
            continue;
        }
        if (choice < 0 || choice > 6)
        {
            printf("Помилка: пункту %d немає в меню.\n", choice);
        }
        switch (choice)
        {
            case 1: showStatistics(text, count); break;
            case 2: showTable(words, count); break;
            case 3: replaceWord(text, words, count); break;
            case 4: compareWords(firstWord, secondWord); break;
            case 5: showCharInfo(text); break;
            case 6: enterNewSentence(text, words, count); break;
        }
    } while (choice != 0);
    freeWords(words, count);
    return 0;
}