/*Плахтина Дмитро
Ші-11
Lab 6, варіант 17: всі слова рядка, які починаються з букви, відсортувати за абеткою */
#include <cstdio>
#include <cstring>
#include <cctype>

int main() {
char text[256];
char words[128][256];
int count = 0;

printf("Введіть текст (до 255 символів, крапка в кінці):\n");
fgets(text, 256, stdin);
char* t = strchr(text, '\n');
if (t != NULL) {
    *t = '\0';
}
int len = strlen(text);
if (len == 0 || text[len - 1] != '.') {
    printf("Помилка! В кінці має стояти крапка! \n");
    return 1;
}
text[len - 1] = '\0';

//Розбиття на слова
char *w = strtok(text, " ");
while (w != NULL) {
    if (isalpha((unsigned char)w[0])) {
        strcpy(words[count], w);
        count ++;
    }
    w = strtok(NULL, " ");
}

//Сортування бульбашкою
for (int i = 0; i < count - 1; i ++) {
    for (int j = 0; j < count - 1 - i; j ++) {
        if (strcmp(words[j], words[j + 1]) > 0) {
            char temp[256];
            strcpy(temp, words[j]);
            strcpy(words[j], words[j + 1]);
            strcpy(words[j + 1], temp);
        }
    }
}

//Вивід
if (count == 0) {
    printf("Слів, що починаються з літери, не знайдено\n");
} else {
    printf("Відсортовані слова, що починаються з літери:\n");
    for (int i = 0; i < count; i ++) {
        printf("%s ", words[i]);
    }
    printf("\n");
}
    return 0;
}