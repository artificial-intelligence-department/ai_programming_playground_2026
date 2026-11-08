/*Epic 5 - Завдання 1 лабораторної 6 варіант 3
Чернихівський Максим
Ші - 14*/

#include <stdio.h>
#include <string.h>

bool isDigit(char c){
    return (c >= '0' && c <= '9');
}

void findWordsWithDigits(char *s1) {
    char *temp = strtok(s1, " .\n"); // Розбиває рядок на за допомогою пробілу або \n

    while (temp != NULL){ // Працює поки strtok знаходить нові слова
        int digits = 0;
        for (size_t i = 0; i < strlen(temp); i++) {
            if (isDigit(temp[i])) {
                digits++;
            }
        }
        if (digits == 1) {
            printf("%s\n", temp);
        }
        temp = strtok(NULL, " .\n"); // Переходить до наступного слова в рядку
    }
}

int main() {
    char s1[257];
    puts("Введіть рядок: ");
    fgets(s1, sizeof(s1), stdin);
    findWordsWithDigits(s1);
    return 0;
}