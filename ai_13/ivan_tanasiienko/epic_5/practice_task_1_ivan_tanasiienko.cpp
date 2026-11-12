/*
    Epic 5, Class Practice, Танасієнко Іван, ШІ-13
*/
#include<cstdio>
#include<cstring>
#include<string>
#include<cctype>
#include<iostream>


void countChars(const char *text, int &letters, int &digits, int &spaces);
void showTextAndStats(char text[]);
void wordsTable(char **words, int totalWords);
void replaceWord(char text[]);
void compoundWords();
void symbolInfo(char text[]);
void printCap(int max);
void quickSortString(char** text, int len);
void freeWords(char **&words, int &count);
char **splitWords(const char *text, int &count);
void updateWords(const char text[], char **&words, int &count);
void newSentence(char text[]);

int main()
{
    char text[256];
    bool valid = true;
    bool hasWord = false;
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if(fgets(text, sizeof(text), stdin) == nullptr) return 1;

    int inputLen = strlen(text);
    if(inputLen == 255 && text[inputLen - 1] != '\n')
    {
        char extra[2];
        if(fgets(extra, sizeof(extra), stdin) != nullptr && extra[0] != '\n')
        {
            printf("Текст занадто довгий. Максимум 255 символів.\n");
            return 1;
        }
    }
    for(int i = 0; text[i] != 0; i++)
    {
        if(text[i] == '\n')
        {
            text[i] = '\0';
            break;
        }
    }
    for(int i = 0; text[i] != '\0'; i++)
    {
        bool isLetter = (text[i] >= 'a' && text[i] <= 'z') ||
                        (text[i] >= 'A' && text[i] <= 'Z');
        bool isDigit = (text[i] >= '0' && text[i] <= '9');
        if(!isLetter && !isDigit && text[i] != ' ' && text[i] != '.')
        {
            valid = false;
        }
        if(isLetter || isDigit)
        {
            hasWord = true;
        }
        if(text[i] == '.' && text[i + 1] != '\0')
        {
            valid = false;
        }
        if(text[i + 1] == '\0' && text[i] != '.')
        {
            valid = false;
        }
    }
    if(!valid || !hasWord)
    {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    char **words = nullptr;
    int wordCount = 0;
    words = splitWords(text, wordCount);
    char choice[1024];
    do
    {
        printf("%s", "----------- Меню ------------\n");
        printf("%s", " Пункт |      Операція\n");
        printf("%s", "   1   | Показати текст і статистику\n");
        printf("%s", "   2   | Таблиця слів\n");
        printf("%s", "   3   | Замінити слово\n");
        printf("%s", "   4   | Порівняти два слова\n");
        printf("%s", "   5   | Інформація про символ\n");
        printf("%s", "   6   | Ввести нове речення\n");
        printf("%s", "   0   | Вийти\n");
        printf("%s", "Ваш вибір: ");
        if(scanf("%1023s", choice) != 1)
            break;
        if(strlen(choice) > 1 || !(choice[0] >= '0' && choice[0] <= '9'))
        {
            printf("%s", "Помилка: введіть номер пункту меню.\n");
            choice[0] = 'n';
            continue;
        }
        switch(choice[0])
        {
            case '1':
                showTextAndStats(text);
                break;
            case '2':
                wordsTable(words, wordCount);
                break;
            case '3':
                replaceWord(text);
                updateWords(text, words, wordCount);
                break;
            case '4':
                compoundWords();
                break;
            case '5':
                symbolInfo(text);
                break;
            case '6':
                newSentence(text);
                updateWords(text, words, wordCount);
                break;
            case '0':
                printf("%s", "Вихід...\n");
                break;
            default:
                printf("Помилка: пункту %c немає в меню.\n", choice[0]);
        }
    }while(choice[0] != '0');
    freeWords(words, wordCount);
    return 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces)
{
    for(int i = 0; *(text + i) != '\0'; i++)
    {
        if((*(text + i) >= 'a' && *(text + i) <= 'z') || (*(text + i) >= 'A' && *(text + i) <= 'Z'))
        {
            letters++;
        }
        else if(*(text + i) >= '0' && *(text + i) <= '9')
        {
            digits++;
        }
        else if(*(text + i) == ' ')
        {
            spaces++;
        }
    }

    return;
}

void showTextAndStats(char text[])
{
    /*
    Текст:    "the old cat and the young cat met 2 dogs near the river."
    Символів:    56
    Слів:        13
    Літер:       42 ( 75.0%)
    Цифр:         1 (  1.8%)
    Пробілів:    12 ( 21.4%)
    */
   printf("Текст:\t\"%s\"\n", text);
   int letters = 0;
   int digits = 0;
   int spaces = 0;
   countChars(text, letters, digits, spaces);
   int totalWords = 0;
   bool inWord = false;
   for(int i = 0; text[i] != '\0'; i++)
   {
       if(text[i] == ' ' || text[i] == '.') inWord = false;
       else if(!inWord)
       {
           totalWords++;
           inWord = true;
       }
   }
   printf("Символів:\t%zu\n", strlen(text)); 
   printf("Слів:\t\t%d\n", totalWords);
   printf("Літер:\t   %d ( %.1f%%)\n", letters, double(letters)*100/double(strlen(text))); 
   printf("Цифр:\t\t%d ( %.1f%%)\n", digits, double(digits)*100/double(strlen(text))); 
   printf("Пробілів:\t%d ( %.1f%%)\n", spaces, double(spaces)*100/double(strlen(text)));
   return;
}

void wordsTable(char **words, int totalWords)
{
    /*
    Кумедний тесткейс щоб перевірити адаптивність розміру таблиці: 
    Die Donaudampfschifffahrtsgesellschaft organisiert eine Kraftfahrzeughaftpflichtversicherung fuer den Bundesausbildungsfoerderungsgesetzexperten.
    */
    int max = 0;
    int min = -1;
    char longest[256];
    char shortest[256];
    int totalLen = 0;
    for(int i = 0; i < totalWords; i++)
    {
        char *word = words[i];
        totalLen += (int)strlen(word);
        if((int)strlen(word) > max)
        {
            max = (int)strlen(word);
            strcpy(longest, word);
        }
        if(min == -1 || (int)strlen(word) < min)
        {
            min = (int)strlen(word);
            strcpy(shortest, word);
        }
    }
    double average = double(totalLen) / totalWords;
    printCap(max);
    printf("| N  | Слово");
    int temp;
    if(max <= 15)
    {
        temp = 15;
    }
    else
    {
        temp = max;
    }
    for(int i = 5; i < temp; i++) printf(" ");
    printf(" | Довж. |\n");
    printCap(max);
    for(int i = 0; i < totalWords; i++)
    {
        char *word = words[i];
        printf("|%3d | %-*s | %5zu |\n", i+1, temp, word, strlen(word));
    }
    printCap(max);
    char** sorted = new char*[totalWords];
    for(int i = 0; i < totalWords; i++)
    {
        *(sorted + i) = words[i];
    }
    quickSortString(sorted, totalWords);
    printf("Найдовше слово: %s (%d)\n", longest, max);
    printf("Найкоротше слово: %s (%d)\n", shortest, min);
    printf("Середня довжина: %.2f\n", average);
    printf("За абеткою: ");
    for(int i = 0; i < totalWords; i++)
    {
        if(i > 0) printf(" ");
        printf("%s", *(sorted + i));
    }
    printf("\n");
    int maxEquals = 0;
    int equals;
    char mostFrequent[256] = "";
   
    for(int i = 0; i < totalWords; i++)
    {
        equals = 0;
        for(int j = 0; j < totalWords; j++)
        {
            if(strcmp(*(sorted + i), *(sorted + j)) == 0)
            {
                equals++;
            }
        }
        if(equals > maxEquals)
        {
            maxEquals = equals;  
            strcpy(mostFrequent, *(sorted + i));  
        }
    }
    printf("Найчастіше слово: %s (%d)\n", mostFrequent, maxEquals);
    delete[] sorted;
    return;
}


void replaceWord(char text[])
{
    /* Тест кейс:
all in all it was all just bricks in the wall.
3
all
ever
    */
    std::string str = text;
    std::string word;
    char buffer[256];
    bool valid;
    do
    {
        valid = true;
        printf("Замінити слово: ");
        if(scanf("%255s", buffer) != 1) return;
        int len = strlen(buffer);
        if(len == 255)
        {
            scanf("%*[^\n]");
            scanf("%*c");
        }
        if(len > 31) valid = false;
        for(int i = 0; i < len; i++)
        {
            if(!((buffer[i] >= 'a' && buffer[i] <= 'z') ||
                 (buffer[i] >= 'A' && buffer[i] <= 'Z') ||
                 (buffer[i] >= '0' && buffer[i] <= '9')))
                valid = false;
        }
        if(valid)
        {
            word = buffer;
            size_t find = 0;
            bool found = false;
            while((find = str.find(word, find)) != std::string::npos)
            {
                bool left = find == 0 || str[find - 1] == ' ';
                size_t end = find + word.length();
                bool right = end == str.length() || str[end] == ' ' || str[end] == '.';
                if(left && right)
                {
                    found = true;
                    break;
                }
                find += word.length();
            }
            if(!found) valid = false;
        }
        if(!valid) printf("Некоректне слово або такого слова немає в тексті.\n");
    }while(!valid);

    printf("На слово: ");
    if(scanf("%255s", buffer) != 1) return;
    int len = strlen(buffer);
    if(len == 255)
    {
        scanf("%*[^\n]");
        scanf("%*c");
    }
    if(len > 31)
    {
        printf("Некоректне нове слово. Текст не змінено.\n");
        return;
    }
    for(int i = 0; i < len; i++)
    {
        if(!((buffer[i] >= 'a' && buffer[i] <= 'z') ||
             (buffer[i] >= 'A' && buffer[i] <= 'Z') ||
             (buffer[i] >= '0' && buffer[i] <= '9')))
        {
            printf("Некоректне нове слово. Текст не змінено.\n");
            return;
        }
    }

    std::string newWord = buffer;
    int reps = 0;
    size_t find = 0;
    while((find = str.find(word, find)) != std::string::npos)
    {
        bool left = find == 0 || str[find - 1] == ' ';
        size_t end = find + word.length();
        bool right = end == str.length() || str[end] == ' ' || str[end] == '.';
        if(left && right)
        {
            if(str.length() - word.length() + newWord.length() > 255)
            {
                printf("Результат перевищує 255 символів. Текст не змінено.\n");
                return;
            }
            str.replace(find, word.length(), newWord);
            reps++;
            find += newWord.length();
        }
        else
        {
            find += word.length();
        }
    }
    printf("Замін виконано: %d\n", reps);
    printf("Було: \"%s\"\n", text);
    strcpy(text, str.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %zu\n", strlen(text));
}

void compoundWords()
{
    char word1[256], word2[256];
    printf("Перше слово: ");
    if(scanf("%255s", word1) != 1) return;
    int len = strlen(word1);
    if(len == 255)
    {
        scanf("%*[^\n]");
        scanf("%*c");
    }
    if(len > 31)
    {
        printf("Перше слово занадто довге (максимум 31 символ).\n");
        return;
    }
    for(int i = 0; i < len; i++)
    {
        if(!((word1[i] >= 'a' && word1[i] <= 'z') ||
             (word1[i] >= 'A' && word1[i] <= 'Z') ||
             (word1[i] >= '0' && word1[i] <= '9')))
        {
            printf("Некоректне перше слово.\n");
            return;
        }
    }
    printf("Друге слово: ");
    if(scanf("%255s", word2) != 1) return;
    len = strlen(word2);
    if(len == 255)
    {
        scanf("%*[^\n]");
        scanf("%*c");
    }
    if(len > 31)
    {
        printf("Друге слово занадто довге (максимум 31 символ).\n");
        return;
    }
    for(int i = 0; i < len; i++)
    {
        if(!((word2[i] >= 'a' && word2[i] <= 'z') ||
             (word2[i] >= 'A' && word2[i] <= 'Z') ||
             (word2[i] >= '0' && word2[i] <= '9')))
        {
            printf("Некоректне друге слово.\n");
            return;
        }
    }
    std::string wordS1 = word1;
    std::string wordS2 = word2;
    int cmp = strcmp(wordS1.c_str(), wordS2.c_str());
    cmp = (cmp > 0) - (cmp < 0);
    bool eq = (wordS1 == wordS2);
    printf("strcmp: %d", cmp);
    if(cmp < 0) printf(" -> перше слово менше\n");
    else if(cmp > 0) printf(" -> перше слово більше\n");
    else printf(" -> слова рівні\n");
    std::string msg;
    if(eq) msg = "так";
    else msg = "ні";
    printf("Рівні (==): %s\n", msg.c_str());
    eq = (wordS1.length() == wordS2.length());
    if(eq)
    {
        for(size_t i = 0; i < wordS1.length(); i++)
        {
            char a = (char)tolower((unsigned char)wordS1[i]);
            char b = (char)tolower((unsigned char)wordS2[i]);
            if(a != b)
            {
                eq = false;
                break;
            }
        }
    }
    if(eq) msg = "так";
    else msg = "ні";
    printf("Рівні без урахування регістру: %s\n", msg.c_str());
    printf("Довжини: %zu і %zu\n", wordS1.length(), wordS2.length());
    printf("Конкатенація: \"%s\" (%zu)\n", (wordS1 + " & " + wordS2).c_str(), wordS1.length() + wordS2.length() + 3);
}

void symbolInfo(char text[])
{   
    char symbol;
    char buffer[256];

    fgets(buffer, sizeof(buffer), stdin);
    printf("Введіть символ: ");
    if(fgets(buffer, sizeof(buffer), stdin) == nullptr || buffer[0] == '\n')
    {
        printf("Символ не введено.\n");
        return;
    }
    if(buffer[1] != '\n' && buffer[1] != '\0')
    {
        if(strlen(buffer) == 255)
        {
            char rest[256];
            while(fgets(rest, sizeof(rest), stdin) != nullptr && strchr(rest, '\n') == nullptr) {}
        }
        printf("Помилка: введіть один символ.\n");
        return;
    }
    symbol = buffer[0];

    printf("Символ: \'%c\'\n", symbol);
    char c = symbol;

    unsigned int code = (unsigned char)c; 
    printf("Код: %u (hex 0x%x, oct 0%o, bin ", code, code, code);

    for (int i = 7; i >= 0; i--)
    {
        printf("%d", ((unsigned char)c >> i) & 1);
    }
    printf(")\n");
    char type[128];
    if(symbol >= 'A' && symbol <= 'Z') strcpy(type, "велика літера");
    else if(symbol >= 'a' && symbol <= 'z') strcpy(type, "мала літера");
    else if(symbol >= '0' && symbol <= '9') strcpy(type, "цифра");
    else if(isspace((unsigned char)symbol)) strcpy(type, "пробільний символ");
    else strcpy(type, "інший символ");
    printf("Тип: %s\n", type);

    char other;
    if(isalpha((unsigned char)c))
    {
        if (islower((unsigned char)c)) other = (char)toupper((unsigned char)c);
        else other = (char)tolower((unsigned char)c);
        printf("Інший регістр: '%c'\n", other);
    }
    printf("Наступний символ: '%c'\n", (int)(unsigned char)(code + 1));
    int entries = 0;
    const char *first = strchr(text, symbol);
    for(int i = 0; text[i] != '\0'; i++)
    {
        if(text[i] == symbol)
        {
            entries++;
        }
    }
    printf("Входжень у тексті: %d", entries);
    if(entries > 0) printf(", перше на позиції %td", first - text + 1);
    else printf(", у тексті не зустрічається");
    printf("\n");
    return;
}

void newSentence(char text[])
{
    char newText[256] = "";
    char word[256];
    bool running = true;
    bool tooLong = false;
    int j = 0;
    int count = 0;

    printf("Введіть речення (крапка після останнього слова):\n");
    while (running)
    {
        std::cin.width(sizeof(word));
        if (!(std::cin >> word))
        {
            printf("Помилка введення.\n");
            return;
        }
        int len = (int)strlen(word);
        running = (word[len - 1] != '.');
        if(len == 255)
        {
            int next = std::cin.peek();
            if(next != EOF && !isspace((unsigned char)next))
            {
                tooLong = true;
                running = true;
            }
        }
        int extra = running ? 2 : 1;
        if(j + len + extra > 256) tooLong = true;
        if(tooLong) continue;
        for (int i = 0; word[i] != '\0'; i++)
        {
            newText[j] = word[i];
            j++;
        }
        if(strcmp(word, ".") != 0) count++;
        if (!running)
        {
            newText[j] = '\0';
        }
        else
        {
            newText[j] = ' ';
            j++;
            newText[j] = '\0';
        }
    }
    if(tooLong)
    {
        printf("Речення занадто довге. Текст не змінено.\n");
        return;
    }

    bool valid = true;
    bool hasword = false;
    for(int i = 0; newText[i] != '\0'; i++)
    {
        bool isLetter = (newText[i] >= 'a' && newText[i] <= 'z') ||
                        (newText[i] >= 'A' && newText[i] <= 'Z');
        bool isDigit = (newText[i] >= '0' && newText[i] <= '9');
        if(!isLetter && !isDigit && newText[i] != ' ' && newText[i] != '.')
            valid = false;
        if(isLetter || isDigit) hasword = true;
        if(newText[i] == '.' && newText[i + 1] != '\0') valid = false;
    }
    if(!hasword) valid = false;

    if (!valid)
    {
        printf("Помилка: некоректне речення. Текст не змінено.\n");
        return;
    }
    else
    {
        strcpy(text, newText);

        printf("Прочитано слів: %d\n", count);
        printf("Новий текст: \"%s\"\n", text);
        printf("Довжина: %zu\n", strlen(text));
        return;
    }
}

void printCap(int max)
{
    printf("+----+");
    if(max <= 15)
    {
        printf("-----------------");
    }
    else
    {
        for(int i = 0; i < max + 2; i++)
        {
            printf("-");
        }
    }
    printf("+-------+\n");
    return;
}

void quickSortString(char** text, int len)
{
    if(len <= 1)
    {
        return;
    }
    char* pivot = text[len - 1];
    int i = -1;
    int j = 0;
    while(j < len-1)
    {
        if(strcmp(text[j], pivot) < 0)
        {
            i++;
            char* temp = text[j];
            text[j] = text[i];
            text[i] = temp;
        }
        j++;
    }
    text[len - 1] = text[i + 1];
    text[i + 1] = pivot;
    quickSortString(text, i + 1);
    quickSortString(text + (i + 2), len - i - 2);
    return;
}

void freeWords(char **&words, int &count)
{
    for(int i = 0; i < count; i++)
    {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}


char **splitWords(const char *text, int &count)
{
    count = 0;
    char copy[256];
    strcpy(copy, text);
    char *word = strtok(copy, " .");
    while(word != nullptr)
    {
        count++;
        word = strtok(nullptr, " .");
    }

    if(count == 0) return nullptr;
    char **words = new char*[count];

    strcpy(copy, text);
    word = strtok(copy, " .");
    int i = 0;
    while(word != nullptr)
    {
        words[i] = new char[strlen(word) + 1];
        strcpy(words[i], word);
        i++;
        word = strtok(nullptr, " .");
    }
    return words;
}

void updateWords(const char text[], char **&words, int &count)
{
    freeWords(words, count);
    words = splitWords(text, count);
}