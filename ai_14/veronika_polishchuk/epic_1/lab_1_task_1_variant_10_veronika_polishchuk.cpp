/*
 * Задача: Автономність портативної зарядної станції
 * Поліщук Вероніка
 * Група 14
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
int main() {
    // Вхідні змінні
    // string потрібна для роботи з текстом, виведення в кінці та первірка довжини
    std::string model;
    double capacity;
    int years;
    int charge;
    double eff;
    double power;

    // Відсоток деградації акумулятора за рік
    const double deg = 2.0; 

    // Ввід та перевірка моделі станції
    std::cout << "Модель станції: ";
    if (!(std::cin >> model) || model.length() > 31) {
        std::cout << "Помилка: некоректні вхідні дані." << std::endl;
        return 1;
    }

    // Ввід та перевірка паспортної ємності
    std::cout << "Паспортна ємність (Вт·год): ";
    if (!(std::cin >> capacity) || capacity <= 0) {
        std::cout << "Помилка: некоректні вхідні дані." << std::endl;
        return 1;
    }

    // Ввід та перевірка віку станції
    std::cout << "Вік станції (років): ";
    if (!(std::cin >> years) || years < 0 || years > 20) {
        std::cout << "Помилка: некоректні вхідні дані." << std::endl;
        return 1;
    }

    // Ввід та перевірка рівня заряду
    std::cout << "Рівень заряду (%): ";
    if (!(std::cin >> charge) || charge < 0 || charge > 100) {
        std::cout << "Помилка: некоректні вхідні дані." << std::endl;
        return 1;
    }

    // Ввід та перевірка ККД інвертора
    std::cout << "ККД інвертора (%): ";
    if (!(std::cin >> eff) || eff <= 0 || eff > 100) {
        std::cout << "ППомилка: некоректні вхідні дані." << std::endl;
        return 1;
    }

    // Ввід та перевірка потужності приладу
    std::cout << "Потужність приладу (Вт): ";
    if (!(std::cin >> power) || power <= 0) {
        std::cout << "Помилка: некоректні вхідні дані." << std::endl;
        return 1;
    }

    // Обчислюємо фактичну ємність з урахуванням зносу акумулятора за роки (Вт·год)
    double c_eff = capacity * std::pow(1.0 - (deg/ 100.0), years);

    // Обчислюємо поточний запас енергії відповідно до відсотка заряду (Вт·год)
    double e_stored = c_eff * (charge / 100.0);

    // Обчислюємо корисну енергію з урахуванням втрат в інверторі (Вт·год)
    double e_useful = e_stored * (eff / 100.0);

    // Обчислюємо втрати енергії під час перетворення напруги (Вт·год)
    double e_loss = e_stored - e_useful;

    // Обчислюємо загальний час роботи приладу (годин)
    double t_total = e_useful / power;

    // Виділяємо кількість повних годин
    int hours = static_cast<int>(t_total);

    // Розраховуємо залишок у хвилинах
    int minutes = static_cast<int>((t_total - hours) * 60.0);

// Вивід результатів із вирівнюванням по лівому краю
    std::cout << std::fixed;
    
    std::cout << "Модель:                 " << model << std::endl;
    std::cout << "Паспортна ємність:      " << std::setprecision(1) << capacity << " Вт·год" << std::endl;
    std::cout << "Вік станції:            " << years << " р." << std::endl;
    std::cout << "Фактична ємність:       " << std::setprecision(1) << c_eff << " Вт·год" << std::endl;
    std::cout << "Рівень заряду:          " << charge << " %" << std::endl;
    std::cout << "ККД інвертора:          " << std::setprecision(2) << eff << " %" << std::endl;
    std::cout << "Запас енергії:          " << std::setprecision(1) << e_stored << " Вт·год" << std::endl;
    std::cout << "Корисна енергія:        " << std::setprecision(1) << e_useful << " Вт·год" << std::endl;
    std::cout << "Втрати на перетворенні: " << std::setprecision(1) << e_loss << " Вт·год" << std::endl;

    std::cout << "Час роботи:             " 
              << std::setprecision(2) << t_total << " год  = " 
              << hours << " год " 
              << std::setfill('0') << std::setw(2) << minutes << " хв" << std::endl;

    return 0;
}