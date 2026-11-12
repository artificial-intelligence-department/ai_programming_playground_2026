/*
Задача:  Лабораторна робота 6
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <cstdio>
#include <cstring>

void findWords(char text[]);

int main() {
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");

    if (!fgets(text, sizeof(text), stdin)) return 0;

    char* end = strchr(text, '\n');
    if (end != nullptr) {
        *end = '\0';
    }
    else {
        char next;
        if (scanf("%c", &next) == 1 && next != '\n') {
            printf("Помилка: текст довший за 255 символів.\n");
            return 1;
        }
    }

    int length = strlen(text);
    if (length == 0 || text[length - 1] != '.') {
        printf("Помилка: текст має завершуватися крапкою.\n");
        return 1;
    }

    text[length - 1] = '\0';
    findWords(text);
    return 0;
}

void findWords(char text[]) {
    char* word = strtok(text, " ");
    if (word == nullptr) {
        printf("Помилка: у тексті немає слів.\n");
        return;
    }

    char* longest = word;
    char* shortest = word;

    while (word != nullptr) {
        if (strlen(word) > strlen(longest)) longest = word;
        if (strlen(word) < strlen(shortest)) shortest = word;
        word = strtok(nullptr, " ");
    }

    printf("Найдовше слово: %s (%zu)\n", longest, strlen(longest));
    printf("Найкоротше слово: %s (%zu)\n", shortest, strlen(shortest));
}
