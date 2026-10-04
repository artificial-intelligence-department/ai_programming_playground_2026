/*
Аналізатор надійності пароля
Карпінський Віталій
СШІ-14
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    // Ініціалізація змінних
    int length;
    char numbers;
    char upChars;
    char specialChars;

    // Введення та перевірка даних
    cout << "Довжина пароля: ";
    cin >> length;

    if (length < 1 || length > 64) {
        cout << "Помилка: довжина пароля повинна бути від 1 до 64 символів." << endl;
        return 0;
    }
    // Введення та перевірка даних
    cout << "Чи є цифри (y/n): ";
    cin >> numbers;

    if (!(numbers == 'y' || numbers == 'n')) {
        cout << "Помилка: відповідь повинна бути y або n" << endl;
        return 0;
    }
    // Введення та перевірка даних
    cout << "Чи є великі літери (y/n): ";
    cin >> upChars;

    if (!(upChars == 'y' || upChars == 'n')) {
        cout << "Помилка: відповідь повинна бути y або n" << endl;
        return 0;
    }
    // Введення та перевірка даних
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> specialChars;
    cout << endl;

    if (!(specialChars == 'y' || specialChars == 'n')) {
        cout << "Помилка: відповідь повинна бути y або n" << endl;
        return 0;
    }
    // Перевірка кількості типів символів
    int score = 0;
    if (numbers == 'y') {
        score++;
    }

    if (upChars == 'y') {
        score++;
    }

    if (specialChars == 'y') {
        score++;
    }
    // Проходить/не проходить мінімальні вимоги
    if (length >= 8 && score >= 2) {
        cout << "Пароль проходить мінімальні вимоги" << endl;
    } else {
        cout << "Пароль не проходить мінімальні вимоги" << endl;
    }

    string lvlname;
    int lvl;
    // Визначення рівня надійності
    if (length < 6) {
        lvlname = "Дуже слабкий";
        lvl = 1;
    } else if (length < 8 || score == 0) {
        lvlname = "Слабкий";
        lvl = 2;
    } else if (score == 1) {
        lvlname = "Середній";
        lvl = 3;
    } else if (length >= 12 && score == 3) {
        lvlname = "Дуже надійний";
        lvl = 5;
    } else {
        lvlname = "Надійний";
        lvl = 4;
    }
    cout << "Рівень надійності: " << lvl << " - " << lvlname << endl;
    // Надання рекомендації
    cout << "Рекомендація: ";
    switch (lvl) {
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

    if (numbers == 'n' && specialChars == 'n') {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }
    
    return 0;
    
}