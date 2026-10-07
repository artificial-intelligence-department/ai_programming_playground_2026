/*
Назва: Автономність портативної зарядної станції
Автор: Макух Арсеній
Група: ШІ-13
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
    string model;
    double capacity;
    int years;
    int charge;
    double eef;
    double power;

    double capacity_eff;
    double energy_stored;
    double energy_useful;
    double energy_loss;
    double time;
    int hours;
    int minutes;

    cout << "Назва моделі станції: ";
    cin >> model;
    if (model.length() > 31)
    {
        cout << "Помилка: назва моделі повинна містити не більше 31 символа." << endl;
        return 1;
    }
    else if (!model.find(' '))
    {
        cout << "Помилка: назва моделі не може містити пробілів." << endl;
        return 1;
    };

    cout << "Паспортна ємність, Вт·год: ";
    cin >> capacity;
    if (capacity <= 0)
    {
        cout << "Помилка: ємність може бути лише більше 0." << endl;
        return 1;
    };

    cout << "Вік станції, років: ";
    cin >> years;
    if (years < 0 || years > 20)
    {
        cout << "Помилка: вік повинен бути від 0 до 20." << endl;
        return 1;
    };

    cout << "Рівень заряду, %: ";
    cin >> charge;
    if (charge < 0 || charge > 100)
    {
        cout << "Помилка: рівень заряду повинен бути від 0 до 100." << endl;
        return 1;
    };

    cout << "ККД інвертора, %: ";
    cin >> eef;
    if (eef <= 0 || eef > 100)
    {
        cout << "Помилка: ККД інвертора має бути в межах від 1 до 100." << endl;
        return 1;
    };

    cout << "Потужність приладу, Вт: ";
    cin >> power;
    if (power <= 0)
    {
        cout << "Помилка: потужність може бути лише більше 0." << endl;
        return 1;
    };

    capacity_eff = capacity * pow((1 - 2 / 100), years);
    energy_stored = capacity_eff * charge / 100;
    energy_useful = energy_stored * eef / 100;
    energy_loss = energy_stored - energy_useful;
    time = energy_useful / power;
    hours = floor(time);
    minutes = floor((time - hours) * 60);

    cout << "\n\n================================================" <<
    "\nМодель: " << model << 
    "\nПаспортна ємність: " << capacity << " Вт·год" <<
    "\nВік станції: " << years << " р." <<
    "\nФактична ємність: " << capacity_eff << " Вт·год" <<
    "\nРівень заряду: " << charge << " %" <<
    "\nККД інвертора: " << eef << " %" <<
    "\nЗапас енергії: " << energy_stored << " Вт·год" <<
    "\nКорисна енергія: " << energy_useful << " Вт·год" <<
    "\nВтрати на перетворенні: " << energy_loss << " Вт·год" <<
    "\nЧас роботи: " << time << " год = " << hours << " год " << minutes << " хв" <<
    "\n================================================" << endl;
    
    return 0;
}