/*Автономність портативної зарядної станції
Максімко - СШІ-13*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main()
{
    //Задання змінних
    string modelStation;

    int years, charge, hours, minutes;

    float capacity, eff, power, capacity_eff, E_stored, E_useful, E_loss, time;
    //Константа втрати ємності
    const double LOSS = 2.0;

    //Оголошення змінних і перевірка на правильність введених даних
    cout << "Введіть модель станції: "; 
    cin >> modelStation;
    //Валідація моделі станції за ознакою того, що кількість символів не довша 31-го
    if(modelStation.size() > 31)
    {
        cout << "Назва моделі повинна бути не довша 31 символу!" << endl;
        return 1;
    }

    cout << "Введіть паспортну ємність: ";
    cin >> capacity;
    //Валідація на правильний тип введених даних
    if(cin.fail())
    {
        cout << "Введені дані повинні бути числом!" << endl;
        return 1;
    }
    //Валідація ємності станції за тим, що вона більше 0 та не більша 5000 Вт*год
    if(capacity <= 0 || capacity > 5000) 
    {
        cout << "Паспортна ємність повинна бути більше 0 і не більша 5000!" << endl;
        return 1;
    }

    cout << "Введіть вік станції: ";
    cin >> years;
    //Валідація на правильний тип введених даних
    if(cin.fail())
    {
        cout << "Введені дані повинні бути числом!" << endl;
        return 1;
    }
    //Валідація віку станції за тим, що він не менше 0 та не більше 20 років
    if(years < 0 || years > 20) 
    {
        cout << "Вік станції повинен бути від 0 до 20 років!" << endl;
        return 1;
    }

    cout << "Введіть рівень заряду: ";
    cin >> charge;
    //Валідація на правильний тип введених даних
    if(cin.fail())
    {
        cout << "Введені дані повинні бути числом!" << endl;
        return 1;
    }
    //Валідація заряду станції за тим, що він не менше 0 та не більше 100 %
    if(charge < 0 || charge > 100)
    {
        cout << "Рівень заряду повинен бути від 0 до 100!" << endl;
        return 1;
    }

    cout << "Введіть ККД інвертора: ";
    cin >> eff;
    //Валідація на правильний тип введених даних
    if(cin.fail())
    {
        cout << "Введені дані повинні бути числом!" << endl;
        return 1;
    }
    //Валідація ККД інвертора за тим, що воно більше 0 і не більше 100 %
    if(eff <= 0 || eff > 100)
    {
        cout << "ККД інвертора повинне бути більше 0, але не більше 100!" << endl;
        return 1;
    }

    cout << "Введіть потужність приладу: ";
    cin >> power;
    //Валідація на правильний тип введених даних
    if(cin.fail())
    {
        cout << "Введені дані повинні бути числом!" << endl;
        return 1;
    }
    //Валідація потужності приладу за тим, що він повинен бути не менше 0 та не більше 21000 Вт
    if(power <= 0 || power > 21000)
    {
        cout << "Потужність приладу повинна бути більше 0 і не більше 21000!" << endl;
        return 1;
    }

    //Розрахунок фактичної ємності
    capacity_eff = capacity * pow(1 - LOSS/100, years);
    
    //Розрахунок запасу енергії при поточному заряді
    E_stored = capacity_eff * charge / 100;

    //Розрахунок корисної енергії
    E_useful = E_stored * eff / 100;

    //Розрахунок втрати на перетворення приладу
    E_loss = E_stored - E_useful;

    //Розрахунок часу роботи
    time = E_useful / power;
    //Розрахунок повних годин
    hours = floor(time);
    //Розрахунок хвилин
    minutes = floor((time - hours) * 60);

    //Виведення даних
    cout << endl << "Модель: " << modelStation << endl;
    cout << "Паспортна ємність: " << fixed << setprecision(1) << capacity << " Вт*год " << endl; 
    cout << "Вік станції: " << years << " р. "<< endl;
    cout << "Фактична ємність: " << fixed << setprecision(1) << capacity_eff << " Вт*год " << endl;
    cout << "Рівень заряду: " << charge << " % " << endl;
    cout << "ККД інвертора: " << fixed << setprecision(2) << eff << " % " << endl;
    cout << "Запас енергії: " << fixed << setprecision(1) << E_stored << " Вт*год " << endl;
    cout << "Корисна енергія: " << fixed << setprecision(1) << E_useful << " Вт*год " << endl;
    cout << "Втрати на перетворенні: " << fixed << setprecision(1) << E_loss << " Вт*год " << endl;
    cout << "Час роботи: " << fixed << setprecision(2) << time << " год = " << fixed << setprecision(0) << hours << " год " << setfill('0') << setw(2) << minutes << " хв " << endl;
    return 0;
}