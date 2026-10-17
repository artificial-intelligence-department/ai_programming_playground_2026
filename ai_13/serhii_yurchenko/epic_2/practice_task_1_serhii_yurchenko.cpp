#include <iostream>
#include <string>

using namespace std;

int main() {
    int length;
    string answer;

    // ---------- Ввід та валідація ----------
    cout << "Довжина пароля: ";
    // NOT: якщо ввід не є числом, cin переходить у стан помилки
    if (!(cin >> length) || length < 1 || length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 0;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> answer;
    if (answer != "y" && answer != "n") {
        cout << "Помилка: введіть y або n." << endl;
        return 0;
    }
    bool hasDigits = (answer == "y");

    cout << "Чи є великі літери (y/n): ";
    cin >> answer;
    if (answer != "y" && answer != "n") {
        cout << "Помилка: введіть y або n." << endl;
        return 0;
    }
    bool hasUpper = (answer == "y");

    cout << "Чи є спеціальні символи (y/n): ";
    cin >> answer;
    if (answer != "y" && answer != "n") {
        cout << "Помилка: введіть y або n." << endl;
        return 0;
    }
    bool hasSpecial = (answer == "y");

    // ---------- Кількість типів символів (0..3) ----------
    int types = 0;
    if (hasDigits) types++;
    if (hasUpper) types++;
    if (hasSpecial) types++;

    cout << endl;

    // ---------- Мінімальні вимоги (if else) ----------
    // AND: потрібні обидві умови одночасно
    if (length >= 8 && types >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    // ---------- Рівень надійності (if, else if) ----------
    // Правила перевіряються зверху вниз, перше що спрацювало визначає рівень
    int level;
    string levelName;

    if (length < 6) {
        level = 1;
        levelName = "Дуже слабкий";
    } else if (length < 8 || types == 0) {          // OR
        level = 2;
        levelName = "Слабкий";
    } else if (types == 1) {
        level = 3;
        levelName = "Середній";
    } else if (length >= 12 && types == 3) {        // AND
        level = 5;
        levelName = "Дуже надійний";
    } else {
        level = 4;
        levelName = "Надійний";
    }

    cout << "Рівень надійності: " << level << " - " << levelName << endl;

    // ---------- Рекомендація (switch case) ----------
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

    // ---------- Попередження ----------
    // NOT: немає ні цифр, ні спецсимволів, тобто пароль лише з літер
    if (!hasDigits && !hasSpecial) {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}