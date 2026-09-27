/* Задача: Автономність портативної зарядної станції
* Поліщук Вероніка
* Група 14
*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main() {
    // Вхідні змінні
    // string потрібна для роботи з текстом, виведення в кінці та перевірка довжини
    string model;
    double capacity;
    int years;
    int charge;
    double eff;
    double power;

    // Відсоток деградації акумулятора за рік
    const double deg = 2.0;

    // Ввід та перевірка моделі станції
    cout << "Модель станції: ";
    if (!(cin >> model) || model.length() > 31) {
        cout << "Помилка: некоректні вхідні дані." << endl;
        return 1;
    }

    // Ввід та перевірка паспортної ємності
    cout << "Паспортна ємність (Вт·год): ";
    if (!(cin >> capacity) || capacity <= 0) {
        cout << "Помилка: некоректні вхідні дані." << endl;
        return 1;
    }

    // Ввід та перевірка віку станції
    cout << "Вік станції (років): ";
    if (!(cin >> years) || years < 0 || years > 20) {
        cout << "Помилка: некоректні вхідні дані." << endl;
        return 1;
    }

    // Ввід та перевірка рівня заряду
    cout << "Рівень заряду (%): ";
    if (!(cin >> charge) || charge < 0 || charge > 100) {
        cout << "Помилка: некоректні вхідні дані." << endl;
        return 1;
    }

    // Ввід та перевірка ККД інвертора
    cout << "ККД інвертора (%): ";
    if (!(cin >> eff) || eff <= 0 || eff > 100) {
        cout << "Помилка: некоректні вхідні дані." << endl;
        return 1;
    }

    // Ввід та перевірка потужності приладу
    cout << "Потужність приладу (Вт): ";
    if (!(cin >> power) || power <= 0) {
        cout << "Помилка: некоректні вхідні дані." << endl;
        return 1;
    }

    // Обчислюємо фактичну ємність з урахуванням зносу акумулятора за роки (Вт·год)
    double c_eff = capacity * pow(1.0 - (deg / 100.0), years);

    // Обчислюємо поточний запас енергії відповідно до відсотка заряду (Вт·год)
    double e_stored = c_eff * (charge / 100.0);

    // Обчислюємо корисну енергію з урахуванням втрат в інверторі (Вт·год)
    double e_useful = e_stored * (eff / 100.0);

    // Обчислюємо втрати енергії під час перетворення напруги (Вт·год)
    double e_loss = e_stored - e_useful;

    // Обчислюємо загальний час роботи приладу (годин)
    double t_total = e_useful / power;

    // Виділяємо кількість повних годин
    int hours = static_cast<int>(t_total);

    // Розраховуємо залишок у хвилинах
    int minutes = static_cast<int>((t_total - hours) * 60.0);

    // Вивід результатів із вирівнюванням по лівому краю
    cout << fixed;
    cout << "Модель:                 " << model << endl;
    cout << "Паспортна ємність:      " << setprecision(1) << capacity << " Вт·год" << endl;
    cout << "Вік станції:            " << years << " р." << endl;
    cout << "Фактична ємність:       " << setprecision(1) << c_eff << " Вт·год" << endl;
    cout << "Рівень заряду:          " << charge << " %" << endl;
    cout << "ККД інвертора:          " << setprecision(2) << eff << " %" << endl;
    cout << "Запас енергії:          " << setprecision(1) << e_stored << " Вт·год" << endl;
    cout << "Корисна енергія:        " << setprecision(1) << e_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні: " << setprecision(1) << e_loss << " Вт·год" << endl;
    cout << "Час роботи:             "
         << setprecision(2) << t_total << " год  = "
         << hours << " год "
         << setfill('0') << setw(2) << minutes << " хв" << endl;

    return 0;
}