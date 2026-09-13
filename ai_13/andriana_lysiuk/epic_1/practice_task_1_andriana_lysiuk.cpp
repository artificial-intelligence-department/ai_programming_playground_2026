
/*
 * Задача: Автономність портативної зарядної станції
 * Автор: Лисюк Андріана
 * Група: ШІ-13
 */

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    const double DEGRADATION_RATE = 2.0; // Відсоток втрати ємності акумулятора за рік

    string model;
    double capacity;
    int years;
    int charge;
    double eff;
    double power;

    // Ввід та перевірка даних
    cout << "Модель станції: ";
    if (!(cin >> model) || model.length() > 31) {
        cout << "Помилка: назва моделі занадто довга або некоректна." << endl;
        return 1;
    }

    cout << "Паспортна ємність (Вт·год): ";
    if (!(cin >> capacity) || capacity <= 0) {
        cout << "Помилка: паспортна ємність мусить бути більше 0." << endl;
        return 1;
    }

    cout << "Вік станції (років): ";
    if (!(cin >> years) || years < 0 || years > 20) {
        cout << "Помилка: вік станції мусить бути від 0 до 20." << endl;
        return 1;
    }

    cout << "Рівень заряду (%): ";
    if (!(cin >> charge) || charge < 0 || charge > 100) {
        cout << "Помилка: рівень заряду мусить бути від 0 до 100." << endl;
        return 1;
    }

    cout << "ККД інвертора (%): ";
    if (!(cin >> eff) || eff <= 0 || eff > 100) {
        cout << "Помилка: ККД інвертора мусить бути в межах від 0 до 100." << endl;
        return 1;
    }

    cout << "Потужність приладу (Вт): ";
    if (!(cin >> power) || power <= 0) {
        cout << "Помилка: потужність приладу мусить бути більше 0." << endl;
        return 1;
    }

    cout << "\nВивід програми\n";

    // 1. Фактична ємність з урахуванням віку, Вт·год
    double c_eff = capacity * pow(1.0 - DEGRADATION_RATE / 100.0, years);

    // 2. Запас енергії при поточному заряді, Вт·год
    double e_stored = c_eff * charge / 100.0;

    // 3. Корисна енергія, що дійде до приладу, Вт·год
    double e_useful = e_stored * eff / 100.0;

    // 4. Втрати на перетворенні напруги, Вт·год
    double e_loss = e_stored - e_useful;

    // 5. Час роботи, годин
    double total_hours = e_useful / power;

    // 6. Повні години
    int h = total_hours;

    // 7. Хвилини, що залишились
    int m = (total_hours - h) * 60;

    // Виведення результат
    cout << fixed;
    cout << "Модель:" << model << endl;
    
    cout << setprecision(1) << "Паспортна ємність: " << capacity << " Вт·год" << endl;
    cout << "Вік станції: " << years << " р." << endl;
    cout << setprecision(2) << "Фактична ємність: " << c_eff << " Вт·год" << endl;
    cout << setprecision(0) << "Рівень заряду: " << charge << " %" << endl;
    cout << setprecision(1) << "ККД інвертора: " << eff << " %" << endl;
    cout << setprecision(2) << "Запас енергії: " << e_stored << " Вт·год" << endl;
    cout << setprecision(2) << "Корисна енергія: " << e_useful << " Вт·год" << endl;
    cout << setprecision(2) << "Втрати на перетворенні: " << e_loss << " Вт·год" << endl;
    
    cout << setprecision(2) << "Час роботи: " << total_hours << " год  = " 
         << h << " год " << (m < 10 ? "0" : "") << m << " хв" << endl;

    return 0;
}
