/*
Задача: Автономність портативної зарядної станції
 Рудь Дмитро
 Група СШІ-11
*/


#include<iostream>
#include <string>

int int_input(std::string message) {
    int x;
    std::cout << message;
    std::cin >> x;
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
    return x;
}


int main() {
    std::string model = str_input("Введіть Модель станції: ");
    if (model.size() > 31){
        std::cout << "Error: Model name must be less than 32 characters." << std::endl;
        exit(0)
    }
    int C = int_input("Введіть Паспортну ємність, Вт·год: ");
    if (C <= 0) {
        std::cout << "Error: Capacity must be a positive integer." << std::endl;
        exit(0);
    }
    int years = int_input("Введіть Вік станції, років: ");
    if (years < 0 || years > 20) {
        std::cout << "Error: Age must be an integer between 0 and 20." << std::endl;
        exit(0);
    }
    int charge = int_input("Введіть Рівень заряду, %: ");
    if (charge < 0 || charge > 100) {
        std::cout << "Error: Charge must be an integer between 0 and 100." << std::endl;
        exit(0);
    }
    float eff = double_input("Введіть ККД інвертора, %: ");
    if (eff <0 || eff > 100){
        std::cout << "Error: Efficiency must be a number between 0 and 100." << std::endl;
        exit(0)
    } 
    int P = int_input("Введіть Потужність приладу, Вт: ");
    if ( P <= 0) {
        std::cout << "Error: Power must be a positive integer." << std::endl;
        exit(0);
    }
    float C_eff = C * (1 - 2 / 100) ^ years; //Фактична ємність з урахуванням віку, Вт·год
    float E_stored = C_eff * charge / 100; // Запас енергії при поточному заряді, Вт·год
    float E_useful = E_stored * eff / 100; // Корисна енергія, Вт·год
    float T = E_useful / P; // Час роботи приладу, год
    int hours = T; // Перетворення часу роботи xbcns в години
    int minutes = (T - hours)*60; // Перетворення часу роботи в чисті хвилини
    float E_loss = E_stored - E_useful; //Втрати, Вт·год


    std::cout << std::left << std::setw(30) << "Модель: " << model << std::endl;
    std::cout << std::left << std::setw(30) << "Паспортна ємність: " << std::fixed << std::setprecision(1) << C << " Вт·год" << std::endl;
    std::cout << std::left << std::setw(30) << "Вік станції: " << years << " років" << std::endl;
    std::cout << std::left << std::setw(30) <<  "Фактична ємність: " << std::fixed << std::setprecision(1) << C_eff << " Вт·год" << std::endl;
    std::cout << std::left << std::setw(30) << "Рівень заряду: " << charge << " %" << std::endl;
    std::cout << std::left << std::setw(30) <<  "ККД інвертора: " << std::fixed << std::setprecision(2) << eff << " %" << std::endl;
    std::cout << std::left << std::setw(30) << "Запас енергії: " << std::fixed << std::setprecision(1) <<  E_stored << " Вт·год" << std::endl; //Запас енергії при поточному заряді, Вт·год
    std::cout << std::left << std::setw(30) <<  "Корисна енергія: " << std::fixed << std::setprecision(1) << E_useful << " Вт·год" << std::endl; //Корисна енергія, Вт·год
    std::cout << std::left << std::setw(30) <<  "Втрати на перетворенні: " << std::fixed << std::setprecision(1) << E_loss << " Вт·год" << std::endl; //Втрати, Вт·год
    std::cout << std::left << std::setw(30) << "Час роботи:" << std::fixed << std::setprecision(2) << T << " год = "<< hours << " год " << std::setfill('0') << std::setw(2) << minutes << " хв" << std::endl;
    return 0;   
}

