/*
Автономність портативної зарядної станції
Проскурня Дмитро
ШІ-13
*/

#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    // ввід даних
    std::string model{};
    std::cout << "Модель станції: ";
    std::cin >> model;
    if (model.size() > 31) {
        std::cout << "Помилка: модель станції мусить бути меньше за 31 симовол.";
        return 1;
    }

    double pass_capacity{};
    std::cout << "Паспортна ємність (Вт·год): ";
    std::cin >> pass_capacity;
    if (pass_capacity <= 0) {
        std::cout << "Паспорна ємність мусить бути більше за 0.";
        return 1;
    }

    int age_of_station{};
    std::cout << "Вік станції (років): ";
    std::cin >> age_of_station;
    if (age_of_station < 0 || age_of_station > 20) {
        std::cout << "Помилка: вік станції мусить бути від 0 до 20.";
        return 1;
    }

    int charge_level{};
    std::cout << "Рівень заряду (%): ";
    std::cin >> charge_level;
    if (charge_level < 0 || charge_level > 100) {
        std::cout << "Помилка: рівень заряду станції мусить бути від 0 до 100.";
        return 1;
    }

    double inventor_efficiency{};
    std::cout << "ККД інвертора (%): ";
    std::cin >> inventor_efficiency;
    if (inventor_efficiency <= 0 || inventor_efficiency > 100) {
        std::cout << "Помилка: ККД інвентора станції мусить бути від 0 до 100.";
        return 1;
    }

    double device_power{};
    std::cout << "Потужність приладу (Вт): ";
    std::cin >> device_power;
    if (device_power <= 0) {
        std::cout << "Помилка: потужність приладу мусить бути більше за 0";
        return 1;
    }

    // розрахунки
    const double kLossPercentage = 2.0 / 100.0;
    // Відсоток втрати аккамулятора
    double C_eff = pass_capacity * std::pow((1.0 - kLossPercentage), age_of_station);
    // Фактична ємність з урахуванням віку Вт·год
    double E_stored = C_eff * charge_level / 100.0;
    // Запас енергії при поточному заряді, Вт·год
    double E_useful = E_stored * inventor_efficiency / 100.0;
    // Корисна енергія, що дійде до приладу, Вт·год
    double E_loss = E_stored - E_useful;
    // Втрати на перетворенні напруги, Вт·год
    double T = E_useful / device_power;
    // Час роботи, годин
    int h = static_cast<int>(T);
    // Повні години
    int m = static_cast<int>((T - h) * 60);
    // Хвилини, що залишились

    // вивід програми
    std::cout                                       << "\nМодель: "               << model                                 << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "Паспортна ємність: "      << pass_capacity            << " Вт·год" << std::endl;
    std::cout                                       << "Вік станції: "            << age_of_station           << " р."     << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "Фактична ємність: "       << C_eff                    << " Вт·год" << std::endl;
    std::cout                                       << "Рівень заряду: "          << charge_level             << " %"      << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "ККД інвертора: "          << inventor_efficiency      << " %"      << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "Запас енергії: "          << E_stored                 << " Вт·год" << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "Корисна енергія: "        << E_useful                 << " Вт·год" << std::endl;
    std::cout                                       << "Втрати на перетворенні: " << E_loss                   << " Вт·год" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Час роботи: "             << T                        << " год = ";
    std::cout                                                                     << h                        << " год ";
    std::cout                                                                     << (m < 10 ? "0" : "") << m << " хв\n";

    return 0;
}
