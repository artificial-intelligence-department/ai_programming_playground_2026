/*Лабораторна №6 варіант №13
ШІ-14
Кравець Аліна*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    char s[256];
    int count = 0;
    printf("Введіть стрічку: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';

    char **words = new char*[128];
    char *t = strtok(s, " ");
    while (t != NULL) 
    {
        words[count] = new char[strlen(t) + 1];
        strcpy(words[count], t);
        count++;
        t = strtok(NULL, " ");
    }

    printf("Результат: ");
    for (int i = 0; i < count; i++)
    {
        char copy[strlen(words[i]) + 1];
        strcpy(copy, words[i]);
        int len = strlen(copy);
        char numbers[len + 1] = {'\0'};
        char letters[len + 1] = {'\0'};
        int num = 0;
        int let = 0;
        char result[256] = {'\0'};

        for (int j = 0; j < len; j++)
        {
            if (isdigit(copy[j]))
            {
                numbers[num] = copy[j];
                num++; 
            }
            else
            {
                letters[let] = copy[j];
                let++;
            }
        }

        for (int j = 0; j < strlen(numbers); j++)
        {
            for (int k = 0; k < strlen(numbers) - 1 - j; k++)
            {
                if(numbers[k] < numbers[k + 1])
                {
                    char x = numbers[k];
                    numbers[k] = numbers[k + 1];
                    numbers[k + 1] = x;
                }
            }
        }

        strcat(result, numbers);
        strcat(result, letters);

        printf("%s ", result);
    }
    printf("\n");

    for (int i = 0; i < count; i++)
    {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;

    return 0;
}
