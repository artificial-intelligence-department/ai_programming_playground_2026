/*
Задача: Lab 6 task 1
Автор:   Катерирна Лисенко
Група:   ШІ-12
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 256        /* до 255 символів + '\0' */

void sortLetters(char s[], int from, int to);
void processText(char s[]);

int main(void) {
    char s[SIZE];
    size_t len;
    int ch;

    printf("Введіть рядок (до 255 символів, слова через пробіли, крапка в кінці):\n");

    /* ввід рядка через fgets з перевіркою довжини */
    if (fgets(s, SIZE, stdin) == NULL) {
        printf("Помилка: рядок не введено або він довший за 255 символів.\n");
        return 1;
    }
    len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[--len] = '\0';
    } else {
        ch = getchar();                 /* буфер заповнено: чи є ще символи? */
        if (ch != '\n' && ch != EOF) {
            printf("Помилка: рядок не введено або він довший за 255 символів.\n");
            return 1;
        }
    }
    if (len > 0 && s[len - 1] == '\r') {
        s[--len] = '\0';
    }

    /* перевірка: є хоча б одне слово, крапка стоїть одразу після останнього слова */
    if (len < 2 || s[len - 1] != '.' || s[len - 2] == ' ') {
        printf("Помилка: рядок має містити хоча б одне слово і закінчуватися крапкою після останнього слова.\n");
        return 1;
    }

    printf("\nПочатковий рядок: \"%s\"\n", s);
    processText(s);
    printf("Результат:        \"%s\"\n", s);
    return 0;
}

/* Сортує за зростанням кодів лише букви в s[from..to-1]; решта символів
   слова лишаються на своїх місцях. */
void sortLetters(char s[], int from, int to) {
    char letters[SIZE];
    int count = 0;
    int i, j;

    for (i = from; i < to; i++) {
        if (isalpha((unsigned char)s[i])) {
            letters[count++] = s[i];
        }
    }
    /* сортування вставками */
    for (i = 1; i < count; i++) {
        char key = letters[i];
        j = i - 1;
        while (j >= 0 && letters[j] > key) {
            letters[j + 1] = letters[j];
            j--;
        }
        letters[j + 1] = key;
    }
    /* повертаємо відсортовані букви на позиції букв */
    j = 0;
    for (i = from; i < to; i++) {
        if (isalpha((unsigned char)s[i])) {
            s[i] = letters[j++];
        }
    }
}

/* Знаходить слова (послідовності непробільних символів до завершальної
   крапки) і сортує букви в кожному. */
void processText(char s[]) {
    int end = (int)strlen(s) - 1;       /* позиція завершальної крапки */
    int i = 0;
    int start;

    while (i < end) {
        while (i < end && s[i] == ' ') {
            i++;
        }
        start = i;
        while (i < end && s[i] != ' ') {
            i++;
        }
        if (i > start) {
            sortLetters(s, start, i);
        }
    }
}
