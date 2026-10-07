/*
Назва задачі: Аналізатор надійності пароля
Автор: Олена Кавалер
Група: Ші_13
*/

#include <iostream>
#include <string>

using namespace std;

int main() {

    int p_lenght = 0;
    char number = '0';
    char uppercase = ' ';
    char sp_char = ' ';

    cout << "Введіть довжину пароля (1-64): ";
    cin >> p_lenght;

    // Перевірка допустимого діапазону довжини
    if (p_lenght < 1 || p_lenght > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 1;
    }

    cout << "Чи є цифри? (y/n): ";
    cin >> number;

    // Перевірка коректності введення символу
    if (!(number == 'y' || number == 'n')) {
        cout << "Помилка: введіть 'y' або 'n'." << endl;
        return 1;
    }

    cout << "Чи є великі літери? (y/n): ";
    cin >> uppercase;

    if (!(uppercase == 'y' || uppercase == 'n')) {
        cout << "Помилка: введіть 'y' або 'n'." << endl;
        return 1;
    }

    cout << "Чи є спеціальні символи? (y/n): ";
    cin >> sp_char;

    if (!(sp_char == 'y' || sp_char == 'n')) {
        cout << "Помилка: введіть 'y' або 'n'." << endl;
        return 1;
    }

    // Підраховуємо кількість спеціальних типів символів
    int score = 0;

    if (number == 'y') {
        score += 1;
    }

    if (uppercase == 'y') {
        score += 1;
    }

    if (sp_char == 'y') {
        score += 1;
    }

    // Перевірка мінімальних вимог 
    if (p_lenght >= 8 && score >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    int level = 0;

    // Визначаємо рівень надійності від 1 до 5
    if (p_lenght < 6) {
        cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
        level = 1;
    } 
    else if (p_lenght < 8 || score == 0) {
        cout << "Рівень надійності: 2 - Слабкий" << endl;
        level = 2;
    } 
    else if (score == 1) {
        cout << "Рівень надійності: 3 - Середній" << endl;
        level = 3;
    } 
    else if (p_lenght >= 12 && score == 3) {
        cout << "Рівень надійності: 5 - Дуже надійний" << endl;
        level = 5;
    } 
    else {
        cout << "Рівень надійності: 4 - Надійний" << endl;
        level = 4;
    }

    // Вивід відповідної рекомендації через switch
    switch (level) {
        case 1:
            cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl;
            break;
        case 2:
            cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
            break;
        case 3:
            cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl;
            break;
        case 4:
            cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
            break;
        case 5:
            cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << endl;
            break;
        default:
            cout << "Помилка: невідомий рівень." << endl;
            break;
    }

    // Попередження, якщо використовуються тільки літери
    if (number == 'n' && sp_char == 'n') {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}