/*
Назва задачі: "Автономність портативної зарядної станції"
Автор: Коваль Михайло 
Група: ШІ_14
*/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std; 

int main () 
{
    //змінні для вхідних даних
    string model; 
    float C;
    int years;
    int charge;
    float eff;
    int P;

    const float cap_loss = 2.0; //втрата ємності за рік
    const float base_cap = 100.0; //базова ємність
    const int minutes_in_hour = 60; //кількість хв в годині

    cout << "--------------Вхідні дані--------------" << endl;

    //введення даних та валідація
    cout << "Модель станції: ";
    cin >> model;
    if (model.length()  > 31)
    {
        cout << "Помилка, назва повинна бути менше за 31 символ" << endl; 
        return 1;
    }

    cout << "Паспортна ємність, Вт*год: ";
    cin >> C;
    if (C <= 0)
    {
        cout << "Помилка, допустимі значення більші за 0" << endl; 
        return 1;
    }

    cout << "Вік станції, років: ";
    cin >> years;
    if (years < 0 || years > 20)
    {
        cout << "Помилка, вік станції має бути в діапазоні 0-20" << endl; 
        return 1;
    }

    cout << "Рівень заряду, %: ";
    cin >> charge;
    if (charge < 0 || charge > 100)
    {
        cout << "Помилка, допустимі значення рівня заряду 0-100%" << endl; 
        return 1;
    }

    cout << "ККД інвертора, %: ";
    cin >> eff;
    if (eff <= 0 || eff > 100)
    {
        cout << "Помилка, допустимі значення ККД інвертора 0-100%" << endl; 
        return 1;
    }
    cout << "Потужність приладу, Вт: ";
    cin >> P;
    if (P <= 0)
    {
        cout << "Помилка, значення потужності має бути більшим за 0" << endl; 
        return 1;
    }

    //обчислення фактичної ємності, Вт*год
    float C_eff;
    C_eff = C * pow((1.0 - cap_loss / 100.0), years);
    //обчислення запасу енергії, Вт*год
    float E_storred;
    E_storred = C_eff * charge / 100.0;
    //обчислення корисної енергії, Вт*год
    float E_useful;
    E_useful = E_storred * eff / 100.0;
    //обчислення втрати на перетворення напруги, Вт*год
    float E_loss;
    E_loss = E_storred - E_useful;
    //обчислення часу роботи, год
    float T;
    T = E_useful / P;
    //повні години та хвилини
    int h;
    h = int(T);
    int m;
    m = ((T - h) * minutes_in_hour);

    //Вивід даних
    cout << "---------Інформація про станцію---------" << endl; 

    cout << "Модель станції:             " << model << endl;
    cout << "Паспортна ємність:          " << fixed << setprecision(1) << C << " Вт*год " << endl; 
    cout << "Вік станції, років:         " << years << " р." << endl;
    cout << "Фактична ємність:           " << fixed << setprecision(1) << C_eff << " Вт*год " << endl;
    cout << "Рівень заряду :             " << charge << " %" << endl;
    cout << "ККД інвертора :             " << fixed << setprecision(2) << eff << " % " << endl;
    cout << "Запас енергії:              " << fixed << setprecision(1) << E_storred << " Вт*год " << endl;
    cout << "Корисна енергія:            " << fixed << setprecision(1) << E_useful << " Вт*год " << endl;
    cout << "Втрати на перетворення:     " << fixed << setprecision(1) << E_loss << " Вт*год " << endl; 
    cout << "Час роботи                  " << fixed << setprecision(2) << T << " год " << " = " << h << " год " << m << " хв " << endl;

    return 0;
}