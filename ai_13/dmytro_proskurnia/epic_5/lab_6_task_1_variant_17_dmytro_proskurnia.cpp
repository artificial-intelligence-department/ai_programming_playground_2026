#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256
#define MAX_WORDS 100

int main() {
    char s[MAX_LEN];
    char words[MAX_WORDS][MAX_LEN];
    int word_count = 0;

    printf("Введіть текст (до 255 символів, в кінці крапка):\n");

    if (fgets(s, sizeof(s), stdin) == NULL) {
        return 1;
    }

    s[strcspn(s, "\n")] = '\0';

    char *dot_ptr = strchr(s, '.');
    if (dot_ptr != NULL) {
        *dot_ptr = '\0';
    }

    char *token = strtok(s, " ");
    while (token != NULL) {
        if (isalpha((unsigned char)token[0])) {
            strcpy(words[word_count], token);
            word_count++;
        }
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < word_count - 1; i++) {
        for (int j = i + 1; j < word_count; j++) {
            if (strcmp(words[i], words[j]) > 0) {
                char temp[MAX_LEN];
                strcpy(temp, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], temp);
            }
        }
    }

    printf("\nВідсортовані слова, що починаються з букви:\n");
    if (word_count == 0) {
        printf("Слів, що починаються з букви, не знайдено.\n");
    } else {
        for (int i = 0; i < word_count; i++) {
            printf("%s ", words[i]);
        }
        printf("\n");
    }

    return 0;
}