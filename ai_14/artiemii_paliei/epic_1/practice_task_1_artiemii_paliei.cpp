/*
    Автономність портативної зарядної станції
    Прізвище: Палєй
    Група: ШІ-14
*/

#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>

int main()
{
    // змінні, що вводить користувач

    std::string ModelName; // Назва станції
    float C;               // Ємність (Вт*год)
    int years;             // Вік станції (Роки)
    int charge;            // Заряд станції (%)
    double eff;            // ККД станції (%)
    double P;              // Потужність станції (Вт)

    // процес вводу зміних користувачем і їх перевірка на правильність вводу

    std::cout << "Модель станції (одним словом): ";
    std::cin >> ModelName;
    if (ModelName.length() > 31)
    {
        std::cout << "Значення перевищує допустимий ліміт символів (31)" << std::endl;
        return 1;
    }

    std::cout << "Паспортна ємність (Вт·год): ";
    if (!(std::cin >> C) || C <= 0)
    {
        std::cout << "Ємність повинна бути числом більшим за 0" << std::endl;
        return 1;
    }

    std::cout << "Вік станції (років): ";
    if (!(std::cin >> years) || years < 0 || years > 20)
    {
        std::cout << "Вік станції повинен бути числом в діапазоні від 0 до 20 років" << std::endl;
        return 1;
    }

    std::cout << "Рівень заряду (%): ";
    if (!(std::cin >> charge) || charge < 0 || charge > 100)
    {
        std::cout << "Заряд станції повинен бути числом в діпазоні від 0 до 100%" << std::endl;
        return 1;
    }

    std::cout << "ККД інфертора (%): ";
    if (!(std::cin >> eff) || eff >= 100 || eff <= 0)
    {
        std::cout << "ККД зарядної станції повинен бути числом в діапазоні від 1 до 100" << std::endl;
        return 1;
    }

    std::cout << "Потужність приладу (Вт): ";
    if (!(std::cin >> P) || P <= 0)
    {
        std::cout << "Потужність приладу повинна бути числом більшим за 0" << std::endl;
        return 1;
    }

    // Створення констант для уникнення magic numbers
    const double hudred_percent = 100.0;             // 100%
    const double year_loss = 1 - 2 / hudred_percent; // Річна втрата ємності
    const int mins_in_hour = 60; // Хвилини у годині (60)

    // Обчислення зміних...

    // Загальний коефіцієнт втрати за певну кількість років
    double loss_coefficient = pow(year_loss, years);

    // Фактична ємність з урахуванням віку (Вт·год)
    double C_eff = C * loss_coefficient;

    // Запас енергії при поточному заряді акумулятора (Вт)
    double E_stored = C_eff * charge / hudred_percent;

    // Корисна енергія, що дійде до приладу (Вт)
    double E_useful = E_stored * eff / hudred_percent;

    // Втрата на перетворення напруги (Вт*год)
    double E_loss = E_stored - E_useful;

    // Час роботи (Години)
    double T = E_useful / P;

    // Повні години роботи (Години)
    int h = int(E_useful / P);

    // Хвилини, що залишились (Хвилини)
    int m = int((T - h) * mins_in_hour);

    // Вивід інформації
    std::cout << "______Інформація про станцію______" << std::endl;
    std::cout << "Назва станції:\t\t" << ModelName << std::endl;
    std::cout << "Паспортна ємність:\t" << C << " Вт*год" << std::endl;
    std::cout << "Вік станції:\t\t" << years << " р." << std::endl;
    std::printf("Фактична ємність:\t%.1f Вт*год\n", C_eff);
    std::cout << "Рівень заряду:\t\t" << charge << " %" << std::endl;
    std::cout << "ККД станції:\t\t" << eff << " %" << std::endl;
    std::printf("Запас енергії:\t\t%.1f Вт*год\n", E_stored);
    std::printf("Корисна енергія:\t%.1f Вт*год\n", E_useful);
    std::printf("Втрати на перетворенні:\t%.1f Вт*год\n", E_loss);
    std::printf("Час роботи:\t\t%.2f год = %i год %i хв\n", T, h, m);
    return 0;
}