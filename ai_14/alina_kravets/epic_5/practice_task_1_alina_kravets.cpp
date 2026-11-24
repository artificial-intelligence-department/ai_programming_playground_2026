/*Редактор текстового повідомлення
ШІ-14
Кравець Аліна*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

bool textValidation(const char* text) //валідація речення
{
    bool valid = true;
    if (strlen(text) == 0) valid = false;
    if (text[strlen(text)-1] != '.') valid = false;
    for (int i = 0; i < strlen(text) - 1; i++)
    {
        if (!isalnum(text[i]) && !isspace(text[i])) valid = false;
    }
    
    return valid;
}

char **splitWords(const char* text, int &count) //розбиваємо речення на слова
{
    char temp[256] = {'\0'};
    stpcpy(temp, text);
    char **words = new char*[128];
    char *t = strtok(temp, " .");
    while (t != NULL)
    {
        words[count] = new char[strlen(t) + 1];
        strcpy(words[count], t);
        count++;
        t = strtok(NULL, " .");
    }
    return words;
}

void freeWords(char **&words, int &count) //звільняємо динамічний масив
{
    if (words != nullptr)
    {
        for (int i = 0; i < count; i++)
        {
            delete[] words[i];
        }
        delete[] words;
        words = nullptr;
    }
    count = 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces) //рахуємо літери, цифри, пробіли у реченні
{
    for(int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i])) letters++;
        else if (isdigit(text[i])) digits++;
        else if (isspace(text[i])) spaces++;
    }
}

void textAndStats(const char *text, int count) //виводимо текст і статистику символів
{
    int letters = 0;
    int digits = 0;
    int spaces = 0;
    int chars = strlen(text);
    countChars(text, letters, digits, spaces);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:%6d\n", chars);
    printf("Слів:%10d\n", count);
    printf("Літер:%9d (%5.1f%%)\n", letters, 100.0*letters/chars);
    printf("Цифр:%10d (%5.1f%%)\n", digits, 100.0*digits/chars);
    printf("Пробілів:%6d (%5.1f%%)\n", spaces, 100.0*spaces/chars);
}

void wordTable(char** words, int count) //виводимо таблицю слів, найдовше і найкоротше слово, слова за алфавітом, найчастіше слово
{
    int max_word = 0;
    int min_word = 0;
    int sum = 0;
    int repeat = 1;
    int mostOftenCount = 1;
    int mostOften = 0;

    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for (int i = 0; i < count; i++)
    {
        printf("| %3d| %-16s| %6d|\n", i+1, words[i], (int)strlen(words[i]));
    }
    printf("+----+-----------------+-------+\n");

    for (int i = 0; i < count; i++)
    {
        if (strlen(words[i]) > strlen(words[max_word])) max_word = i;
        else if (strlen(words[i]) < strlen(words[min_word])) min_word = i;
        sum += (int)strlen(words[i]);
    }
    printf("Найдовше слово: %s (%d)\n", words[max_word], (int)strlen(words[max_word]));
    printf("Найкоротше слово: %s (%d)\n", words[min_word], (int)strlen(words[min_word]));
    printf("Середня довжина: %.2f\n", (double)sum/count);

    char** copy = new char*[count];
    for (int i = 0; i < count; i++)
    {
        copy[i] = new char[strlen(words[i])+1];
        strcpy(copy[i], words[i]);
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (strcmp(copy[j], copy[j + 1]) > 0)
            {
                char *x = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = x;
            }
        } 
    }
    printf("За абеткою: ");
    for(int i = 0; i < count; i++)
    {
        printf("%s ", copy[i]);
    }
    printf("\n");
    
    for (int i = 0; i < count - 1; i++)
    {
        if (strcmp(copy[i], copy[i + 1]) == 0)
        {
            repeat++;
            if (repeat > mostOftenCount)
            {
                mostOftenCount = repeat;
                mostOften = i;
            }
        }
        else repeat = 1;
    }
    printf("Найчастіше слово: %s (%d)\n", copy[mostOften], mostOftenCount);

    freeWords(copy, count);
}

void replaceWord (char* text, char** &words, int &count) //замінюємо слово у реченні
{
    char from[32] = {'\0'};
    char to[32] = {'\0'};
    int replaced = 0;
    int position = 0;
    string new_text = text;

    printf("Замінити слово: ");
    scanf("%31s", from);
    printf("На слово: ");
    scanf("%31s", to);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(words[i], from) == 0)
        {
            position = (int)new_text.find(words[i], position);
            new_text.replace(position, strlen(words[i]), to);
            position += strlen(to);
            replaced++;
        }
    }

    if (replaced < 0 || new_text.length() > 255 || !textValidation(new_text.c_str())) printf("Заміни не буде\n");
    else
    {
        printf("Замін виконано: %d\n", replaced);
        printf("Було: \"%s\"\n", text);

        strcpy(text, new_text.c_str());
        freeWords(words, count);
        words = splitWords(text, count);

        printf("Стало: \"%s\"\n", text);
        printf("Нова довжина: %d\n", (int)strlen(text));
    }
}

string lowerCase(string s) //стрічка без урахування регістру
{
    s[0] = tolower(s[0]);
    return s;
}

void compareWords() //порівнюємо два слова і конкатенуємо їх
{
    char a[32] = {'\0'};
    char b[32] = {'\0'};
    char concatenation[66] = {'\0'};

    printf("Введіть перше слово: ");
    scanf("%31s", a);
    printf("Введіть друге слово: ");
    scanf("%31s", b);

    int comparison = strcmp(a, b);
    if (comparison < 0) printf("strcmp: -1 -> перше слово менше\n");
    else if (comparison == 0) printf("strcmp: 0 -> слова рівні\n");
    else printf("strcmp: 1 -> друге слово менше\n");
    
    string a_s = a;
    string b_s = b;
    
    printf("Рівні (==): ");
    if(a_s == b_s) printf("так\n");
    else printf("ні\n");
    printf("Рівні без урахування регістру: ");
    if(lowerCase(a_s) == lowerCase(b_s)) printf("так\n");
    else printf("ні\n");
    printf("Довжини: %d і %d\n", (int)a_s.length(), (int)b_s.length());

    strcpy(concatenation, a);
    strcat(concatenation, " & ");
    strcat(concatenation, b);
    printf("Конкатенація: %s (%d)\n", concatenation, (int)strlen(concatenation));
}

void symbolInfo(const char* text) //виводимо інформацію про символ
{
    char c;
    int count = 0;
    bool firstFound = false;
    int first = 0;
    char binary[8] = {'\0'};

    printf("Введіть символ: ");
    scanf(" %c", &c);

    char copy = c;
    for (int i = 7; i >= 0; i--)
    {
        binary[7 - i] = (copy >> i) & 1 ? '1' : '0';
    }

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex %x, oct %o, bin %s)\n", c, c, c, binary);

    if (isalpha(c))
    {
        if(islower(c))
        {
            printf("Тип: мала літера\n");
            printf("Інший регістр: '%c'\n", toupper(c));
            printf("Наступний символ: '%c'\n", c+1);
        }
        else
        {
            printf("Тип: велика літера\n");
            printf("Інший регістр: '%c'\n", tolower(c));
            printf("Наступний символ: '%c'\n", c+1);
        }
    }
    else if(isdigit(c)) printf("Тип: число\n");
    else if(isspace(c)) printf("Тип: пробіл\n");
    else if(ispunct(c)) printf("Тип: пунктуаційний символ\n");
    else printf("Тип: інший символ\n");
    
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == c)
        {
            count++;
            if (firstFound) continue;
            first = i;
            firstFound = true;
        }
    }
    if (count == 0) printf("Не зустрічається в тексті\n");
    else printf("Входжень в тексті: %d, перше на позиції %d\n", count, first+1);
}

void newSentence(char* text, char** &words, int &count) //вводимо нове речення
{
    char word[31] = {'\0'};
    char newSentence[256] = {'\0'};

    printf("Введіть нове речення: ");
    while (cin >> word)
    {
        strcat(newSentence, word);
        if (word[strlen(word) - 1] == '.') break;
        strcat(newSentence, " ");
    }
    cin.ignore(1000, '\n');

    if (strlen(newSentence) > 255)
    {
        printf("Нове речення занадто довге.\n");
        return;
    }
    if (!textValidation(newSentence))
    {
        printf("Помилка: нове речення має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }

    strcpy(text, newSentence);
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

int main()
{
    char text[256] = {'\0'};
    int count = 0;
    int choice = 0;

    printf("Введіть текст (до 255 символів, крапка в кінці): ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    if(!textValidation(text)) //перевірка тексту на валідацію
    {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    char **words = splitWords(text, count);

    do
    {
        menu:
        printf("----Меню----\n");
        printf("1 - Показати текст і статистику\n");
        printf("2 - Таблиця слів\n");
        printf("3 - Замінити слово\n");
        printf("4 - Порівняти два слова\n");
        printf("5 - Інформація про символ\n");
        printf("6 - Ввести нове речення\n");
        printf("0 - Вийти\n");

        printf("Оберіть дію: ");

        if (scanf("%d", &choice) != 1) //перевірка вводу
        {
            printf("Помилка: введіть дію\n");
            while (getchar() != '\n');
            goto menu;
        }

        switch(choice)
        {
            case 0:
            break;
            case 1:
            textAndStats(text, count);
            break;
            case 2:
            wordTable(words, count);
            break;
            case 3:
            replaceWord(text, words, count);
            break;
            case 4:
            compareWords();
            break;
            case 5:
            symbolInfo(text);
            break;
            case 6:
            newSentence(text, words, count);
            break;
            default:
            printf("Помилка: пункту %d немає в меню\n", choice); //не можна обрати пункт, якого в меню немає
            break;
        }
    }while (choice != 0);

    freeWords(words, count);

    return 0;
}
