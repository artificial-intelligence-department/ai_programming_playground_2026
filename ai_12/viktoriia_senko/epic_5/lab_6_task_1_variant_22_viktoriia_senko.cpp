/*Lab 6 Task 1 Variant 22
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <cstdio>
#include <cstring>
#include <cctype>

int CountWordsOnA(char str[]) {
    int k = 0;
    char *token = strtok(str, " ");
    while (token != NULL) {
        if (tolower((unsigned char)token[0]) == 'a')
            k++;
        token = strtok(NULL, " ");
    }
    return k;
}

int main() {
    char sentence[256];

    printf("Введіть текст:\n");
    if (fgets(sentence, sizeof sentence, stdin) == NULL) {
        printf("Помилка: текст не введено.\n");
        return 1;
    }
    char *nl = strchr(sentence, '\n');
    if (nl != NULL) *nl = '\0';

    int len = strlen(sentence);
    if (len == 0 || sentence[len - 1] != '.') {
        printf("Помилка: текст має закінчуватися крапкою.\n");
        return 1;
    }
    sentence[len - 1] = '\0';                
    printf("Кількість слів, що починаються на букву \"a\": %d\n", CountWordsOnA(sentence));
    return 0;
}