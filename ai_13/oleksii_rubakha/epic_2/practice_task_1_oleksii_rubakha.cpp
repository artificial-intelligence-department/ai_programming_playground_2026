
/*
 Аналізатор надійності пароля
 Автор: Рубаха Олексій 
 Група: ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    // Змінні для характеристик пароля
    int length, level;
    int types = 0;
    char hasDigits, hasUppercase, hasSpecial;
    bool minRequirements;


    // Введення довжини пароля
    cout << "Довжина пароля: ";
    cin >> length;

    // Перевірка допустимого діапазону довжини
    if (length < 1 || length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 1;
    }


    // Введення інформації про наявність цифр
    cout << "Чи є цифри (y/n): ";
    cin >> hasDigits;

    // Перевірка правильності введеної відповіді
    if (hasDigits != 'y' && hasDigits != 'n') {
        cout << "Помилка: потрібно ввести y або n." << endl;
        return 1;
    }


    // Введення інформації про наявність великих літер
    cout << "Чи є великі літери (y/n): ";
    cin >> hasUppercase;

    // Перевірка правильності введеної відповіді
    if (hasUppercase != 'y' && hasUppercase != 'n') {
        cout << "Помилка: потрібно ввести y або n." << endl;
        return 1;
    }


    // Введення інформації про наявність спеціальних символів
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> hasSpecial;

    // Перевірка правильності введеної відповіді
    if (hasSpecial != 'y' && hasSpecial != 'n') {
        cout << "Помилка: потрібно ввести y або n." << endl;
        return 1;
    }


    // Підрахунок кількості типів символів
    if (hasDigits == 'y') {
        types++;
    }
    if (hasUppercase == 'y') {
        types++;
    }
    if (hasSpecial == 'y') {
        types++;
    }

    // Перевірка мінімальних вимог
    if (length >= 8 && types >= 2) {
        minRequirements = true;
    } else {
        minRequirements = false;
    }

    // Визначення рівня надійності пароля
    if (length < 6) {
        level = 1;
    } else if (length < 8 || types == 0) {
        level = 2;
    } else if (types == 1) {
        level = 3;
    } else if (length >= 12 && types == 3) {
        level = 5;
    } else {
        level = 4;
    }


    // Виведення результатів перевірки мінімальних вимог
    cout << "/n";

    if (minRequirements) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }


    // Виведення назви рівня
    cout << "Рівень надійності: " << level << " - ";

    if (level == 1) {
        cout << "Дуже слабкий" << endl;
    } else if (level == 2) {
        cout << "Слабкий" << endl;
    } else if (level == 3) {
        cout << "Середній" << endl;
    } else if (level == 4) {
        cout << "Надійний" << endl;
    } else {
        cout << "Дуже надійний" << endl;
    }


    // Виведення рекомендації за допомогою switch
    cout << "Рекомендація: ";

    switch (level) {
        case 1:
            cout << "Пароль надто короткий. Мінімум 8 символів.";
            break;

        case 2:
            cout << "Збільште довжину до 8+ символів і додайте цифри, "
                    "великі літери або спеціальні символи.";
            break;

        case 3:
            cout << "Додайте ще один тип символів або збільште довжину до 12.";
            break;

        case 4:
            cout << "Хороший пароль. Для максимуму 12+ символів і всі три "
                    "типи символів.";
            break;

        case 5:
            cout << "Відмінно. Змінювати нічого не потрібно.";
            break;

        default:
            cout << "Невідомий рівень надійності.";
            break;
    }

    cout << "/n";

    // Попередження для паролів, що містять тільки малі літери
    if (!minRequirements && types == 0) {
        cout << "Попередження: пароль тільки з літер підбирається швидше."
             << endl;
    }

    return 0;
}