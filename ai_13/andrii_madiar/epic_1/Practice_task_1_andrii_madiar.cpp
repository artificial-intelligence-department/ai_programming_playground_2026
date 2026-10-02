/* Назва задачі: Автономність портативної зарядної станції
Автор: Мадяр Андрій
Група: ШІ-13
*/
// Бібліотеки для можливості виконання тих чи інших дій
#include <iostream>
#include <cmath>
#include<string>
#include <iomanip>
using namespace std;

int main(){
   // Максимальна довжина назви model щоб потім перевіряти за критеріями
   const int name_limit = 31;
   // % ємніть що втрачається за рік для подальших розрахунків
   const double age_losses = 2.0;
   // для переведення з відсотків
   const double percentage = 100.0;
   // для переведення часу
   const int min_in_hr = 60;
   // створюю змінні для подальших внесень їхзначень користувачем
   string model;
   double C = 0.0;
   int years = 0;
   int charge = 0;
   double eff = 0.0;
   double P = 0.0;
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
    // розрахунок фактичної ємності з врахуванням віку(Вт*год)
    double c_eff = C * pow(1.0 - (age_losses / percentage), years);
    // розрахунок запасу енергії(Вт*год)
    double E_stored = c_eff * charge/percentage;
    // розрахунок корисної енергії(Вт*год)
    double E_useful = E_stored * eff/percentage;
    // розрахунок втрат енергії(Вт*год)
    double E_loss = E_stored - E_useful;
    // розрахунок часу роботи(год)
    double T = E_useful / P;
    // розрахунок цілих годин(год)
    int h = (int)T;
    //розрахунок хвилин(хв)
    int m = (int)((T - h) * min_in_hr);
    // виведення результатів
    cout << "" << endl;
    cout << fixed << left << setw(41) << "Модель станції: "                                              << model << endl;
    cout << fixed << left << setw(35) << "Ємність: "                << fixed << setprecision(1) << C << " Вт*год" << endl;
    cout << fixed << left << setw(31) << "Вік: "                                             << years << " років" << endl;
    cout << fixed << left << setw(43) << "Фактична ємність: "   << fixed << setprecision(1) << c_eff << " Вт*год" << endl;
    cout << fixed << left << setw(40) << "Рівень заряду: "                                       << charge << "%" << endl;
    cout << fixed << left << setw(31) << "ККД: "                        << fixed << setprecision(2) << eff << "%" << endl;
    cout << fixed << left << setw(40) << "Запас енергії: "   << fixed << setprecision(1) << E_stored << " Вт*год" << endl;
    cout << fixed << left << setw(42) << "Корисна енергія: " << fixed << setprecision(1) << E_useful << " Вт*год" << endl;
    cout << fixed << left << setw(41) << "Втрати енергії: "    << fixed << setprecision(1) << E_loss << " Вт*год" << endl;
    cout << fixed << left << setw(37) << "Час роботи: " << fixed << setprecision(2)<< T << " годин = " << h << " годин " << m << " хвилин" << endl;
    return 0;
}
 