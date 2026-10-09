/*Епік 2. Задача: Аналізатор надійності пароля
Автор: Матішак Михайло
Група: ШІ-11*/
#include <iostream>

using namespace std;
int main(){

    //змінні
    int length, type = 0, lvl;
    char hasDigits, hasUppercase, hasSpecial;
    bool baseMinimum;

    //зчитування даних
    cout << "Введіть довжину пароля: ";
    cin >> length;

    if (length < 1 || length > 64) {
        cout << "Помилка: довжина пароля має бути від 1 до 64 символів." << endl;  //пароль повинен бути від 1 до 64 символів
        return 1;
    }

    cout << "Чи є цифри у вашому паролі? (y/n): ";
    cin >> hasDigits;

    if (hasDigits == 'y') {
        type++;  //добавляєм рівень пароля якщо є цифри
    }
    else if (hasDigits != 'n') {
        cout << "Помилка: введіть 'y' або 'n'." << endl;
        return 1;
    }

    cout << "Чи є великі літери у вашому паролі? (y/n): ";
    cin >> hasUppercase;

    if (hasUppercase == 'y') {
        type++;    //добавляєм рівень пароля якщо є великі літери
    }
    else if (hasUppercase != 'n') {
        cout << "Помилка: введіть 'y' або 'n'." << endl;
        return 1;
    }

    cout << "Чи є спеціальні символи у вашому паролі? (y/n): ";
    cin >> hasSpecial;

    if (hasSpecial == 'y') {
        type++;  //добавляєм рівень пароля якщо є спеціальні символи
    }
    else if (hasSpecial != 'n') {
        cout << "Помилка: введіть 'y' або 'n'." << endl;
        return 1;
    }

    if (length < 8 || type < 2) {
        baseMinimum = false;
    }
    else {
        baseMinimum = true;
    }

    //вивід даних
    cout << endl;
    cout << "Довжина пароля: " << length << endl;
    cout << "Чи є цифри (y/n): " << hasDigits << endl;
    cout << "Чи є великі літери (y/n): " << hasUppercase << endl;
    cout << "Чи є спеціальні символи (y/n): " << hasSpecial << endl;
    cout << endl;  //пропуск між даними та результатами
    cout << "Мінімальні вимоги: " << (baseMinimum ? "ПРОЙДЕНО" : "НЕ ПРОЙДЕНО") << endl;

    //обчислення рівня надійності пароля
    if (length < 6) {
        lvl = 1;
    }
    else if (length < 8 || type == 0) {
        lvl = 2;
    }
    else if (type == 1) {
        lvl = 3;
    }
    else if (length >= 12 && type == 3) {
        lvl = 5;
    }
    else {
        lvl = 4;
    }
    //вивід рівня надійності пароля
    if (lvl == 1) {
        cout << "Рівень надійності пароля: 1 - Дуже слабкий" << endl;
    }
    else if (lvl == 2) {
        cout << "Рівень надійності пароля: 2 - Слабкий" << endl;
    }
    else if (lvl == 3) {
        cout << "Рівень надійності пароля: 3 - Середній" << endl;
    }
    else if (lvl == 4) {
        cout << "Рівень надійності пароля: 4 - Надійний" << endl;
    }
    else if (lvl == 5) {
        cout << "Рівень надійності пароля: 5 - Дуже надійний" << endl;
    }

    // видача рекомендації
switch (lvl) {
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
        cout << "Рекомендація: Невідомий рівень." << endl;  // на всяк випадок
        break;
}
// додаткове попередження якщо пароль тільки з літер
if (hasDigits == 'n' && hasSpecial == 'n') {
    cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
}
    return 0;
}