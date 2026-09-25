/*
    Задача: Автономність портативної зарядної станції
    Михайловська Анна
    ШІ-14
*/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main(){
    const int MAX_LEIGHT = 31;               // Максимальна кількість символів у назві моделі
    const int MAX_AGE = 20;                  // Максимально допустимий вік станції в роках
    const int MAX_PERCENT = 100;             // Найбільше допустиме значення відсотків для рівня заряду та ккд інвертора
    const double PERCENT_BASE = 100.0;       // Число для переведення відсотків у частку
    const double YEARLY_CAPACITY_LOSS = 2.0; //Втрата ємності акумулятора за один рік, %
    
    string model;
    double C;
    int years;
    int charge;
    double eff;
    double P;

    cout << "Модель станції: ";
    if (!(cin >> model) || model.length() > MAX_LEIGHT ){
        cout << "Помилка: назва моделі станції має бути коротшою за 31 символ.\n";
        return 1;
    }
    cout << "Паспортна ємність, Вт·год: ";
    if (!(cin >> C) || C <= 0 ){
        cout << "Помилка: ємність має бути числом, більшим за 0.\n";
        return 1;
    }
    cout << "Вік станції, років: ";
    if (!(cin >> years) || years < 0 || years > MAX_AGE){
        cout << "Помилка: вік станції має бути цілим числом від 0 до 20.\n";
        return 1;
    }
    cout << "Рівень заряду, %: ";
    if (!(cin >> charge) || charge < 0 || charge > MAX_PERCENT) {
        cout << "Помилка: рівень заряду має бути цілим числом від 0 до 100.\n";
        return 1;
    }
    cout << "ККД інвертора, %: ";
    if (!(cin >> eff) || eff <= 0 || eff > MAX_PERCENT) {
        cout << "Помилка: ККД має бути числом від 0 до 100.\n";
        return 1;
    }
    cout << "Потужність приладу, Вт: ";
    if (!(cin >> P) || P <= 0) {
        cout << "Помилка: потужність має бути числом, більшим за 0.\n";
        return 1;
    }

    // Обчислюємо фактичну ємність станції з урахуванням її віку, у Вт·год
    double C_eff = C * pow(1.0 - YEARLY_CAPACITY_LOSS / PERCENT_BASE, years);
   
    // Обчислюємо запас енергії за поточного рівня заряду, у Вт·год
    double E_stored = C_eff * charge / PERCENT_BASE;

    // Обчислюємо корисну енергію, що дійде до приладу, у Вт·год
    double E_useful = E_stored * eff / PERCENT_BASE;

    // Обчислюємо втрати енергії на перетворенні напруги, у Вт·год
    double E_loss = E_stored - E_useful;

    // Обчислюємо загальний час роботи, у годинах
    double T = E_useful / P;

    // Відокремлюємо повні години від загального часу роботи
    int h = static_cast<int>(T);

    // Обчислюємо кількість хвилин, що залишились
    int m = static_cast<int>((T - h) * 60);

    cout << "\nМодель:                     " << model << '\n';
    cout << "Паспортна ємність:     " << right << setw(10) << fixed << setprecision(1) << C << " Вт·год\n";
    cout << "Вік станції:           " << right << setw(10) << years << " р.\n";
    cout << "Фактична ємність:      " << right << setw(10) << fixed << setprecision(1) << C_eff << " Вт·год\n";
    cout << "Рівень заряду:         " << right << setw(10) << charge << " %\n";
    cout << "ККД інвертора:         " << right << setw(10) << fixed << setprecision(2) << eff << " %\n";
    cout << "Запас енергії:         " << right << setw(10) << fixed << setprecision(1) << E_stored << " Вт·год\n";
    cout << "Корисна енергія:       " << right << setw(10) << fixed << setprecision(1) << E_useful << " Вт·год\n";
    cout << "Втрати на перетворенні:" << right << setw(10) << fixed << setprecision(1) << E_loss << " Вт·год\n";
    cout << "Час роботи:            " << right << setw(10) << fixed << setprecision(2) << T << " год = " << h << " год " 
         << setfill('0') << setw(2) << m << setfill(' ') << " хв\n";

    return 0;  
}