/*
Автономність портативної зарядної станції, Танасієнко Іван, група 13
*/

//Включення бібліотек
#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    //Оголошення змінних
    const double loss = 0.02;
    std::string model, minutesToPrint;
    int years, P, charge;
    double C, eff;
    bool running = false;
    //Введення даних, перевірка, чи в назві моделі немає пробілів
    do {
        std::cout << "Модель станції: ";
        std::getline(std::cin, model);
        auto space = std::find(model.begin(), model.end(), ' ');
        if (space != model.end()) {
            running = true;
            std::cout << "Введіть назву без пробілів" << std::endl;
        }
        else {
            running = false;
        }
    }while (running);
    std::cout << "Паспортна ємність (Вт·год): ";
    std::cin >> C;
    std::cout << "Вік станції (років): ";
    std::cin >> years;
    std::cout << "Рівень заряду (%): ";
    std::cin >> charge;
    std::cout << "ККД інвертора (%): ";
    std::cin >> eff;
    std::cout << "Потужність приладу (Вт): ";
    std::cin >> P;

    //Перевірка чи дані введено коректно
    if (model.length() > 31) {
        std::cout << "Model's name is too long" << std::endl;
        return 1;
    }
    if (C <= 0 || P <= 0) {
        std::cout << "Negative value of capacity or power entered" << std::endl;
        return 1;
    }
    if (years < 0 || years > 20) {
        std::cout << "Wrong age entered" << std::endl;
        return 1;
    }
    if (charge < 0 || charge > 100) {
        std::cout << "Wrong charge entered" << std::endl;
        return 1;
    }
    if (eff <= 0 || eff > 100) {
        std::cout << "Wrong efficiency entered" << std::endl;
        return 1;
    }
    //Обчислення фактичної місткості
    double fC = C * std::pow((1-loss), years);
    //Обчислення поточного фактичного заряду
    double currentFC = fC * charge / 100;
    //Обчислення фактичної міткості з урахуванням ККД інвертора
    double effFc = currentFC * eff / 100;
    //Обчислення втрати енергії через ККД інвертора
    double effLoss = currentFC - effFc;
    //Обчислення кількості годин роботи
    double hours = effFc / P;
    //Обчислення повної кількості годин роботи
    int fullHours = (int) hours;
    //Обчислення кількості хвилин роботи
    int minutes = (hours - fullHours) * 60;
    //Перевірка чи кількість хвилин менша за 10, щоб вивести 0 перед кількістю хвилин
    if (minutes > 0 && minutes < 10) {
        minutesToPrint  = "0" + std::to_string(minutes);
    }
    else {
        minutesToPrint = std::to_string(minutes);
    }

    //Виведення результатів
    std::cout << std::endl << "Модель: " << std::setw(56) << model << std::endl; // 56
    std::cout << std::fixed << std::setprecision(1) << "Паспортна ємність: " << std::setw(45) << C << " Вт·год" << std::endl; //45
    std::cout << "Вік станції: " << std::setw(47) << years << " р." << std::endl; //47
    std::cout << std::fixed << std::setprecision(1) << "Фактична ємність: "  << std::setw(46) << fC << " Вт·год" << std::endl; //46
    std::cout << "Рівень заряду: "  << std::setw(46)  << charge << " %" << std::endl; //46
    std::cout << std::fixed << std::setprecision(2) << "ККД інвертора: "  << std::setw(49) << eff << " %" << std::endl; //49
    std::cout << std::fixed << std::setprecision(1) << "Запас енергії: "  << std::setw(49) << currentFC << " Вт·год" << std::endl; //49
    std::cout << std::fixed << std::setprecision(1) << "Корисна енергія: "  << std::setw(47) << effFc << " Вт·год" << std::endl; //47
    std::cout << std::fixed << std::setprecision(1) << "Втрати на перетворенні: "  << std::setw(40) << effLoss << " Вт·год" << std::endl; //40
    std::cout << std::fixed << std::setprecision(2) << "Час роботи: "  << std::setw(52) << hours << " год = " << fullHours << " год " << minutesToPrint << " хв" << std::endl; //52

    return 0;
}

    /*
Ввід користувача
Модель станції: EcoRiver-2Pro
Паспортна ємність (Вт·год): 768
Вік станції (років): 3
Рівень заряду (%): 100
ККД інвертора (%): 85
Потужність приладу (Вт): 150


Вивід програми
Модель:                 EcoRiver-2Pro
Паспортна ємність:           768.0 Вт·год
Вік станції:                     3 р.
Фактична ємність:            722.8 Вт·год
Рівень заряду:                 100 %
ККД інвертора:               85.00 %
Запас енергії:               722.8 Вт·год
Корисна енергія:             614.4 Вт·год
Втрати на перетворенні:      108.4 Вт·год
Час роботи:                   4.10 год  = 4 год 05 хв


     */