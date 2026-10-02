/*
 * Задача: Автономність портативної зарядної станції
 * Автор: Балицький Ростислав
 * Група: СШІ-12
 */
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

    const double A = 2.0; // відсоток втрати ємності за рік (%)
    const double Per = 100.0; // Дільник для переведення відсоткових значень у частку
    const double MinH = 60.0; // Кількість хвилин в одній годині (хв)

    string model;
    cout << "Модель станції: ";
     if (!(cin >> model) || model.length() > 31) {
        cout << "Помилка: назва моделі станції не повинна містити більше 31 символу." << endl;
        return 1;
    }
    double c;
    cout << "Паспортна ємність, Вт·год:";
     if (!(cin >> c) || c <= 0) {
        cout << "Помилка: Паспортна ємність мусить бути більше 0." << endl;
        return 1;
    }
   
    int years;
    cout << "Вік станції, років: ";
    if (!(cin >> years) || years <0 || years > 20) {
        cout << "Помилка: вік станції мусить бути від 0 до 20." << endl;
        return 1;
    }   
  
    int charge;
    cout << "Рівень заряду, %:";
    if (!(cin >> charge) || charge < 0 || charge > 100) {
        cout << "Помилка: рівень заряду мусить бути від 0 до 100." << endl;
        return 1;
    }

    double eff;
    cout << "ККД інвертора, %:";
    if (!(cin >> eff) || eff <= 0 || eff > 100) {
        cout << "Помилка: ККД інвертора мусить бути більше 0, не більше 100." << endl;
        return 1;
    }

    double P;
    cout << "Потужність приладу, Вт: ";
    if (!(cin >> P) || P <= 0) {
        cout << "Помилка: потужність приладу мусить бути більше 0." << endl;
        return 1;
    }

// порядок обчислень

    double c_eff = c *pow(1.0 - (A/Per), years); //обчислення фактичної ємності з урахуванням віку станції (Вт·год)
    if (years == 0) { c_eff = c; }

    double E_stored = c_eff * charge / Per; //Переводимо відсотки у частку та обчислюємо запас енергії при поточному заряді (Вт·год)

    double E_useful = E_stored * eff / Per; //Обчислення корисної енергії, із врахуванням ККД інвертора (Вт·год)

    double E_loss = E_stored - E_useful; //Обчислення втрат на перетворенні напруги (Вт·год)

    double t = E_useful / P; // Обчислення загального часу роботи приладу від станції (годин)

    int h = t; //Виділення цілої частини від загального часу роботи (години)

    int m = (t - h) * MinH; //Виділення дробової частини від загального часу роботи та переведення її у хвилини
    
    // Вивід результатів
    cout << endl;
    cout << left << setw(23) << "Модель:" << right << setw(34) << model << endl;

    cout << fixed << setprecision(1);
    cout << left << setw(23) << "Паспортна ємність:" << right << setw(30) << c << " Вт·год" << endl;
    cout << left << setw(23) << "Вік станції:" << right << setw(35) << years << " р." << endl;

    cout << setprecision(1);
    cout << left << setw(23) << "Фактична ємність з урахуванням віку: " << right << setw(11) << c_eff << " Вт·год" << endl;
    cout << left << setw(23) << "Рівень заряду:" << right << setw(34) << charge << " %" << endl;

    cout << setprecision(2);
    cout << left << setw(21) << "ККД інвертора:" << right << setw(34) << eff << " %" << endl;
    
    cout << setprecision(1);
    cout << left << setw(23) << "Запас енергії при поточному заряді:" << right << setw(13) << E_stored << " Вт·год" << endl;
    cout << left << setw(23) << "Корисна енергія, що дійде до приладу:" << right << setw(11) << E_useful << " Вт·год" << endl;
    cout << left << setw(23) << "Втрати на перетворенні напруги:" << right << setw(17) << E_loss << " Вт·год" << endl;
    cout << left << setw(23) << "Час роботи:" << right << setw(34) << t << " год  = "
         << h << " год " << setfill('0') << setw(2) << m << " хв" << endl;
    
        return 0;
}