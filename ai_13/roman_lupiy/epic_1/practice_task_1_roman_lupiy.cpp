/*
Автономність портативної зарядної станції
Лупій Роман
Група ШІ-13
*/

// Підключення бібліотек
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std; // Підключення стандартного простору імен

int main() {
    // Оголошення змінних
    string model;
    double C, charge, eff;
    int years, P;

    // Введення даних користувачем
    cout << "Модель станції: ";
    getline(cin, model);

    cout << "Паспортна ємність (Вт·год): ";
    cin >> C;

    cout << "Вік станції (років): ";
    cin >> years;

    cout << "Рівень заряду (%): ";
    cin >> charge;

    cout << "ККД інвертора (%): ";
    cin >> eff;

    cout << "Потужність приладу (Вт): ";
    cin >> P;

    // Перевірка довжини назви моделі
    if (model.length() > 31) {
        cout << "Помилка: назва моделі має бути не довшою за 31 символ.\n";
        return 1;
    }

    // Перевірка паспортної ємності
    if (C <= 0) {
        cout << "Помилка: паспортна ємність має бути більшою за нуль.\n";
        return 1;
    }

    // Перевірка віку станції
    if (years < 0 || years > 20) {
        cout << "Помилка: вік станції має бути від 0 до 20 років.\n";
        return 1;
    }

    // Перевірка рівня заряду
    if (charge < 0 || charge > 100) {
        cout << "Помилка: рівень заряду має бути від 0 до 100%.\n";
        return 1;
    }

    // Перевірка ККД інвертора
    if (eff < 0 || eff > 100) {
        cout << "Помилка: ККД має бути від 0 до 100%.\n";
        return 1;
    }

    // Перевірка потужності приладу
    if (P <= 0) {
        cout << "Помилка: потужність приладу має бути більшою за нуль.\n";
        return 1;
    }

    // Розрахунок фактичної ємності з урахуванням втрати 2% за кожен рік
    double actualCapacity = C * pow(0.98, years);

    // Розрахунок запасу енергії з урахуванням рівня заряду
    double storedEnergy = actualCapacity * charge / 100.0;

    // Розрахунок корисної енергії після перетворення інвертором
    double usefulEnergy = storedEnergy * eff / 100.0;

    // Розрахунок втрат енергії під час перетворення
    double loss = storedEnergy - usefulEnergy;

    // Розрахунок часу роботи приладу в годинах
    double runtime = usefulEnergy / P;

    // Переведення часу роботи в години та хвилини
    int hours = static_cast<int>(runtime);
    int minutes = static_cast<int>((runtime - hours) * 60);

    // Виведення результатів програми
    cout << "\nВивід програми\n";
    cout << fixed << setprecision(1);

    cout << "Модель:                       " << model << '\n';
    cout << "Паспортна ємність:            " << setw(8) << C
         << " Вт·год\n";
    cout << "Вік станції:                  " << setw(8) << years
         << " р.\n";
    cout << "Фактична ємність:             " << setw(8) << actualCapacity
         << " Вт·год\n";
    cout << "Рівень заряду:                " << setw(8) << charge
         << " %\n";

    cout << setprecision(2);
    cout << "ККД інвертора:                " << setw(8) << eff
         << " %\n";

    cout << setprecision(1);
    cout << "Запас енергії:                " << setw(8) << storedEnergy
         << " Вт·год\n";
    cout << "Корисна енергія:              " << setw(8) << usefulEnergy
         << " Вт·год\n";
    cout << "Втрати на перетворенні:       " << setw(8) << loss
         << " Вт·год\n";

    cout << setprecision(2);
    cout << "Час роботи:                   " << setw(5) << runtime
         << " год  = " << hours << " год "
         << setw(2) << setfill('0') << minutes << setfill(' ') << " хв\n";

    return 0; // Завершення програми
}