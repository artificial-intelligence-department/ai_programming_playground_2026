/* Задача: Practice task 1
Хробуст Андрій
Група ШІ - 11
*/
#include <iostream>
using namespace std;

int main() {
    int length;
    char digits;
    char uppercase;
    char special;
    int types = 0;
    int level;
    cout << "Довжина пароля: ";
    cin >> length;//ввід довжини
    if (length < 1 || length > 64) {//перевірка довжини
        cout << "Довжина пароля: " << length << endl;
        cout << "Помилка: довжина мусить бути від 1 до 64.";
        return 0;
    }
    cout << "Чи є цифри (y/n): ";
    cin >> digits;//перевірка наявності цифр
    cout << "Чи є великі літери (y/n): ";
    cin >> uppercase;//перевірка наявності великих літер
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> special;//перевірка наявності спеціальних символів
    if ((digits != 'y' && digits != 'n') ||   //перевірка правильності вводу
        (uppercase != 'y' && uppercase != 'n') ||
        (special != 'y' && special != 'n')) {
        cout << "Помилка: потрібно вводити тільки y a6o n.";
        return 0;
    }
    if (digits == 'y') {//перевірка кількості типів символів
        types++;
    }
    if (uppercase == 'y') {
        types++;
    }
    if (special == 'y') {
        types++;
    }
    if (length >= 8 && types >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    }
    else {
        cout << "Мінімальні вимоги: HE ПРОЙДЕНО" << endl;
    }
    if (length < 6) { // дуже слабкий пароль
        level = 1;
    }
    else if (length < 8 || types == 0) {//слабкий пароль
        level = 2;
    }
    else if (types == 1) {//середній пароль
        level = 3;
    }
    else if (length >= 12 && types == 3) {//дуже надійний пароль
        level = 5;
    }
    else {
        level = 4;//надійний пароль
    }

    cout << "Рівень надійності: ";//вивід надійності пароля
    switch (level) {
        case 1:
            cout << "1 - Дуже слабкий" << endl;
            break;
        case 2:
            cout << "2 - Слабкий" << endl;
            break;
        case 3:
            cout << "3 - Середній" << endl;
            break;
        case 4:
            cout << "4 - Надійний" << endl;
            break;
        case 5:
            cout << "5 - Дуже надійний" << endl;
            break;
    }
    cout << "Рекомендація: ";//вивід рекомендації
    switch (level) {
        case 1:
            cout << "Пароль надто короткий. Мінімум 8 символів.";
            break;
        case 2:
            cout << "Збільшіть довжину до 8+ символів i додайте цифри, великі літери або спеціальні символи.";
            break;
        case 3:
            cout << "Додайте ще один тип символів a6o збільшіть довжину до 12.";
            break;
        case 4:
            cout << "Хороший пароль. Для максимуму 12+ символів i всі три типи символів.";
            break;
        case 5:
            cout << "Відмінно. Змінювати нічого не потрібно.";
            break;
    }

    return 0;
}