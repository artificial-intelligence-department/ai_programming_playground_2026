/*
Назва: Лабораторна 6 варіант 3
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <cstdio> 
#include <cstring> 
#include <cctype>


int main() {
    char s[256]; 
    int found = 0;

    printf("Введіть рядок (не більше 255 символів, наприкінці поставте крапку):\n");
    if (fgets(s, sizeof(s), stdin) == NULL) {
        return 1;
    }

    printf("\nСлова, які містять по одній цифрі:\n");

    char *token = strtok(s, " .\n");
    while (token != NULL) {
        int digitCount = 0;

        for (size_t i = 0; token[i] != '\0'; i++) {
            if (isdigit((unsigned char)token[i])) {
                digitCount++;
            }
        }

        if (digitCount == 1) {
            printf("%s\n", token);
            found = 1;
        }

        token = strtok(NULL, " .\n");
    }

    if (!found) {
        printf("Слів, що містять рівно одну цифру, не знайдено.\n");
    }

    return 0;
}