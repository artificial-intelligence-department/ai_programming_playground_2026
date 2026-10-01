/*  
Аналізатор надійності пароля
Ярошенко Володимир 
11 група 
*/
#include <iostream>

using namespace std;

int main() {
int lenght;
char nums, U_sym, Sp_sym; // Створюєм кількість типів символів 
int level = 0; // Рівень надійності паролю
const int min_lenght = 0; // мінімальні обмеження вводу
const int max_lenght = 64; // максимальні обмеження вводу
const int psw_min_lenght = 8; // мінімальна довжина паролю 
const int psw_lenght = 6; // довжина паролю для 1 рівня надійності 
const int psw_lvl_lenght = 12; // довжина паролю для 5 рівню надійності 

cout << "Введіть довжину: " << endl;
cin >> lenght;
if(lenght < min_lenght && lenght > max_lenght) {
    cout << "Введіть коректне значення довжини" << endl;
    return -1;
}
cout << "Чи є цифри: " << endl;
cin >> nums;
if(nums != 'y' && nums != 'n') {
    cout << "Введіть коректне значення цифр" << endl;
    return -1;
}
cout << "Чи є великі літери: " << endl;
cin >> U_sym;
if(U_sym != 'y' && U_sym != 'n') {
    cout << "Введіть коректне значення великих літер" << endl;
    return -1;
}
cout << "Чи є спеціальні символи: " << endl;
cin >> Sp_sym;
if(Sp_sym != 'y' && Sp_sym != 'n') {
    cout << "Введіть коректне значення спеціальних символів" << endl;
    return -1;
}
/* 
Вводимо дані,
Перевіряємо чи допустимі значення
*/

if(lenght >= psw_min_lenght && nums == 'y'   && U_sym == 'y') {
    cout <<  "Мінімальні вимоги: ПРОЙДЕНО" << endl;
}
 else if(lenght >= psw_min_lenght && nums == 'y'   && Sp_sym == 'y') {
    cout <<  "Мінімальні вимоги: ПРОЙДЕНО" << endl;
}
 else if(lenght >= psw_min_lenght && U_sym == 'y'   && Sp_sym == 'y') {
    cout <<  "Мінімальні вимоги: ПРОЙДЕНО" << endl;
}
else {
    cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
}
/* 
Перевіряємо чи пройдено мінімальні умови згідно умови задачі
Користуємось операторами if, esle if, та логічними операторами кон'юкції(&&) та диз'юнкції(||)
*/

if(lenght < psw_lenght) {
    level = 1;
    cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
}
else if(lenght < psw_min_lenght ||( nums == 'n' && U_sym == 'n' && Sp_sym == 'n')) {
    level = 2;
    cout << "Рівень надійності: 2 - Слабкий" << endl;
}
else if(nums == 'y' && U_sym == 'n' &&  Sp_sym == 'n') {
 level = 3;
    cout << "Рівень надійності: 3 - Середній" << endl;
}
else if(nums == 'n' && U_sym == 'y' &&  Sp_sym == 'n') {
 level = 3;
    cout << "Рівень надійності: 3 - Середній" << endl;
}
else if(nums == 'n' && U_sym == 'n' &&  Sp_sym == 'y') {
 level = 3;
    cout << "Рівень надійності: 3 - Середній" << endl;
}
else if(lenght > psw_lvl_lenght && nums == 'y' && U_sym == 'y' && Sp_sym == 'y') {
    level = 5;
    cout << "Рівень надійності: 5 - Дуже надійний" << endl;
}
else {
    level = 4; 
    cout << "Рівень надійності: 4 - Надійний" << endl;
}
/* 
Перевіряємо рівень надійності паролю 
Користуємось операторами if, esle if, та логічними операторами кон'юкції(&&) та диз'юнкції(||)
*/
switch(level)  {
case 1 : {
    cout << "Пароль надто короткий. Мінімум 8 символів" << endl;
    break;
}
case 2 : {
    cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи" << endl;
    break;
}
case 3 : {
    cout << "Додайте ще один тип символів або збільште довжину до 12" << endl;
    break;
}
case 4 : {
    cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів" << endl;
    break;
}
case 5 : {
    cout << "Відмінно. Змінювати нічого не потрібно" << endl;
    break;
}
    default: 
    cout << "Неправильний рівень надійності паролю" << endl;
}    
/* 
Даєм рекомендації щодо надійності паролю
Користуємось операторами switch() {case}
*/

if(nums == 'n' && U_sym == 'n' && Sp_sym == 'n') {
    cout << "Пароль тільки з літер підбирається швидше" << endl; // Перевіряєм чи потрібно попередження та виводим його 
}
    return 0;
}