/*
Задача:  Автономність портативної зарядної станції
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8");
    // Відсоток втрати ємності за рік експлуатації
    const double DEGRADATION_PER_YEAR = 2.0;

    string model;       // назва моделі станції
    double C;           // паспортна ємність, Вт·год
    int years;          // вік станції, років
    int charge;         // поточний рівень заряду, %
    double eff;         // ККД інвертора, %
    double P;           // потужність приладу, Вт

    // Модель станції: одне слово, не довше 31 символа
    cout << "Модель станції: ";
    cin >> model;
    if (cin.fail() || model.length() > 31) {
        cout << "Помилка: назва моделі станції не повинна перевищувати 31 символ." << endl;
        return 1;
    }

    // Паспортна ємність: додатне число
    cout << "Паспортна ємність (Вт·год): ";
    cin >> C;
    if (cin.fail() || C <= 0) {
        cout << "Помилка: паспортна ємність повинна бути додатним числом." << endl;
        return 1;
    }

    // Вік станції: ціле число від 0 до 20
    cout << "Вік станції (років): ";
    cin >> years;
    if (cin.fail() || years < 0 || years > 20) {
        cout << "Помилка: вік станції мусить бути від 0 до 20." << endl;
        return 1;
    }

    // Рівень заряду: ціле число від 0 до 100
    cout << "Рівень заряду (%): ";
    cin >> charge;
    if (cin.fail() || charge < 0 || charge > 100) {
        cout << "Помилка: рівень заряду мусить бути від 0 до 100." << endl;
        return 1;
    }

    // ККД інвертора: число більше 0 і не більше 100
    cout << "ККД інвертора (%): ";
    cin >> eff;
    if (cin.fail() || eff <= 0 || eff > 100) {
        cout << "Помилка: ККД інвертора мусить бути більше 0 і не більше 100." << endl;
        return 1;
    }

    // Потужність приладу: додатне число
    cout << "Потужність приладу (Вт): ";
    cin >> P;
    if (cin.fail() || P <= 0) {
        cout << "Помилка: потужність приладу повинна бути додатним числом." << endl;
        return 1;
    }

    // Крок 1: фактична ємність з урахуванням старіння акумулятора
    double C_eff = C * pow(1.0 - DEGRADATION_PER_YEAR / 100.0, years);

    // Крок 2: запас енергії при поточному рівні заряду
    double E_stored = C_eff * charge / 100.0;

    // Крок 3: корисна енергія, що дійде до приладу
    double E_useful = E_stored * eff / 100.0;

    // Крок 4: втрати на перетворенні напруги
    double E_loss = E_stored - E_useful;

    // Крок 5: час роботи приладу від станції
    double T = E_useful / P;

    // Крок 6-7: розкладаємо час роботи на повні години та хвилини, що залишились.
    int h = static_cast<int>(T);
    int m = static_cast<int>((T - h) * 60);

    // Вивід результатів
    cout << fixed << setprecision(1);
    cout << " " << endl;
    cout << "Модель: " << model << endl;
    cout << "Паспортна ємність: " << C << " Вт·год" << endl;
    cout << "Вік станції: " << years << " р." << endl;
    cout << "Фактична ємність: " << C_eff << " Вт·год" << endl;
    cout << "Рівень заряду: " << charge << " %" << endl;
    cout << setprecision(2) << "ККД інвертора: " << eff << " %" << endl;
    cout << setprecision(1) << "Запас енергії: " << E_stored << " Вт·год" << endl;
    cout << "Корисна енергія: " << E_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні: " << E_loss << " Вт·год" << endl;
    cout << setprecision(2) << "Час роботи: " << T << " год = "
         << h << " год " << setw(2) << setfill('0') << m << " хв" << endl;
         
    return 0;
}