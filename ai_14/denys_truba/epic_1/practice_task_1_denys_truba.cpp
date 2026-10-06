/*
    Автономність портативної зарядної станції
    Автор: Труба Денис
    Група: ШІ-14
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main()
{
    const double PERCENT = 100.0; // переведення відсотків у частку
    const double LOSS = 2.0;      // втрата ємності за рік
    const int MINUTES = 60;       // хвилин у годині
    
    string model;
    double C, eff, P;
    int years, charge;

    // Введення даних та їх перевірка
    cout << "Модель станції: ";
    cin >> model;
    if (model.empty() || model.length() > 31)
    {
        cout << "Помилка: назва моделі має бути одним словом і до 31 символа" << endl;
        return 1;
    }

    cout << "Паспортна ємність (Вт·год): ";
    cin >> C;
    if (C <= 0)
    {
        cout << "Помилка: ємність повинна бути більше 0." << endl;
        return 1;
    }

    cout << "Вік станції (років): ";
    cin >> years;
    if (years < 0 || years > 20)
    {
        cout << "Помилка: вік станції мусить бути від 0 до 20." << endl;
        return 1;
    }

    cout << "Рівень заряду (%): ";
    cin >> charge;
    if (charge < 0 || charge > 100)
    {
        cout << "Помилка: заряд мусить бути від 0 до 100." << endl;
        return 1;
    }

    cout << "ККД інвертора (%): ";
    cin >> eff;
    if (eff <= 0 || eff > 100)
    {
        cout << "Помилка: ККД мусить бути більше 0 і менше 100." << endl;
        return 1;
    }

    cout << "Потужність приладу (Вт): ";
    cin >> P;
    if (P <= 0)
    {
        cout << "Помилка: потужність повинна бути більше 0." << endl;
        return 1;
    }

    // Фактична ємність з урахуванням віку
    double C_eff = C * pow(1 - LOSS / PERCENT, years);

    // Запас енергії
    double E_stored = C_eff * charge / PERCENT;

    // Корисна енергія
    double E_useful = E_stored * eff / PERCENT;

    // Втрати на перетворенні
    double E_loss = E_stored - E_useful;

    // Час роботи
    double T = E_useful / P;

    // Повні години та хвилини
    int h = (int)T;
    int m = (int)((T - h) * MINUTES);

    cout << fixed;

    cout << "\nМодель: " << model << endl;
    cout << "Паспортна ємність: " << setprecision(1) << C << " Вт·год" << endl;
    cout << "Вік станції: " << years << " р." << endl;
    cout << "Фактична ємність: " << C_eff << " Вт·год" << endl;
    cout << "Рівень заряду: " << charge << " %" << endl;
    cout << "ККД інвертора: " << setprecision(2) << eff << " %" << endl;
    cout << "Запас енергії: " << setprecision(1) << E_stored << " Вт·год" << endl;
    cout << "Корисна енергія: " << E_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні: " << E_loss << " Вт·год" << endl;
    cout << "Час роботи: " << setprecision(2) << T << " год = " << h << " год " << setw(2) << setfill('0') << m << " хв" << endl;

    return 0;
}