#include <iostream>
 // #include <string>

using namespace std;

int main() {
int lenght;
char nums, U_sym, Sp_sym;
int level = 0;
cout << "Введіть довжину: " << endl;
cin >> lenght;
if(lenght<0 && lenght > 64) {
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

 /*if(lenght <8 && nums == 'n' && U_sym == 'n' && Sp_sym == 'n') {
    cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
}
else if(lenght <8 && nums == 'n' || U_sym == 'n' || Sp_sym == 'n') {
    cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
}
else if(lenght <8 && U_sym == 'n' || nums == 'n'  || Sp_sym == 'n') {
    cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
}
else if(lenght <8 && Sp_sym == 'n' || nums == 'n' || U_sym == 'n' ) {
    cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
}
else if (lenght <8 || Sp_sym == 'n' || nums == 'n' || U_sym == 'n' ) {
    cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
}
else {
    cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
}*/
if(lenght>=8 && nums == 'y'   && U_sym == 'y') {
    cout <<  "Мінімальні вимоги: ПРОЙДЕНО" << endl;
}
 else if(lenght>=8 && nums == 'y'   && Sp_sym == 'y') {
    cout <<  "Мінімальні вимоги: ПРОЙДЕНО" << endl;
}
 else if(lenght>=8 && U_sym == 'y'   && Sp_sym == 'y') {
    cout <<  "Мінімальні вимоги: ПРОЙДЕНО" << endl;
}
else {
    cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
}


if(lenght <6) {
    level = 1;
    cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
}
else if(lenght < 8 ||( nums == 'n' && U_sym == 'n' && Sp_sym == 'n')) {
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
else if(lenght >12 && nums == 'y' && U_sym == 'y' && Sp_sym == 'y') {
    level = 5;
    cout << "Рівень надійності: 5 - Дуже надійний" << endl;
}
else {
    level = 4; 
    cout << "Рівень надійності: 4 - Надійний" << endl;
}
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
}
if(nums == 'n' && U_sym == 'n' && Sp_sym == 'n') {
    cout << "Пароль тільки з літер підбирається швидше" << endl;
}
    return 0;
}