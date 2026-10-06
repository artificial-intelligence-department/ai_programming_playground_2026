/* 
Епік 2. Практичне завдання: Аналізатор надійності пароля.
Авторка: Дячок Маргарита.
Група: ШІ-14.
*/

#include <iostream>
using namespace std;

int main() {
const char yes = 'y';
const char no = 'n';
int password_length;
char password_numbers;
char password_caps;
char password_sym;
int min = 0;
int poper = 0; 
int nad;
cout << "Довжина пароля: ";
cin >> password_length;
if ((password_length <= 0) || (password_length > 64)) { //Перевірка довжини
    cout << "Довжина пароля мусить бути від 1 до 64.\n Введіть дійсне значення.";
    return 1;} 
cout << "Чи є цифри: ";
cin >> password_numbers;
if ((password_numbers != yes ) && (password_numbers != no)) {//Перевірка на наявність цифр
    cout << "Введіть дійсне значення.";
    return 1;}
    else if (password_numbers == yes) {min = min + 1; poper = poper + 1;}
    //poper для перевірки чи треба видавати попередження, min для перевірки скільки з 3 умов для символів виконується
cout << "Чи є великі символи: ";
cin >> password_caps;
if ((password_caps != yes ) && (password_caps != no)) { //Перевірка на великі літери
    cout << "Введіть дійсне значення.";
    return 1;} 
else if (password_caps == yes) {min = min + 1;}
cout << "Чи є спеціальні символи: ";
cin >> password_sym;
if ((password_sym != yes ) && (password_sym != no)) {//Перевірка на спеціальні символи
    cout << "Введіть дійсне значення.";
    return 1;}
else if (password_sym == yes) {min = min + 1; poper = poper + 1;}
//Для визначення рівня надійності
if (password_length < 6) {cout << "Рівень надійності пароля: дуже слабкий.\n"; nad = 1;}
else if (password_length < 8 || min == 0) {cout << "Рівень надійності пароля: слабкий.\n"; nad = 2;}
else if (min == 1) {cout << "Рівень надійності пароля: середній.\n"; nad = 3;}
else if (password_length >= 12 && min == 3) {cout << "Рівень надійності пароля: дуже надійний.\n"; nad = 5;}
else {cout << "Рівень надійності пароля: надійний.\n"; nad = 4;}

//Вибір рекомендації
switch(nad) {
    case 1: cout << "Рекомендація: пароль надто короткий. Мінімум 8 символів.\n"; break;
    case 2: cout << "Рекомендація: збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.\n"; break;
    case 3: cout << "Рекомендація: додайте ще один тип символів або збільште довжину до 12.\n"; break;
    case 4: cout << "Рекомендація: хороший пароль. Для максимуму 12+ символів і всі три типи символів.\n"; break;
    case 5: cout << "Рекомендація: відмінно. Змінювати нічого не потрібно.\n"; break;
    default:
    break;
}
//Видає попередження
if (poper == 0) {
    cout << "Попередження: пароль тільки з літер підбирається швидше.\n";
}

//Перевірка на мінімальні вимоги
if ((password_length >= 8) && min >= 2) {cout << "Код пройшов мінімальні вимоги.\n";}
else {cout << "Код не пройшов мінімальні вимоги.\n";}

    return 0;
}