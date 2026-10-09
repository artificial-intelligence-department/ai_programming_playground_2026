#include <iostream>
#include <string>

using namespace std;

int main() {
    // Ініціалізація змінних
    int typeCount = 0;
    int level = 0;
    int length = 0;
    string levelName;
    char hasDigits = '\0', hasUpper = '\0', hasSpecial = '\0';

    // Ввід даних
    cout << "Довжина пароля: ";
    cin >> length;
    if (length < 1 || length > 64) {
        cout << "Помилка: довжина має бути від 1 до 64" << endl;
        return 1;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> hasDigits;
    if (!(hasDigits == 'y' || hasDigits == 'n')) {
        cout << "Помилка: відповідь має бути 'y' або 'n'" << endl;
        return 1;
    }

    cout << "Чи є великі літери (y/n): ";
    cin >> hasUpper;
    if (!(hasUpper == 'y' || hasUpper == 'n')) {
        cout << "Помилка: відповідь має бути 'y' або 'n'." << endl;
        return 1;
    }

    cout << "Чи є спеціальні символи (y/n): ";
    cin >> hasSpecial;
    if (!(hasSpecial == 'y' || hasSpecial == 'n')) {
        cout << "Помилка: відповідь має бути 'y' або 'n'." << endl;
        return 1;
    }

    // Підрахунок кількості типів спеціальних символів
    if (hasDigits == 'y') {
        typeCount++;
    }
    if (hasUpper == 'y') {
        typeCount++;
    }
    if (hasSpecial == 'y') {
        typeCount++;
    }

    // Перевірка мінімальних вимог
    cout << "Мінімальні вимоги: ";
    if (length >= 8 && typeCount >= 2) {
        cout << "ПРОЙДЕНО" << endl;
    } else {
        cout << "НЕ ПРОЙДЕНО" << endl;
    }

    // Визначення рівня безпеки
    if (length < 6) {
        level = 1;
        levelName = "Дуже слабкий";
    } else if (length < 8 || typeCount == 0) {
        level = 2;
        levelName = "Слабкий";
    } else if (typeCount == 1) {
        level = 3;
        levelName = "Середній";
    } else if (length >= 12 && typeCount == 3) {
        level = 5;
        levelName = "Дуже надійний";
    } else {
        level = 4;
        levelName = "Надійний";
    }
    cout << "Рівень надійності: " << level << " - " << levelName << endl;

    // Надання рекомендацій
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
            cout << "Невідомий рівень надійності." << endl;
            break;
    }

    // Виведення попередження
    if (hasDigits == 'n' && hasSpecial == 'n') {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }
    
    return 0;
}