/*
    Автономність портативної зарядної станції
    Автор: Дудка Андрій
    Група: ШІ-14
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

int main() {
    const double degradation = 2.0; // втрата ємності за рік, %
    const double percent = 100.0;    // переведення відсотків у частку
    const int minutes_per_hour = 60;  // хвилин у годині
    const int OUTPUT_WIDTH = 12;     // ширина колонки результатів

    std::string model;

    double C = 0.0, eff = 0.0, P = 0.0;
    int years = 0, charge = 0;

    // перевірка назви моделі
    std::cout << "Модель станції: ";
    std::getline(std::cin, model);

    if (!std::cin || model.length() == 0 || model.length() > 31) {
        std::cout << "Помилка: модель має містити від 1 до 31 символа.\n";
        return 1;
    }

    for (char symbol : model) {
        if (symbol == ' ' || symbol == '\n') {
            std::cout << "Помилка: модель має бути одним словом без пробілів.\n";
            return 1;
        }
    }

    // введення чисел і перевірка меж
    std::cout << "Паспортна ємність (Вт·год): ";
    std::cin >> C;
    if (!std::cin || C <= 0) {
        std::cout << "Помилка: ємність має бути числом більше 0.\n";
        return 1;
    }

    std::cout << "Вік станції (років): ";
    std::cin >> years;
    if (!std::cin || years < 0 || years > 20) {
        std::cout << "Помилка: вік має бути цілим числом від 0 до 20.\n";
        return 1;
    }

    std::cout << "Рівень заряду (%): ";
    std::cin >> charge;
    if (!std::cin || charge < 0 || charge > 100) {
        std::cout << "Помилка: заряд має бути цілим числом від 0 до 100.\n";
        return 1;
    }

    std::cout << "ККД інвертора (%): ";
    std::cin >> eff;
    if (!std::cin || eff <= 0 || eff > 100) {
        std::cout << "Помилка: ККД має бути числом більше 0 і не більше 100.\n";
        return 1;
    }

    std::cout << "Потужність приладу (Вт): ";
    std::cin >> P;
    if (!std::cin || P <= 0) {
        std::cout << "Помилка: потужність має бути числом більше 0.\n";
        return 1;
    }

    // ємність з урахуванням віку, Вт·год
    double C_eff = C * std::pow(1.0 - degradation / percent, years);

    // енергія при поточному заряді, Вт·год
    double E_stored = C_eff * (charge / percent);

    // корисна енергія після інвертора, Вт·год
    double E_useful = E_stored * (eff / percent);

    // втрати в інверторі, Вт·год
    double E_loss = E_stored - E_useful;

    // час роботи, год
    double T = E_useful / P;

    // повні години
    double h = std::floor(T);

    // залишок часу, повні хвилини
    int m = static_cast<int>((T - h) * minutes_per_hour);

    std::cout << '\n' << std::fixed;
    std::cout << "Модель:                 " << model << '\n';
    std::cout << "Паспортна ємність:      " << std::setw(OUTPUT_WIDTH) << std::setprecision(1) << C << " Вт·год\n";
    std::cout << "Вік станції:            " << std::setw(OUTPUT_WIDTH) << years << " р.\n";
    std::cout << "Фактична ємність:       " << std::setw(OUTPUT_WIDTH) << std::setprecision(1) << C_eff << " Вт·год\n";
    std::cout << "Рівень заряду:          " << std::setw(OUTPUT_WIDTH) << charge << " %\n";
    std::cout << "ККД інвертора:          " << std::setw(OUTPUT_WIDTH) << std::setprecision(2) << eff << " %\n";
    std::cout << "Потужність приладу:     " << std::setw(OUTPUT_WIDTH) << std::setprecision(1) << P << " Вт\n";
    std::cout << "Запас енергії:          " << std::setw(OUTPUT_WIDTH) << std::setprecision(1) << E_stored << " Вт·год\n";
    std::cout << "Корисна енергія:        " << std::setw(OUTPUT_WIDTH) << std::setprecision(1) << E_useful << " Вт·год\n";
    std::cout << "Втрати на перетворенні: " << std::setw(OUTPUT_WIDTH) << std::setprecision(1) << E_loss << " Вт·год\n";
    std::cout << "Час роботи:             " << std::setw(OUTPUT_WIDTH) << std::setprecision(2) << T
         << " год = " << std::setprecision(0) << h << " год "
         << std::setfill('0') << std::setw(2) << m << std::setfill(' ') << " хв\n";

    return 0;
}
