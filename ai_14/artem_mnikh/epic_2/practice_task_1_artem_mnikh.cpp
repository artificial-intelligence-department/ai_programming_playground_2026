/*
Аналізатор надійності пароля
Artem Mnikh
AI_14
*/



#include <iostream>
#include <string>

using namespace std;

int main(){
    // Ініціалізація та валідація вхідних даних
    int length_of_pass;
    char digits_in_pass, uppercase_in_pass, special_symbols;

    cout << "Довжина пароля: ";
    cin >> length_of_pass;
    if (length_of_pass < 1 || length_of_pass > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64" << "\n";
        return 1;   }
    cout << "Чи є цифри (y/n): ";
    cin >> digits_in_pass;
    if (digits_in_pass != 'y' && digits_in_pass != 'n') {
        cout << "Помилка: відповідь мусить бути 'y' або 'n'" << "\n";
        return 1;   }
      cout << "Чи є великі літери (y/n): ";
    cin >> uppercase_in_pass;
    if (uppercase_in_pass != 'y' && uppercase_in_pass != 'n') {
        cout << "Помилка: відповідь мусить бути 'y' або 'n'" << "\n";
        return 1;   }
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> special_symbols;
    if (!(special_symbols == 'y' || special_symbols == 'n')) {
        cout << "Помилка: відповідь мусить бути 'y' або 'n'" << "\n";
        return 1;   }

    // Визначення кількості типів символів
    int counter = 0;
    if (digits_in_pass == 'y') counter++;
    if (uppercase_in_pass == 'y') counter++;
    if (special_symbols == 'y') counter++;

    // Перевірка мінімальних вимог
    if (length_of_pass >= 8 && counter >= 2){
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << "\n";
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << "\n"; }
    
    // Ініціалізація змінних для визначення рівня надійності
    int level;
    string level_name;
    // Визначення рівня надійності
     if (length_of_pass < 6) {
        level = 1;
        level_name = "Дуже слабкий";
    } else if (length_of_pass < 8 || counter == 0) {
        level = 2;
        level_name = "Слабкий";
    } else if (counter == 1) {
        level = 3;
        level_name = "Середній";
    } else if (length_of_pass >= 12 && counter == 3) {
        level = 5;
        level_name = "Дуже надійний";
    } else {
        level = 4;
        level_name = "Надійний";
    }

    // Виведення рівня надійності та рекомендацій
    cout << "Рівень надійності: " << level << " - " << level_name << "\n";
    switch (level) {
        case 1:
            cout << "Пароль надто короткий. Мінімум 8 символів." << "\n";
            break;
        case 2:
            cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << "\n";
            break;
        case 3:
            cout << "Додайте ще один тип символів або збільште довжину до 12." << "\n";
            break;
        case 4:
            cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << "\n";
            break;
        case 5:
            cout << "Відмінно. Змінювати нічого не потрібно." << "\n";
            break;
    }
    if (!(counter) || (uppercase_in_pass == 'y' && counter == 1)) cout << "Попередження: пароль тільки з літер підбирається швидше." << "\n";
    return 0;
}