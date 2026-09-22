/*
 * Назва задачі - Автономність портативної зарядної станції
 * Автор - Бакунець Андрій
 * Група: ШІ-12
 */
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <clocale>

using namespace std;

int main() {

    setlocale(LC_ALL, "uk_UA.UTF-8");

    double znoshenya = 2.0; // Втрата ємності за рік (%/рік)

    string model;
    double C, eff, P;
    int years, charge;

    cout << "Модель станції: ";
    getline(cin, model);

    if (model.length() > 31) { // Перевірка щоб назва була не довша 31 символа
        cout << "Помилка: назва моделі мусить бути не довшою 31 символа." << endl;
        return 1;
    }

    cout << "Паспортна ємність (Вт·год): ";
    cin >> C;
    if (C <= 0) { // Перевірка щоб ємність була більша за 0
        cout << "Помилка: паспортна ємність мусить бути більшою за 0." << endl;
        return 1;
    }

    cout << "Вік станції (років): ";
    cin >> years;
    if (years < 0 or years > 20) { // Перевірка щоб вік був від 0 до 20 років
        cout << "Помилка: вік станції мусить бути від 0 до 20." << endl;
        return 1;
    }

    cout << "Рівень заряду (%): ";
    cin >> charge;
    if (charge < 0 or charge > 100) { // Перевірка щоб заряд був від 0 до 100
        cout << "Помилка: рівень заряду мусить бути від 0 до 100." << endl;
        return 1;
    }

    cout << "ККД інвертора (%): ";
    cin >> eff;
    if (eff <= 0 or eff > 100) { // Перевірка щоб ККД був від 0 до 100
        cout << "Помилка: ККД інвертора мусить бути більшим за 0 і не більшим за 100." << endl;
        return 1;
    }

    cout << "Потужність приладу (Вт): ";
    cin >> P;
    if (P <= 0) { // Перевірка щоб потужність була більша за 0
        cout << "Помилка: потужність приладу мусить бути більшою за 0." << endl;
        return 1;
    }

    double C_eff = C * pow(1.0 - znoshenya / 100.0 , years); // Фактична ємність зі старінням (Вт·год)
    double E_stored = C_eff * charge / 100.0; // Запас енергії при поточному заряді (Вт·год)
    double E_useful = E_stored * eff / 100.0; // Корисна енергія з урахуванням ККД (Вт·год)
    double E_loss = E_stored - E_useful; // Втрати енергії при перетворенні (Вт·год)
    double T = E_useful / P; // Час автономної роботи (год)

    int h = T; // Ціла кількість годин
    int m = (T - h) * 60; // Залишок часу у хвилинах

    cout << endl;
    cout << "Модель:                  " << model << endl;

    cout << fixed << setprecision(1);
    cout << "Паспортна ємність:       " << C << " Вт·год" << endl;

    cout << defaultfloat;
    cout << "Вік станції:             " << years << " р." << endl;
   
    cout << fixed << setprecision(1);
    cout << "Фактична ємність:        " << C_eff << " Вт·год" << endl;

    cout << defaultfloat;
    cout << "Рівень заряду:           " << charge << " %" << endl;

    cout << fixed << setprecision(2);
    cout << "ККД інвертора:           " << eff << " %" << endl;

    cout << setprecision(1);
    cout << "Запас енергії:           " << E_stored << " Вт·год" << endl;
    cout << "Корисна енергія:         " << E_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні:  " << E_loss << " Вт·год" << endl;

    cout << setprecision(2);
    cout << "Час роботи:              " << T << " год  = ";
    
    cout << defaultfloat << h << " год ";
    if (m < 10) cout << "0"; // Перевірка чи менше 10 хв щоб додати нуль попереду
    cout << m << " хв" << endl;

    return 0;
}