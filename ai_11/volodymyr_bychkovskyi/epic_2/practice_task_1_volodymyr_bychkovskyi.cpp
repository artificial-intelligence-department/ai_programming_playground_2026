/*
Назва: Epic 2 - Practice Task "Аналізатор надійності пароля"
Автор: Бичковський Володимир
Група: ШІ-11
*/

#include <iostream> // Для введення та виведення даних
#include <string>   // Для роботи з рядками
#include <clocale>  // Для налаштування мови консолі

using namespace std; // Стандартний простір імен

int main() {
    setlocale(LC_ALL, "uk_UA"); // Встановлення української мови
    
    int length;     // Довжина
    int types = 0;  // Кількість типів символів
    int level;      // Рівень надійності

    char number;      // Наявність цифр
    char big_letter;  // Наявність великих літер
    char specials;    // Наявність спецсимволів

    string min_requirements; // Мінімальні вимоги
    string level_name;       // Назва рівня
    string recommendation;   // Рекомендація

    
    // Введення довжини
    cout << "Введіть довжину пароля: ";
    cin >> length;
    if (length > 64 || length < 1) {
        cout << "Помилка: довжина пароля повинна бути від 1 до 64 символів." << endl;
        return 1; 
    }

    // Введення цифр
    cout << "Чи є в паролі цифри (y/n): ";
    cin >> number;
    if (number != 'y' && number != 'n') {
        cout << "Помилка: введіть дійсне значення." << endl;
        return 1; 
    }
    
    // Введення великих літер 
    cout << "Чи є в паролі великі літери (y/n): ";
    cin >> big_letter;
    if (big_letter != 'y' && big_letter != 'n') {
        cout << "Помилка: введіть дійсне значення." << endl;
        return 1; 
    }

    // Введення спецсимволів
    cout << "Чи є в паролі спецсимволи (y/n): ";
    cin >> specials;
    if (specials != 'y' && specials != 'n') {
        cout << "Помилка: введіть дійсне значення." << endl;
        return 1; 
    }

    // Підрахунок типів символів
    if (number == 'y') {
        types++;
    }
    if (big_letter == 'y') {
        types++;
    }
    if (specials == 'y') {
        types++;
    }

    // Перевірка мінімальних вимог
    if (length >= 8 && types >= 2) {
        min_requirements = "ПРОЙДЕНО";
    } else {
        min_requirements = "НЕ ПРОЙДЕНО";
    }

    // Визначення рівня
    if (length < 6) {
        level = 1;
    }
    else if (length < 8 || types == 0) {
        level = 2;
    }
    else if (types == 1) {
        level = 3;
    }
    else if (length >= 12 && types == 3) { 
        level = 5;
    }
    else {
        level = 4;
    }

    // Текстові розшифровки рівня
    switch (level) {
    case 1:
        level_name = "Дуже слабкий";
        recommendation = "Пароль надто короткий. Мінімум 8 символів.";
        break;
    case 2:
        level_name = "Слабкий";
        recommendation = "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.";
        break;
    case 3:
        level_name = "Середній";
        recommendation = "Додайте ще один тип символів або збільште довжину до 12.";
        break;
    case 4:
        level_name = "Надійний";
        recommendation = "Хороший пароль. Для максимуму 12+ символів і всі три типи символів.";
        break;
    case 5:
        level_name = "Дуже надійний";
        recommendation = "Відмінно. Змінювати нічого не потрібно.";
        break;
    default:
        level_name = "Невідомий";
        recommendation = "Помилка обчислення рівня";
        break;
    }

    // Підсумкове виведення
    cout << "Мінімальні вимоги: " << min_requirements << endl;
    cout << "Рівень надійності: " << level << " - " << level_name << endl;
    cout << "Рекомендація: " << recommendation << endl;

    // Перевірка для попередження
    if (number == 'n' && specials == 'n') {
        cout << "Попередження: Пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}