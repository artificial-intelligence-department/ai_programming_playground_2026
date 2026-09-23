/* 
Епік 1. Практичне завдання: Автономність портативної зарядної станції
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    
    string model;
    int C=0;
    int years=0;
    int charge=0;
    float eff=0.0;
    int P=0;
    const float deg_rate_yr=2.0;
    
    cout << "Введіть модель станції: ";
    cin >> model;
    while (model.length() > 31 || model.find(' ') != string::npos) {
        cout << "Модель станції не може перевищувати 31 символ або містити пробіл. Введіть модель станції: ";
        cin >> model;
    }

    cout << "Введіть паспортну ємність станції (C): ";
    cin >> C;
    while (C < 0) {
        cout << "Паспортна ємність станції не може бути від'ємною. Введіть паспортну ємність станції (C): ";
        cin >> C;
    }

    cout << "Введіть вік станції: ";
    cin >> years;
    while (years < 0 || years > 20) {
        cout << "Вік станції не може бути від'ємною або перевищувати 20 років. Введіть вік станції: ";
        cin >> years;
    }

    cout << "Введіть заряд станції: ";
    cin >> charge;
    while (charge < 0 || charge > 100) {
        cout << "Заряд станції не може бути від'ємним або перевищувати 100. Введіть заряд станції: ";
        cin >> charge;
    }

    cout << "Введіть ККД івентора: ";
    cin >> eff;
    while (eff < 0 || eff > 100) {
        cout << "ККД івентора не може бути від'ємною або перевищувати 100. Введіть ККД івентора: ";
        cin >> eff;
    }

    cout << "Введіть потужність приладу: ";
    cin >> P;
    while (P < 0) {
        cout << "Потужність приладу не може бути від'ємною. Введіть потужність приладу: ";
        cin >> P;
    }

    // Обчислення фактичної ємності з урахуванням зносу акумулятора (Вт·год)
    float C_eff = C * pow(1 - (deg_rate_yr / 100 /* переведення відсотків у частку */), years);
    
    // Обчислення поточного запасу енергії в акумуляторі (Вт·год)
    float E_stored = C_eff * charge / 100;
    
    // Обчислення корисної енергії з урахуванням ККД інвертора (Вт·год)
    float E_useful = E_stored * eff / 100;
    
    // Обчислення втрат енергії на перетворенні (Вт·год)
    float E_loss = E_stored - E_useful;
    
    // Обчислення загального часу автономної роботи приладу (год)
    float T = E_useful / P;
    
    // Конвертація часу у години та хвилини
    int h = (int)T;
    int m =(int)((T - h) * 60 /* переведення дробової частини години у хвилини */);
    
    cout << "Модель:                 " << model << endl;
    cout << "Паспортна ємність:      " << fixed << setprecision(1) << C << " Вт·год" << endl;
    cout << "Фактична ємність:       " << fixed << setprecision(1) << C_eff << " Вт·год" << endl;
    cout << "Вік станції:            " << years << " р." << endl;
    cout << "Рівень заряду:          " << charge << " %" << endl;
    cout << "ККД інвертора:          " << fixed << setprecision(2) << eff << " %" << endl;
    cout << "Запас енергії:          " << fixed << setprecision(1) << E_stored << " Вт·год" << endl;
    cout << "Корисна енергія:        " << fixed << setprecision(1) << E_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні: " << fixed << setprecision(1) << E_loss << " Вт·год" << endl;
    cout << "Час роботи:             " << fixed << setprecision(2) << T << " год = " << h << " год " << setfill('0') << setw(2) << m << " хв" << endl;
    return 0;
}
