/*
 * Задача: Автономність портативної зарядної станції
 * Автор: Illia Strazhets
 * Група: AI-13
 */

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    // Оголошення змінних для введення даних користувачем
    string model;
    double C;
    int years;
    int charge;
    double eff;
    double P;

    // ВВід користувачем значень параметрів станції та приладу

    cout << "Модель станції: ";
    cin >> model;
    if (model.length() > 31)
    {
        cout << "Помилка: Назва моделі задовга." << endl;
        return 1; // Завершення програми з кодом помилки
    }

    cout << "Паспортна ємність (Вт·год): ";
    cin >> C;
    if (C <= 0)
    {
        cout << "Помилка: Паспортна ємність повинна бути додатнім числом." << endl;
        return 1; // Завершення програми з кодом помилки
    }

    cout << "Вік станції (років): ";
    cin >> years;
    if (years < 0)
    {
        cout << "Помилка: Вік станції не може бути від'ємним числом" << endl;
        return 1; // Завершення програми з кодом помилки
    }
    else if (years > 20)
    {
        cout << "Помилка: Вік станції не може перевищувати 20 років." << endl;
        return 1; // Завершення програми з кодом помилки
    }

    cout << "Рівень заряду (%): ";
    cin >> charge;
    if (charge < 0 || charge > 100)
    {
        cout << "Помилка: Рівень заряду повинен бути в межах від 0 до 100%." << endl;
        return 1; // Завершення програми з кодом помилки
    }

    cout << "ККД інвертора (%): ";
    cin >> eff;
    if (eff <= 0 || eff > 100)
    {
        cout << "Помилка: ККД інвертора повинен бути в межах від 0 до 100%." << endl;
        return 1; // Завершення програми з кодом помилки
    }

    cout << "Потужність приладу (Вт): ";
    cin >> P;
    if (P <= 0)
    {
        cout << "Помилка: Потужність приладу повинна бути додатнім числом." << endl;
        return 1; // Завершення програми з кодом помилки
    }

    // Оголошення змінних для розрахунків та розрахунки

    // 1. Розрахунок ефективної(фактичноЇ) ємності з урахуванням віку (Вт·год)
    double C_eff = C * pow((1 - 2 / 100.0), years);
    if (years == 0)
    {
        C_eff = C; // При years = 0 фактична ємність дорівнює паспортній.
    }

    // 2. Розрахунок запасу енергії при поточному заряді (Вт·год)
    double E_stored = C_eff * charge / 100;

    // 3. Розрахунок корисної енергії, що дійде до приладу (Вт·год)
    double E_useful = E_stored * eff / 100;

    // 4. Розрахунок втрат на перетворенні напруги (Вт·год)
    double E_loss = E_stored - E_useful;

    // 5. Розрахунок автономності станції(годин роботи)
    double T = E_useful / P;

    // 6. Розрахунок повних годин та хвилин роботи
    int h = (int)T;              // Повні години роботи, ціле число T
    int m = (int)((T - h) * 60); // Хвилини, що залишилися

    // Вивід результатів розрахунків
    cout << " " << endl; // для красивого відступу між введенням даних та результатами
    cout << fixed << left << setw(40) << "Модель: " << model << endl;
    cout << fixed << left << setw(40) << "Паспортна ємність: " << fixed << setprecision(1) << C << " Вт·год" << endl;
    cout << fixed << left << setw(40) << "Вік станції: " << years << " р." << endl;
    cout << fixed << left << setw(40) << "Фактична ємність: " << fixed << setprecision(1) << C_eff << " Вт·год" << endl;
    cout << fixed << left << setw(40) << "Рівень заряду: " << charge << " %" << endl;
    cout << fixed << left << setw(40) << "ККД інвертора: " << fixed << setprecision(2) << eff << " %" << endl;
    cout << fixed << left << setw(40) << "Запас енергії: " << fixed << setprecision(1) << E_stored << " Вт·год" << endl;
    cout << fixed << left << setw(40) << "Корисна енергія: " << fixed << setprecision(1) << E_useful << " Вт·год" << endl;
    cout << fixed << left << setw(40) << "Втрати на перетворенні:  " << fixed << setprecision(1) << E_loss << " Вт·год" << endl;
    cout << fixed << left << setw(40) << "Час роботи: " << fixed << setprecision(2) << T << " год " << "= " << h << " год " << right << setfill('0') << setw(2) << m << " хв" << setfill(' ') << endl;
    return 0;
}
