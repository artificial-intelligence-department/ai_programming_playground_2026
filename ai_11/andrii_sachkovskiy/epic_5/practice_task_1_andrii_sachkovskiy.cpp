/*
 * Задача: practice_task_1
 * Автор: Сачковський Андрій
 * Група: AI-11
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

char **splitWords(const char *text, int &count){

    char *copy = new char[strlen(text) + 1];
    strcpy(copy, text);
//нарізаємо слова
    count = 0;
    char *p = strtok(copy, " .");
    while (p != NULL)
    {
        count++;
        p = strtok(NULL, " .");
    }
//копіюємо кожне слово в масив
    char **words = new char*[count];

    strcpy(copy, text);
    int i = 0;
    p = strtok(copy, " .");
    while (p != NULL)
    {
        words[i] = new char[strlen(p) + 1];
        strcpy(words[i], p);
        i++;
        p = strtok(NULL, " .");
    }

    delete[] copy;
    return words;
}
//звідьняємо память
void freeWords(char **&words, int &count)
{
    for (int i = 0; i < count; i++)
        delete[] words[i];
    delete[] words;
    words = NULL;
    count = 0;
}

//пошук даних для пункта 1
void countChars(const char *text, int &letters, int &digits, int &spaces){
   letters = 0 ;
   digits = 0 ;
   spaces = 0 ;

   while (*text != '\0'){

        if (*text == ' '){
            spaces++;
        }

        if (*text >= '0' && *text <= '9'){
            digits++;
        }

        if ((*text >= 'a' && *text <= 'z') || (*text >= 'A' && *text <= 'Z')){
            letters++;
        }

        text++;
   }
}

//Пункт 2
void printWordTable(char **words, int count )
{
printf("+----+---------------------------------------------------------------------+-------+\n");
printf("| N  | СЛОВО                                                                | ДОВЖ. |\n");
printf("+----+---------------------------------------------------------------------+-------+\n");
    for (int i = 0; i < count; i++)
    {
       printf("| %-2d | %-69s | %-5d |\n", i + 1, words[i], (int)strlen(words[i]));
    }
 printf("+----+---------------------------------------------------------------------+-------+\n");
    // пошук найдовшого і найкоротшого слова і середнє значення
    int longestIndex = 0;
    int shortestIndex = 0;

    for (int i = 1; i < count; i++)
    {
        if (strlen(words[i]) > strlen(words[longestIndex]))
            longestIndex = i;

        if (strlen(words[i]) < strlen(words[shortestIndex]))
            shortestIndex = i;
    }

    int suma = 0;
    for (int i = 0; i < count; i++)
    {
        suma += strlen(words[i]);
    }

    double seredina = suma / (double)count;

    printf("\n");
    printf("Найдовше слово:    %s (%d)\n", words[longestIndex], (int)strlen(words[longestIndex]));
    printf("Найкоротше слово:  %s (%d)\n", words[shortestIndex], (int)strlen(words[shortestIndex]));
    printf("Середня довжина:   %.2f\n", seredina);
//алфавіт
    int index[1000];
    for (int i = 0; i < count; i++)
        index[i] = i;

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (strcmp(words[index[j]], words[index[j + 1]]) > 0)
            {
                int tmp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = tmp;
            }
        }
    }

    printf("\nЗа алфавітом:\n");

    printf("За абеткою: ");
    for (int i = 0; i < count; i++)
    {
        printf("%s", words[index[i]]);
        if (i < count - 1)
            printf(" ");
    }
    printf("\n");

    int bestCount = 0;
    int bestIndex = 0;

    for (int i = 0; i < count; i++)
    {
        int c = 0;
        for (int j = 0; j < count; j++)
        {
            if (strcmp(words[i], words[j]) == 0)
                c++;
        }
        if (c > bestCount)
        {
            bestCount = c;
            bestIndex = i;
        }
        else if (c == bestCount && c > 1 && strcmp(words[i], words[bestIndex]) < 0)
        {
            bestIndex = i;
        }
    }
    if (bestCount == 1 ){
        printf("Всіх слів по 1 штуці в рядку ");
    }
    else
        printf("Найчастіше слово: %s (%d)\n", words[bestIndex], bestCount);
}

//пункт 3
void printChange(char text[256], char **&words, int &count)
{
    char oldWord[32];
    char newWord[32];

slovo:
    printf("Замінити слово: ");
    scanf("%31s", oldWord);

    int z = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(words[i], oldWord) == 0)
            z++;
    }

    if (z == 0)
    {
        printf("Даного слова немає в рядку, спробуйте ще раз\n");
        goto slovo;
    }

    printf("На слово: ");
    scanf("%31s", newWord);

    for (int i = 0; newWord[i] != '\0'; i++)
    {
        char c = newWord[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')))
        {
            printf("Помилка: нове слово має складатися лише з латинських літер і цифр.\n");
            return;
        }
    }

    {
        string s = text;
        string oldS = oldWord;
        string newS = newWord;
        string result = "";
        size_t pos = 0;
        int replaced = 0;

        while (pos < s.length())
        {
            size_t found = s.find(oldS, pos);
            if (found == string::npos)
            {
                result += s.substr(pos);
                break;
            }bool leftOk = (found == 0) || !((s[found-1] >= 'a' && s[found-1] <= 'z') || (s[found-1] >= 'A' && s[found-1] <= 'Z') || (s[found-1] >= '0' && s[found-1] <= '9'));
             size_t afterPos = found + oldS.length();
             bool rightOk = (afterPos == s.length()) || !((s[afterPos] >= 'a' && s[afterPos] <= 'z') || (s[afterPos] >= 'A' && s[afterPos] <= 'Z') || (s[afterPos] >= '0' && s[afterPos] <= '9'));

            result += s.substr(pos, found - pos);

            if (leftOk && rightOk)
            {
                result += newS;
                replaced++;
            }
            else
            {
                result += oldS;
            }

            pos = afterPos;
        }

        if (result.length() > 255)
        {
            printf("Помилка: результат перевищує 255 символів, текст не змінено.\n");
            return;
        }

        printf("Замін виконано: %d\n", replaced);
        printf("Було:\t\"%s\"\n", s.c_str());
        printf("Стало:\t\"%s\"\n", result.c_str());
        printf("Нова довжина: %d\n", (int)result.length());

        strcpy(text, result.c_str());
        freeWords(words, count);
        words = splitWords(text, count);
    }
}

// Пункт 4
void comparison(char *word1, char *word2)
{
    int r = strcmp(word1, word2);
    printf("strcmp: ");
    if (r < 0)
        printf("-1 -> перше слово менше\n");
    else if (r > 0)
        printf("1 -> друге слово менше\n");
    else
        printf("0 -> слова рівні\n");

    string s1 = word1;
    string s2 = word2;

    printf("Рівні (==): %s\n", (s1 == s2) ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)strlen(word1), (int)strlen(word2));

    if (strlen(word1) != strlen(word2))
    {
        printf("Рівні без урахування регістру: ні\n");
    }
    else
    {
        int lenWord = strlen(word1);
        int z = 0;

        for (int i = 0; i < lenWord; i++)
        {
            int r2 = word1[i] - word2[i];
            if (r2 == 0 || r2 == 32 || r2 == -32)
                z++;
        }
        if (z == lenWord)
            printf("Рівні без урахування регістру: так\n");
        else
            printf("Рівні без урахування регістру: ні\n");
    }

    string combined = s1 + " & " + s2;
    printf("Конкатенація: \"%s\" (%d)\n", combined.c_str(), (int)combined.length());
}

//пункт 5
void Simvol(const char *text)
{
cimvol:
    char code;
    printf("Введіть символ: ");
    scanf(" %c", &code);

    if (code < 32 || code > 126)
    {
        printf("Помилка: некоректний символ, спробуйте ще раз.\n");
        goto cimvol;
    }

    printf("Код: %d ", code);
    printf("(hex 0x%x, ", code);
    printf("oct 0%o, ", code);

    int bits[8];
    int n = code;
    int k = 0;

    while (n > 0)
    {
    bits[k] = n & 1; 
    n = n >> 1;   
        k++;
    }

    printf("bin ");
    for (int i = k - 1; i >= 0; i--)
        printf("%d", bits[i]);
    printf(") ");

    if (code >= 'A' && code <= 'Z')
    {
        char other = code + 32;
        printf("Інший регістр: '%c' ", other);
    }
    else if (code >= 'a' && code <= 'z')
    {
        char other = code - 32;
        printf("Інший регістр: '%c' ", other);
    }
    else
    {
        printf("Інший регістр: немає (не літера) ");
    }
    char next = code + 1;
    printf("Наступний символ: '%c'\n", next);

    printf("Тип: ");
    if (code >= 'A' && code <= 'Z')
        printf("велика літера\n");
    else if (code >= 'a' && code <= 'z')
        printf("мала літера\n");
    else if (code >= '0' && code <= '9')
        printf("цифра\n");
    else if (code == ' ')
        printf("пробіл\n");
    else
        printf("інший символ\n");

    int count = 0;
    int firstPos = -1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == code)
        {
            count++;
            if (firstPos == -1)
                firstPos = i + 1;
        }
    }
    if (count == 0)
        printf("Такого символу немає в тексті\n");
    else
    {
        printf("Входжень у тексті: %d\n", count);
        printf("Перше входження на позиції: %d\n", firstPos);
    }
}
//пункт 6 
void enterNewSentence(char text[256], char **&words, int &count)
{
    cin.ignore(10000, '\n');
    printf("Введіть нове речення (слова через пробіл/Enter, останнє слово має закінчуватись крапкою):\n");
sentence:
    string result = "";
    string word;
    int z = 0;

    while (cin >> word)
    {
        z++;

        int lenWord = word.length();
        for (int i = 0; i < lenWord; i++)
        {
            char c = word[i];
            if (c == '.' && i == lenWord - 1)
                continue;
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')))
            {
                printf("Помилка: дозволені лише латинські букви, цифри та крапка в кінці речення. Спробуйте ще раз.\n");
                goto sentence;
            }
        }

        result += word;

        if ((int)result.length() > 255)
        {
            printf("Помилка: речення занадто довге (максимум 255 символів). Спробуйте ще раз.\n");
            goto sentence;
        }

        if (word.back() == '.')
            break;

        result += " ";
    }

    if (result.empty() || result.back() != '.')
    {
        printf("Помилка: речення має закінчуватись крапкою. Спробуйте ще раз.\n");
        goto sentence;
    }

    printf("Прочитано слів: %d\n", z);
    printf("Новий текст: \"%s\"\n", result.c_str());
    printf("Довжина: %d\n", (int)result.length());

    strcpy(text, result.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
}

int main(){
    // користувач вводить дані і робиться перевірка на довжину також корекнтінсть
    printf("Введіть речення в 1 рядок до 255 символів:\n");

    char text[256];
    fgets(text, sizeof(text), stdin);

    if (strchr(text, '\n') == NULL){
        printf("Помилка: текст задовгий, введіть не більше 255 символів.\n");
        return 0;
    }

    text[strcspn(text, "\n")] = '\0';
    int len = strlen(text);

    if (len == 0)
    {
        printf("Помилка: ви нічого не ввели.\n");
        return 0;
    }

    if (text[len - 1] != '.'){
        printf("Помилка: текст не закінчується крапкою\n");
        return 0;
    }
    int z = 0;

    for (int i = 0; i < len - 1; i++)
    {
        if (text[i] == ' ' || text[i] == '\t')
        {
            z++;
        }
    }

    if (z == len-1){
        printf("Ви ввели нуль слів\n");
        return 0;
    }

    char simvol[33] = {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
                     ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~', '\t'};

    for (int i = 0; i < len - 1; i++)
    {
        if (text[i] < 32 || text[i] > 126)
        {
            printf("Ви ввели не латинські літери \n");
            return 0;
        }

        for (int j = 0; j < 33; j++)
        {
            if (text[i] == simvol[j])
            {
                printf("Ви ввели заборонені символи\n");
                return 0;
            }
        }
    }

    int count = 0;
    char **words = splitWords(text, count);

    // користувач вибирає дію в меню
    int menu;
menu:
    do {
        printf("Меню: \n");
        printf("Пункт \t Операція \n");
        printf("1 \t Показати текст і статистику \n");
        printf("2 \t Таблиця слів\n");
        printf("3 \t Замінити слово\n");
        printf("4 \t Порівняти два слова\n");
        printf("5 \t Інформація про символ\n");
        printf("6 \t Ввести нове речення\n");
        printf("0 \t Вийти\n");

        if (scanf("%d", &menu) != 1){
            printf("Ви ввели не число спробуйте ще раз\n");
            while (getchar() != '\n');
            goto menu;
        }
        if (menu < 0 || menu > 6){
            printf("Ви ввели число не з проміжку від 0 да 6 спробуйте ще раз\n");
            while (getchar() != '\n');
            goto menu;
        }

        switch (menu)
        {
            //перший пункт в меню
            case 1:
            {
                int letters;
                int digits;
                int spaces;

                countChars(text, letters, digits, spaces);

                int all_simvol = strlen(text);

                printf("Текст:\t\"%s\"\n", text);
                printf("Символів:%d\n", all_simvol);
                printf("Слів:\t%d\n", count);
                printf("%-12s%-4d(%.1f%%)\n", "Літер:", letters, letters * 100.0 / all_simvol);
                printf("%-12s%-4d(%.1f%%)\n", "Цифр:", digits, digits * 100.0 / all_simvol);
                printf("%-12s%-4d(%.1f%%)\n", "Пробілів:", spaces, spaces * 100.0 / all_simvol);
                break;
            }
            case 2:
            {
                printWordTable(words, count);
                break;
            }
            case 3:
            {
                printChange(text, words, count);
                break;
            }
            case 4:
            {
                char word1[32];
                char word2[32];

                printf("Перше слово: ");
                scanf("%31s", word1);
                printf("Друге слово: ");
                scanf("%31s", word2);

                comparison(word1, word2);
                break;
            }
            case 5:
            {
                Simvol(text);
                break;
            }
            case 6:
            {
                enterNewSentence(text, words, count);
                break;
            }
            case 0:
                freeWords(words, count);  
                return 0;
        }
    } while(true);
}