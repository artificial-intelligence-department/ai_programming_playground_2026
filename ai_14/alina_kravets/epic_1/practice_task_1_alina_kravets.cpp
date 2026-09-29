/*Автономність портативної зарядної станції
Кравець Аліна
ШІ-14*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{

    string model_name = "no name"; //створюємо змінні
    double passport_capacity = 0.0;
    int age = 0;
    int charge = 0;
    double efficiency = 0.0;
    double power = 0.0;
    double actual_capacity = 0.0;
    double energy = 0.0;
    double useful_energy = 0.0;
    double lost_energy = 0.0;
    double time = 0.0;
    double capacity_left = 0.0;
    double hours = 0.0;
    double minutes = 0.0;

    cout << "Input name: ";
    cin >> model_name; //вводимо назву моделі
    if (model_name.length() > 31) //перевіряємо довжину назви моделі
    {
        cout << "Model name is too long" << endl;
        return 1;
    }

    cout << "Input capacity (W/hour): ";
    cin >> passport_capacity; //вводимо паспортну ємність
    if (passport_capacity < 0) //перевіряємо значення паспортної ємності
    {
        std::cout << "Incorrect capacity" << endl;
        return 1;
    }

    cout << "Input age (years): "; //вводимо вік
    cin >> age; //перевіряємо значення віку
    if (age < 0 || age > 20)
    {
        cout << "Incorrect age" << endl;
        return 1;
    }

    cout << "Input charge (%): "; //вводимо заряд
    cin >> charge; //перевіряємо значення заряду
    if (charge < 0 || charge > 100)
    {
        cout << "Incorrect charge" << endl;
        return 1;
    }

    cout << "Input efficiency (%): "; //вводимо ККД
    cin >> efficiency; //перевіряємо значення ККД
    if (efficiency < 0 || efficiency > 100)
    {
        cout << "Incorrect efficiency" << endl;
        return 1;
    }

    cout << "Input power (W): "; //вводимо потужність
    cin >> power; //перевіряємо значення потужності
    if (power < 0)
    {
        cout << "Incorrect power" << endl;
        return 1;
    }

    capacity_left = pow (1-2.0/100, age); //рахуємо скільки відсотків ємності залишиться
    actual_capacity = passport_capacity * capacity_left; //рахуємо фактичну ємність за формулою
    energy = actual_capacity * charge /100.0; //рахуємо енергію, переводячи відсотки в десятковий дріб
    useful_energy = energy * efficiency /100; //рахуємо корисну енергію, переводячи відсотки в десятковий дріб
    lost_energy = energy - useful_energy; //рахуємо втрату енергії за формулою
    time = useful_energy / power; //рахуємо час за формулою
    hours = floor(time); //визначаємо цілу частину всього часу
    minutes = floor((time - hours)*60); //рахуємо хвилини і беремо цілу частину

    cout << "-------Information-------" << endl; //вивід інформації
    cout << "Model name: " << model_name << endl;
    cout << "Passport capacity: " << passport_capacity << " W/hour" << endl;
    cout << "Age: " << age << " years" << endl;
    cout << "Actual capacity: " << actual_capacity << " W/hour" << endl;
    cout << "Charge: " << charge << " %" << endl;
    cout << "Efficiency: " << efficiency << " %" << endl;
    cout << "Energy: " << energy << " W/hour" << endl;
    cout << "Useful energy: " << useful_energy << " W/hour" << endl;
    cout << "Energy loss: " << lost_energy << " W/hour" << endl;
    cout << "Time: " << time << " hours = " << hours << " hours " << minutes << " minutes" << endl;

    return 0;
}