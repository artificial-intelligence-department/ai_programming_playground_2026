/* 
 Обчислення часу роботи портативної зарядної станції
 Цьона Олена
 ШІ-12
 */

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    //вхідні змінні
    string model;      // Модель станції
    double C;          // Паспортна ємність (Вт·год)
    int years;         // Вік станції (років)
    int charge;        // Рівень заряду (%)
    double eff;        // ККД інвертора (%) 
    double P;          // Потужність приладу (Вт)

    const double DEGRADATION_RATE = 2.0;       // відсоток втрати ємності за рік.


    // Введення даних із перевіркою на коректність введення

    cout << "Модель станції: ";
    if (!(cin >> model) || model.length() > 31) {
        cout << "Помилка введення даних! Назва моделі повинна містити не більше 31 символа.\n";
        return 1;
    }

    cout << "Паспортна ємність (Вт·год): ";
    if (!(cin >> C) || C <= 0) {
        cout << "Помилка введення даних! Ємність може бути лише більше 0\n";
        return 1;
    }

    cout << "Вік станції (років): ";
    if (!(cin >> years) || years < 0 || years > 20) {
        cout << "Помилка введення даних! Вік повинен бути від 0 до 20.\n";
        return 1;
    }

    cout << "Введіть рівень заряду (%): ";
    if (!(cin >> charge) || charge < 0 || charge > 100) {
        cout << "Помилка введення даних! Рівень заряду повинен бути від 0 до 100.\n";
        return 1;
    }

    cout << "ККД інвертора (%): ";
    if (!(cin >> eff) || eff <= 0 || eff > 100) {
        cout << "Помилка введення даних! ККД інвертора повинно бути більше 0 і не більше 100.\n";
        return 1;
    }

    cout << "Потужність приладу (Вт): ";
    if (!(cin >> P) || P <= 0) {
        cout << "Помилка введення даних! Потужність може бути лише більше 0.\n";
        return 1;
    }

    // Обчислення 

    // Корригуємо паспортну ємність з урахуванням річного зносу акумулятора (Вт·год)
    // Переводимо відсоток деградації у частку для розрахунку залишкового ресурсу
    double C_eff = C * pow(1.0 - DEGRADATION_RATE / 100.0, years);

    // Визначаємо фактичний запас енергії відповідно до поточного рівня заряду (Вт·год)
    // Переводимо відсотки заряду у частку від реальної ємності
    double E_stored = C_eff * charge / 100.0;

    // Обчислюємо обсяг енергії, який дійде до споживача після перетворення напруги (Вт·год)
    // Враховуємо коефіцієнт корисної дії (ККД) інвертора
    double E_useful = E_stored * eff / 100.0;

    // Визначаємо втрати енергії, що розсіюються у вигляді тепла під час роботи інвертора (Вт·год)
    double E_loss = E_stored - E_useful;

    // Обчислюємо тривалість автономної роботи приладу заданої потужності (годин)
    double T = E_useful / P;

    // Розкладаємо загальний час на цілу кількість годин та хвилини
    int h = static_cast<int>(T);
    int m = static_cast<int>((T - h) * 60.0);

    // Виведення результатів 

    const int label_width = 25;       //ширина колонки
    const int val_width = 10;

   cout << endl;

    cout << left << setw(label_width) << "Модель:" 
         << right << setw(val_width) << model << endl;

    cout << fixed << setprecision(1);             // fixed - ввід дійсних чисел із фіксованою кількістю знаків після крапки
                                                  // setprecision(n) — задає n знаків після крапки для дійсних чисел
    cout << left << setw(label_width) << "Паспортна ємність:" 
         << right << setw(val_width) << C << " Вт·год" << endl;

    cout << left << setw(label_width) << "Вік станції:" 
         << right << setw(val_width) << years << " р." << endl;

    cout << left << setw(label_width) << "Фактична ємність:" 
         << right << setw(val_width) << C_eff << " Вт·год" << endl;

    cout << left << setw(label_width) << "Рівень заряду:" 
         << right << setw(val_width) << charge << " %" << endl;

    cout << fixed << setprecision(2);
    cout << left << setw(label_width) << "ККД інвертора:" 
         << right << setw(val_width) << eff << " %" << endl;

    cout << fixed << setprecision(1);
    cout << left << setw(label_width) << "Запас енергії:" 
         << right << setw(val_width) << E_stored << " Вт·год" << endl;

    cout << left << setw(label_width) << "Корисна енергія:" 
         << right << setw(val_width) << E_useful << " Вт·год" << endl;

    cout << left << setw(label_width) << "Втрати на перетворенні:" 
         << right << setw(val_width) << E_loss << " Вт·год" << endl;

    cout << fixed << setprecision(2);
    cout << left << setw(label_width) << "Час роботи:" 
         << right << setw(val_width) << T << " год  = " 
         << h << " год " << setfill('0') << setw(2) << m << " хв" << endl;  
           //якщо кількість хвилин менша за 10, доповнить її нулем спереду (05 замість 5).

    return 0;
}