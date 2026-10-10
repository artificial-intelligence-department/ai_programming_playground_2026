#include <iostream>
#include <string>

using namespace std;

int main() {
    int length;
    char digits, upper, special;

    // Введення даних
    cout << "Довжина пароля: ";
    cin >> length;
    cout << "Чи є цифри: ";
    cin >> digits;
    cout << "Чи є великі літери: ";
    cin >> upper;
    cout << "Чи є спеціальні символи: ";
    cin >> special;

    // Перевірка довжини
    if (length < 1 || length > 64) {
        cout << "Помилка" << endl;
        return 1;
    }

    // Перевірка символів
    if (!(digits == 'y' || digits == 'n') ||
        !(upper == 'y' || upper == 'n') ||
        !(special == 'y' || special == 'n')) {
        cout << "Помилка" << endl;
        return 1;
    }

    // Рахуємо кількість типів символів
    int types = 0;
    if (digits == 'y') types++;
    if (upper == 'y') types++;
    if (special == 'y') types++;

    // Мінімальні вимоги
    if (length >= 8 && types >= 2) {
        cout << "Мінімальні вимоги: проходить" << endl;
    } else {
        cout << "Мінімальні вимоги: не проходить" << endl;
    }

    // Рівень надійності
    int level;
    string name;
    if (length < 6) {
        level = 1;
        name = "Дуже слабкий";
    } else if (length < 8 || types == 0) {
        level = 2;
        name = "Слабкий";
    } else if (types == 1) {
        level = 3;
        name = "Середній";
    }  else if (length < 12 || types < 3) {
        level = 4;
        name = "Надійний";
    } else {
        level = 5;
        name = "Дуже надійний";
    }

    cout << "Рівень надійності: " << level << " (" << name << ")" << endl;

    // Рекомендація
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
            cout << "Невідомий рівень." << endl;
            break;
    }

    return 0;
}