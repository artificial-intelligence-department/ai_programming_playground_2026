#include <iostream>

using namespace std;

int main() {
    int length;
    char numbers, big, symbols;

    cout << "Довжина пароля: ";
    cin >> length;

    if (length < 1 || length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 0;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> numbers;
    cout << "Чи є великі літери (y/n): ";
    cin >> big;
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> symbols;

    if (!(numbers == 'y' || numbers == 'n') ||
        !(big == 'y' || big == 'n') ||
        !(symbols == 'y' || symbols == 'n')) {
        cout << "Помилка: введіть дійсне значення (y/n)." << endl;
        return 0;
    }

    // Мінімальні вимоги
    if (length >= 8 && ((numbers == 'y' && big == 'y') || 
                        (numbers == 'y' && symbols == 'y') || 
                        (big == 'y' && symbols == 'y'))) {
        cout << "\nМінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        cout << "\nМінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    // Рівень надійності
    int lvl;
    if (length < 6) {
        lvl = 1;
    } else if (length < 8 || (numbers == 'n' && big == 'n' && symbols == 'n')) {
        lvl = 2;
    } else if ((numbers == 'y' && big == 'n' && symbols == 'n') ||
               (numbers == 'n' && big == 'y' && symbols == 'n') ||
               (numbers == 'n' && big == 'n' && symbols == 'y')) {
        lvl = 3;
    } else if (length >= 12 && numbers == 'y' && big == 'y' && symbols == 'y') {
        lvl = 5;
    } else {
        lvl = 4;
    }

    // Світч кейс для рівня надійності
    cout << "Рівень надійності: " << lvl << " - ";
    switch (lvl) {
        case 1:
            cout << "Дуже слабкий" << endl;
            break;
        case 2:
            cout << "Слабкий" << endl;
            break;
        case 3:
            cout << "Середній" << endl;
            break;
        case 4:
            cout << "Надійний" << endl;
            break;
        case 5:
            cout << "Дуже надійний" << endl;
            break;
        default:
            cout << "Невідомо" << endl;
            break;
    }

    // Світч кейс для рекомендації
    cout << "Рекомендація: ";
    switch (lvl) {
        case 1:
            cout << "Пароль надто короткий. Мінімум 8 символів." << endl;
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
        default:
            cout << "Немає рекомендації." << endl;
            break;
    }

    // Попередження
    if (numbers == 'n' && symbols == 'n') {
        cout << "Попередження: Пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}