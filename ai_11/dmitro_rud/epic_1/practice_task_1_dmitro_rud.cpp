/*
Задача: Автономність портативної зарядної станції
 Рудь Дмитро
 Група СШІ-11
*/

#include <iostream>
#include <string>
#include <iomanip>  
#include <cmath>    // pow - степінь тут рахую через неї, бо оператор ^ в С++ це не степінь, а xor (сам про це забув спочатку)
#include <cstdlib>  // exit()

int main() {
    //оголошуємо всі змінні на початку
    std::string model;
    double C;          // паспортна ємність, Вт·год (не обов'язково ціле, буває і 768.5)
    int years;         // вік станції, років
    int charge;        // рівень заряду, %
    double eff;        // ККД інвертора, %
    double P;          // потужність приладу, Вт (теж не обов'язково ціле)
    double C_eff;      // фактична ємність з урахуванням віку, Вт·год
    double E_stored;   // запас енергії при поточному заряді, Вт·год
    double E_useful;   // корисна енергія, що дійде до приладу, Вт·год
    double E_loss;     // втрати на перетворенні напруги, Вт·год
    double T;          // час роботи приладу, год
    int hours;         // повні години
    int minutes;       // хвилини, що залишились

    // Ввід: модель станції
    std::cout << "Введіть Модель станції: ";
    std::cin >> model;
    // Довжина моделі > 31?
    if (model.size() > 31){
        std::cout << "Помилка: назва моделі має бути не довшою за 31 символ." << std::endl;
        exit(0);
    }

    // Ввід: паспортна ємність, C
    std::cout << "Введіть Паспортну ємність, Вт·год: ";
    std::cin >> C;

    if (C <= 0) {
        std::cout << "Помилка: паспортна ємність повинна бути додатним числом." << std::endl;
        exit(0);
    }

    // Ввід: вік станції, years
    std::cout << "Введіть Вік станції, років: ";
    std::cin >> years;

    // years < 0 or years > 20?
    if (years < 0 || years > 20) {
        std::cout << "Помилка: вік станції мусить бути від 0 до 20." << std::endl;
        exit(0);
    }

    // Ввід: рівень заряду, charge
    std::cout << "Введіть Рівень заряду, %: ";
    std::cin >> charge;

    // charge < 0 or charge > 100?
    if (charge < 0 || charge > 100) {
        std::cout << "Помилка: рівень заряду має бути цілим числом від 0 до 100." << std::endl;
        exit(0);
    }

    // Ввід: ККД інвертора, eff
    std::cout << "Введіть ККД інвертора, %: ";
    std::cin >> eff;

    // eff < 0 or eff > 100?
    if (eff <0 || eff > 100){
        std::cout << "Помилка: ККД інвертора має бути числом від 0 до 100." << std::endl;
        exit(0);
    }

    // Ввід: потужність приладу, P
    std::cout << "Введіть Потужність приладу, Вт: ";
    std::cin >> P;
    
    // P <= 0?
    if ( P <= 0) {
        std::cout << "Помилка: потужність приладу повинна бути додатним числом." << std::endl;
        exit(0);
    }

    // фактична ємність з урахуванням віку, Вт·год
    // 2 - це відсоток втрати ємності за рік (деградація акумулятора), ділимо на 100 щоб перевести у частку
    // степінь рахуємо через pow, бо ^ в С++ це побітовий xor, а не піднесення до степеня
    C_eff = C * pow(1 - 2.0 / 100, years);

    // запас енергії при поточному заряді, Вт·год
    E_stored = C_eff * charge / 100; // charge теж переводимо з % у частку

    // корисна енергія, що дійде до приладу, Вт·год
    E_useful = E_stored * eff / 100; // тут так само eff у %, переводимо у частку

    // втрати на перетворенні напруги в інверторі, Вт·год
    E_loss = E_stored - E_useful;

    // час роботи приладу, год
    T = E_useful / P;

    // розбиваємо години на цілі години і хвилини, що залишились
    hours = T; // ціла частина T - повні години
    minutes = (T - hours) * 60; // залишок переводимо в хвилини

// Вирівнюємо назви до 24 символів, а для чисел використовуємо правостороннє вирівнювання шириною 5
    std::cout << "Модель:                 " << model << std::endl;

    std::cout << "Паспортна ємність:      " << std::right << std::setw(5) << std::fixed << std::setprecision(1) << C << " Вт·год" << std::endl;

    std::cout << "Вік станції:            " << std::right << std::setw(5) << years << " р." << std::endl;

    std::cout << "Фактична ємність:       " << std::right << std::setw(5) << std::fixed << std::setprecision(1) << C_eff << " Вт·год" << std::endl;

    std::cout << "Рівень заряду:          " << std::right << std::setw(5) << charge << " %" << std::endl;

    std::cout << "ККД інвертора:          " << std::right << std::setw(5) << std::fixed << std::setprecision(2) << eff << " %" << std::endl;

    std::cout << "Запас енергії:          " << std::right << std::setw(5) << std::fixed << std::setprecision(1) << E_stored << " Вт·год" << std::endl;

    std::cout << "Корисна енергія:        " << std::right << std::setw(5) << std::fixed << std::setprecision(1) << E_useful << " Вт·год" << std::endl;

    std::cout << "Втрати на перетворення: " << std::right << std::setw(5) << std::fixed << std::setprecision(1) << E_loss << " Вт·год" << std::endl;

// Для часу роботи (години з хвилинами виводимо окремо з заповненням нулями)
    std::cout << "Час роботи:             " << std::right << std::setw(5) << std::fixed << std::setprecision(2) << T
          << " год = " << hours << " год "
          << std::setfill('0') << std::setw(2) << minutes << " хв" << std::endl;

    return 0;
}