/* 
Епік 2. Практичне завдання: Аналізатор надійності пароля
Автор: Боднар Василь Іванович
Група: ШІ-12
*/

#include <iostream>

using namespace std;

int main() {

// Отримую дані з якими працюватиму і перевіряю на наявність недопустимих значень
    int len;
    char numb;
    char uCase;
    char symb;
    bool numb_bool;
    bool uCase_bool;
    bool symb_bool;

    cout << "Введіть довжину пароля: ";
    cin >> len;
    if (len < 1 || len > 64) {
        cout << "Помилка: Довжиною пароля повинно бути число від 1 до 64." << endl;
        return 0;
    }
    
    cout << "Чи є в паролі цифри? (y)так /(n)ні: ";
    cin >> numb;
    if (!(numb == 'y') && !(numb == 'n')) {
        cout << "Помилка: відповідь повинна бути y або n." << endl;
        return 0;
    }
    (numb == 'y')? numb_bool = 1 : numb_bool = 0;

    cout << "Чи є в паролі великі літери? (y)так /(n)ні: ";
    cin >> uCase;
    if (!(uCase == 'y') && !(uCase == 'n')) {
        cout << "Помилка: відповідь повинна бути y або n." << endl;
        return 0;
    }
    (uCase == 'y')? uCase_bool = 1 : uCase_bool = 0;

    cout << "Чи є в паролі спеціальні символи? (y)так /(n)ні: ";
    cin >> symb;
    if (!(symb == 'y') && !(symb == 'n')) {
        cout << "Помилка: відповідь повинна бути y або n." << endl;
        return 0;
    }
    (symb == 'y')? symb_bool = 1 : symb_bool = 0;

    int dif_types = numb_bool + uCase_bool + symb_bool;

// Перевірка на відповідність мінімальним вимогам
    if (len < 8 || dif_types < 2) {
        cout << "Не пройдено." << endl;
    }
    else {
        cout << "Пройдено." << endl;
    }

// Визначення рівня надійності пароля
    cout << "Рівень надійності пароля: ";
    int level;
    if (len < 6) {
        cout << "Дуже слабкий." << endl;
        level = 1; 
    }

    else if (len < 8 || dif_types < 0) {
        cout << "Слабкий." << endl;
        level = 2; 
    }

    else if (dif_types == 1) {
        cout << "Середній." << endl;
        level = 3; 
    }

    else if (len >= 12 && dif_types == 3) {
        cout << "Дуже надійнийю" << endl;
        level = 5; 
    }

    else {
        cout << "Надійний." << endl;
        level = 4; 
    }

// Виведення рекомендації на основі надійності пароля
    cout << "Рекомендація: ";
    switch (level) {
        case 1: cout << "Пароль надто короткий. Мінімум 8 символів." << endl;
        break;
    }

    switch (level) {
        case 2: cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
        break;
    }

    switch (level) {
        case 3: cout << "Додайте ще один тип символів або збільште довжину до 12." << endl;
        break;
    }

    switch (level) {
        case 4: cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
        break;
    }

    switch (level) {
        case 5: cout << "Відмінно. Змінювати нічого не потрібно." << endl;
        break;
    }
    return 0;
}