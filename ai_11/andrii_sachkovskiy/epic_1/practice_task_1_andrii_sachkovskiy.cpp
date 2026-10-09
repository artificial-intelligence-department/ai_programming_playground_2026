/*
 * Задача: Автономність портативної зарядної станції
 * Автор: Сачковський Андрій
 * Група: AI-11
 */
#include <iostream>  // cin, cout
#include <iomanip>   // setw, setprecision, setfill
#include <cmath>     // pow
#include <string>    // string для назви моделі

using namespace std;

// Сталі
const int MAX_MODEL_LEN = 31;      // максимальна довжина назви моделі (символів)
const int MAX_YEARS = 20;          // максимально допустимий вік станції (років)
const double PERCENT = 100.0;      // 100 % це верхня межа для заряду та ККД, а також база для переводу відсотків у частку
const double DEGRADATION = 2.0;    // відсоток втрати ємності акумулятора за рік
const int MIN_PER_HOUR = 60;       // кількість хвилин в одній годині

int main() {
    // Ввід даних з перевіркою
    string model;
    cout << "Модель станції: ";
    cin >> model;
    if (model.length() > MAX_MODEL_LEN) {
        cout << "Помилка: назва моделі не довша " << MAX_MODEL_LEN << " символів." << endl;
        return 1;
    }

    double capacity;  // паспортна ємність, Вт·год
    cout << "Паспортна ємність (Вт·год): ";
    cin >> capacity;
    if (cin.fail()) {
        cout << "Помилка: ємність має бути числом." << endl;
        return 1;
    }
    if (capacity <= 0) {
        cout << "Помилка: паспортна ємність мусить бути більше 0." << endl;
        return 1;
    }

    int years;  // вік станції, років
    cout << "Вік станції (років): ";
    cin >> years;
    if (cin.fail()) {
        cout << "Помилка: вік станції має бути цілим числом." << endl;
        return 1;
    }
    if (years < 0  years > MAX_YEARS) {
        cout << "Помилка: вік станції мусить бути від 0 до " << MAX_YEARS << "." << endl;
        return 1;
    }

    int charge;  // поточний рівень заряду, %
    cout << "Рівень заряду (%): ";
    cin >> charge;
    if (cin.fail()) {
        cout << "Помилка: рівень заряду має бути цілим числом." << endl;
        return 1;
    }
    if (charge < 0  charge > PERCENT) {
        cout << "Помилка: рівень заряду мусить бути від 0 до " << PERCENT << "." << endl;
        return 1;
    }

    double eff;  // ККД інвертора, %
    cout << "ККД інвертора (%): ";
    cin >> eff;
    if (cin.fail()) {
        cout << "Помилка: ККД має бути числом." << endl;
        return 1;
    }
    if (eff <= 0 || eff > PERCENT) {
        cout << "Помилка: ККД мусить бути більше 0 і не більше " << PERCENT << "." << endl;
        return 1;
    }

    double power;  // потужність приладу, Вт
    cout << "Потужність приладу (Вт): ";
    cin >> power;
    if (cin.fail()) {
        cout << "Помилка: потужність має бути числом." << endl;
        return 1;
    }
    if (power <= 0) {
        cout << "Помилка: потужність мусить бути більше 0." << endl;
        return 1;
    }

    // Обчислення
    // Фактична ємність з урахуванням старіння акумулятора, Вт·год
    double actualCapacity = capacity * pow(1 - DEGRADATION / PERCENT, years);

    // Запас енергії при поточному рівні заряду, Вт·год
    double stored = actualCapacity * charge / PERCENT;

    // Корисна енергія, що дійде до приладу після інвертора, Вт·год
    double useful = stored * eff / PERCENT;

    // Втрати енергії на перетворенні напруги, Вт·год
    double loss = stored - useful;

    // Час роботи приладу, годин
    double time = useful / power;

    // Повні години (відкидаємо дробову частину)
    int hours = (int)time;

    // Хвилини, що залишились: дробову частину години переводимо у хвилини
    int minutes = (int)((time - hours) * MIN_PER_HOUR);

    // Вивід результатів
    
    cout << fixed;
    cout << "Модель:                 " << model << endl;
    cout << "Паспортна ємність:      " << setw(10) << setprecision(1) << capacity << " Вт·год" << endl;
    cout << "Вік станції:            " << setw(10) << years << " р." << endl;
    cout << "Фактична ємність:       " << setw(10) << setprecision(1) << actualCapacity << " Вт·год" << endl;
    cout << "Рівень заряду:          " << setw(10) << charge << " %" << endl;
    cout << "ККД інвертора:          " << setw(10) << setprecision(2) << eff << " %" << endl;
    cout << "Запас енергії:          " << setw(10) << setprecision(1) << stored << " Вт·год" << endl;
    cout << "Корисна енергія:        " << setw(10) << setprecision(1) << useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні: " << setw(10) << setprecision(1) << loss << " Вт·год" << endl;
    cout << "Час роботи:             " << setw(10) << setprecision(2) << time << " год  = "
         << hours << " год " << setfill('0') << setw(2) << minutes << " хв" << endl;

    return 0;
}