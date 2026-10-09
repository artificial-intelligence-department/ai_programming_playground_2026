#include <iostream>
using namespace std;

int main() {
    int pass_length = 0;
    char num = 0;
    char caps = 0;
    char symb = 0;

    // 1. Ввід даних та валідація
    cout << "Довжина пароля: ";
    cin >> pass_length;
    if (pass_length < 1 || pass_length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64.\n";
        return 0;
    }

    cout << "Чи є цифри? (y/n): ";
    cin >> num;
    if (num != 'y' && num != 'n' && num != 'Y' && num != 'N') {
        cout << "Помилка введення значень!\n";
        return 0;
    }

    cout << "Чи є великі літери? (y/n): ";
    cin >> caps;
    if (caps != 'y' && caps != 'n' && caps != 'Y' && caps != 'N') {
        cout << "Помилка введення значень!\n";
        return 0;
    }

    cout << "Чи є спеціальні символи? (y/n): ";
    cin >> symb;
    if (symb != 'y' && symb != 'n' && symb != 'Y' && symb != 'N') {
        cout << "Помилка введення значень!\n";
        return 0;
    }

    // 2. Підрахунок кількості типів символів (0..3)
    int types_count = 0;
    if (num == 'y' || num == 'Y') types_count++;
    if (caps == 'y' || caps == 'Y') types_count++;
    if (symb == 'y' || symb == 'Y') types_count++;

    // 3. Мінімальні вимоги (if / else)
    if (pass_length >= 8 && types_count >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО\n";
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО\n";
    }

    // 4. Визначення рівня надійності (if, else if)
    int level = 0;
    string level_name = "";

    if (pass_length < 6) {
        level = 1;
        level_name = "Дуже слабкий";
    } else if (pass_length < 8 || types_count == 0) {
        level = 2;
        level_name = "Слабкий";
    } else if (types_count == 1) {
        level = 3;
        level_name = "Середній";
    } else if (pass_length >= 12 && types_count == 3) {
        level = 5;
        level_name = "Дуже надійний";
    } else {
        level = 4;
        level_name = "Надійний";
    }

    cout << "Рівень надійності: " << level << " " << level_name << endl;

    // 5. Рекомендація
    cout << "Рекомендація: ";
    switch (level) {
        case 1:
            cout << "Пароль надто короткий. Мінімум 8 символів.\n";
            break;
        case 2:
            cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.\n";
            break;
        case 3:
            cout << "Додайте ще один тип символів або збільште довжину до 12.\n";
            break;
        case 4:
            cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів.\n";
            break;
        case 5:
            cout << "Відмінно. Змінювати нічого не потрібно.\n";
            break;
        default:
            cout << "Невідомий рівень надійності.\n";
    }

    // 6. Попередження
    bool has_any_extra = (num == 'y' || num == 'Y' || caps == 'y' || caps == 'Y' || symb == 'y' || symb == 'Y');
    if (!has_any_extra) {
        cout << "Попередження: пароль тільки з літер підбирається швидше.\n";
    }

    return 0;
}