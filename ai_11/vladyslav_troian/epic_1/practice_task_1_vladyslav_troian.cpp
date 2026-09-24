/* 
Задача: Автономність портативної зарядної станції
Автор: Троян Владислав
Група: AI-11
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    const double degradation_per_year = 2.0; //стала втрати місткості на рік
    const int minutes_in_hour = 60; //кількість хвилин в 1 год

    //Отримую дані від користувача
    string stname; 
    cout << "Назва зарядної станції (без пропусків): ";
    cin >> stname;
    if (stname.length() > 31) { 
        cout << "Назва перевищує 31 символ." << endl;
        return 1;
    }

    double C;
    cout << "Паспортна місткість, Вт*год: ";
    cin >> C;
    if (C <= 0) { 
        cout << "Неприпустиме значення C <= 0" << endl;
        return 1;
    }
    
    int years;
    cout << "Вкажіть вік станції від 0 до 20 років: ";
    cin >> years;
    if (years < 0 || years > 20) { 
        cout << "Вказаний вік має бути в межах від 0 до 20 років" << endl;
        return 1;
    }

    int charge;
    cout << "Рівень заряду від 0 до 100 %: ";
    cin >> charge;
    if (charge < 0 || charge > 100){ 
        cout << "Вказаний рівень заряду має бути в межах від 0 до 100 %" << endl;
        return 1;
    }

    double eff;
    cout << "Вкажіть ККД інвертора до 100%: ";
    cin >> eff;
    if (eff <= 0 || eff > 100){ 
        cout << "Неприпустиме значення" << endl;
        return 1;
    }

    int P;
    cout << "Потужність приладу, Вт: ";
    cin >> P;
    if (P <= 0) { 
        cout << "Неприпустиме значення P <= 0" << endl;
        return 1;
    }

    cout << "-----> Результат обчислень <-----" << endl;
    //Виводить отримані дані
    cout << "Модель зарядної станції:        " << stname << endl;
    cout << "Паспортна ємність, Вт*год:      " << C << endl;
    cout << "Вік станції, роки:              " << years << endl;
    //Обчислення Фактичної ємності з урахуванням втрати щороку
    double C_eff = C*pow((1-degradation_per_year/100), years);
    cout << "Фактична ємність, Вт*год:       " << fixed << setprecision(1) << C_eff << endl;

    cout << "Рівень заряду, %:               " << charge << endl;

    cout << "ККД інвертора, %:               " << fixed << setprecision(2) << eff << endl;
    //Обчислення Запасу енергії відносно заряду
    double E_stored = C_eff*charge/100;
    cout << "Запас енергії, Вт*год:          " << fixed << setprecision(1) << E_stored << endl;
    //Обчислення корисної енергії
    double E_useful = E_stored*eff/100;
    cout << "Корисна енергія, Вт*год:        " << fixed << setprecision(1) << E_useful << endl;
    //Обчислення втрати енергії на перетворення
    double E_loss = E_stored - E_useful;
    cout << "Втрати на перетворенні, Вт*год: " << fixed << setprecision(1) << E_loss << endl;
    //Обчислення часу роботи
    double T = E_useful / P;
    int h = T;
    int m = ((T - h)*minutes_in_hour); // переведення залишку в хвилини 
    cout << "Час роботи:                     " << h << " год " << m << " хв" << endl;
    return 0;
}