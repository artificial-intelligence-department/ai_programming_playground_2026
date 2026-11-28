/*
    Лабораторна робота 6. Завдання 1. Варіант 6.
    Гончаренко Семен
    ШІ-11
*/
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

int main() {
    char s[260];
    char letters[260];
    int n = 0;

    printf("Start text: ");
    fgets(s, sizeof(s), stdin);
    if (strlen(s) > 0 && s[strlen(s)-1] == '\n') {
        s[strlen(s)-1] = '\0';
    }

    for (int i = 0; s[i] != '\0'; i++) {
        if (isalpha(s[i])) {
            letters[n] = s[i];
            n++;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (letters[j] > letters[j + 1]) {
                char temp = letters[j];
                letters[j] = letters[j + 1];
                letters[j + 1] = temp;
            }
        }
    }

    int k = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (isalpha(s[i])) {
            s[i] = letters[k];
            k++;
        }
    }

    printf("Final text: %s\n", s);
    return 0;
}