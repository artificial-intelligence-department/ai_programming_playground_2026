/*
 * Автономність портативної зарядної станції
 * Ткач Артем
 * ші-13
 */

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

int main() {
// Відсоток деградації ємності акумулятора за один рік
    const double DEGRADATION_RATE_PER_YEAR = 2.0;

    std::string model; // Назва моделі акумулятора
    double capacity; // Заявлена ємність акумулятора (Вт*год)
    int years; // Вік акумулятора у роках
    double charge; // Заряд (%)
    double efficiency; // ККД інвертора (%)
    double power; // Потужність (Вт)

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

    // Обчислення
    double c_eff = capacity * std::pow(1.0 - DEGRADATION_RATE_PER_YEAR / 100.0, years);
    double e_stored = c_eff * charge / 100.0;
    double e_useful = e_stored * efficiency / 100.0;
    double e_loss = e_stored - e_useful;

    double t_hours = e_useful / power;
    int hours = static_cast<int>(t_hours);
    int minutes = static_cast<int>(std::round((t_hours - hours) * 60.0));
    if (minutes == 60) {
        hours += 1;
        minutes = 0;
    }

    // Виведення результатів
const int w_label = 25; 
    const int w_num   = 10; 

    std::cout << "\n";

    std::cout << std::left  << std::setw(w_label) << "Модель:" 
              << std::right << std::setw(w_num + 7) << model << "\n";

    std::cout << std::left  << std::setw(w_label) << "Паспортна ємність:" 
              << std::right << std::setw(w_num) << std::fixed << std::setprecision(2) << capacity 
              << std::left  << " Вт·год\n";

    std::cout << std::left  << std::setw(w_label) << "Вік станції:" 
              << std::right << std::setw(w_num) << years 
              << std::left  << " р.    \n"; // 4 пробіли після р.

    std::cout << std::left  << std::setw(w_label) << "Фактична ємність:" 
              << std::right << std::setw(w_num) << std::fixed << std::setprecision(2) << c_eff 
              << std::left  << " Вт·год\n";

    std::cout << std::left  << std::setw(w_label) << "Рівень заряду:" 
              << std::right << std::setw(w_num) << std::fixed << std::setprecision(2) << charge 
              << std::left  << " %     \n"; // 5 пробілів після %

    std::cout << std::left  << std::setw(w_label) << "ККД інвертора:" 
              << std::right << std::setw(w_num) << std::fixed << std::setprecision(2) << efficiency 
              << std::left  << " %     \n"; // 5 пробілів після %

    std::cout << std::left  << std::setw(w_label) << "Запас енергії:" 
              << std::right << std::setw(w_num) << std::fixed << std::setprecision(3) << e_stored 
              << std::left  << " Вт·год\n";

    std::cout << std::left  << std::setw(w_label) << "Корисна енергія:" 
              << std::right << std::setw(w_num) << std::fixed << std::setprecision(3) << e_useful 
              << std::left  << " Вт·год\n";

    std::cout << std::left  << std::setw(w_label) << "Втрати на перетворенні:" 
              << std::right << std::setw(w_num) << std::fixed << std::setprecision(3) << e_loss 
              << std::left  << " Вт·год\n";

    std::cout << std::left  << std::setw(w_label) << "Час роботи:" 
              << std::right << std::setw(6) << std::fixed << std::setprecision(2) << t_hours 
              << " год  = " << hours << " год " 
              << std::setfill('0') << std::setw(2) << minutes << " хв\n";

    return 0;
}