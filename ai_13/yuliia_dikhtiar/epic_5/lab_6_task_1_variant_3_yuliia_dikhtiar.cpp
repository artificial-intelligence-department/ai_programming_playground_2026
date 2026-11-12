/*
Назва задачі: Lab 6 Task 1
Варіант: 3
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <cstdio>
#include <cstring>

using namespace std;

bool hasOneDigit(const char *word) {
    int digits = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] >= '0' && word[i] <= '9') {
            digits++;
        }
    }
    return digits == 1;
}

int main() {
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, sizeof(text), stdin) == nullptr) {
        printf("Помилка введення.\n");
        return 1;
    }

    int length = strlen(text);
    if (length > 0 && text[length - 1] == '\n') {
        text[length - 1] = '\0';
        length--;
    } else {
        int next = getchar();
        if (next != '\n' && next != EOF) {
            printf("Помилка: текст перевищує 255 символів.\n");
            return 1;
        }
    }

    if (length < 2 || text[length - 1] != '.') {
        printf("Помилка: введіть текст зі словами та крапкою в кінці.\n");
        return 1;
    }
    text[length - 1] = '\0';

    printf("Слова, які містять рівно одну цифру:\n");
    bool found = false;
    char *word = strtok(text, " ");
    while (word != nullptr) {
        if (hasOneDigit(word)) {
            printf("%s\n", word);
            found = true;
        }
        word = strtok(nullptr, " ");
    }

    if (!found) {
        printf("Таких слів немає.\n");
    }
    return 0;
}