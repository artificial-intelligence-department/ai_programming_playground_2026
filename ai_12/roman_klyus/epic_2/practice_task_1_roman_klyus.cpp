#include <iostream>
#include <string>

using namespace std;

int main() {
    const int min_length = 1;
    const int max_length = 64;

    int length;
    char answer;
    bool has_digits, has_upper, has_symbols;


    cout << "Довжина пароля: ";
    if (!(cin >> length) || length < min_length || length > max_length) {
        cout << "Помилка: довжина пароля мусить бути від " << min_length <<  " до " << max_length << "." << endl;
        return 1;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> answer;
    if (answer != 'y' && answer != 'n') {
        cout << "Помилка: відповідь має бути (y/n).";
        return 1;
    }

    has_digits = (answer == 'y');

    
    cout << "Чи є великі літери (y/n): ";
    cin >> answer;
    if (answer != 'y' && answer != 'n') {
        cout << "Помилка: відповідь має бути (y/n).";
        return 1;
    }

    has_upper = (answer == 'y');


    cout << "Чи є спеціальні символи (y/n): ";
    cin >> answer;
    if (answer != 'y' && answer != 'n') {
        cout << "Помилка: відповідь має бути (y/n).";
        return 1;
    }

    has_symbols = (answer == 'y');

    int count = 0;

    if (has_digits) count++;
    if (has_upper) count++;
    if (has_symbols) count++;

    string min_requirements;

    if (length >= 8 && count >= 2) {
        min_requirements = "ПРОЙДЕНО";
    } else {
        min_requirements = "НЕ ПРОЙДЕНО";
    }

    int level;
    string level_name;

    if (length < 6) {
        level = 1; 
        level_name = "Дуже слабкий";

    } else if (length < 8 && count == 0) {
        level = 2;
        level_name = "Слабкий";

    } else if (count == 1) {
        level = 3;
        level_name = "Середній";

    } else if (length >= 12 && count == 3) {
        level = 5;
        level_name = "Дуже надійний";

    } else {
        level = 4;
        level_name = "Надійний";
    }

    string recommendation;
    switch (level) {
        case 1:
            recommendation = "Пароль надто короткий. Мінімум 8 символів.";
            break;
        case 2:
            recommendation = "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.";
            break;
        case 3:
            recommendation = "Додайте ще один тип символів або збільште довжину до 12.";
            break;
        case 4:
            recommendation = "Хороший пароль. Для максимуму 12+ символів і всі три типи символів.";
            break;
        case 5:
            recommendation = "Відмінно. Змінювати нічого не потрібно.";
            break;
        default:
            recommendation = "Невідомий рівень надійності.";
            break;
    }

    cout << endl;
    cout << "Мінімальні вимоги: " << min_requirements << endl;
    cout << "Рівень надійності: " << level << " - " << level_name << endl;
    cout << "Рекомендація: " << recommendation << endl;

    if (!has_digits && !has_symbols) {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

}