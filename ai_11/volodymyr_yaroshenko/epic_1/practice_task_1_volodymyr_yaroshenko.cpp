/*  
Автономність портативної зарядної станції
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

 int main() {
const float loss_year = 2.0/100; // відсоток втрат ємності щороку
const int percent = 100; // відсотки 
const int minutes_in_h = 60; // хвилини в годині 
string name; // назва станції 
int  years, charge;
float C, eff, P;

cout << "Введіть модель станції:";
getline(cin, name);
if(name.length() >31 ) { // перевіряємо довжину назви станції
    cout << "Назва станції не повинна перевищувати 31 символ" << endl;
    return 1; // зупиняємо програму якщо не правильна довжина назви
}

cout << "Введіть паспортну ємність (Вт·год): ";
cin >> C;
if(C <= 0 ) {
    cout << "Паспортна ємність не може бути від'ємною" << endl;
    return 1;
}

cout << "Вік станції: ";
cin >> years;
if(years < 0  || years > 20) {
    cout << "Кількість років експлуатації повинна бути в межах від 0 до 20" << endl;
    return 1;
}

cout << "Введіть рівень заряду (у відсотках): ";
cin >> charge;
if(charge < 0 || charge > 100) {
    cout << "Рівень заряду повинен бути в межах від 0 до 100" << endl;
    return 1;
}

cout << "Введіть ККД інвертора (у відсотках): ";
cin >> eff;
if(eff < 0 || eff > 100) {
    cout << "ККД інвертора повинен бути в межах від 0 до 100" << endl;
    return 1;
}

cout << "Введіть потужність споживання (Вт): ";
cin >> P;
if(P <= 0 ) {
    cout << "Потужність споживання не може бути від'ємною" << endl;
    return 1; 
    
}

float C_eff = C * pow(1 - loss_year , years); // обчислюємо фактичну ємність станції у відстоках
float E_stored = C_eff *charge / percent; //  запас енергії у Вт*год 
float E_useful = E_stored * eff / percent; // корисна енергія у Вт*год
float E_loss = E_stored - E_useful; // втрати енергії у Вт*год
float T = E_useful / P;  // весь час роботи станції у годинах в дробовому вигляді
float h = int(T); // визначаємо цілі години роботи 
int  m = ((T - h) * minutes_in_h); // визначаємо хвилини роботи з урахуванням годин 

cout << left << setw(41) << "Модель станції:" << name << endl;
cout << left << setw(44) << "Паспортна ємність:" << fixed << setprecision(1) << C << " Вт·год" << endl;
cout << left << setw(38) << "Вік станції:" << years << endl;
cout << left << setw(43) << "Фактична ємність:"<< fixed << setprecision(1) << C_eff << " Вт·год" << endl;
cout << left << setw(40) << "Рівень заряду:" << charge << "%" << endl;
cout << left << setw(40) << "ККД інвертора:"  << fixed << setprecision(2) << eff << "%" << endl;
cout << left << setw(40) << "Запас енергії:"  << fixed << setprecision(1) << E_stored << " Вт·год" << endl;
cout << left << setw(42) << "Корисна енергія:"  << fixed << setprecision(1) << E_useful << " Вт·год" << endl;
cout << left << setw(41) << "Втрати енергії:"  << fixed << setprecision(1) << E_loss << " Вт·год" << endl;
cout << left << setw(37) << "Час роботи:"  << fixed << setprecision(1) << h << "год  = " << h << " год " << m << " хв" << endl;
     return 0;
 }



   
