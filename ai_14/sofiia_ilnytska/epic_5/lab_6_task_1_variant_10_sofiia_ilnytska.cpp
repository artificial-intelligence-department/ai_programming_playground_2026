/*
    Задача: Лабораторна робота №6. Варіант №10
    Автор: Ільницька Софія
    Група: ШІ-14
*/

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int main() {
    char text[256];
    char words[256][256];
    int count = 0;

    printf("Введіть текст: ");
    fgets(text, 256, stdin);

    // Розділяємо текст на слова
    char *word = strtok(text, " .\n");

    while (word != NULL) {
        strcpy(words[count], word);    // Зберігаємо знайдене слово
        count++;                       // Збільшуємо кількість слів
        word = strtok(NULL, " .\n");   // Переходимо до наступного слова
    }

    printf("Результат: ");

    // Тричі проходимо по всіх словах:
    // 1 - тільки цифри, 2 - тільки букви, 3 - букви і цифри
    for (int type = 1; type <= 3; type++) {
        for (int i = 0; i < count; i++) {
            bool letters = false;
            bool digits = false;

            // Перевіряємо кожен символ поточного слова
            for (int j = 0; words[i][j] != '\0'; j++) {
                if (words[i][j] >= '0' && words[i][j] <= '9') {
                    digits = true;
                } else {
                    letters = true;
                }
            }

            // Виводимо слова, що містять тільки цифри
            if (type == 1 && digits && !letters) {
                printf("%s ", words[i]);
            }

            // Виводимо слова, що містять тільки букви
            if (type == 2 && letters && !digits) {
                printf("%s ", words[i]);
            }

            // Виводимо слова, що містять і букви, і цифри
            if (type == 3 && letters && digits) {
                printf("%s ", words[i]);
            }
        }
    }

    printf("\b.\n");
    return 0;
}
