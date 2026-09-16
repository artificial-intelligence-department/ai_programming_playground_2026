/*
Автономність портативної зарядної станції
Артюх Іван
ШІ-12
 */

#include <iostream> 
#include <cmath>
#include <string>
#include <iomanip>

int main() {
    
    //Втрата ємності акумулятора за рік у десятковому дробі
    const double capacity_loss = 0.02; 

    //Ініціалізація змінних для запису вводу користувача
    int years = 0; //Вік станції
    int charge = 0; //Відсоток заряду
    double C = 0.0; //Ємність станції
    double eff = 0.0; //ККД інвертора, %
    double P = 0.0; //Потужність споживача
    std::string station_name; //Назва станції

    //Виведення запинту на дані у консоль, зчитування, валідація(для кожної змінної)
    std::cout<<"Модель станції: ";
    std::cin>>station_name;
    if(std::cin.fail() || station_name.length() > 31) {
        std::cout<<"Некоректна назва моделі.\n";
        return 1;
    }
    
    std::cout<<"Паспортна ємність (Вт·год): ";
    std::cin>>C;
    if(std::cin.fail() || C <= 0) {
        std::cout<<"Паспортна ємність має бути додатним числом.\n";
        return 1;
    }

    std::cout<<"Вік станції (років): ";
    std::cin>>years;
    if( std::cin.fail() || years < 0 || years > 20) {
        std::cout<<"Вік станції має бути числом від 0 до 20.\n";
        return 1;
    }

    std::cout<<"Рівень заряду (%): ";
    std::cin>>charge;
    if( std::cin.fail() || charge > 100 || charge < 0) {
        std::cout<<"Рівень заряду має бути числом від 0 до 100.\n";
        return 1;
    }

    std::cout<<"ККД інвертора (%): ";
    std::cin>>eff;
    if( std::cin.fail() || eff > 100 || eff <= 0) {
        std::cout<<"ККД інвертора має бути числом від 0 до 100.\n";
        return 1;

    }

    std::cout<<"Потужність приладу (Вт): ";
    std::cin>>P;
    if( std::cin.fail() || P <= 0) {
        std::cout<< "Потужність має бути додатним числом.\n";
        return 1;
    }

    //Обчислення фактичної ємності із урахування деградації, Вт*год
    double C_eff = C * pow( (1 - capacity_loss), years);

    //Обчислення фактичної запасу енергії, Вт*год
    double E_stored = C_eff * charge / 100;

    //Обчислення кількість корисної енергії, яку може використати прилад, Вт*год
    double E_useful = E_stored * eff / 100;

    //Обчислення встрат енергії при перетворенні напруги, Вт*год
    double E_loss = E_stored - E_useful;

    //Обчислення часу роботи приладу, години
    double T = E_useful / P;

    //Обчислення кількості повних годин роботи, години
    int h = (int)T;

    //Обчислення кількості хвилин роботи із заокругленням до цілих, хвилини
    int m = (int)((T - h) * 60);   

    //Зняття ліміту на кількість цифр у цілій частині числа при використанні функції std::setprescision
    std::cout << std::fixed;

    //Вивід 
    std::cout <<"Модель: " << station_name <<std::endl;

    std::cout << "Паспортна ємність: "<< std::setprecision(1) << C << " Вт*год"<<std::endl;

    std::cout << "Вік станції: "<< years << " pоків"<<std::endl;

    std::cout << "Фактична ємність: "<< std::setprecision(1)
    << C_eff << " Вт*год"<<std::endl;

    std::cout << "Рівень заряду: " << charge << " %"<<std::endl;

    std::cout <<"ККД інвертора: " << std::setprecision(2) << eff << " %"<<std::endl;

    std::cout << "Запас енергії: " << std::setprecision(1) << E_stored << " Вт*год"<<std::endl;

    std::cout << "Корисна енергія: " << std::setprecision(1) << E_useful << " Вт*год"<<std::endl;

    std::cout << "Втрати на перетворенні: " << std::setprecision(1) << E_loss << " Вт*год"<<std::endl;

    std::cout << std::setprecision(2) << "Час роботи: " << T << " год = "
    << h << " год " << ((m>9) ? "" : "0" ) << m << " xв"<< std::endl; // Додавання '0' перед кількістю хвилин, якщо їх менше 10

    return 0;
    
}