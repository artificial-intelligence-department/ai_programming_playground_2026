/*
    Назва: Class Practice Work
    Автор: Макух Арсеній
    Група: ШІ-13
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int p_len = 0, cts = 0, p_lvl = 0;
    char nums, uls, ssymb;

    cout << "Довжина пароля: ";
    cin >> p_len;

    if (p_len < 1 || p_len > 64) {
        cout << "Довжина пароля: 0\nПомилка: довжина мусить бути від 1 до 64." << endl;
        return 1;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> nums;

    if (nums != 'y' && nums != 'n') {
        cout << "Введіть дійсне значення (y/n)." << endl;
        return 1;
    }

    cout << "Чи є великі літери (y/n): ";
    cin >> uls;

    if (uls != 'y' && uls != 'n') {
        cout << "Введіть дійсне значення (y/n)." << endl;
        return 1;
    }

    cout << "Чи є спеціальні символи (y/n): ";
    cin >> ssymb;

    if (ssymb != 'y' && ssymb != 'n') {
        cout << "Введіть дійсне значення (y/n)." << endl;
        return 1;
    }

    if (nums == 'y') {
        cts += 1;
    }

    if (uls == 'y') {
        cts += 1;
    }

    if (ssymb == 'y') {
        cts += 1;
    }

    cout << "\nМінімальні вимоги: ";
    if (p_len >= 8 && cts >= 2) {
        cout << "ПРОЙДЕНО" << endl;
    } else {
        cout << "НЕ ПРОЙДЕНО" << endl;
    }

    if (p_len < 6) {
        p_lvl = 1;
    } else if (p_len < 8 || cts == 0) {
        p_lvl = 2;
    } else if (cts == 1) {
        p_lvl = 3;
    } else if (p_len >= 12 && cts == 3) {
        p_lvl = 5;
    } else {
        p_lvl = 4;
    }

    cout << "Рівень надійності: " << p_lvl << " - ";
    switch (p_lvl) {
        case 1:
            cout << "Дуже слабкий" << 
            "\nРекомендація: Пароль надто короткий. Мінімум 8 символів." << endl;
            break;
        case 2:
            cout << "Слабкий" << 
            "\nРекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
            break;
        case 3:
            cout << "Середній" << 
            "\nРекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl;
            break;
        case 4:
            cout << "Надійний" <<
            "\nРекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
            break;
        case 5:
            cout << "Дуже надійний" << 
            "\nРекомендація: Відмінно. Змінювати нічого не потрібно." << endl;
            break;
    }

    if (nums == 'n' && ssymb == 'n') {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}