
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void Obrobka(char str[], char res[]) {

    int k = 0;
    int n = strlen(str);
    for (int i = 0; i < n; i++) {
        if (isalpha(str[i])) {
            res[k] = str[i];
            k++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (isdigit(str[i])) {
            res[k] = str[i];
            k++;
        }
    }
    res[k] = '\0';
}

int main() {

    char s[256];
    char res[256];
    printf("Введіть рядок (в кінці крапка): ");
    fgets(s, 256, stdin);

    char *p = strchr(s, '\n');
    if (p != NULL) {
        *p = '\0';
}

int len = strlen(s);
if (len == 0 || s[len - 1] != '.') {
    printf("Помилка: рядок має закінчуватись крапкою.\n");
    return 0;
}

Obrobka(s, res);

printf("Результат: %s\n", res);

return 0;
}