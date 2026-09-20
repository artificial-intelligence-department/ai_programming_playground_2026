/*  
Автономність портативної зарядної станції
Карпінський Віталій
СШІ-14
*/



#include <iostream>
#include <locale>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "uk_UA");
    // Введення змінних для вхідних даних
    string name;
    float C;
    int years;
    int charge;
    float eff;
    float P;
    // Введення та перевірка вхідних даних
    cout << "Введіть назву станції (без пробілів): ";
    cin >> name;
    if (name.length() > 31) {
        cout << "Помилка: назва станції не може перевищувати 31 символ" << endl;
    return 1; 
    }
    cout << "Введіть паспортну ємність Вт·год: ";
    cin >> C;
    if (C <= 0){
        cout << "Помилка: паспортна ємність повинна бути більшою за 0" << endl;
    return 1; 
    }
    cout << "Введіть вік станції: ";
    cin >> years;
    if ( years > 20 || years < 0) {
        cout << "Помилка: вік станції повинен бути в діапазоні від 0 до 20" << endl;
    return 1; 
    }
    cout << "Введіть рівень заряду, %: ";
    cin >> charge;
    if (charge < 0 || charge > 100) {
        cout << "Помилка: рівень заряду повинен бути в діапазоні від 0 до 100" << endl;
        return 1;
    }
    cout << "Введіть ККД інвертора, %: ";
    cin >> eff;
    if (eff <= 0 || eff > 100) {
        cout << "Помилка: ККД інвертора повинен бути в діапазоні від 1 до 100" << endl;
        return 1;
    }
    cout << "Введіть потужність приладу, Вт: ";
    cin >> P;
    if (P <= 0){
        cout << "Помилка: потужність приладу повинна бути більшою за 0" << endl;
    return 1; 
    }
    // Рахуємо ємність з врахуванням зносу (0.98 - це мінус 2% ємності за кожен рік) у Вт·год
    float C_eff = C * pow(0.98, years);
    // Рахуємо скільки зараз є енергії в базі від поточного заряду у Вт·год
    float E_stored = C_eff * (charge / 100);
    // Переводимо відсотки ККД у частку і рахуємо корисну енергію у Вт·год
    float E_useful = E_stored * (eff / 100);
    // Втрати енергії при перетворенні у Вт·год
    float E_loss = E_stored - E_useful;
    // Час роботи приладу в годинах
    float T = E_useful / P;
    // Переводимо дробовий час у години та хвилини
    int h = T;
    int m = (T - h) * 60;

    // Виводимо табличку
    cout << left << setw(30) << "Модель:"
            << right << setw(15) << name << endl;
    cout << left << setw(30) << "Паспортна ємність:"
            << right << setw(15) << fixed << setprecision(1) << C << " Вт·год" << endl;
    cout << left << setw(30) << "Вік станції:"
         << right << setw(10) << years << " р." << endl;
    cout << left << setw(30) << "Фактична ємність:"
         << right << setw(10) << fixed << setprecision(1) << C_eff << " Вт·год" << endl;
    cout << left << setw(30) << "Рівень заряду:"
         << right << setw(10) << charge << " %" << endl;
    cout << left << setw(30) << "ККД інвертора:"
         << right << setw(10) << fixed << setprecision(2) << eff << " %" << endl;
    cout << left << setw(30) << "Запас енергії:"
         << right << setw(10) << fixed << setprecision(1) << E_stored << " Вт·год" << endl;
    cout << left << setw(30) << "Корисна енергія:"
         << right << setw(10) << fixed << setprecision(1) << E_useful << " Вт·год" << endl;
    cout << left << setw(30) << "Втрати на перетворенні:"
         << right << setw(10) << fixed << setprecision(1) << E_loss << " Вт·год" << endl;
    cout << left << setw(30) << "Час роботи:"
         << right << setw(10) << fixed << setprecision(2) << T << " год  = "
         << h << " год " << setfill('0') << setw(2) << m << " хв" << endl;

    return 0;
}