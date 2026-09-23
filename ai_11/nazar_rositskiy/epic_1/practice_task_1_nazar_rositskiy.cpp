#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    //оголошення змінних
    string model;
    double C, eff, P, C_eff, E_stored, E_useful, E_loss, T;
    int years, charge, h, m;
    //Отримання моделі
    cout << "Модель станції: ";
    getline(cin, model);
    //Перевірка значення 
    if(model.find(" ") != string::npos){
        cout << "Модель не може містити пробіли";
        return 1;
    } else if(model.length() > 31){
        cout << "Модель не може довшою за 31 літеру";
        return 1;
    } else if(model.empty()){
        cout << "Модель не може бути пустою";
        return 1;
    }
    //Отримання ємності
    cout << "Паспортна ємність, Вт·год: ";
    cin >> C;
    if(C <= 0){
        cout << "Введіть дійсне значення";
        return 1;
    }
    //Отримання віку
    cout << "Вік станції, років: ";
    cin >> years;
    if (cin.fail() || cin.peek() == ',' || cin.peek() == '.' || years > 20 || years < 0){
       cout << "Недопустимий формат вводу: значення має бути цілим числом від 0 до 20";
       return 1;
    }
    //Отримання заряду
    cout << "Рівень заряду, %: ";
    cin >> charge;
    if (cin.fail() || cin.peek() == ',' || cin.peek() == '.' || charge > 100 || charge < 0){
       cout << "Недопустимий формат вводу: значення має бути цілим числом від 0 до 100";
       return 1;
    }
    //Отримання ККД
    cout << "ККД інвертора, %: ";
    cin >> eff;
    if (cin.fail() || eff > 100 || eff <= 0){
       cout << "Недопустимий формат вводу: значення має бути цілим числом до 100 та більше за 0";
       return 1;
    }
    //Отримання потужності
    cout << "Потужність приладу, Вт: ";
    cin >> P;
    if(P <= 0){
        cout << "Введіть дійсне значення";
        return 1;
    }

    //C_eff = C*((98/100)^years);
    C_eff = C * pow(98.0 / 100.0, years);
    E_stored = C_eff * charge / 100.0;
    E_useful = E_stored * eff / 100.0;
    E_loss = E_stored - E_useful;
    T = E_useful / P;
    h = floor(T);
    m = floor((T-h)*60.0);

    cout << "Модель:                 " << model << endl;
    cout << "Паспортна ємність:      " << fixed << setprecision(1) << C << " Вт·год" << endl;
    cout << "Вік станції:            " << years << " р." << endl;
    cout << "Фактична ємність:       " << C_eff << " Вт·год" << endl;
    cout << "Рівень заряду:          " << charge << " %" << endl;
    cout << "ККД інвертора:          " << setprecision(0) << eff << " %" << endl;
    cout << "Запас енергії:          " << setprecision(1) << E_stored << " Вт·год" << endl;
    cout << "Корисна енергія:        " << E_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні: " << E_loss << " Вт·год" << endl;
    cout << "Час роботи:             " << setprecision(2) << T << " год = " << h << " год " << m << " хв" << endl;

}
   