#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    // 1. Оголошення змінних для збереження даних
    string model;   // Назва зарядної станції
    double C;       // Паспортна ємність (Вт-год) 
    int years;      // Вік станції (років)
    int charge;     // Поточний рівень заряду (%)
    double eff;     // ККД інвертора (%)
    double P;       // Потужність підключеного приладу (Вт)

    // 2. Введення даних з перевіркою
    cout << "Модель станції: ";
    cin >> model;
    if (model.length() >= 31) {
        cout << "Помилка: назва станції не повинна перевищувати 30 символів." << endl;
        return 1;
    }

    cout << "Паспортна ємність (Вт-год): ";
    if (!(cin >> C) || C <= 0) {
        cout << "Помилка: невірне значення паспортної ємності." << endl;
        return 1;
    }

    cout << "Вік станції (років): ";
    if (!(cin >> years) || years < 0 || years > 20) {
        cout << "Помилка: невірне значення віку станції." << endl;
        return 1;
    }

    cout << "Рівень заряду (%): ";
    if (!(cin >> charge) || charge < 0 || charge > 100) {
        cout << "Помилка: невірне значення рівня заряду." << endl;
        return 1;
    }

    cout << "ККД інвертора (%): ";
    if (!(cin >> eff) || eff < 0 || eff > 100) {
        cout << "Помилка: невірне значення ККД інвертора." << endl;
        return 1;
    }
    
    cout << "Потужність приладу (Вт): ";
    if (!(cin >> P) || P <= 0) {
        cout << "Помилка: невірне значення потужності приладу." << endl;
        return 1;
    }

    // 3. Математичні розрахунки
    
    // Коефіцієнт зносу акумулятора (2% на рік)
    const double ANNUAL_DEGRADATION_RATE = 2.0;

    // Фактична ємність батареї з урахуванням її віку (формула складного відсотка)
    double C_eff = C * pow(1.0 - (ANNUAL_DEGRADATION_RATE / 100.0), years);

    // Запас енергії у акумуляторі при поточному заряді
    double E_stored = C_eff * (charge / 100.0);

    // Корисна енергія, яку видасть інвертор з урахуванням його ККД
    double E_useful = E_stored * (eff / 100.0);

    // Втрати енергії на нагрів та перетворення
    double E_loss = E_stored - E_useful;

    // Загальний час роботи приладу в годинах (дробове число)
    double T = E_useful / P;

    // Виділяємо цілі години
    int h = static_cast<int>(T);

    // Переводимо дробовий залишок годин у хвилини
    int m = static_cast<int>((T - h) * 60);

    // 4. Форматований вивід результатів у колонку
    cout << "\nВивід програми:" << endl;
    cout << left << setw(25) << "Модель:" << model << endl;
    
    cout << fixed << setprecision(1); // 1 знак після коми для ємності та відсотків
    cout << left << setw(25) << "Паспортна ємність:" << C << " Вт-год" << endl;
    cout << left << setw(25) << "Вік станції:" << years << " р." << endl;
    cout << left << setw(25) << "Фактична ємність:" << C_eff << " Вт-год" << endl;
    cout << left << setw(25) << "Рівень заряду:" << charge << "%" << endl;
    
    cout << setprecision(2); // 2 знаки після коми для ККД
    cout << left << setw(25) << "ККД інвертора:" << eff << "%" << endl;
    
    cout << setprecision(1);
    cout << left << setw(25) << "Запас енергії:" << E_stored << " Вт-год" << endl;
    cout << left << setw(25) << "Корисна енергія:" << E_useful << " Вт-год" << endl;
    cout << left << setw(25) << "Втрати на перетворенні:" << E_loss << " Вт-год" << endl;
    
    cout << setprecision(2); // 2 знаки після коми для часу
    cout << left << setw(25) << "Час роботи:" << T << " год = " 
         << h << " год " << setfill('0') << setw(2) << m << " хв" << endl;

    return 0;
}