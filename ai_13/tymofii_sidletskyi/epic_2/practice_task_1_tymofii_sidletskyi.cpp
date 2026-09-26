#include <iostream>
#include <string>
using namespace std;
int main() {
    int passLength;
    int level;
    string digits;
    string capitals;
    string specialChars;
    int charTypes = 0;

    cout << "Довжина пароля (від 1 до 64): ";
    cin >> passLength;
    if (passLength < 1 || passLength > 64 || cin.fail()) {
        cout << "Помилка: введіть довжину пароля (ціле число від 1 до 64)." << endl;
        return 1;
    }

    cout << "Чи є цифри у паролі (y/n): ";
    cin >> digits;
    if (digits != "y" && digits != "n") {
        cout << "Помилка: введіть y або n." << endl;
        return 1;
    }

    cout << "Чи є великі літери у паролі (y/n): ";
    cin >> capitals;
    if (capitals != "y" && capitals != "n") {
        cout << "Помилка: введіть y або n." << endl;
        return 1;
    }

    cout << "Чи є спеціальні символи у паролі (y/n): ";
    cin >> specialChars;
    if (specialChars != "y" && specialChars != "n") {
        cout << "Помилка: введіть y або n." << endl;
        return 1;
    }
    
    if (specialChars == "y") {
        charTypes++;
    }
    if (capitals == "y") {
        charTypes++;
    }
    if (digits == "y") {
        charTypes++;
    }

    if (passLength >= 8 && charTypes >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    if (passLength < 6) {
        level = 1;
        cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
    }   else if (passLength < 8 || charTypes == 0) {
        level = 2;
        cout << "Рівень надійності: 2 - Слабкий" << endl;
    }   else if (charTypes == 1) {
        level = 3;
        cout << "Рівень надійності: 3 - Середній" << endl;
    }   else if (passLength >= 12 && charTypes == 3) {
        level = 5;
        cout << "Рівень надійності: 5 - Дуже надійний" << endl;
    }   else {
        level = 4;
        cout << "Рівень надійності: 4 - Надійний" << endl;
    }
    
    switch (level) {
        case 1:
            cout << "Пароль надто короткий. Мінімум символів 8." << endl;
            break;
        case 2:
            cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
            break;
        case 3:
            cout << "Додайте ще один тип символів або збільште довжину до 12." << endl;
            break;
        case 4:
            cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
            break;
        case 5:
            cout << "Відмінно. Змінювати нічого не потрібно." << endl;
            break;
    }
    if (digits == "n" || specialChars == "n") {
        cout << "Попередження: пароль тільки з літер підбирається швидше" << endl;
    }
    return 0;
}