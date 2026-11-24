#include <stdio.h>

bool read(char text[256]) {
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, 256, stdin) == NULL) {
        return false;
    }

    char *end = text;
    while (*end != '\0' && *end != '\n' && *end != '\r') {
        end++;
    }
    *end = '\0';

    int len = (int)(end - text);
    if (len == 0 || *(end - 1) != '.') {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return false;
    }

    bool areThereWords = false;
    for (char *p = text; p < end - 1; p++) {
        if (*p == ' ') {
            continue;
        }

        bool isLetter = (*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z');
        bool isDigit  = (*p >= '0' && *p <= '9');

        if (isDigit || isLetter) {
            areThereWords = true;
        } else {
            printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
            return false;
        }
    }

    if (!areThereWords) {
        printf("Помилка: у тексті має бути хоча б одне слово.\n");
        return false;
    }

    return true;
}

void maxMinWords(const char *text) {
    const char *p = text;
    bool inWord = false;
    int minLength = 256;
    int minIndex = -1;
    int maxLen = 0;
    int maxIndex = -1;
    int currLength = 0;

    while (*p != '\0') {
        if (*p != ' ' && *p != '.') {
            currLength++;
            inWord = true;
        } else {
            if (inWord) {
                if (minIndex == -1 || currLength < minLength) {
                    minLength = currLength;
                    minIndex = (int)(p - text) - currLength;
                }
                if (maxIndex == -1 || currLength > maxLen) {
                    maxLen = currLength;
                    maxIndex = (int)(p - text) - currLength;
                }
                currLength = 0;
                inWord = false;
            }
        }

        if (*p == '.') {
            break;
        }
        p++;
    }

    char max[256];
    for (int i = 0; i < maxLen; i++) {
        max[i] = text[maxIndex + i];
    }
    max[maxLen] = '\0';

    char min[256];
    for (int i = 0; i < minLength; i++) {
        min[i] = text[minIndex + i];
    }
    min[minLength] = '\0';

    printf("Найдовше слово: '%s', довжина: %d\n", max, maxLen);
    printf("Найкоротше слово: '%s', довжина: %d\n", min, minLength);
}

int main(void) {
    char text[256];
    if (!read(text)) {
        return 1;
    }
    maxMinWords(text);
    return 0;
}