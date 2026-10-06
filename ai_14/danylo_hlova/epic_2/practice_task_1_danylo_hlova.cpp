/*
Task name: Аналізатор надійності пароля
Name: Данило Глова
Group: ШІ-14
*/

#include<iostream>
#include<string>

using namespace std;


int main(){
    //ініціалізація змінних
    int l;
    int level;
    int tp=0;
    char isDigits;
    char isUpper;
    char isSpec;
    string level_name = "";

    cout<< "Довжина пароля: ";
    cin>> l;
     if (l < 1 || l > 64) {
        cout << "Помилка: допустима довжина від 1 до 64." << endl;
        return 0;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> isDigits;
    if (!(isDigits == 'y' || isDigits == 'n')) {
        cout << "Помилка: Відповідь лише 'y' або 'n'." << endl;
        return 0;
    }

    cout << "Чи є великі літери (y/n): ";
    cin >> isUpper;
    if (!(isUpper == 'y' || isUpper == 'n')) {
        cout << "Помилка: Відповідь лише 'y' або 'n'." << endl;
        return 0;
    }
    
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> isSpec;
    if (!(isSpec == 'y' || isSpec == 'n')) {
        cout << "Помилка: Відповідь лише 'y' або 'n'." << endl;
        return 0;
    }

    // визначення рівня надійності

    if(isDigits=='y') tp++;
    if(isUpper=='y') tp++;
    if(isSpec=='y') tp++;

    // Валідація мінімальних вимог
    if (l < 8 || tp < 2) {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }
    else {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    }

    // визначення рівня надійності
    if (l < 6) {
        level = 1;
        level_name = "Дуже слабкий";
    } else if (l < 8 || tp == 0) {
        level = 2;
        level_name = "Слабкий";
    } else if (tp == 1) {
        level = 3;
        level_name = "Середній";
    } else if (l >= 12 && tp == 3) {
        level = 5;
        level_name = "Дуже надійний";
    } else {
        level = 4;
        level_name = "Надійний";
    }

    // Виведення результатів
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

    if (isDigits == 'n' && isSpec == 'n' && isUpper == 'n') {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}

