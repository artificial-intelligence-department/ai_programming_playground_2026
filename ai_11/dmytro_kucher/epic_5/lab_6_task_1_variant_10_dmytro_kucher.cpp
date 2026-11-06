/*
Епік 5. Лабораторна робота №6. Завдання №1. Варіант №10
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

int main () {

    char str[256];
    char copy[256];
    char result[256] = "";
    
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    str[strcspn(str, ".")] = '\0';

    for (int k = 0; k<3; k++) {
        strcpy(copy, str);
        char *portion = strtok(copy, " ");

        while (portion != NULL) {

            bool hasDigit = false;
            bool hasLetter = false;

            for (int i = 0; portion[i] != '\0'; i++) {
                if (isdigit(portion[i]) == true) hasDigit = true;
                if (isalpha(portion[i]) == true) hasLetter = true;
            }

            if (k == 0 && hasDigit && !hasLetter) {
                if (result[0] != '\0') strcat(result, " ");
                strcat(result, portion);
            }

            else if (k == 1 && !hasDigit && hasLetter) {
                if (result[0] != '\0') strcat(result, " ");
                strcat(result, portion);
            }

            else if (k == 2 && hasDigit && hasLetter) {
                if (result[0] != '\0') strcat(result, " ");
                strcat(result, portion);
            }

            portion = strtok(NULL, " ");
        }
    }

    strcat(result, ".");

    printf("Result: %s \n", result);

    return 0;
}