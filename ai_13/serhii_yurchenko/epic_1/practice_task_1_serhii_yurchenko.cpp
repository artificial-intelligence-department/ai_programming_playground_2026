/*
 * Назва задачі: Автономність портативної зарядної станції
 * Автор: Serhii Yurchenko
 * Група: AI-13
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    // Вхідні дані
    string model;
    double C;       // Паспортна ємність, Вт·год
    int years;      // Вік станції, років
    int charge;     // Рівень заряду, %
    double eff;     // ККД інвертора, %
    double P;       // Потужність приладу, Вт

    // Константи задачі
    const double DEGRADATION_PER_YEAR = 2.0; // Щорічна втрата ємності (%)

    // Введення даних з підказками
    cout << "Модель станції: ";
    if ((cin >> model) && model.length() <= 31) {
        // Успішне зчитування
    } else {
        cout << "Помилка: назва моделі занадто довга або некоректна!" << endl;
        return 1;
    }

    cout << "Паспортна ємність (Вт·год): ";
    if ((cin >> C) && C > 0) {
        // Успішне зчитування
    } else {
        cout << "Помилка: ємність мусить бути більше 0!" << endl;
        return 1;
    }

    cout << "Вік станції (років): ";
    if ((cin >> years) && years >= 0 && years <= 20) {
        // Успішне зчитування
    } else {
        cout << "Помилка: вік станції мусить бути від 0 до 20 років!" << endl;
        return 1;
    }

    cout << "Рівень заряду (%): ";
    if ((cin >> charge) && charge >= 0 && charge <= 100) {
        // Успішне зчитування
    } else {
        cout << "Помилка: рівень заряду мусить бути від 0 до 100%!" << endl;
        return 1;
    }

    cout << "ККД інвертора (%): ";
    if ((cin >> eff) && eff > 0 && eff <= 100) {
        // Успішне зчитування
    } else {
        cout << "Помилка: ККД інвертора мусить бути в межах від 0 до 100%!" << endl;
        return 1;
    }

    cout << "Потужність приладу (Вт): ";
    if ((cin >> P) && P > 0) {
        // Успішне зчитування
    } else {
        cout << "Помилка: потужність мусить бути більше 0!" << endl;
        return 1;
    }

    // 1. Фактична ємність з урахуванням деградації 2% на рік 
    double C_eff = C;
    double factor = 1.0 - (DEGRADATION_PER_YEAR / 100.0);
    for (int i = 0; i < years; ++i) {
        C_eff *= factor;
    }

    // 2. Запас енергії при поточному рівні заряду
    double E_stored = C_eff * (charge / 100.0);

    // 3. Корисна енергія з урахуванням ККД інвертора
    double E_useful = E_stored * (eff / 100.0);

    // 4. Втрати на перетворенні напруги
    double E_loss = E_stored - E_useful;

    // 5. Загальний час роботи в годинах
    double T = E_useful / P;

    // 6. Розрахунок годин та хвилин
    int hours = static_cast<int>(T);
    int minutes = static_cast<int>((T - hours) * 60.0);

    // Форматований вивід результатів
    cout << "\n=== Результати обчислення ===" << endl;
    
    cout << left << setw(28) << "Модель:" << model << endl;
    
    cout << fixed << setprecision(1);
    cout << left << setw(28) << "Паспортна ємність:" << C << " Вт·год" << endl;
    cout << left << setw(28) << "Вік станції:" << years << " р." << endl;
    cout << left << setw(28) << "Фактична ємність:" << C_eff << " Вт·год" << endl;
    cout << left << setw(28) << "Рівень заряду:" << charge << " %" << endl;
    
    cout << fixed << setprecision(2);
    cout << left << setw(28) << "ККД інвертора:" << eff << " %" << endl;
    
    cout << fixed << setprecision(1);
    cout << left << setw(28) << "Запас енергії:" << E_stored << " Вт·год" << endl;
    cout << left << setw(28) << "Корисна енергія:" << E_useful << " Вт·год" << endl;
    cout << left << setw(28) << "Втрати на перетворенні:" << E_loss << " Вт·год" << endl;
    
    cout << fixed << setprecision(2);
    cout << left << setw(28) << "Час роботи:" << T << " год = "
         << hours << " год " << setfill('0') << setw(2) << minutes << setfill(' ') << " хв" << endl;

    return 0;
}
