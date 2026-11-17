#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char s[256];
    char words[256][256];
    char temp[256];
    int n = 0;

    printf("Enter a string:\n");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';

    // Розбиваємо рядок на окремі слова
    char *token = strtok(s, " ");

    while (token != NULL){
        // Перевіряємо, чи починається слово з цифри
        if (isdigit((unsigned char)token[0])){
            strcpy(words[n], token);
            n++;
        }

        token = strtok(NULL, " ");
    }

    // Сортуємо слова за спаданням
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (strcmp(words[j], words[j + 1]) < 0){
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], temp);
            }
        }
    }

    // Виводимо результат
    printf("Sorted words:\n");

    for (int i = 0; i < n; i++){
        printf("%s\n", words[i]);
    }

    return 0;
}
