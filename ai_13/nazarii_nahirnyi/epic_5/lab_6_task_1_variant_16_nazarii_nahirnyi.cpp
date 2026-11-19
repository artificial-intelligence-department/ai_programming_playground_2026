#include <stdio.h>
#include <string.h>

int main() {
    char s[256];
    char word[128][256];  
    int count = 0;

    printf("Введіть рядок:");
    fgets(s, 256, stdin);

    s[strcspn(s, "\n")] = '\0';
int len = strlen(s);
if (len == 0 || s[len - 1] != '.') {
    puts("Помилка: рядок порожній або немає крапки в кінці!");
    return 1;
}
    char *token = strtok(s," .");

    while (token != NULL) {
        strcpy(word[count], token);
        count++;

       token = strtok(NULL," .");
    }
    
if (count == 0) {
    puts("Помилка: у рядку немає слів!");
    return 1;
}
    printf("Унікальні слова:");

    for (int i = 0; i < count; i++) {
        int matches = 0;

        for (int j = 0; j < count; j++) {
            if (strcmp(word[i],word[j]) == 0) {
                matches++;
            }
        }

        if (matches == 1) {
            puts(word[i]);
        }
    }

    return 0;
}