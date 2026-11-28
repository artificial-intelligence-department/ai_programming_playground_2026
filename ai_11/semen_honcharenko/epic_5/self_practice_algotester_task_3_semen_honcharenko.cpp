/*
    Алготестер. "Патріотична cтрічка"
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char s[100001] = {};

    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = 0;

    int resY = 0;
    int resB = 0;

    for (int i = 0; s[i] != '\0'; ) {
        if (i % 2 == 0) {
            if (s[i] == 'Y') {
                i++;
            }
            else {
                resY++;
                i++;
            }
        }
        else {
            if (s[i] == 'B') {
                i++;
            }
            else {
                resY++;
                i++;
            }
        }
    }
    for (int i = 0; s[i] != '\0'; ) {
        if (i % 2 == 0) {
            if (s[i] == 'B') {
                i++;
            }
            else {
                resB++;
                i++;
            }
        }
        else {
            if (s[i] == 'Y') {
                i++;
            }
            else {
                resB++;
                i++;
            }
        }
    }
    if (resY > resB) {
        printf("%d\n", resB);
    }
    else {
        printf("%d\n", resY);
    }
    return 0;
}