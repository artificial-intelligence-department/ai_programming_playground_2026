#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;
/*  
Автономність портативної зарядної станції
Ярошенко Володимир 
11 група 
*/
 int main() {

string name; // назва станції 
int  years, charge, eff, P;
float C;

cout << "Введіть модель станції:";
getline(cin, name);
if(name.length() >31 ) { // перевіряємо довжину назви станції
    cout << "Назва станції не повинна перевищувати 31 символ" << endl;
    return 1; // зупиняємо програму якщо не правильна довжина назви
}

cout << "Введіть паспортну ємність (Вт·год): ";
cin >> C;
if(C < 0 ) {
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
if(P < 0 ) {
    cout << "Потужність споживання не може бути від'ємною" << endl;
    return 1;
}

float C_eff = C * pow(1 - 2.0/100 , years); // 2 -відсоток втрата ємності щороку, обчислюємо фактичну ємність станції у відстоках
float E_stored = C_eff *charge / 100; //  запас енергії у Вт*год 
float E_useful = E_stored * eff / 100; // корисна енергія у Вт*год
float E_loss = E_stored - E_useful; // втрати енергії у Вт*год
float T = E_useful / P;  // весь час роботи станції у годинах в дробовому вигляді
float h = int(T); // визначаємо цілі години роботи 
float m = ((T - h) * 60); // визначаємо хвилини роботи з урахуванням годин 

cout << "Модель станції: " << name << endl;
cout << "Паспортна ємність: " << fixed << setprecision(1) << C << " Вт·год" << endl;
cout << "Вік станції: " << years << endl;
cout << "Фактична ємність: "<< fixed << setprecision(1) << C_eff << " Вт·год" << endl;
cout << "Рівень заряду: " << charge << "%" << endl;
cout << "ККД інвертора: "  << fixed << setprecision(2) << eff << "%" << endl;
cout << "Запас енергії: "  << fixed << setprecision(1) << E_stored << " Вт·год" << endl;
cout << "Корисна енергія: "  << fixed << setprecision(1) << E_useful << " Вт·год" << endl;
cout << "Втрати енергії: " << fixed << setprecision(1) << E_loss << " Вт·год" << endl;
cout << "Час роботи: "  << fixed << setprecision(1) << h << "год  = " << h << " год " << m << " хв" << endl;
     return 0;
 }



   
