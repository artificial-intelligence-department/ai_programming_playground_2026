/*Автономність портативної зарядної станції 
  Човган ШІ-14*/
#include <iostream>
#include <cmath> //Додано для рахування степіння у 22 рядку 
#include <iomanip> // Для форматування вихідних даних
using namespace std; //використовує std для всього подальшого коду
int main() {
    string model ;
    cout << "Введіть модель станції "; 
    cin >> model ;
    int years, charge, h,m;  //Вводить функції з цілими числами
    float C, C_eff, E_stored, eff, E_useful, E_loss, p, T;  //Вводить функції з дробовими числами
    cout << "Введіть паспортну ємність Вт·год " ;
     if(!(cin >> C ) || C <= 0) {
        cout << "Паспортна ємність має бути більша за 0";
        return 1 ;
    }
    cout << "Введіть вік станції ";
    if( !(cin >> years ) || years < 0 || years > 20){
        cout << "Вік має бути більшим  0 та меншим 20";
        return 1;
    }
    C_eff = C * pow(1 - 2.0 / 100, years);
    cout << "Введіть Рівень заряду,% ";
    if (!(cin >> charge) || charge <0 || charge > 100) {
        cout << "Рівень заряду має бути більшим 0 та меншим 100";
        return 1;
    }
    E_stored = C_eff * charge / 100.0;
    cout << "Введіть ККД інвертора,% ";
    if( !(cin >> eff ) || eff <= 0 || eff > 100){
        cout << "ККД має бути більшим 0 та меншим 100";
        return 1;
    }
    E_useful = E_stored * eff / 100;
    E_loss = E_stored - E_useful;
    cout << "Введіть Потужність приладу, Вт ";
    if(!(cin >> p ) || p <= 0){
        cout << "Потужність має бути більша за 0";
        return 1;
    }
    T = E_useful / p;
    h = floor(T);
    m = floor(((T - h) * 60));
    //Виводимо всі результати
    //
    cout << left << setw(34) << "Модель:" << model << endl;
    cout << left << setw(44) << "Паспортна ємність:" << fixed << setprecision(1) << C << " Вт·год" << endl;
    cout << left << setw(38) << "Вік станції:" << years << " років" << endl;
    cout << left << setw(43) << "Фактична ємність:" << fixed << setprecision(1) << C_eff << " Вт·год" << endl;
    cout << left << setw(40) << "Рівень заряду:" << charge << "%" << endl;
    cout << left << setw(40) << "ККД інвертора:" << fixed << setprecision(2) << eff << "%" << endl;
    cout << left << setw(40) << "Запас енергії:" << fixed << setprecision(1)  << E_stored << " Вт·год" << endl;
    cout << left << setw(42) << "Корисна енергія:" << fixed << setprecision(1) << E_useful << " Вт·год" << endl;
    cout << left << setw(48) << "Втрати на перетворенні:" << fixed << setprecision(1) << E_loss << " Вт·год" << endl; 
    cout << left << setw(37) << "Час роботи:" << fixed << setprecision(2) << T << " год =" << h << " год" 
    << setw(2) << setfill('0') << m << " хв" << endl;

    return 0;

}
