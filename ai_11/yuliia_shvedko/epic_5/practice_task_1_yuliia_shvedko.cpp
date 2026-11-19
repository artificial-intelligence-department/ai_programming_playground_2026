#include <iostream>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>

using namespace std;

char **splitWords(const char *text, int &count);
void countChars(const char *text, int &letters, int &digits, int &spaces);
void freeWords(char **&words, int &count);
void case1(char *text, int count, size_t l);
void case2(char **words, char *text, int count);
void case3(char *text);
void case4();
void case5(char *text);
void case6(char *text, int count);

int main()
{
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    char text[256];
    fgets(text, sizeof(text), stdin);
    size_t l = strlen(text);
    if( l > 0 && text[l - 1] == '\n')
    l--;
    int c = 0;
    for(size_t i = 0; i < l - 1; i++)
    {
        if(isalpha(text[i]) || isdigit(text[i]))
        c++;
    }
    if(c == 0)
    {
        printf("Текст має містити хоча б одне слово!");
        return 0;
    }
    if(l > 255)
    {
        printf("Текст має містити не більше 255 символів!");
        return 0;
    }
    if(text[l - 1] != '.')
    {
        printf("Текст має закінчуватися крапкою!");
        return 0;
    }
    for(size_t i = 0; i < l - 1; i++)
    {
        bool letter = isalpha(text[i]);
        bool digit = isdigit(text[i]);
        bool space = isspace(text[i]);
        if(!letter && !digit && !space)
        {
            printf("Текст має містити лише латинські літери, цифри та пробіли!");
            return 0;
        }
    }
    text[l] = '\0';

    int count;
    char **words = splitWords(text, count);

    int a;
    do
    {
        printf("\nМеню:\n");
        printf("1 - Показати текст і статистику\n");
        printf("2 - Таблиця слів\n");
        printf("3 - Замінити слово\n");
        printf("4 - Порівняти два слова\n");
        printf("5 - Інформація про символ\n");
        printf("6 - Ввести нове речення\n");
        printf("0 - Вийти\n\n");
        printf("Ваш вибір: ");
        
        while (scanf("%d", &a) != 1)
        {
            printf("Введіть число!\n");
            getchar();
        }
        
        switch(a)
        {
            case 1:
            case1(text, count, l);
            break;

            case 2:
            case2(words, text, count);
            break;

            case 3:
            case3(text);
            break;

            case 4:
            case4();
            break;

            case 5:
            case5(text);
            break;

            case 6:
            case6(text, count);
            break;

            case 0:
            printf("Роботу програми завершено!\n");
            break;

            default:
            printf("\nВиберіть пункт від 0 до 6!\n");
            break;
        }
    }
    while(a != 0);
    freeWords(words, count);
    return 0;
}

char **splitWords(const char *text, int &count)
{
    count = 0;
    size_t l = strlen(text);
    char* copy = new char[l + 1];
    strcpy(copy, text);
    char* ccopy = new char[l + 1];
    strcpy(ccopy, text);
    char* t = strtok(ccopy, " .");
    while(t != nullptr)
    {
        count++;
        t = strtok(nullptr, " .");
    }
    delete[] ccopy;
    char** words = new char*[count];
    t = strtok(copy, " .");
    int i = 0;
    while(t != nullptr)
    {
        words[i] = new char[strlen(t) + 1];
        strcpy(words[i], t);
        i++;
        t = strtok(nullptr, " .");
    }
    delete[] copy;
    return words;
}

void countChars(const char *text, int &letters, int &digits, int &spaces)
{
    size_t l = strlen(text);
    letters = 0;
    digits = 0;
    spaces = 0;
    for(const char *i = text; *i != '\0'; i++)
    {
        if(isalpha(*i))
        {
            letters++;
        }
        else if(isdigit(*i))
        {
            digits++;
        }
        else if(isspace(*i))
        {
            spaces++;
        }
    }
}

void freeWords(char **&words, int &count)
{
    for(int i = 0; i < count; i++)
    delete[] words[i];
    delete[] words;
    words = nullptr;
}

void case1(char *text, int count, size_t l)
{
    printf("\nТекст:\t\"%s\"\n", text);
    printf("Cимволів: %2lu\n", strlen(text));
    splitWords(text, count);
    printf("Слів: %6d\n", count);
    int letters;
    int digits;
    int spaces;
    countChars(text, letters, digits, spaces);
    printf("Літер: %5d(%5.1f %%)\n", letters, (((double)letters/l)*100));
    printf("Цифр: %6d(%5.1f %%)\n", digits, (((double)digits/l)*100));
    printf("Пробілів: %2d(%5.1f %%)\n", spaces, (((double)spaces/l)*100));
}

void case2(char **words, char *text, int count)
{
    words = splitWords(text, count);
    printf("+----+--------------+-------+\n");
    printf("| N  | Слово        | Довж. |\n");
    printf("+----+--------------+-------+\n");
    for(int i = 0; i < count; i++)
    printf("|%3d | %-13s|%6lu |\n", i + 1, words[i], strlen(words[i]));
    printf("+----+--------------+-------+\n");
    int min = 0;
    int max = 0;
    int sum = 0;
    for(int i = 0; i < count; i++)
    {
        sum += strlen(words[i]);
        if(strlen(words[i]) < strlen(words[min]))
        min = i;
        if(strlen(words[i]) > strlen(words[max]))
        max = i;
    }
    printf("Найдовше слово: %s (%lu)\n", words[max], strlen(words[max]));
    printf("Найкоротше слово: %s (%lu)\n", words[min], strlen(words[min]));
    printf("Середня довжина: %.2f \n", (double)sum/count);
    char **words2 = new char*[count];
    for(int i = 0; i < count; i++)
    words2[i] = words[i];
    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i -1; j++)
        {
            if(strcmp(words2[j], words2[j + 1]) > 0)
            {
                char *t = words2[j];
                words2[j] = words2[j + 1];
                words2[j + 1] = t;
            }

        }
    }
    printf("За абеткою: ");
    for(int i = 0; i < count; i++)
    printf("%s ", words2[i]);
    delete[] words2;
    words2 = nullptr;
    int m = 0;
    for(int i = 0; i < count; i++)
    {
        int n = 0;
        for(int j = 0; j < count; j++)
        {
            if(strcmp(words[i], words[j]) == 0)
            n++;
        }
        if(n > m)
        {
            m = n;
            max = i;
        }
    }
    printf("\nНайчастіше слово: %s (%d)\n", words[max], m);
}

void case3(char *text)
{
    char old[32];
    char neww[32];
    printf("Замінити слово: ");
    scanf("%31s", old);
    printf("На слово: ");
    scanf("%31s", neww);
    string oold(old);
    string nnew(neww);
    if(oold == nnew)
    {
        printf("Старе та нове слово не мають збігатися!\n");
        return;
    }
    if(oold.length() > 31 || nnew.length() > 31)
    {
        printf("Довжина нового та старого слова має бути не більше 31 символу!\n");
        return;
    }
    for(size_t i = 0; i < nnew.length(); i++)
    {
        if(!isalpha(nnew[i]) && !isdigit(nnew[i]))
        {
            printf("Нове слово має містити лише латинські літери та цифри!\n");
            return;
        }
    }
    string newtext(text);
    size_t pos = 0;
    int rCount = 0;
    while((pos = newtext.find(oold, pos)) != string::npos)
    {
        bool left = (pos == 0 || isspace(newtext[pos - 1]));
        size_t endPos = pos + oold.length();
        bool right = (endPos == newtext.length() || isspace(newtext[endPos]) || newtext[endPos] == '.');
        if(left && right)
        {
            newtext.replace(pos, oold.length(), nnew);
            rCount++;
            pos += nnew.length();
        }
        else
        pos += oold.length();
    }
    if(newtext.length() > 255)
    {
        printf("Довжина тексту перевищує 255 символів!\n");
        return;
    }
    printf("Замін виконано: %d\n", rCount);
    printf("Було:\t\"%s\"\n", text);
    strcpy(text, newtext.c_str());
    printf("Стало:\t\"%s\"\n", text);
    printf("Нова довжина: %lu\n", newtext.length());
}

void case4()
{
    char first[32];
    char second[32];
    printf("Перше слово: ");
    scanf("%31s", first);
    printf("Друге слово: ");
    scanf("%31s", second);
    string firstW(first);
    string secondW(second);
    if(firstW.length() > 31 || secondW.length() > 31)
    {
        printf("Довжина першого та другого слова має бути не більше 31 символу!\n");
        return;
    }
    for(size_t i = 0; i < firstW.length(); i++)
    {
        if(!isalpha(firstW[i]) && !isdigit(firstW[i]))
        {
            printf("Cловa мають містити лише латинські літери та цифри!\n");
            return;
        }
    }
    for(size_t i = 0; i < secondW.length(); i++)
    {
        if(!isalpha(secondW[i]) && !isdigit(secondW[i]))
        {
            printf("Cловa мають містити лише латинські літери та цифри!\n");
            return;
        }
    }
    int b = strcmp(first, second);
    printf("strcmp: ");
    if(b < 0)
    printf("-1 -> перше слово менше\n");
    if(b == 0)
    printf("0 -> слова однакові\n");
    if(b > 0)
    printf("1 -> перше слово більше\n");

    printf("Рівні (==): ");
    if(firstW == secondW)
    printf("так\n");
    if(firstW != secondW)
    printf("ні\n");

    printf("Рівні без урахування регістру: ");
    if(firstW.length() != secondW.length())
    printf("ні\n");
    else
    {
        bool q = true;
        for(size_t i = 0; i < firstW.length(); i++)
        {
            if(tolower(first[i]) != tolower(second[i]))
            q = false;
        }
        if(q)
        printf("так\n");
        else
        printf("ні\n");
    }
    printf("Довжини: %lu i %lu\n", firstW.length(), secondW.length());

    string c = firstW + " & " + secondW;
    printf("Конкатенація: %s (%lu)\n", c.c_str(), c.length());
}

void case5(char *text)
{
    printf("Введіть символ: ");
    getchar();
    char c;
    scanf("%c", &c);
    printf("Cимвол: '%c'\n", c);
    printf("Код: %d (hex 0x%X, oct %04o, bin ", c, c, c);
    for(int i = 7; i >= 0; i--)
    {
        int b = (c >> i) & 1;
        printf("%d", b);
    }
    printf(")\n");
    printf("Тип: ");
    if(isalpha(c))
    {
        if(isupper(c))
        printf("велика літера\n");
        else
        printf("мала літера\n");
    }
    else if(isdigit(c))
    printf("цифра\n");
    else if(isspace(c))
    printf("пробіл\n");
    else
    printf("інший символ\n");
    if(isalpha(c))
    {
        printf("Інший регістр: ");
        if(isupper(c))
        printf("'%c'\n", tolower(c));
        else
        printf("'%c'\n", toupper(c));
    }
    printf("Наступний символ: '%c'\n", c + 1);
    if(strchr(text, c) == nullptr)
    printf("Цього символа немає в тексті.\n");
    else
    {
        string textt(text);
        int d = 0;
        for(size_t i = 0; i < textt.length(); i++)
        {
            if(textt[i] == c)
            d++;
        }
        printf("Входжень у тексті: %d, перше на позиції %ld\n", d, strchr(text, c) - text + 1);
    }
}

void case6(char *text, int count)
{
    string newtext;
    char word[256];
    printf("Введіть речення (крапка після останнього слова):\n");
    bool q = true;
    while (cin >> word)
    {
        for(size_t i = 0; word[i] != '\0'; i++)
        {
            if(!isalnum(word[i]) && word[i] != '.' && word[i] != ' ')
            q = false;
        }
        newtext += word;
        size_t len = strlen(word);
        if (word[len - 1] == '.') break;
        newtext += " "; 
    }
    if(!q || strlen(word) > 255)
    {
        printf("Текст має містити лише латинські літери, цифри та пробіли і бути не довшим за 255 символів!\n");
        return;
    }
    else
    strcpy(text, newtext.c_str());
    splitWords(text, count);
    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %lu\n", strlen(text));
}