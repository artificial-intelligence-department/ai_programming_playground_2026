/*
 * Задача: Автономність портативної зарядної станції
 * Автор: Овчарова Аріна
 * Група: ШІ-12
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main() {
    // Введення початкових даних та перевірка коректності

    string model;
    cout << "Модель станції: ";
    cin >> model;
    if (model.length() > 31) {
        cout << "Помилка: назва моделі не повинна перевищувати 31 символ." << endl;
        return 1;
    }

    double C;
    cout << "Паспортна ємність (Вт*год): ";
    cin >> C;
    if (cin.fail() || C <= 0) {
        cout << "Помилка: паспортна ємність мусить бути додатним числом." << endl;
        return 1;
    }

    int years;
    cout << "Вік станції (років): ";
    cin >> years;
    if (cin.fail() || years < 0 || years > 20) {
        cout << "Помилка: вік станції мусить бути від 0 до 20." << endl;
        return 1;
    }

    int charge;
    cout << "Рівень заряду (%): ";
    cin >> charge;
    if (cin.fail() || charge < 0 || charge > 100) {
        cout << "Помилка: рівень заряду мусить бути від 0 до 100." << endl;
        return 1;
    }

    double eff;
    cout << "ККД інвертора (%): ";
    cin >> eff;
    if (cin.fail() || eff <= 0 || eff > 100) {
        cout << "Помилка: ККД інвертора мусить бути більше 0 і не більше 100." << endl;
        return 1;
    }

    double P;
    cout << "Потужність приладу (Вт): ";
    cin >> P;
    if (cin.fail() || P <= 0) {
        cout << "Помилка: потужність приладу мусить бути додатним числом." << endl;
        return 1;
    }

    // Обчислення параметрів роботи станції

    // Втрата ємності 2% за кожен рік експлуатації
    const double degradationPerYear = 2.0;

    // Обчислюємо реальну ємність з урахуванням зносу
    double C_eff = C * pow(1.0 - degradationPerYear / 100.0, years);

    // Запас енергії при поточному рівні заряду
    double E_stored = C_eff * charge / 100.0;

    // Корисна енергія з урахуванням ККД інвертора
    double E_useful = E_stored * eff / 100.0;

    // Втрати енергії при перетворенні
    double E_loss = E_stored - E_useful;

    // Розрахунок часу роботи приладу (в годинах і хвилинах)
    double T = E_useful / P;
    int h = (int)T;
    int m = (int)((T - h) * 60.0);

    // Форматований вивід результатів

    cout << "\n--- Результати розрахунку ---" << endl;
    cout << fixed;
    cout << left << setw(25) << "Модель:" << model << endl;
    cout << left << setw(25) << "Паспортна ємність:" << setprecision(1) << C << " Вт*год" << endl;
    cout << left << setw(25) << "Вік станції:" << years << " р." << endl;
    cout << left << setw(25) << "Фактична ємність:" << setprecision(1) << C_eff << " Вт*год" << endl;
    cout << left << setw(25) << "Рівень заряду:" << charge << " %" << endl;
    cout << left << setw(25) << "ККД інвертора:" << setprecision(2) << eff << " %" << endl;
    cout << left << setw(25) << "Запас енергії:" << setprecision(1) << E_stored << " Вт*год" << endl;
    cout << left << setw(25) << "Корисна енергія:" << setprecision(1) << E_useful << " Вт*год" << endl;
    cout << left << setw(25) << "Втрати на перетворенні:" << setprecision(1) << E_loss << " Вт*год" << endl;
    cout << left << setw(25) << "Час роботи:" << setprecision(2) << T << " год  = "
         << h << " год " << right << setw(2) << setfill('0') << m << " хв" << endl;

    return 0;
}
