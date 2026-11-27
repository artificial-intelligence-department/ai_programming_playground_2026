/* 
Задача: Лабораторна робота №6
Автор: Вероніка Третяк
Група: ШІ-13
*/

#include <cstdio>
#include <cstring>

using namespace std;

int main() {
    char text[257];  

    printf("Введіть речення з крапкою в кінці:\n");
    if (fgets(text, sizeof(text), stdin) == nullptr) {
        return 1;
    }
    
    char *input = strchr(text, '\n');
    if (input != nullptr) {
        *input = '\0';
    }

    int len = strlen(text);

    if (len > 255) {
        printf("Помилка: текст довший за 255 символів.\n");
        return 1;
    }

    if (len == 0 || text[len - 1] != '.') {
        printf("Помилка: у кінці речення має бути крапка.\n");
        return 1;
    }

    text[len - 1] = '\0'; 

    char *word = strtok(text, " ");
    if (word == nullptr) {
        printf("Слів немає.\n");
        return 0;
    }

    char *longest = word;
    char *shortest = word;
word = strtok(nullptr, " ");
while (word != nullptr) {
        if (strlen(word) > strlen(longest)) {
            longest = word;
        }

        if (strlen(word) < strlen(shortest)) {
            shortest = word;
        }

        word = strtok(nullptr, " ");
    }

    printf("Найдовше слово: %s\n", longest);
    printf("Найкоротше слово: %s\n", shortest);

    return 0;
}