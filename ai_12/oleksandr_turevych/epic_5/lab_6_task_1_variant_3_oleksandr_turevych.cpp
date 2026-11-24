/*
Епік 5. Лабораторна робота № 6 (Варіант 3): Надрукувати всі слова, які містять по одній цифрі
Автор: Туревич Олександр
Група: ШІ-12
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

int countDigits(const char *word) {
    int digits = 0;
    for (int i = 0; word[i] != '\0'; ++i) {
        if (isdigit(word[i])) {
            digits++;
        }
    }
    return digits;
}

int main() {
    char text[256];

    cout << "Введіть рядок (до 255 символів, з крапкою в кінці): ";
    if (fgets(text, sizeof(text), stdin) == nullptr) {
        cout << "Помилка вводу." << endl;
        return 1;
    }

    text[strcspn(text, "\n")] = '\0';

    cout << "Слова, які містять рівно одну цифру:" << endl;

    // Розбиваємо рядок на слова по пробілах та крапці
    char *token = strtok(text, " .");
    bool found = false;

    while (token != nullptr) {
        if (countDigits(token) == 1) {
            cout << token << endl;
            found = true;
        }
        token = strtok(nullptr, " .");
    }

    if (!found) {
        cout << "Таких слів не знайдено." << endl;
    }

    return 0;
}
