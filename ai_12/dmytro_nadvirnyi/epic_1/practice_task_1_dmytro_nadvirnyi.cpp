/*
    Автономність портативної зарядної станції
    Автор: Дмитро Надвірний
    Група: 12
*/

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

double C;
int years;
int charge;
double eff;
double P;
string name;

const double LOSS_PER_YEAR = 2.0; // Відсоток втрати ємності за один рік

int main() {
    cout << "Введіть ім'я станції: ";
    if (!(cin >> name) || name.length() > 31) { 
        cout << "Помилка: неправильно вказана модель станції." << endl;
        return 1; // Завершення програми з кодом помилки
    }
    cout << "Введіть паспортну ємність (Вт·год): ";
    if (!(cin >> C) || C <= 0) {
        cout << "Помилка: Паспортна ємність повинна бути числом та повинна бути більше нуля." << endl;
        return 1;
    }

    cout << "Введіть вік станції: ";
    if (!(cin >> years) || years < 0 || years > 20) {
        cout << "Помилка: Вік станції повинен бути числом в діапазоні від 0 до 20." << endl;
        return 1;
    }

    cout << "Введіть рівень заряду станції: ";
    if (!(cin >> charge) || charge < 0 || charge > 100) {
        cout << "Помилка: Рівень заряду повинен бути числом та повинен бути в діапазоні від 0 до 100." << endl;
        return 1;
    }

    cout << "ККД інвертора (%): ";
    if (!(cin >> eff) || eff <= 0 || eff > 100) {
        cout << "Помилка: ККД повинен бути числом та повинен бути в діапазоні від 0 до 100." << endl;
        return 1;
    }

    cout << "Введіть потужність приладу (Вт): ";
    if (!(cin >> P) || P <= 0) {
        cout << "Помилка: Потужність приладу повинна бути числом та повинна бути більше нуля." << endl;
        return 1;
    }

    // Фактична ємність станції після врахування її віку, Вт·год
    // LOSS_PER_YEAR — відсоток втрати ємності за один рік
    double C_eff = C * pow((1 - LOSS_PER_YEAR / 100), years);

    // Енергія, яка зараз зберігається в станції, Вт·год
    double E_stored = C_eff * charge / 100;

    // Корисна енергія, яку можна отримати від станції, Вт·год
    double E_useful = E_stored * eff / 100;

    // Енергія, яка втрачається під час роботи інвертора, Вт·год
    double E_loss = E_stored - E_useful;

    // Час роботи приладу від станції, год
    double Time = E_useful / P;

    // Ціла кількість годин роботи
    int hours = (int)Time;

    // Залишок часу роботи після повних годин, хв
    int minutes = (int)((Time - hours) * 60);

    /* Вивід результатів */

    cout << "Модель: " << setw(27) << name << "\n"
         << "Паспортна ємність: " << fixed << setprecision(1) << setw(16) << C << " Вт·год\n"
         << "Вік станції: " << setw(22) << years << " р.\n"
         << "Фактична ємність: " << fixed << setprecision(1) << setw(17) << C_eff << " Вт·год\n"
         << "Рівень заряду: " << setw(20) << charge << "%\n"
         << "ККД інвертора: " << fixed << setprecision(2) << setw(20) << eff << "%\n"
         << "Запас енергії: " << fixed << setprecision(1) << setw(20) << E_stored << " Вт·год\n"
         << "Корисна енергія: " << fixed << setprecision(1) << setw(18) << E_useful << " Вт·год\n"
         << "Втрати енергії: " << fixed << setprecision(1) << setw(19) << E_loss << " Вт·год\n"
         << "Час роботи: " << fixed << setprecision(2) << setw(23) << Time
         << " год = " << hours << " год " << setfill('0') << setw(2) << minutes << " хв" << endl;

    return 0;
}





