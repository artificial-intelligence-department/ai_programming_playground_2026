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
std::cout << "\n";
    // Для текстового поля
    std::cout << std::left << std::setw(30) << "Модель:" 
              << std::right << std::setw(15) << model << "\n";

    // Фіксуємо 1 знак після коми для більшості чисел
    std::cout << std::fixed << std::setprecision(1);

    /* ПРОСТИЙ І НАДІЙНИЙ СПОСІБ ВИРІВНЯННЯ: */
    // 1. Назва параметра: left, width = 25
    // 2. Число: right, width = 7
    // 3. Одиниця виміру: left, width = 10

    std::cout << std::left << std::setw(30) << "Паспортна ємність:" 
              << std::right << std::setw(10) << capacity 
              << std::left << " Вт·год\n";

    std::cout << std::left << std::setw(30) << "Вік станції:" 
              << std::right << std::setw(10) << years 
              << std::left << " р.\n";

    std::cout << std::left << std::setw(30) << "Фактична ємність:" 
              << std::right << std::setw(10) << c_eff 
              << std::left << " Вт·год\n";

    std::cout << std::left << std::setw(30) << "Рівень заряду:" 
              << std::right << std::setw(10) << charge 
              << std::left << " %\n";

    std::cout << std::left << std::setw(30) << "ККД інвертора:" 
              << std::setprecision(2) << std::right << std::setw(10) << efficiency 
              << std::left << " %\n";

    std::cout << std::fixed << std::setprecision(1);
    std::cout << std::left << std::setw(30) << "Запас енергії:" 
              << std::right << std::setw(10) << e_stored 
              << std::left << " Вт·год\n";

    std::cout << std::left << std::setw(30) << "Корисна енергія:" 
              << std::right << std::setw(10) << e_useful 
              << std::left << " Вт·год\n";

    std::cout << std::left << std::setw(30) << "Втрати на перетворенні:" 
              << std::right << std::setw(10) << e_loss 
              << std::left << " Вт·год\n";

    std::cout << std::left << std::setw(30) << "Час роботи:" 
              << std::setprecision(2) << std::right << std::setw(7) << t_hours 
              << " год  = " << hours << " год " 
              << std::setfill('0') << std::setw(2) << minutes << " хв\n";

    return 0;
}