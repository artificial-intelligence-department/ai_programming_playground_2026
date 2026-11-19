/*
lab 6
Варіант: 2
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <stdio.h>
#include <string.h>


int hasVowel(const char word[])
{
    const char vowels[]="aeiouAEIOU"; 
    for (int i = 0; word[i]!='\0'; i++) {
        if (strchr(vowels, word[i]) != NULL) 
        { 
            return 1;
        }
    }
    return 0;
}

int main()
{
    char s[256]; 
    printf("Введіть текст (в кінці крапка): ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';
    printf("Слова без голосних:\n");
    int found = 0;
    char *word = strtok(s, " .");
    while (word != NULL) {
        if (hasVowel(word) == 0) {
            printf("%s\n", word);
            found++;
        }
        word = strtok(NULL, " ."); 
    }
    if (found == 0) {
        printf("Таких слів немає.\n");
    }
    return 0;
}