// Автономність портативної станції; Гуляєв; ШІ-14.;
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main(){
    system("chcp 65001 > nul");

//Оголошуємо константи для виконання задачі
const double DEGRADATION_PER_YEAR = 0.02; //Коефіціент втрати ємності акумулятора на рік (2%)
const double PERSENT_TO_FRACTION = 100.0; //Дільник для переведення відсотків у частку
const int MINUTES_IN_HOUR = 60; // Показує скільки хвилин в годині

//Оголошуємо змінні
string model; //Модель станції
double C; //Паспортна ємність
int years; //Вік станції
int charge; //Рівень заряду
double eff; //ККД інвертора
double P; //Потужність приладу

//Введення значень змінних
cout << "Модель станції: ";
    if (!(cin >> model) || model.length() > 31){
    cout << "Помилка! Довжина назви моделі має бути коротша за 31 символ!";
    return 1;}

cout << "Паспортна ємність (Вт·год) (Більше 0): ";
    if (!(cin >> C) || C <= 0){
    cout << "Помилка! Паспортна ємність має бути більше 0!";
    return 1;}

cout << "Вік станції (років) (Від 0 до 20): ";
    if (!(cin >> years) || years < 0 || years > 20){
    cout << "Помилка! Вік станції має бути від 0 до 20 років!";
    return 1;}

cout << "Рівень заряду (%) (Від 0 до 100): ";
    if (!(cin >> charge) || charge < 0 || charge > 100){
    cout << "Помилка! Рівень заряду має бути від 0 до 100 відсотків!";
    return 1;}

cout << "ККД інвертора (%) (Від 0 до 100): ";
    if (!(cin >> eff) || eff < 0 || eff > 100){
    cout << "Помилка! ККД інвертора має бути від 0 до 100!";
    return 1;}

cout << "Потужність приладу (Вт) (Більше 0): ";
    if (!(cin >> P) || P < 0){
    cout << "Помилка! Потужність приладу має бути більше 0!";
    }

//Розрахунки

double C_eff = C * pow(0.98, years); //Вираховуємо фактичну ємність з урахуванням віку
double E_stored = C_eff * (charge / PERSENT_TO_FRACTION); //Вираховуємо запас енергії при поточному заряді
double E_useful = E_stored * (eff / PERSENT_TO_FRACTION); //Вираховуємо корисну дію, що дійде до прилада
double E_loss = E_stored - E_useful; //Вираховуємо втрати на перетворення напруги
double T = E_useful / P; //Вираховуємо час роботи у годинах
int h = static_cast<int>(T); //Вираховуємо повні години
int m = static_cast<int>((T - h) * MINUTES_IN_HOUR); //Вираховуємо хвилини, що залишились

//Вивід даних користувачу

cout << "------------\n";
cout << "Модель станції: " << model << "\n";
cout << "Паспортна ємність: " << fixed << setprecision(1) << C << " Вт·год\n";
cout << "Вік станції: " << years << " р.\n";
cout << "Фактична ємність з урахуванням віку: " << fixed << setprecision(1) << C_eff << " Вт·год\n";
cout << "Рівень заряду: " << charge << " %\n";
cout << "ККД інвертора: " << fixed << setprecision(2) << eff << " %\n";
cout << "Запас енергії: " << fixed << setprecision(1) << E_stored << " Вт·год\n";
cout << "Корисна енергія: " << fixed << setprecision(1) << E_useful << " Вт·год\n";
cout << "Втрати на перетворенні: " << fixed << setprecision(1) << E_loss << " Вт·год\n";
cout << "Час роботи: " << fixed << setprecision(2) << T << "год = " << h << "год ";
if (m < 10){
cout << "0";}
cout << m << "хв";
}