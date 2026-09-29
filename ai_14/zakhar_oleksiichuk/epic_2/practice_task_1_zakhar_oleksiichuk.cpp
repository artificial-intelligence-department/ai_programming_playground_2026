/*
Task name: Аналізатор надійності пароля
Name: Захар Олексійчук
Group: ШІ-14 (ai_14)
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    // Ініціалізація
    int length = 0;
    char digitsPresent = 'n';
    char uppercasePresent = 'n';
    char specialSymbolsPresent = 'n';


    // Введення даних та валідація
    cout << "Довжина пароля: ";
    cin >> length;

    if (length < 1 || length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 0;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> digitsPresent;
    if (!(digitsPresent == 'y' || digitsPresent == 'n')) {
        cout << "Помилка: відповідь мусить бути 'y' або 'n'." << endl;
        return 0;
    }

    cout << "Чи є великі літери (y/n): ";
    cin >> uppercasePresent;
    if (!(uppercasePresent == 'y' || uppercasePresent == 'n')) {
        cout << "Помилка: відповідь мусить бути 'y' або 'n'." << endl;
        return 0;
    }

    cout << "Чи є спеціальні символи (y/n): ";
    cin >> specialSymbolsPresent;
    if (!(specialSymbolsPresent == 'y' || specialSymbolsPresent == 'n')) {
        cout << "Помилка: відповідь мусить бути 'y' або 'n'." << endl;
        return 0;
    }


    // Підрахунок типів
    int typesCount = 0;
    if (digitsPresent == 'y') typesCount++;
    if (uppercasePresent == 'y') typesCount++;
    if (specialSymbolsPresent == 'y') typesCount++;

    // Валідація мінмальнмх вимог
    if (length < 8 || typesCount < 2) {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }
    else {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    }


    // Визначення рівня безпеки
    int level = 0;
    string level_name = "";

    if (length < 6) {
        level = 1;
        level_name = "Дуже слабкий";
    } else if (length < 8 || typesCount == 0) {
        level = 2;
        level_name = "Слабкий";
    } else if (typesCount == 1) {
        level = 3;
        level_name = "Середній";
    } else if (length >= 12 && typesCount == 3) {
        level = 5;
        level_name = "Дуже надійний";
    } else {
        level = 4;
        level_name = "Надійний";
    }

    // Виведення рузультатів
    cout << "Рівень надійності: " << level << " - " << level_name << endl;

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

    if (digitsPresent == 'n' && specialSymbolsPresent == 'n' && uppercasePresent == 'n') {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}