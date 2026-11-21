#include <stdio.h>
#include <string.h>

int main() {
    char s[256];
    char result[256] = "";

    printf("Input text: ");
    fgets(s, 256, stdin);

    s[strcspn(s, "\n")] = '\0';
    // прибираємо крапку в кінці
    int len = strlen(s);
    if (len > 0 && s[len - 1] == '.') {
        s[len - 1] = '\0';
    }

    int index = 0; // номер слова

    char* word = strtok(s, " ");

    while (word != NULL) {
        index++;

    //залишаємо слова на непарних позиціях, а парні (2, 4, 6 і так далі) знищуємо
        if (index % 2 != 0) {
            if (strlen(result) > 0) {
                strcat(result, " ");
            }
            strcat(result, word);
        }

        word = strtok(NULL, " ");
    }

    if (strlen(result) > 0) {
        strcat(result, ".");
    }

    printf("Output text: %s\n", result);
    return 0;
}