/*
Варінт №8
Кузовніков В'ячеслав Євгенійович
ШІ - 13
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>


void processWord(char *src, char *dest) {
    int i, j = 0;
    int len = strlen(src);

    //  Очищаємо: залишаємо лише букви, цифри та '_'
    for (i = 0; i < len; i++) {
        if (isalnum((unsigned char)src[i]) || src[i] == '_') {
            dest[j++] = src[i];
        }
    }
    dest[j] = '\0';

    // Якщо після очищення слово порожнє — виходимо
    if (j == 0) {
        return;
    }

    //  Тепер перевіряємо, чи очищене слово складається ТІЛЬКИ з цифр
    int allDigits = 1;
    for (i = 0; i < j; i++) {
        if (!isdigit((unsigned char)dest[i])) {
            allDigits = 0;
            break;
        }
    }

    // Якщо повністю з цифр — знищуємо слово
    if (allDigits) {
        dest[0] = '\0';
        return;
    }

    //  Якщо починається з цифри (але містить і букви) — додаємо '_' на початок
    if (isdigit((unsigned char)dest[0])) {
        for (i = j; i >= 0; i--) {
            dest[i + 1] = dest[i];
        }
        dest[0] = '_';
    }
}

int main() {
    char str[256];      
    char result[256] = ""; 
    char token_out[256];   

    printf("Введіть речення (воно має обовєязково завершуватись крапкою): ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 0;
    }

    char *token = strtok(str, " .\n");

    while (token != NULL) {
        processWord(token, token_out);

        if (strlen(token_out) > 0) {
            if (strlen(result) > 0) {
                strcat(result, " ");
            }

            strcat(result, token_out);
        }

        token = strtok(NULL, " .\n");
    }

    strcat(result, ".");

    printf("Нове речення (з  ідентифікаторами): %s\n", result);

    return 0;
}