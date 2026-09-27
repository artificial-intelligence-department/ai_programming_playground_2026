/*
 * Автономність портативної зарядної станції
 * Ткач Артем
 * ШІ-13
 */

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

int main() {
    // Відсоток деградації ємності акумулятора за один рік
    const double DEGRADATION_RATE_PER_YEAR = 2.0;

    std::string model; // Назва моделі акумулятора
    double capacity;   // Заявлена ємність акумулятора (Вт*год)
    int years;         // Вік акумулятора у роках
    int charge;        // Заряд (%)
    double efficiency; // ККД інвертора (%)
    double power;      // Потужність (Вт)

    // Введення та валідація даних
    std::cout << "Модель станції: ";
    if (!(std::cin >> model) || model.length() > 31) {
        std::cout << "Помилка: некоректна модель станції.\n";
        return 1;
    }

    std::cout << "Паспортна ємність (Вт·год): ";
    if (!(std::cin >> capacity) || capacity <= 0) {
        std::cout << "Помилка: паспортна ємність мусить бути більше 0.\n";
        return 1;
    }

    std::cout << "Вік станції (років): ";
    if (!(std::cin >> years) || years < 0 || years > 20) {
        std::cout << "Помилка: вік станції мусить бути від 0 до 20.\n";
        return 1;
    }

    std::cout << "Рівень заряду (%): ";
    if (!(std::cin >> charge) || charge < 0 || charge > 100) {
        std::cout << "Помилка: рівень заряду мусить бути від 0 до 100.\n";
        return 1;
    }

    std::cout << "ККД інвертора (%): ";
    if (!(std::cin >> efficiency) || efficiency <= 0 || efficiency > 100) {
        std::cout << "Помилка: ККД інвертора мусить бути від 0 до 100.\n";
        return 1;
    }

    std::cout << "Потужність приладу (Вт): ";
    if (!(std::cin >> power) || power <= 0) {
        std::cout << "Помилка: потужність приладу мусить бути більше 0.\n";
        return 1;
    }

    // Фактична ємність з урахуванням деградації за роки, Вт·год
    double c_eff = capacity * std::pow(1.0 - DEGRADATION_RATE_PER_YEAR / 100.0, years);
    // Запас енергії при поточному рівні заряду, Вт·год
    double e_stored = c_eff * charge / 100.0;
    // Корисна енергія, що дійде до приладу через інвертор, Вт·год
    double e_useful = e_stored * efficiency / 100.0;
    // Втрати енергії на перетворенні напруги в інверторі, Вт·год
    double e_loss = e_stored - e_useful;

    // Час роботи приладу від накопиченої корисної енергії, год
    double t_hours = e_useful / power;
    // Повні години роботи — ціла частина часу
    int hours = static_cast<int>(t_hours);
    // Хвилини понад повні години — ціла частина залишку часу, помножена на 60
    int minutes = static_cast<int>((t_hours - hours) * 60.0);
    if (minutes == 60) {
        hours += 1;
        minutes = 0;
    }

    // Вивід результатів
    std::cout << "\n";
    std::cout << "Модель:                  " << model << "\n";
    std::cout << "Паспортна ємність:       " << std::fixed << std::setprecision(1) << capacity << " Вт·год\n";
    std::cout << "Вік станції:             " << years << " р.\n";
    std::cout << "Фактична ємність:        " << std::fixed << std::setprecision(1) << c_eff << " Вт·год\n";
    std::cout << "Рівень заряду:           " << charge << " %\n";
    std::cout << "ККД інвертора:           " << std::fixed << std::setprecision(2) << efficiency << " %\n";
    std::cout << "Запас енергії:           " << std::fixed << std::setprecision(1) << e_stored << " Вт·год\n";
    std::cout << "Корисна енергія:         " << std::fixed << std::setprecision(1) << e_useful << " Вт·год\n";
    std::cout << "Втрати на перетворенні:  " << std::fixed << std::setprecision(1) << e_loss << " Вт·год\n";

    std::cout << "Час роботи:              " << std::fixed << std::setprecision(2) << t_hours << " год  = " 
              << hours << " год " << (minutes < 10 ? "0" : "") << minutes << " хв\n";

    return 0;
}