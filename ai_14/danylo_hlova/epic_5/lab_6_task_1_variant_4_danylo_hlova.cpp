#include <stdio.h>
#include <string.h>

void PrintSameWords(char str[])
{
    char first[256];
    char *token;

    
    token = strtok(str, " .\n");
    if (token == NULL) {
        return;
    }

    strcpy(first, token); //перше слово

    printf("Повтори першого слова: ");
    // Перебирав решту слів, починаючи з другого
    while (token != NULL) {
        token = strtok(NULL, " .\n");
        if (token != NULL && strcmp(token, first) == 0) {
            printf("%s ", token);
        }
    }
    printf("\n");
}

int main()
{
    char s[256];

    printf("Введіть речення: ");
    fgets(s, 256, stdin);

    PrintSameWords(s);

    return 0;
}