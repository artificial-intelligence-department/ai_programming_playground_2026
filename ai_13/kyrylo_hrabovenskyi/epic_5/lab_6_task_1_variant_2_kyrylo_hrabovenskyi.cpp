#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Функція перевіряє, чи є символ голосною літерою (латинський алфавіт)
int isVowel(char c) {
    char ch = (char)tolower((unsigned char)c);
    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y');
}

// Функція перевіряє, чи містить слово хоча б одну голосну літеру
int hasVowels(const char* word) {
    for (int i = 0; word[i] != '\0'; ++i) {
        if (isVowel(word[i])) {
            return 1; // Голосну знайдено
        }
    }
    return 0; // Голосних немає
}

int main() {
    char str[256];
    printf("Enter a string (up to 255 characters, dot at the end):\n");

    // Зчитування рядка
    if (!fgets(str, sizeof(str), stdin)) return 0;

    // Видалення символу переходу рядка \n та крапки в кінці
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[--len] = '\0';
    if (len > 0 && str[len - 1] == '.') str[--len] = '\0';

    // Копія рядка для strtok
    char temp[256];
    strcpy(temp, str);

    printf("\nWords that do not contain vowels:\n");
    int count = 0;

    // Розбиття рядка на слова за допомогою strtok
    char* token = strtok(temp, " ");
    while (token != NULL) {
        // Перевірка кожного слова
        if (!hasVowels(token)) {
            printf("- %s\n", token);
            count++;
        }
        token = strtok(NULL, " ");
    }

    if (count == 0) {
        printf("No words without vowels were found in the text.\n");
    }

    return 0;
}