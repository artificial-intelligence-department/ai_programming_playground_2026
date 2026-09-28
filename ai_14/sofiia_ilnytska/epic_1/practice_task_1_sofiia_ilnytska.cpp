/*
    Задача: Розрахунок автономності портативної зарядної станції
    Автор: Ільницька Софія
    Група: ШІ-14
*/

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip> // для std::setprecision (форматування виводу чисел з плаваючою комою)

int main() {
    const double BATTERY_DEGRADATION = 0.02;  // 2% деградація батареї на рік
    std::string station_model;
    double rated_capacity = 0.0;
    int station_age = 0;
    int charge_level = 0;
    double inverter_efficiency = 0.0;
    double device_power = 0.0;

    std::cout << "Модель станції: "; 
    std::getline(std::cin, station_model);  //зчитує назву моделі разом із можливими пробілами
    if (station_model.length() > 31 || station_model.find(' ') != std::string::npos) {
        std::cout << "Помилка: Модель станції не може перевищувати 31 символ і не може містити пробіл." << std::endl;
        return 1;
    }
    std::cout << "Паспортна ємність (Вт*год): ";
    std::cin >> rated_capacity;
    if (rated_capacity <= 0) {
        std::cout << "Помилка: Паспортна ємність повинна бути додатнім числом." << std::endl;
        return 1;
    }
    std::cout << "Вік станції (років): ";
    std::cin >> station_age;
    if (station_age < 0 || station_age > 20) {
        std::cout << "Помилка: Вік станції повинен бути в діапазоні від 0 до 20." << std::endl;
        return 1;
    }
    std::cout << "Рівень заряду (%): ";
    std::cin >> charge_level;
    if (charge_level < 0 || charge_level > 100) {
        std::cout << "Помилка: Рівень заряду повинен бути в діапазоні від 0 до 100." << std::endl;
        return 1;
    }
    std::cout << "ККД інвертора (%): ";
    std::cin >> inverter_efficiency;
    if (inverter_efficiency <= 0 || inverter_efficiency > 100) {
        std::cout << "Помилка: ККД інвертора повинен бути в діапазоні від 0 до 100." << std::endl;
        return 1;
    }
    std::cout << "Потужність приладу (Вт): ";
    std::cin >> device_power;
    if (device_power <= 0) {
        std::cout << "Помилка: Потужність приладу повинна бути додатнім числом." << std::endl;
        return 1;
    }

     // Обчислюємо фактичну ємність акумулятора після врахування деградації за весь період експлуатації
    double efficient_capacity = rated_capacity * std::pow(1 - BATTERY_DEGRADATION, station_age);
    // Обчислюємо кількість енергії, яка фактично зберігається в акумуляторі відповідно до рівня заряду
    double energy_stored = efficient_capacity * charge_level / 100;
    // Обчислюємо корисну енергію після втрат під час роботи інвертора
    double energy_useful = energy_stored * inverter_efficiency / 100;
    // Обчислюємо кількість енергії, яка втрачається під час перетворення інвертором
    double energy_loss = energy_stored - energy_useful;
    // Обчислюємо орієнтовний час роботи приладу від доступної корисної енергії
    double working_time = energy_useful / device_power;
    // Відокремлюємо повні години від загального часу роботи
    int hours = static_cast<int>(std::floor(working_time));
    // Перетворюємо дробову частину часу роботи на повні хвилини
    int minutes = static_cast<int>(std::floor((working_time - hours) * 60));
    
    std::cout << std::endl;
    std::cout << "Модель: " << station_model << std::endl;
    std::cout << "Паспортна ємність: "  << std::fixed << std::setprecision(1) << rated_capacity << " Вт*год" << std::endl;
    std::cout << "Вік станції: " << station_age << " р." << std::endl;
    std::cout << "Фактична ємність: "  << std::fixed << std::setprecision(1) << efficient_capacity << " Вт*год" << std::endl;
    std::cout << "Рівень заряду: " << charge_level << "%" << std::endl;
    std::cout << "ККД інвертора: "  << std::fixed << std::setprecision(2) << inverter_efficiency << "%" << std::endl;
    std::cout << "Запас енергії: "  << std::fixed << std::setprecision(1) << energy_stored << " Вт*год" << std::endl;
    std::cout << "Корисна енергія: "  << std::fixed << std::setprecision(1) << energy_useful << " Вт*год" << std::endl;
    std::cout << "Втрати на перетворенні: "  << std::fixed << std::setprecision(1) << energy_loss << " Вт*год" << std::endl;
    std::cout << "Час роботи: " << hours << " год " << std::setfill('0') << std::setw(2) << minutes << " хв" << std::endl;

    return 0;
}