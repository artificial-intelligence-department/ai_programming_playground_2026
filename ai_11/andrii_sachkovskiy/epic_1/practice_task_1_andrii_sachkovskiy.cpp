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
    if (years < 0 || years > MAX_YEARS) {
        cout << "Помилка: вік станції мусить бути від 0 до " << MAX_YEARS << "." << endl;
        return
