/*
Лабораторна №6 завдання 1 варіант 14
Небеснюк Маркіян
ШІ-12
*/
#include <cstdio>
#include <cstring>
#include <cctype>

// Перевірка, що слово складається лише з літер та цифр і містить хоча б одну літеру та одну цифру
bool hasLettersAndDigits(const char *word) {
    bool hasLetter = false;
    bool hasDigit = false;

    for (int i = 0; word[i] != '\0'; i++) {
        unsigned char c = (unsigned char)word[i];
        if (isalpha(c) != 0) {
            hasLetter = true;
        } else if (isdigit(c) != 0) {
            hasDigit = true;
        } else {
            // Будь-який спецсимвол чи знак пунктуації одразу відсіює слово
            return false;
        }
    }

    return hasLetter && hasDigit;
}

int main() {
    char s[256];

    printf("Введіть рядок (до 255 символів, крапка в кінці):\n");
    if (fgets(s, sizeof(s), stdin) == NULL) {
        printf("Помилка зчитування рядка.\n");
        return 1;
    }
    s[strcspn(s, "\n")] = '\0';

    int len = (int)strlen(s);
    if (len == 0 || s[len - 1] != '.') {
        printf("Помилка: рядок має завершуватися крапкою.\n");
        return 1;
    }

    // Прибираємо крапку перед нарізанням, щоб вона не приклеїлася до останнього слова
    s[len - 1] = '\0';

    char result[256] = "";

    bool firstWord = true;

    // Перевірка умови для кожного слова
    char *word = strtok(s, " ");
    while (word != NULL) {
        if (hasLettersAndDigits(word) == true) {
            if (firstWord == false) {
                strcat(result, " ");
            }
            strcat(result, word);
            firstWord = false;
        }
        word = strtok(NULL, " ");
    }

    strcat(result, ".");
    strcpy(s, result);

    printf("Результат:\n%s\n", s);
    return 0;
}