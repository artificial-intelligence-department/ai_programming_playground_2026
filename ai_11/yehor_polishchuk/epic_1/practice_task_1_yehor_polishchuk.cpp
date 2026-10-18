/*
    Задача:    Автономність портативної зарядної станції
    Автор:     Поліщук Єгор
    Група:     ai-11
*/


#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;


int main()
{
    setlocale(LC_ALL, "uk_UA.UTF-8");

    string model;
    double C = 0.0;   // паспортна ємність станції, Вт·год
    int years = 0;    // вік станції, років
    int charge = 0;   // поточний рівень заряду, %
    double eff = 0.0; // ККД інвертора, %
    double P = 0.0;   // потужність приладу, Вт


    cout << "Модель станції: ";
    cin >> model;
    if (model.length() > 31)
    {
        cout << "Помилка: назва моделі не має перевищувати 31 символ." << endl;
        return 1;
    }


    cout << "Паспортна ємність (Вт·год): ";
    cin >> C;
    if (cin.fail() || C <= 0)
    {
        cout << "Помилка: паспортна ємність мусить бути додатним числом." << endl;
        return 1;
    }


    cout << "Вік станції (років): ";
    cin >> years;
    if (cin.fail() || years < 0 || years > 20)
    {
        cout << "Помилка: вік станції мусить бути від 0 до 20." << endl;
        return 1;
    }


    cout << "Рівень заряду (%): ";
    cin >> charge;
    if (cin.fail() || charge < 0 || charge > 100)
    {
        cout << "Помилка: рівень заряду мусить бути від 0 до 100." << endl;
        return 1;
    }


    cout << "ККД інвертора (%): ";
    cin >> eff;
    if (cin.fail() || eff <= 0 || eff > 100)
    {
        cout << "Помилка: ККД інвертора мусить бути більше 0 і не більше 100." << endl;
        return 1;
    }


    cout << "Потужність приладу (Вт): ";
    cin >> P;
    if (cin.fail() || P <= 0)
    {
        cout << "Помилка: потужність приладу мусить бути додатним числом." << endl;
        return 1;
    }


    // * Обчислення *


    // Відсоток втрати ємності акумулятора за рік
    const double DEGRADATION_PER_YEAR = 2.0;


    double C_eff = C * pow(1.0 - DEGRADATION_PER_YEAR / 100.0, years);


    //запас енергії при поточному рівні заряду, Вт·год
    double E_stored = C_eff * charge / 100.0;


    // корисна енергія, що дійде до приладу після інвертора, Вт·год
    double E_useful = E_stored * eff / 100.0;


    // втрати на перетворенні напруги в інверторі, Вт·год
    double E_loss = E_stored - E_useful;


    // час роботи приладу від станції, год
    double T = E_useful / P;


    // кількість повних годин роботи
    int h = static_cast<int>(T);


    // кількість хвилин понад повні години
    int m = static_cast<int>((T - h) * 60);


    //  Виведення результату


    cout << fixed;
    cout << endl;
    cout << "Модель: " << model << endl;
    cout << setprecision(1);
    cout << "Паспортна ємність: " << setw(8) << C << " Вт·год" << endl;
    cout << "Вік станції: " << years << " р." << endl;
    cout << "Фактична ємність: " << setw(8) << C_eff << " Вт·год" << endl;
    cout << "Рівень заряду: " << charge << " %" << endl;
    cout << setprecision(2);
    cout << "ККД інвертора: " << setw(8) << eff << " %" << endl;
    cout << setprecision(1);
    cout << "Запас енергії: " << setw(8) << E_stored << " Вт·год" << endl;
    cout << "Корисна енергія: " << setw(8) << E_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні: " << setw(8) << E_loss << " Вт·год" << endl;
    cout << setprecision(2);
    cout << "Час роботи: " << T << " год = "
         << h << " год " << setw(2) << setfill('0') << m << " хв" << endl;

    return 0;
}
