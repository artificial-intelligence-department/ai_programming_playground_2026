/*
    Епік 1. Автономність портативної зарядної станції
    Автор: Данило Морикишка
    Група: ШІ-11

*/

//Підключаємо бібліотеки, які необхідні для подальшої реалізації завдання

#include <iostream> // Бібліотека iostream для введення та виведення даних
#include <cmath> // Бібліотеки cmath для використання математичних функцій
#include <iomanip>  // Бібліотека iomanip для встановлення кількості знаків після коми
#include <string> // Бібліотека string для роботи з рядками

using namespace std;

int main()
{
    // Ініціалізовуємо константи для перевірки на допустимі значення

    const int MAX_MODEL_LENGTH = 31; // Максимальна кількість символів для назви моделі
    const int MIN_YEARS = 0; // Мінімальний вік станції
    const int MAX_YEARS = 20; // Максимальний вік станції
    const int MIN_CHARGE = 0; // Мінімальний рівень заряду
    const int MAX_CHARGE = 100; // Максимальний рівень заряду
    const double MAX_EFFICIENCY = 100; // Максимальний ККД інвертора
    const double ANNUAL_CAPACITY_LOSS = 2; // Щорічна втрата ємності у відсотках
    const double PERCENT = 100.0; // Значення для переведення відсотків у десятковий формат
    const int MINUTES_PER_HOUR = 60; // Кількість хвилин в одній годині

    // Оголошуємо змінні для їх подальшого використання

     string stationModel; // Модель станції
     double ratedCapacity; // Паспортна ємність
     int years; // Вік станції
     int charge; // Рівень заряду
     double efficiency; // ККД інвертора
     double power; // Потужність

    // Виводимо текст в консоль, ініціалізовуємо змінні та за допомогою констант робимо перевірку на допустимі значення

    cout<< "Модель станції: ";   
    cin>> stationModel; 

    if (stationModel.length() > MAX_MODEL_LENGTH) 
    {
        cout << "Назва моделі перевищує допустиму кількість символів!Допустима кількість символів -" << MAX_MODEL_LENGTH;
        return 1;
    }    

    cout<< "Паспортна ємність (Вт·год): "; 
    cin>> ratedCapacity; 
    
    if (ratedCapacity <= 0) 
    {
        cout << "Ємність повинна бути більше 0!";
        return 1;
    }
       
    
    cout<< "Вік станції (років): ";  
    cin>> years; 
    
    if (years < MIN_YEARS || years > MAX_YEARS)
    {
        cout << "Недопустиме значення для віку станції!Значення може набувати від " << MIN_YEARS << "до " << MAX_YEARS << endl;
        return 1;
    }
       
    cout<< "Рівень заряду (%): ";  
    cin>> charge; 
    
    if (charge < MIN_CHARGE || charge > MAX_CHARGE)
    {
        cout << "Помилка! Рівень заряду може бути від " << MIN_CHARGE << " до " << MAX_CHARGE << endl;
        return 1;
    }
        
    cout<< "ККД інвертора (%): ";  
    cin>> efficiency; 
    
    if (efficiency <= 0 || efficiency > MAX_EFFICIENCY)
    {
        cout << "Помилка! ККД може набувати значення від 0 до " << MAX_EFFICIENCY << endl;
        return 1;
    }
       
    cout<< "Потужність приладу (Вт): ";  
    cin>> power; 
    
    if (power <= 0)
    {
        cout << "Потужність не може бути від'ємною!" << endl;
        return 1;
    }
    
    // Обчислюємо формули, які вказані в умові задачі

    double C_eff = ratedCapacity * pow((1 - ANNUAL_CAPACITY_LOSS/PERCENT),years); // Обчислюємо фактичну ємність з урахуванням віку
    double E_Stored = C_eff * charge / PERCENT; // Обчислюємо запас енергії при поточному заряді
    double E_useful = E_Stored * efficiency / PERCENT; // Обчислюємо корисну енергію, що дійде до приладу
    double E_loss = E_Stored - E_useful; // Обчислюємо втрати на перетворенні напруги
    double T = E_useful / power; // Обчислюємо час роботи
    int h = (int)T; // Знаходимо цілу частини числа.Використовую явне претворення типів
    int m = (int) (MINUTES_PER_HOUR * (T - h)); // Знаходимо кількість хвилин, що залишились

    // Виводимо результат обчислень

    cout << endl;
    cout << left << setw(35) << "Модель станції: "  << right << setw(10)<< stationModel << endl;
    cout << left << setw(35) << "Паспортна ємність: " << right << setw(10) << fixed << setprecision(1) << ratedCapacity << " Вт·год" << endl;
    cout << left << setw(35) << "Вік станції: " << right << setw(10) << years << " р." << endl;
    cout << left << setw(35) << "Фактична ємність: " << right << setw(10) << fixed << setprecision(1) << C_eff << " Вт·год" << endl;
    cout << left << setw(35) << "Рівень заряду: "  << right << setw(10) << charge << "%" << endl;
    cout << left << setw(35) << "ККД інвертора: "  << right << setw(10)<< fixed << setprecision(2) << efficiency <<'%' << endl;
    cout << left << setw(35) << "Запас енергії: "  << right << setw(10)<< fixed << setprecision(1) << E_Stored << " Вт·год" << endl;
    cout << left << setw(35) << "Корисна енергія: " << right << setw(10) << fixed << setprecision(1) << E_useful <<" Вт·год" << endl;
    cout << left << setw(35) << "Втрати на перетворенні: " << right << setw(10) << fixed << setprecision(1) << E_loss << " Вт·год"<<endl;
    cout << left << setw(35) << "Час роботи: " << right << setw(10) << fixed << setprecision(2) << T << " год" << " = " << h << "годин " << m << " хв" << endl;
}