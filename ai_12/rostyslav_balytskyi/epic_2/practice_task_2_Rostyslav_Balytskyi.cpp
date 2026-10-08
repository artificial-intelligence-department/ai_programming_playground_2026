#include <iostream>
#include <string>

using namespace std ;

int main() {


// Введення довжини пароля
int length;
cout << "Довжина пароля: ";
cin >> length;

    if (length < 1|| length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
            return 0;
    }

// Введення наявності цифр
char number;
cout << "Чи є цифри (y/n)? ";
cin >> number;

    if (!(number == 'y' || number == 'n')) {
        cout << "Помилка: введіть 'y' або 'n'." << endl;
            return 0;
    }

// Введення наявності великих літер
char bigletter;
cout << "Чи є великі літери (y/n)? "; 
cin >> bigletter;

    if (!(bigletter == 'y' || bigletter == 'n')) {
        cout << "Помилка: введіть 'y' або 'n'." << endl;
            return 0;
    }

// Введення наявності спеціальних символів
char specialsymbol;
cout << "Чи є спеціальні символи (y/n)? ";
cin >> specialsymbol;

    if (!(specialsymbol == 'y' || specialsymbol == 'n')) {
        cout << "Помилка: введіть 'y' або 'n'." << endl;
            return 0;
    }

// Підрахунок кількості типів символів
int types = 0;
if (number == 'y') types++;
if (bigletter == 'y') types++;
if (specialsymbol == 'y') types++;

// Перевірка мінімальних вимог
cout << endl;
cout << "Мінамальні вимоги: ";
    if (length >= 8 && types >= 2) {
        cout << "Пройдено" << endl;
    } else {
        cout << "Не пройдено" << endl;
    }

// Визначення рівня надійності
int level = 0;
string levelname = "";

if (length < 6) {
    level = 1;
        levelname = "Дуже слабкий";
}
else if (length < 8 || types == 0) {
    level = 2;
        levelname = "Cлабкий";
}
else if (types == 1) {
    level = 3;
        levelname = "Середній";
} 
else if (length >= 12 && types == 3) { // Використання оператора AND (&&)
    level = 5;
        levelname = "Дуже надійний";
} 
else {
    level = 4;
        levelname = "Надійний";
}
cout << "Рівень надійності: " << level << " - " << levelname << endl;

// Рекомендація за допомогою switch case
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
}

if (number == 'n' && specialsymbol == 'n') {
    cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
}

return 0;
}