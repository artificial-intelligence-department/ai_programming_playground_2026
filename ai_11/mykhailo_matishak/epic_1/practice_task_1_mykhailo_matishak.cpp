 /* Задача: Автономність портативної зарядної станції
 * Автор: Матішак Михайло
 * Група: ШІ-11*/

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int main()
{
    const double DEGRADATION = 2.0; // константа, на скільки падає ємність акумулятора за рік

    string model;
    double capacity, eff, power;
    int years, charge;

    // зчитування даних

    cout << "Модель станції: ";
    cin >> model;

    if (model.length() > 31)
    {
        cout << "Помилка: назва станції має не перевищувати 31 символ." << endl;
        return 1;
    }

    cout << "Паспортна ємність (Вт*год): ";
    cin >> capacity;

    if (cin.fail())
    {
        cout << "Помилка: ємність має бути числом." << endl;
        return 1;
    }

    if (capacity <= 0)
    {
        cout << "Помилка: ємність мусить бути більше 0." << endl;
        return 1;
    }

    cout << "Вік станції (років): ";
    cin >> years;

    if (cin.fail())
    {
        cout << "Помилка: вік має бути цілим числом." << endl;
        return 1;
    }

    if (years < 0 || years > 20)
    {
        cout << "Помилка: вік станції мусить бути від 0 до 20." << endl;
        return 1;
    }

    cout << "Рівень заряду (%): ";
    cin >> charge;

    if (cin.fail())
    {
        cout << "Помилка: рівень заряду має бути цілим числом." << endl;
        return 1;
    }

    if (charge < 0 || charge > 100)
    {
        cout << "Помилка: рівень заряду мусить бути від 0 до 100." << endl;
        return 1;
    }

    cout << "ККД інвертора (%): ";
    cin >> eff;

    if (cin.fail())
    {
        cout << "Помилка: ККД має бути числом." << endl;
        return 1;
    }

    if (eff <= 0 || eff > 100)
    {
        cout << "Помилка: ККД мусить бути від 0 до 100." << endl;
        return 1;
    }

    cout << "Потужність приладу (Вт): ";
    cin >> power;

    if (cin.fail())
    {
        cout << "Помилка: потужність має бути числом." << endl;
        return 1;
    }

    if (power <= 0)
    {
        cout << "Помилка: потужність приладу мусить бути більше 0." << endl;
        return 1;
    }

    double C_eff = capacity * pow(1 - DEGRADATION / 100, years); //фактична ємність + вік Вт*год 
    double E_stored = C_eff * charge / 100; //запас енергії при поточному заряді (Вт*год), переводимо відсотки заряду в частку
    double E_useful = E_stored * eff / 100; // корисна енергія що дійде до приладу (Вт*год)
    double E_loss = E_stored - E_useful; // втрати на перетворенні (Вт*год)
    double T = E_useful / power; // час роботи (год)
    int h = T; //ціла кількість годин
    int m = (T - h) * 60; //залишок хвилин

    //вивід результату

    cout << fixed;

    cout << endl;
    cout << "Модель:                 " << model << endl;

    cout.precision(1);
    cout << "Паспортна ємність:      " << capacity << " Вт*год" << endl;

    cout << "Вік станції:            " << years << " р." << endl;

    cout << "Фактична ємність:       " << C_eff << " Вт*год" << endl;

    cout << "Рівень заряду:          " << charge << " %" << endl;

    cout.precision(2);
    cout << "ККД інвертора:          " << eff << " %" << endl;

    cout.precision(1);
    cout << "Запас енергії:          " << E_stored << " Вт*год" << endl;

    cout << "Корисна енергія:        " << E_useful << " Вт*год" << endl;

    cout << "Втрати на перетворенні: " << E_loss << " Вт*год" << endl;

    cout.precision(2);
    cout << "Час роботи:             " << T << " год  = " << h << " год ";

    // щоб хвилини завжди виводились двома цифрами
    if (m < 10)
        cout << "0" << m << " хв" << endl;
    else
        cout << m << " хв" << endl;

    return 0;
}