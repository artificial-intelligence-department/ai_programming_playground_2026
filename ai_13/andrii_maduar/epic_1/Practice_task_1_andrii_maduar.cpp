#include <iostream>
#include <cmath>
#include <locale>
#include<string> // Бібліотеки
using namespace std;

int main(){
   setlocale (LC_ALL, "Uk_ua.UTF-8");
   const int name_limit = 31; // Максимальна довжина назви model
   const double age_losses = 2.0; // % ємніть що втрачається за рік
   const double percentage = 100.0; // для переведення з відсотків
   const int min_in_hr = 60; // для переведення часу
   string model;
   double C = 0.0;
   int years = 0;
   int charge = 0;
   double eff = 0.0;
   double P = 0.0; // створюю змінні щоб їх далі вводити і використовували
   cout << "Модель станції(не більше 31 символу): ";
   cin >> model;
   if (model.length() > name_limit) {
      cout << "Помилка: назва моделі перевищує 31 символ" << endl;
      return 1; // Виведення помилки і завершення роботи програми(з іншими змінними зроблю схоже)
    }
   cout << "Ємність(в Вт*год) ";
    cin >> C;
    if (C <= 0.0) {
        cout << "Помилка: ємність повинна бути > 0" << endl;
        return 1;
    }
    cout << "Вік: ";
    cin >> years;
    if (years < 0 || years > 20) {
        cout << "Помилка: кількість років повинна бути від 0 до 20" << endl;
        return 1;
    }
    cout << "Рівень заряду: ";
    cin >> charge;
    if (charge < 0 || charge > 100) {
        cout << "Помилка: рівень заряду повинен бути від 0 до 100" << endl;
        return 1;
    }
    cout << "Ефективність: ";
    cin >> eff;
    if (eff <= 0.0 || eff > 100.0) {
        cout << "Помилка: ефективність повинна бути більше 0 до 100" << endl;
        return 1;
    }
    cout << "Потужність: ";
    cin >> P;
    if (P <= 0.0) {
        cout << "Помилка: потужність повинна бути > 0" << endl;
        return 1;
    }
    // пішло обрахування формул
    double c_eff = C * pow(1.0 - (age_losses / percentage), years);
    double E_stored = c_eff * charge/percentage;
    double E_useful = E_stored * eff/percentage;
    double E_loss = E_stored - E_useful;
    double T = E_useful / P;
    int h = (int)T;
    int m = (int)((T - h) * min_in_hr);
    // виведення результатів
    cout << "Модель станції: " << model << endl;
    cout << "Ємність: " << C << " Вт*год" << endl;
    cout << "Вік: " << years << " років" << endl;
    cout << "Фактична ємність: " << c_eff << " Вт*год" << endl;
    cout << "Рівень заряду: " << charge << "%" << endl;
    cout << "ККД: " << eff << "%" << endl;
    cout << "Запас енергії: " << E_stored << " Вт*год" << endl;
    cout << "Корисна енергія: " << E_useful << " Вт*год" << endl;
    cout << "Втрати енергії: " << E_loss << " Вт*год" << endl;
    cout << "Час роботи: " << h << " годин " << m << " хвилин" << endl;
    return 0;
}
