#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;


int main() {
    string name; 
    cout << "Введіть назву моделі:" << endl;
    cin >> name;
    if (name.length() > 31) {
        cout << "Довжина назви моделі не повинна перевищувати 31 символ" << endl; 
        return 0;
    } 
    double C; 
    cout << "Введіть паспортну ємність моделі (Вт·год):" << endl;
    cin >> C;
    if (C <= 0) {
        cout << "Паспортна ємність моделі повинна бути додатнім числом" << endl; 
        return 0;
    }
    int years;
    cout << "Введіть вік станції (років):" << endl;
    cin >> years;
    if (years < 0 || years > 20) {
        cout << "Вік станції повинен лежати в межах від 0 до 20" << endl; 
        return 0;
    }
    int charge; 
    cout << "Введіть рівень заряду станції (%):" << endl;
    cin >> charge;
    if (charge < 0 || charge > 100) {
        cout << "Рівень заряду станції повинен лежати в межах від 0 до 100" << endl;
        return 0;
    }
    double eff;
    cout << "Введіть ККД інвертора (%):" << endl;
    cin >> eff;
    if (eff <= 0 || eff > 100) {
        cout << "ККД інвертора повинен бути більшим за 0 і не більшим за 100" << endl;
        return 0;
    }
    double P;
    cout << "Введіть потужність станції (Вт):" << endl;
    cin >> P;
    if (P <= 0) {
        cout << "Потужність станції повинна бути додатнім числом" << endl; 
        return 0;
    }
    double C_eff = C*pow(1.0 - (2.0/100.0), years);
    double E_stored = C_eff * (charge/100.0);
    double E_useful = E_stored * eff / 100.0;
    double E_loss = E_stored - E_useful;
    double T = E_useful / P;
    int h = floor(T);
    int m = floor((T - h) * 60);
    cout << "Назва моделі: " << name << "\n";
    cout << "Паспортна ємність моделі: " << fixed << setprecision(1) << C << " Вт·год\n";
    cout << "Вік станції: " << years << " р.\n";
    cout << "Фактична ємність: " << fixed << setprecision(1) << C_eff << " Вт·год\n";
    cout << "Рівень заряду станції: " << charge << "%\n";
    cout << "ККД інвертора: " << eff << "%\n";
    cout << "Енергія, збережена в моделі: " << fixed << setprecision(1) << E_stored << " Вт·год\n";
    cout << "Запас енергії: " << fixed << setprecision(1) << E_stored << " Вт·год\n";
    cout << "Корисна енергія: " << fixed << setprecision(1) << E_useful << " Вт·год\n";
    cout << "Втрати енергії: " << fixed << setprecision(1) << E_loss << " Вт·год\n";
    cout << "Час роботи: " << fixed << setprecision(2) << T << " год = " << h << " год ";
    if (m >= 10) cout << m << " хвилин\n";
    else
    cout << "0" << m << " хвилин\n";

    return 0;
}