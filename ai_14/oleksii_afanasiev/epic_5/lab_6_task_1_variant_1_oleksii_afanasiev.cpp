/*
Задача: Lab 6 Task 1 Variant 1
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <stdio.h>
#include <cstring>
using namespace std;

int main() 
    {
        char s[256];
        char max_word[256];
        char min_word[256];
        int max_length = 0;
        int min_length = 256;
        
        printf("Введіть речення: ");

        fgets(s, sizeof(s), stdin);
        s[strcspn(s, "\n")] = '\0';

        char *t = strtok(s, " ");

        if(t == nullptr)
        {
            printf("Речення не містить слів.");
            return 0;
        }

        while(t != nullptr)
        {
            if(strlen(t) > max_length)
            {
                strcpy(max_word, t);
                max_length = strlen(t);
            }
            
            if(strlen(t) < min_length)
            {
                strcpy(min_word, t);
                min_length = strlen(t);
            }

            t = strtok(nullptr, " .");
        }

        printf("Найдовше слово: %s\nНайкоротше слово: %s\n", max_word, min_word);
        
        return 0;
    }
