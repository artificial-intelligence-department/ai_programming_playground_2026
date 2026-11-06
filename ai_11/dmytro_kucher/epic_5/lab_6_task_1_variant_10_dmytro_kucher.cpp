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
    
    if (fgets(str, sizeof(str), stdin) == nullptr) {
        cout << "Помилка введення!\n";
        return 1;
    }

    str[strcspn(str, "\n")] = '\0';

    int len = strlen(str);

    if (len == 0) {
        cout << "Помилка! Рядок порожній.\n";
        return 1;
    }

    if (str[len-1] != '.') {
        cout << "Помилка! Рядок повинен закінчуватися крапкою.\n";
        return 1;
    }

    for (int i = 0; i < len - 1; i++) {
        if (!isalnum((unsigned char)str[i]) && str[i] != ' ') {
            cout << "Помилка! Недопустимий символ.\n";
            return 1;
        }
    }

    str[len - 1] = '\0';

    for (int k = 0; k<3; k++) {
        strcpy(copy, str);
        char *portion = strtok(copy, " ");

        while (portion != NULL) {

            bool hasDigit = false;
            bool hasLetter = false;

            for (int i = 0; portion[i] != '\0'; i++) {
                if (isdigit((unsigned char)portion[i])) hasDigit = true;
                if (isalpha((unsigned char)portion[i])) hasLetter = true;
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

    cout << "Result: " << result << "\n";

    return 0;
}