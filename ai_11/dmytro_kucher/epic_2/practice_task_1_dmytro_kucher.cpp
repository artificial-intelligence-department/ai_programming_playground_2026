/*
Епік 2. Практичне завдання: Аналізатор надійності пароля
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;

int main() {

    //Оголошуємо змінні
    short length;
    char numbers, letters, symbols;
    int k, r;

    //Вводимо змінні та перевіряємо їх
    cout << "\nДовжина пароля: "; cin >> length;
    if (cin.fail() || length <= 0 || length > 64) {
        cout << "Помилка! Введіть число від 1 до 64\n";
        return 1; }
    
    cout << "Чи є цифри (y/n): "; cin >> numbers;
    if (numbers != 'y' && numbers != 'n') {
        cout << "Помилка! Введіть y або n\n";
        return 1; }
    else if (numbers == 'y') k++;

    cout << "Чи є великі літери (y/n): "; cin >> letters;
    if (letters != 'y' && letters != 'n') {
        cout << "Помилка! Введіть y або n\n";
        return 1; }
    else if (letters == 'y') k++;

    cout << "Чи є спеціальні символи (y/n): "; cin >> symbols;
    if (symbols != 'y' && symbols != 'n') {
        cout << "Помилка! Введіть y або n\n";
        return 1; }
    else if (symbols == 'y') k++;

    cout << endl;

    //Визначаємо рівень надійності пароля
    if (length < 6) r = 1;
    else if (length < 8 || k == 0) r = 2;
    else if (k == 1) r = 3;
    else if (length >= 12 && k == 3) r = 5;
    else r = 4;
    
    //Перевіряємо чи відповідає пароль мінімальним вимогам
    if (length >= 8 && k >=2) cout << "Мінімальні вимоги: ПРОЙДЕНО\n";
    else cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО\n";

    //Виводимо користувачу рівень надійності
    cout << "Рівень надійності: ";
    switch (r) {
        case 1: cout << "Дуже слабкий\n"; break;
        case 2: cout << "Слабкий\n"; break;
        case 3: cout << "Середній\n"; break;
        case 4: cout << "Надійний\n"; break;
        case 5: cout << "Дуже надійний\n"; break;

    }

    //Виводимо користувачу рекомендації щодо пароля
    cout << "Рекомендація: ";
    switch (r) {
        case 1: cout << "Пароль надто короткий. Мінімум 8 символів.\n"; break;
        case 2: cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.\n"; break;
        case 3: cout << "Додайте ще один тип символів або збільште довжину до 12.\n"; break;
        case 4: cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів.\n"; break;
        case 5: cout << "Відмінно. Змінювати нічого не потрібно.\n"; break;

    }

    //Якщо всі літери пароля маленькі, то виводимо користувачу попередження про це
    if (numbers == 'n' && symbols == 'n') cout << "Попередження: пароль тільки з літер підбирається швидше.\n";

    return 0;
}