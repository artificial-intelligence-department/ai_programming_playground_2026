#include <iostream>

using namespace std;

int main() {
    // Оголошення змінних для вхідних даних
    int length;     //довжина пароля
    char numbers, capsLaters, special;     // цифри, великі літери, спецііальні символи

    // Зчитування даних
    cout << "Довжина пароля: ";
    cin >> length;

    // Перевірка коректності введення даних
    if (!(length >= 1 && length <= 64)) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 0; 
    }

    cout << "Чи є цифри (y/n): ";
    cin >> numbers;
    if (numbers != 'y' && numbers != 'n') {
        cout << "Помилка: введіть 'y' або 'n'." << endl;
        return 0;
    }

    cout << "Чи є великі літери (y/n): ";
    cin >> capsLaters;
    if (capsLaters != 'y' && capsLaters != 'n') {
        cout << "Помилка: введіть 'y' або 'n'." << endl;
        return 0;
    }

    cout << "Чи є спеціальні символи (y/n): ";
    cin >> special;
    if (special != 'y' && special != 'n') {
        cout << "Помилка: введіть 'y' або 'n'." << endl;
        return 0;
    }

    // Підрахунок кількості типів символів
    int typesCount = 0;
    if (numbers == 'y') typesCount++;
    if (capsLaters == 'y') typesCount++;
    if (special == 'y') typesCount++;

    cout << endl;

    // Перевірка мінімальних вимог 
    if (length >= 8 && typesCount >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    // рівень надійності 
    int level = 0;

    cout << "Рівень надійності: ";

    if (length < 6) {
        level = 1; 
        cout << "1 - Дуже слабкий" << endl;
    } else if (length < 8 || typesCount == 0) {
        level = 2; 
        cout << "2 - Слабкий" << endl;
    } else if (typesCount == 1) {
        level = 3; 
        cout << "3 - Середній" << endl;
    } else if (length >= 12 && typesCount == 3) {
        level = 5; 
        cout << "5 - Дуже надійний" << endl;
    } else {
        level = 4; 
        cout << "4 - Надійний" << endl;
    }

    // Виведення рекомендації
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
            cout << "Невідомий рівень." << endl;
            break;
    }

    // Перевірка і попередження(у разі якщо пароль лише з літер)
    if (numbers == 'n') {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}