/*
Назва задачі: «Автономність портативної зарядної станції»
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main()
{
    // Константи, які визначають умови задачі.
    const double CAPACITY_LOSS_PERCENT = 2.0; // Втрата ємності акумулятора за один рік, %.
    const double PERCENT = 100.0;             // Повна кількість відсотків для переведення у частку.
    const int MINUTES_IN_HOUR = 60;           // Кількість хвилин в одній годині.
    const int MAX_MODEL_LENGTH = 31;          // Максимальна довжина назви моделі.
    const int MAX_STATION_AGE = 20;           // Максимально допустимий вік станції, років.

    // Змінні для вхідних даних.
    string model;
    double C;
    int years;
    int charge;
    double eff;
    double P;

    cout << "Модель станції: ";
    if (!(cin >> model))
    {
        cout << "Помилка: не вдалося прочитати модель станції.\n";
        return 1;
    }

    if (model.length() > MAX_MODEL_LENGTH)
    {
        cout << "Помилка: назва моделі не може містити більше 31 символу.\n";
        return 1;
    }

    cout << "Паспортна ємність (Вт·год): ";
    if (!(cin >> C))
    {
        cout << "Помилка: паспортна ємність має бути числом.\n";
        return 1;
    }

    if (C <= 0)
    {
        cout << "Помилка: паспортна ємність мусить бути більшою за 0.\n";
        return 1;
    }

    cout << "Вік станції (років): ";
    if (!(cin >> years))
    {
        cout << "Помилка: вік станції має бути цілим числом.\n";
        return 1;
    }

    if (years < 0 || years > MAX_STATION_AGE)
    {
        cout << "Помилка: вік станції мусить бути від 0 до 20.\n";
        return 1;
    }

    cout << "Рівень заряду (%): ";
    if (!(cin >> charge))
    {
        cout << "Помилка: рівень заряду має бути цілим числом.\n";
        return 1;
    }

    if (charge < 0 || charge > PERCENT)
    {
        cout << "Помилка: рівень заряду мусить бути від 0 до 100.\n";
        return 1;
    }

    cout << "ККД інвертора (%): ";
    if (!(cin >> eff))
    {
        cout << "Помилка: ККД інвертора має бути числом.\n";
        return 1;
    }

    if (eff <= 0 || eff > PERCENT)
    {
        cout << "Помилка: ККД інвертора мусить бути більшим за 0 і не більшим за 100.\n";
        return 1;
    }

    cout << "Потужність приладу (Вт): ";
    if (!(cin >> P))
    {
        cout << "Помилка: потужність приладу має бути числом.\n";
        return 1;
    }

    if (P <= 0)
    {
        cout << "Помилка: потужність приладу мусить бути більшою за 0.\n";
        return 1;
    }

    // Переводимо річну втрату ємності з відсотків у частку.
    double annualCapacityPart = 1.0 - CAPACITY_LOSS_PERCENT / PERCENT;

    // Обчислюємо фактичну ємність станції з урахуванням її віку, Вт·год.
    double C_eff = C * pow(annualCapacityPart, years);

    // Обчислюємо запас енергії при поточному рівні заряду, Вт·год.
    double E_stored = C_eff * charge / PERCENT;

    // Обчислюємо корисну енергію, яка дійде до приладу, Вт·год.
    double E_useful = E_stored * eff / PERCENT;

    // Обчислюємо втрати енергії під час перетворення напруги, Вт·год.
    double E_loss = E_stored - E_useful;

    // Обчислюємо загальний час роботи станції, год.
    double T = E_useful / P;

    // Визначаємо кількість повних годин роботи.
    int hours = static_cast<int>(T);

    // Визначаємо кількість хвилин після відкидання повних годин.
    int minutes = static_cast<int>((T - hours) * MINUTES_IN_HOUR);

    cout << "\nРезультати обчислення\n\n";

cout << "Модель:                     " << model << '\n';

cout << fixed << setprecision(1);
cout << "Паспортна ємність:          " << C << " Вт·год\n";
cout << "Вік станції:                " << years << " р.\n";
cout << "Фактична ємність:           " << C_eff << " Вт·год\n";
cout << "Рівень заряду:              " << charge << " %\n";

cout << setprecision(2);
cout << "ККД інвертора:              " << eff << " %\n";

cout << setprecision(1);
cout << "Запас енергії:              " << E_stored << " Вт·год\n";
cout << "Корисна енергія:            " << E_useful << " Вт·год\n";
cout << "Втрати на перетворенні:     " << E_loss << " Вт·год\n";

cout << setprecision(2);
cout << "Час роботи:                 " << T << " год = "
     << hours << " год "
     << setfill('0') << setw(2) << minutes
     << setfill(' ') << " хв\n";

return 0;
}