// Лабораторна робота №6, варіант 16
// визначити, які слова зустрічаються в рядку по одному разу
#include <stdio.h>
#include <string.h>

// 255 символів + '\0'
const int MAX_LEN = 256;
// слів не буде більше ніж половина довжини (слово + пробіл)
const int MAX_WORDS = 128;

// розбиваю рядок на слова, strtok псує рядок, тому сюди даю копію
int splitWords(char str[], char *words[]) {
    int count = 0;
    char *token = strtok(str, " .");
    while (token != NULL && count < MAX_WORDS) {
        words[count] = token;
        count++;
        token = strtok(NULL, " .");
    }
    return count;
}

// скільки разів слово з номером index є серед усіх слів
int countWord(char *words[], int count, int index) {
    int k = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], words[index]) == 0) {
            k++;
        }
    }
    return k;
}

int main() {
    char text[MAX_LEN];
    char copy[MAX_LEN];
    char *words[MAX_WORDS];

    printf("Введіть текст (до 255 символів, в кінці крапка):\n");
    if (fgets(text, MAX_LEN, stdin) == NULL) {
        printf("Текст не введено.\n");
        return 1;
    }

    // fgets лишає '\n' в кінці, прибираю його
    text[strcspn(text, "\n")] = '\0';

    int len = strlen(text);
    if (len == 0 || text[len - 1] != '.') {
        printf("Помилка: текст має закінчуватися крапкою.\n");
        return 1;
    }

    strcpy(copy, text);
    int count = splitWords(copy, words);
    if (count == 0) {
        printf("Помилка: у тексті немає слів.\n");
        return 1;
    }

    printf("Текст: \"%s\"\n", text);
    printf("Кількість слів: %d\n", count);
    printf("Слова, які зустрічаються один раз:");

    int unique = 0;
    for (int i = 0; i < count; i++) {
        if (countWord(words, count, i) == 1) {
            printf(" %s", words[i]);
            unique++;
        }
    }
    // якщо всі слова повторюються
    if (unique == 0) {
        printf(" таких слів немає");
    }
    printf("\nКількість таких слів: %d\n", unique);

    return 0;
}
