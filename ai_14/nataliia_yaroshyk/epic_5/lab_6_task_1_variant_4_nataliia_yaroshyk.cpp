#include <stdio.h>
#include <string.h>

int main(){
    char s[256] = "";
    printf("Введіть рядок: ");
    fgets(s, 256, stdin);

    char *first_word = strtok(s, " .\n");

    printf("Перше слово: %s\n", first_word);

    if(first_word == NULL){
        printf("Рядок порожній.\n");
        return 0;
    }

    char *token = strtok(NULL, " .\n");
    int found = 0;

    printf("Слова, що співпадають з першим:\n");

    while(token != NULL){
        if(strcmp(first_word, token) == 0){
            printf("%s\n", token);
            found = 1;
        }
        token = strtok(NULL, " .\n");
    }

    if(!found) printf("Збігів з першим словом не знайдено.\n");
    return 0;
}