#include <iostream>
#include <string>
using namespace std;

int main() {
    int lenght;
    string has_digits, has_upper, has_special;

    // Зчитуємо характеристики пароля та перевіряємо введення.
    cout << "Введіть довжину пароля: ";
    cin >> lenght;
    if (lenght < 1 || lenght > 64) {
        cout << "Помилка: введіть цілу довжину від 1 до 64." << endl;
        return 0;
    }

    cout << "Чи містить пароль цифри (y/n): ";
    cin >> has_digits;
    if (has_digits != "y" && has_digits != "n") {
        cout << "Помилка: введіть y або n." << endl;
        return 0;
    }

    cout << "Чи містить пароль великі літери (y/n): ";
    cin >> has_upper;
    if (has_upper != "y" && has_upper != "n") {
        cout << "Помилка: введіть y або n." << endl;
        return 0;
    }

    cout << "Чи містить пароль спеціальні символи (y/n): ";
    cin >> has_special;
    if (has_special != "y" && has_special != "n") {
        cout << "Помилка: введіть y або n." << endl;
        return 0;
    }

    cout << "\nПароль введено правильно." << endl;

    // Рахуємо кількість наявних типів символів.
    int type_count = 0;
    if (has_digits == "y") {
        type_count++;
    }
    if (has_upper == "y") {
        type_count++;
    }
    if (has_special == "y") {
        type_count++;
    }

    // Перевіряємо мінімальні вимоги через if else.
    if (lenght >= 8 && type_count >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    // Перша виконана умова визначає рівень надійності.
    int level = 0;
    if (lenght < 6) {
        level = 1;
    } else if (lenght < 8 || type_count == 0) {
        level = 2;
    } else if (type_count == 1) {
        level = 3;
    } else if (lenght >= 12 && type_count == 3) {
        level = 5;
    } else {
        level = 4;
    }

    cout << "Рівень надійності: " << level << " - ";
    if (level == 1) {
        cout << "Дуже слабкий" << endl;
    } else if (level == 2) {
        cout << "Слабкий" << endl;
    } else if (level == 3) {
        cout << "Середній" << endl;
    } else if (level == 4) {
        cout << "Надійний" << endl;
    } else if (level == 5) {
        cout << "Дуже надійний" << endl;
    }

    // Виводимо рекомендацію за допомогою switch case.
    cout << "Рекомендація: ";
    switch (level) {
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
            cout << "Помилка рівня складності." << endl;
            break;
    }

    // Пароль без цифр і спеціальних символів складається лише з літер.
    if (has_digits == "n" && has_special == "n") {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl ;
    }

    return 0;
}