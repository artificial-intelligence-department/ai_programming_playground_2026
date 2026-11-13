#include <iostream>
#include <stdio.h>
#include <string.h>
#include <clocale>
#include <cstring>
using namespace std;

int main()
{
    setlocale (LC_CTYPE, "ukr");
    const int MAX_LENGTH = 256;
    char s[MAX_LENGTH];
    fgets(s,MAX_LENGTH,stdin);
    char firstWord[50];
    int counter = 0;
    sscanf(s,"%s",firstWord);
    char *word = strtok(s," !?-+");
    while (word != NULL) {
        if (strcmp(firstWord,word) == 0){
            counter++;
            printf("%s\n",word);
        }
        word = strtok(NULL," !?-+");
    }
    printf("Перше слово: %s\n",firstWord);
    printf("Кількість слів , які дорівнюють першому : %d",counter);

    return 0;
}