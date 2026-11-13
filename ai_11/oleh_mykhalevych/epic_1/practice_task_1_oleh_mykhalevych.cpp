/*
 * Задача: Автономність портативної зарядної станції
 * Автор: Михалевич Олег Миколайович
 * Група: ШІ-11
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

int main() {
    std::string model;
    double capacity = 0.0;
    int years = 0;
    int charge = 0;
    double efficiency = 0.0;
    double power = 0.0;

    std::cout << "Модель станції: ";
    if (!(std::cin >> model) || model.length() > 31) {
        std::cout << "Помилка: некоректна назва моделі (максимум 31 символ)." << std::endl;
        return 1;
    }

    std::cout << "Паспортна ємність (Вт·год): ";
    if (!(std::cin >> capacity) || capacity <= 0.0) {
        std::cout << "Помилка: паспортна ємність мусить бути більшою за 0." << std::endl;
        return 1;
    }

    std::cout << "Вік станції (років): ";
    if (!(std::cin >> years) || years < 0 || years > 20) {
        std::cout << "Помилка: вік станції мусить бути від 0 до 20." << std::endl;
        return 1;
    }

    std::cout << "Рівень заряду (%): ";
    if (!(std::cin >> charge) || charge < 0 || charge > 100) {
        std::cout << "Помилка: рівень заряду мусить бути від 0 до 100." << std::endl;
        return 1;
    }

    std::cout << "ККД інвертора (%): ";
    if (!(std::cin >> efficiency) || efficiency <= 0.0 || efficiency > 100.0) {
        std::cout << "Помилка: ККД інвертора мусить бути більше 0 і не більше 100." << std::endl;
        return 1;
    }

    std::cout << "Потужність приладу (Вт): ";
    if (!(std::cin >> power) || power <= 0.0) {
        std::cout << "Помилка: потужність приладу мусить бути більшою за 0." << std::endl;
        return 1;
    }

    const double DEGRADATION_RATE_PER_YEAR = 2.0; // Відсоток втрати ємності акумулятора за рік експлуатації
    const double PERCENT_FACTOR = 100.0;          // Коефіцієнт для переведення відсотків у десяткову частку
    const double MINUTES_PER_HOUR = 60.0;         // Кількість хвилин в одній годині

    // Обчислюємо фактичну ємність станції з урахуванням щорічної деградації (Вт·год)
    double c_eff = capacity * std::pow(1.0 - (DEGRADATION_RATE_PER_YEAR / PERCENT_FACTOR), years);

    // Обчислюємо наявний запас енергії при поточному рівні заряду (Вт·год)
    double e_stored = c_eff * (charge / PERCENT_FACTOR);

    // Обчислюємо корисну енергію на виході інвертора з урахуванням його ККД (Вт·год)
    double e_useful = e_stored * (efficiency / PERCENT_FACTOR);

    // Обчислюємо втрати енергії на перетворенні напруги в інверторі (Вт·год)
    double e_loss = e_stored - e_useful;

    // Обчислюємо загальний час автономної роботи приладу (годин)
    double t_hours = e_useful / power;

    // Виділяємо кількість повних годин роботи (годин)
    int h = static_cast<int>(t_hours);

    // Обчислюємо залишок часу роботи в цілих хвилинах (хвилин)
    int m = static_cast<int>((t_hours - h) * MINUTES_PER_HOUR);

    std::cout << "\n";
    std::cout << "Модель:                 " << model << "\n";

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Паспортна ємність:      " << std::setw(10) << capacity << " Вт·год\n";
    std::cout << "Вік станції:            " << std::setw(10) << years << " р.\n";
    std::cout << "Фактична ємність:       " << std::setw(10) << c_eff << " Вт·год\n";
    std::cout << "Рівень заряду:          " << std::setw(10) << charge << " %\n";

    std::cout << std::setprecision(2);
    std::cout << "ККД інвертора:          " << std::setw(10) << efficiency << " %\n";

    std::cout << std::setprecision(1);
    std::cout << "Запас енергії:          " << std::setw(10) << e_stored << " Вт·год\n";
    std::cout << "Корисна енергія:        " << std::setw(10) << e_useful << " Вт·год\n";
    std::cout << "Втрати на перетворенні: " << std::setw(10) << e_loss << " Вт·год\n";

    std::cout << std::setprecision(2);
    std::cout << "Час роботи:             " << std::setw(10) << t_hours << " год  = "
              << h << " год " << std::setw(2) << std::setfill('0') << m << " хв\n";

    return 0;
}
