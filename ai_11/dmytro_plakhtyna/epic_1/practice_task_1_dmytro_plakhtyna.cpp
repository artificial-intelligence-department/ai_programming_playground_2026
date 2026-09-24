
/*Автономність портативної зарядної станції;
Плахтина Дмитро;
ШІ-11.*/
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;
int main() {
    string model;
    double capacity = 0;
    int years = 0;
    int charge = 0;
    double eff = 0;
    double p = 0;

    cout << "Введіть назву станції: " << endl;
    cin >> model;
    if(model.length() > 31) {
        cout << "Помилка! Назва станції не повинна перевищувати 31 символ!" << endl;
        return 1;
    }

    cout << "Введіть паспортну ємність, Вт-год: " << endl;
    cin >> capacity;
    if(capacity <= 0) {
        cout << "Помилка! Паспортна ємність повинна бути більше 0!" << endl;
        return 1;
    }

    cout << "Введіть вік станції (років): " << endl;
    cin >> years;
    if(years < 0 || years > 20) {
        cout << "Помилка! Вік станції не може бути від'ємним або більшим за 20!" << endl;
        return 1;
    }

    cout << "Введіть рівень заряду, %: " << endl;
    cin >> charge;
    if(charge < 0 || charge > 100) {
        cout << "Помилка! Рівень заряду не може бути від'ємним або більшим за 100!" << endl;
        return 1;
    }

    cout << "Введіть ККД інвентора, %: " << endl;
    cin >> eff;
    if(eff <= 0 || eff > 100) {
        cout << "Помилка! ККД інвентора не може бути від'ємним або більшим за 100!" << endl;
        return 1;
    }

    cout << "Введіть потужність приладу, Вт: " << endl;
    cin >> p;
    if(p <= 0) {
        cout << "Помилка! Потужність приладу повинна бути більше 0!" << endl;
        return 1;
    }

    double c_eff = capacity * pow(1.0 - 0.02, years);
    double e_stored = c_eff * charge / 100.0;
    double e_useful = e_stored * eff / 100.0;
    double e_loss = e_stored - e_useful;
    double T = e_useful / p;
    int hours = static_cast<int>(T);
    int minutes = static_cast<int>((T - hours) * 60 + 0.5);

    cout << "\nМодель станції: " << model << endl;
    
    cout << fixed << setprecision(1);
    cout << "Паспортна ємність: " << capacity << " Вт-год" << endl;
    cout << "Вік станції: " << years << " років" << endl;
    cout << "Фактична ємність: " << c_eff << " Вт-год" << endl;
    cout << "Рівень заряду: " << charge << "%" << endl;
    
    cout << fixed << setprecision(2);
    cout << "ККД інвентора: " << eff << "%" << endl;
    
    cout << fixed << setprecision(1);
    cout << "Запас енергії: " << e_stored << " Вт-год" << endl;
    cout << "Корисна енергія: " << e_useful << " Вт-год" << endl;
    cout << "Втрати енергії: " << e_loss << " Вт-год" << endl;
    
    cout << fixed << setprecision(2);
    cout << "Час роботи (год): " << T << " год" << endl;
    
    cout << "Час роботи (год хв): " << hours << " год " 
         << setw(2) << setfill('0') << minutes << " хв" << endl;

    return 0;
}
