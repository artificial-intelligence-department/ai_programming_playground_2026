/*
Задача: Автономність портативної зарядної станції
 Рудь Дмитро
 Група СШІ-11
*/

#include <iostream>
#include <string>
#include <iomanip>  // setw, setprecision, setfill, left - без цього форматований вивід не збереться
#include <cmath>    // pow - степінь тут рахую через неї, бо оператор ^ в С++ це не степінь, а xor (сам про це забув спочатку)
#include <cstdlib>  // exit()

int int_input(std::string message) {
    int x;
    std::cout << message;
    std::cin >> x;
    if (std::cin.fail()) { // якщо ввели не число - cin впаде в fail-стан
        std::cout << "Помилка: введено не число." << std::endl;
        exit(0);
    }
    return x;
}

std::string str_input(std::string message) {
    std::string x;
    std::cout << message;
    std::cin >> x;
    return x;
} 

double double_input(std::string message) {
    double x;
    std::cout << message;
    std::cin >> x;
    if (std::cin.fail()) {
        std::cout << "Помилка: введено не число." << std::endl;
        exit(0);
    }
    return x;
}


int main() {
    // модель зчитуємо одним словом, cin >> сам зупиниться на пробілі
    std::string model = str_input("Введіть Модель станції: ");
    if (model.size() > 31){
        std::cout << "Помилка: назва моделі має бути не довшою за 31 символ." << std::endl;
        exit(0);
    }

    // паспортна ємність - число, не обов'язково ціле (буває і 768.5)
    double C = double_input("Введіть Паспортну ємність, Вт·год: ");
    if (C <= 0) {
        std::cout << "Помилка: паспортна ємність повинна бути додатним числом." << std::endl;
        exit(0);
    }

    int years = int_input("Введіть Вік станції, років: ");
    if (years < 0 || years > 20) {
        std::cout << "Помилка: вік станції мусить бути від 0 до 20." << std::endl;
        exit(0);
    }

    int charge = int_input("Введіть Рівень заряду, %: ");
    if (charge < 0 || charge > 100) {
        std::cout << "Помилка: рівень заряду має бути цілим числом від 0 до 100." << std::endl;
        exit(0);
    }

    double eff = double_input("Введіть ККД інвертора, %: ");
    if (eff <0 || eff > 100){
        std::cout << "Помилка: ККД інвертора має бути числом від 0 до 100." << std::endl;
        exit(0);
    } 

    // потужність приладу теж число, не обов'язково ціле
    double P = double_input("Введіть Потужність приладу, Вт: ");
    if ( P <= 0) {
        std::cout << "Помилка: потужність приладу повинна бути додатним числом." << std::endl;
        exit(0);
    }

    // Крок 1: фактична ємність з урахуванням віку, Вт·год
    // 2 - це відсоток втрати ємності за рік (деградація акумулятора), ділимо на 100 щоб перевести у частку
    // степінь рахуємо через pow, бо ^ в С++ це побітовий xor, а не піднесення до степеня
    double C_eff = C * pow(1 - 2.0 / 100, years);

    // Крок 2: запас енергії при поточному заряді, Вт·год
    double E_stored = C_eff * charge / 100; // charge теж переводимо з % у частку

    // Крок 3: корисна енергія, що дійде до приладу, Вт·год
    double E_useful = E_stored * eff / 100; // тут так само eff у %, переводимо у частку

    // Крок 4: втрати на перетворенні напруги в інверторі, Вт·год
    double E_loss = E_stored - E_useful;

    // Крок 5: час роботи приладу, год
    double T = E_useful / P;

    // Крок 6-7: розбиваємо години на цілі години і хвилини, що залишились
    int hours = T; // ціла частина T - повні години
    int minutes = (T - hours) * 60; // залишок переводимо в хвилини

    std::cout << std::left << std::setw(30) << "Модель: " << model << std::endl;
    std::cout << std::left << std::setw(30) << "Паспортна ємність: " << std::fixed << std::setprecision(1) << C << " Вт·год" << std::endl;
    std::cout << std::left << std::setw(30) << "Вік станції: " << years << " років" << std::endl;
    std::cout << std::left << std::setw(30) <<  "Фактична ємність: " << std::fixed << std::setprecision(1) << C_eff << " Вт·год" << std::endl;
    std::cout << std::left << std::setw(30) << "Рівень заряду: " << charge << " %" << std::endl;
    std::cout << std::left << std::setw(30) <<  "ККД інвертора: " << std::fixed << std::setprecision(2) << eff << " %" << std::endl;
    std::cout << std::left << std::setw(30) << "Запас енергії: " << std::fixed << std::setprecision(1) <<  E_stored << " Вт·год" << std::endl;
    std::cout << std::left << std::setw(30) <<  "Корисна енергія: " << std::fixed << std::setprecision(1) << E_useful << " Вт·год" << std::endl;
    std::cout << std::left << std::setw(30) <<  "Втрати на перетворенні: " << std::fixed << std::setprecision(1) << E_loss << " Вт·год" << std::endl;
    // std::right тут важливо - до цього стоїть std::left, а нулі для хвилин мають бути зліва (05, а не 50)
    std::cout << std::left << std::setw(30) << "Час роботи:" << std::fixed << std::setprecision(2) << T << " год = "<< hours << " год " << std::right << std::setfill('0') << std::setw(2) << minutes << " хв" << std::endl;

    return 0;
}