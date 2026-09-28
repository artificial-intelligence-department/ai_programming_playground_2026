/*
Задача: Аналізатор надійності пароля
 Рудь Дмитро
 Група СШІ-11
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
    int len;
    string _1;
    string _A;
    string _special;
    int n = 0;
    string min_req;
    string lvl;
    string recomendation;

    cout << "Довжина пароля: ";
    cin >> len;
    if (len < 1 or len > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 0;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> _1;
    // логічний NOT: перевіряємо, що це НЕ (y або n)
    if (!(_1 == "y" or _1 == "n")) {
        cout << "Помилка: значення може бути лише y або n" << endl;
        return 0;
    }
    if (_1 == "y") {
        n++;
    }

    cout << "Чи є великі літери (y/n): ";
    cin >> _A;
    if (!(_A == "y" or _A == "n")) {
        cout << "Помилка: значення може бути лише y або n" << endl;
        return 0;
    }
    if (_A == "y") {
        n++;
    }

    cout << "Чи є спеціальні символи (y/n): ";
    cin >> _special;
    if (!(_special == "y" or _special == "n")) {
        cout << "Помилка: значення може бути лише y або n" << endl;
        return 0;
    }
    if (_special == "y") {
        n++;
    }

    //перевірка на проходження мінімальних вимог
    if (len >= 8 and n >= 2) {
        min_req = "ПРОЙДЕНО";
    } else {
        min_req = "НЕ ПРОЙДЕНО";
    }

    //перевірка на рівень надійності
    int level;
    if (len < 6) {
        level = 1;
        lvl = "1 - Дуже слабкий";
    }
    else if (len < 8 or n == 0) {
        level = 2;
        lvl = "2 - Слабкий";
    }
    else if (n == 1) {
        level = 3;
        lvl = "3 - Середній";
    }
    else if (len >= 12 and n == 3) {
        level = 5;
        lvl = "5 - Дуже надійний";
    }
    else {
        level = 4;
        lvl = "4 - Надійний";
    }

    //видача рекомендації за рівнем
    switch (level) {
        case 1:
            recomendation = "Пароль надто короткий. Мінімум 8 символів.";
            break;
        case 2:
            recomendation = "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.";
            break;
        case 3:
            recomendation = "Додайте ще один тип символів або збільште довжину до 12.";
            break;
        case 4:
            recomendation = "Хороший пароль. Для максимуму 12+ символів і всі три типи символів.";
            break;
        case 5:
            recomendation = "Відмінно. Змінювати нічого не потрібно.";
            break;
        default:
            recomendation = "Помилка визначення рівня.";
            break;
    }

    cout << "Мінімальні вимоги: " << min_req << endl;
    cout << "Рівень надійності: " << lvl << endl;
    cout << "Рекомендація: " << recomendation << endl;
    if (n == 0) {
        cout << "Попередження: пароль тільки з літер підбирається швидше. " << endl;
    }
}