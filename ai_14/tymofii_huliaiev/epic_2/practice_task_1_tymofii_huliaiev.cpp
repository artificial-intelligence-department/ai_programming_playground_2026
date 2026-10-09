#include <iostream>
#include <string>

using namespace std;

int main() {
    system("chcp 65001 > nul");
    
    int length;
    string has_digits, has_upper, has_special;

    // Введення даних з підказками
    cout << "Довжина пароля: ";
    cin >> length;

    // Валідація довжини пароля (від 1 до 64)
    if (length < 1 || length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 0;
    }

    cout << "Чи є цифри (yes/no): ";
    cin >> has_digits;
    if (has_digits != "yes" && has_digits != "no") {
        cout << "Помилка: введіть рівно yes або no." << endl;
        return 0;
    }

    cout << "Чи є великі літери (yes/no): ";
    cin >> has_upper;
    if (has_upper != "yes" && has_upper != "no") {
        cout << "Помилка: введіть рівно yes або no." << endl;
        return 0;
    }

    cout << "Чи є спеціальні символи (yes/no): ";
    cin >> has_special;
    if (has_special != "yes" && has_special != "no") {
        cout << "Помилка: введіть рівно yes або no." << endl;
        return 0;
    }

    // Підрахунок кількості типів символів (від 0 до 3)
    int types_count = 0;
    if (has_digits == "yes") types_count++;
    if (has_upper == "yes") types_count++;
    if (has_special == "yes") types_count++;

    // Перевірка мінімальних вимог 
    bool meets_min_req = false;
    if (length >= 8 && types_count >= 2) {
        meets_min_req = true;
        cout << "\nМінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        meets_min_req = false;
        cout << "\nМінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    // Визначення рівня надійності 
    int level = 0;
    string level_name = "";

    // Довжина менше 6
    if (length < 6) {
        level = 1;
        level_name = "Дуже слабкий";
    }
    // Довжина менше 8 АБО типів символів 0
    else if (length < 8 || types_count == 0) {
        level = 2;
        level_name = "Слабкий";
    }
    // Типів символів рівно 1
    else if (types_count == 1) {
        level = 3;
        level_name = "Середній";
    }
    // Довжина 12 і більше і типів символів рівно 3
    else if (length >= 12 && types_count == 3) {
        level = 5;
        level_name = "Дуже надійний";
    }
    // Усі інші випадки
    else {
        level = 4;
        level_name = "Надійний";
    }

    cout << "Рівень надійності: " << level << " - " << level_name << endl;

    // Вивід рекомендації
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
            cout << "Помилка визначення рівня." << endl;
            break;
    }

    // Вивід попередження, якщо пароль тільки з літер
    if (!types_count) { 
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}