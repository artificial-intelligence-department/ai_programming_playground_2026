/*Назва задачі: Автономність портативної зарядної станції
Автор: Барановський Максим
Група: ШІ-11*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

    /*Введення даних та їх перевірка умовними конструкціями*/

    cout << "Введіть модель станції: ";
    string chargingStationModel;

    if(!((cin >> chargingStationModel)) || chargingStationModel.length() > 31){
        cout << "Помилка: Модель станції повинна складатись з одного слова та не більше 31 символу." << endl;
        return 1;
    }

    cout << "Введіть паспортну ємність станції (Вт*год): ";
    double nominalCapacity;

    if(!(cin >> nominalCapacity) || nominalCapacity <= 0){
        cout << "Помилка: Паспортна ємність повинна бути додатним числом." << endl;
        return 1;
    }

    cout << "Введіть вік станції (років): ";
    int yearsOfUse;

    if(!(cin >> yearsOfUse) || yearsOfUse < 0 || yearsOfUse > 20){
        cout << "Помилка: Вік станції повинен бути цілим числом від 0 до 20." << endl;
        return 1;
    }

    cout << "Введіть рівень заряду станції (%): ";
    int chargeLevel;

    if(!(cin >> chargeLevel) || chargeLevel < 0 || chargeLevel > 100){
        cout << "Помилка: Рівень заряду станції повинен бути цілим числом від 0 до 100." << endl;
        return 1;
    }

    cout << "Введіть ККД інвертора (%): ";
    double efficiency;

    if(!(cin >> efficiency) || efficiency <= 0 || efficiency > 100){
        cout << "Помилка: ККД інвертора повинен бути числом від 0 до 100." << endl;
        return 1;
    }

    cout << "Введіть потужність зарядної станції (Вт): ";
    double power;

    if(!(cin >> power) || power <= 0){
        cout << "Помилка: Потужність станції повинна бути додатним числом." << endl;
        return 1;
    }

    /*Декларуємо змінні та здійснюємо розрахунки*/
     
    const double DEGRADATION_RATE = 0.02; // Відсоток втрати ємності за рік

    double actualCapacity = nominalCapacity * pow((1 - DEGRADATION_RATE), yearsOfUse); // Фактична ємність з урахуванням віку (Вт*год)
    double storedEnergy = actualCapacity * chargeLevel / 100.0; // Запас енергії (Вт*год)
    double usefulEnergy = storedEnergy * efficiency / 100.0; // Корисна енергія (Вт*год)
    double lostEnergy = storedEnergy - usefulEnergy; // Втрати при перетворенні (Вт*год)
    double workingTime = usefulEnergy / power; // Час роботи (год)
    int hours = int(workingTime); //Ціла частина часу роботи (год)
    int minutes = int((workingTime - hours) * 60); //Хвилини часу роботи (хв)

    
    // Виведення результатів

    cout << left;
    cout << fixed;

    cout << setw(32) << "Модель:" << chargingStationModel << endl;

    cout << setprecision(1);
    cout << setw(42) << "Паспортна ємність:" << nominalCapacity << " Вт*год" << endl;
    cout << setw(36) << "Вік станції:" << yearsOfUse << " р." << endl;
    cout << setw(38) << "Рівень заряду:" << chargeLevel << " %" << endl;
    cout << setw(41) << "Фактична ємність:" << actualCapacity << " Вт*год" << endl;

    cout << setprecision(2);
    cout << setw(38) << "ККД інвертора:" << efficiency << " %" << endl;

    cout << setprecision(1);
    cout << setw(38) << "Запас енергії:" << storedEnergy << " Вт*год" << endl;
    cout << setw(40) << "Корисна енергія:" << usefulEnergy << " Вт*год" << endl;
    cout << setw(47) << "Втрати при перетворенні:" << lostEnergy << " Вт*год" << endl;

    cout << setprecision(2);
    cout << setw(35) << "Час роботи:" << workingTime << " год = " << hours << " год " 
     << right << setw(2) << setfill('0') << minutes << setfill(' ') << " хв" << endl;

    return 0;
}