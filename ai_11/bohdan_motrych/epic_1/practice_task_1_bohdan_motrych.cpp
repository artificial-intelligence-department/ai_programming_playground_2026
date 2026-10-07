/*
Автономність портативної зарядної станції
ШІ-11
Мотрич Богдан
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main () {
    // Константи
    const double degradation = 2.0;

    // Вхідні змінні
    string model;
    double C = 0.0;
    int years = 0;
    int charge = 0;
    double eff = 0.0;
    double P = 0.0;
    
    // Введення даних
    cout << "Модель станції: ";
    cin >> model;
    if (model.length() > 31){
        cout << "Помилка: назва має бути не більше 31 символа" << endl;
        return 1;
    }

    cout << "Паспортна ємність, Вт·год: ";
    cin >> C;
    if (C <= 0 or cin.fail()){
        cout << "Помилка: паспортна ємність має бути більше 0" << endl;
        return 1;
    }

    cout << "Вік станції, років: ";
    cin >> years;
    if (years < 0 or years > 20 or cin.fail()){
        cout << "Помилка: вік станції має бути від 0 до 20 років" << endl;
        return 1;
    }

    cout << "Рівень заряду, %: ";
    cin >> charge;
    if (charge < 0 or charge > 100 or cin.fail()){
        cout << "Помилка: рівень заряду має бути від 0% до 100%" << endl;
        return 1;
    }

    cout << "ККД інвертора, %: ";
    cin >> eff;
    if (eff <= 0 or eff > 100 or cin.fail()){
        cout << "Помилка: ККД інвентора має бути більше 0% і не більше 100%" << endl;
        return 1;
    }

    cout << "Потужність приладу, Вт: ";
    cin >> P;
    if (P <= 0 or cin.fail()){
        cout << "Помилка: потужність приладу має бути більше 0" << endl;
        return 1;
    }

    // Обчислення нових значень
    double C_eff = C * pow(1.0 - degradation / 100.0, years); // Фактична ємність з урахуванням віку, Вт·год
    double E_stored = C_eff * charge / 100; // Запас енергії при поточному заряді, Вт·год
    double E_useful = E_stored * eff / 100; // Корисна енергія, що дійде до приладу, Вт·год
    double E_loss = E_stored - E_useful; // Втрати на перетворенні напруги, Вт·год
    double T = E_useful / P; // Час роботи, годин
    int h =(int)T; // Повні години
    int m = (int)((T - h) * 60); // Остача хвилин

    // Вивід
    cout << left << setw(35) << "Модель: " << model << endl; 
    cout << left << setw(35) <<"Паспортна ємність: " << fixed << setprecision(1) << C << " Вт·год" << endl;
    cout << left << setw(35) <<"Вік станції: " << years << " р." << endl;
    cout << left << setw(35) <<"Фактична ємність: " << fixed <<  setprecision(1) << C_eff << " Вт·год" << endl;
    cout << left << setw(35) <<"Рівень заряду: " << charge << " %" << endl;
    cout << left << setw(35) <<"ККД інвентора: " << fixed << setprecision(2) << eff << " %" << endl;
    cout << left << setw(35) <<"Запас енергії: " << fixed << setprecision(1) << E_stored << " Вт·год" << endl;
    cout << left << setw(35) <<"Корисна енергія: " << fixed << setprecision(1) << E_useful << " Вт·год" << endl;
    cout << left << setw(35) <<"Витрати на перетворенні: " << fixed << setprecision(1) << E_loss << " Вт·год" << endl;
    cout << left << setw(35) <<"Час роботи: " << fixed << setprecision(2) << T << " год = " << h << " год " << right << setfill('0') << setw (2) << m << setfill(' ') << " хв " << endl;

    return 0;
}