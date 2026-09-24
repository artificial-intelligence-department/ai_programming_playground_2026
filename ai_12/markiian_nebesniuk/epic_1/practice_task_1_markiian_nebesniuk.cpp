/*
Автономність портативної зарядної станції
Небесню
ШІ-12
*/


#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    // Введення та перевірка вихідних даних
    string model;
    int word_length;
    cout << "Модель станції: ";
    cin >> model;
    word_length = model.size();
    if (word_length > 31) {
        cout << "Помилка: кількість символів в назві моделі станції не повинна перевищувати 31." << endl;
        return 1;
    }

    double C;
    cout << "Паспортна ємність (Вт·год): ";
    cin >> C;
    if (C <= 0) {
        cout << "Помилка: паспортна ємність мусить бути більше 0." << endl;
        return 1;
    }


    int years;
    cout << "Вік станції (років): ";
    cin >> years;
    if (years > 20 || years < 0) {
        cout << "Помилка: вік станції мусить бути від 0 до 20." << endl;
        return 1;
    }

    int charge;
    cout << "Рівень заряду (%): ";
    cin >> charge;
    if (charge > 100 || charge < 0) {
        cout << "Помилка: рівень зарядку мусить бути від 0 до 100." << endl;
        return 1;
    }
    
    double eff;
    cout << "ККД інвертора (%): ";
    cin >> eff;
    if (eff > 100 || eff <= 0) {
        cout << "Помилка: ККД інвертора мусить бути більше 0, не більше 100." << endl;
        return 1;
    }

    int P;
    cout << "Потужність приладу (Вт): ";
    cin >> P;
    if (P <= 0) {
        cout << "Помилка: потужність приладу мусить бути більше 0." << endl;
        return 1;
    }
    
    // Відсоток втрати ємності акумулятора за один рік
    const double deg_rate = 0.02;

    // Обчислюємо фактичну ємність з урахуванням віку (Вт·год)
    double C_eff;
    C_eff = C * pow((1 - deg_rate), years); 

    //Обчислюємо запас енергії при поточному заряді (Вт·год)
    double E_stored;
    E_stored = C_eff * charge / 100;


    //Обчислюємо корисну енергію, що дійде до приладу (Вт·год)
    double E_useful;
    E_useful = E_stored * eff / 100;

    //Обчислюємо втрати на перетворенні напруги (Вт·год)
    double E_loss;
    E_loss = E_stored - E_useful;

    //Обчислюємо час роботи приладу (годин)
    double T;
    T = E_useful / P;

    // Виділяємо цілу кількість годин із загального часу
    int h;
    h = static_cast<int>(T);

    // Переводимо дробову залишок часу у хвилини
    int m;
    m = static_cast<int>((T - h) * 60);

    // Форматований вивід результатів у термінал
    cout << endl;

    cout << "Модель:                   " << model << endl; 
    
    cout << fixed << setprecision(1);
    cout << "Паспортна ємність:        " << C << " Вт·год" << endl;

    cout << "Вік станції:              " << years << " р." << endl;

    cout << fixed << setprecision(1);
    cout << "Фактична ємність:         " << C_eff << " Вт·год" << endl;
    
    cout << "Рівень заряду:            " << charge << " %" << endl;

    cout << fixed << setprecision(2);
    cout << "ККД інвертора:            " << eff << " %" << endl;

    cout << fixed << setprecision(1);
    cout << "Запас енергії:            " << E_stored << " Вт·год" << endl;

    cout << fixed << setprecision(1);
    cout << "Корисна енергія:          " << E_useful << " Вт·год" << endl;

    cout << fixed << setprecision(1);
    cout << "Втрати на перетворенні:   " << E_loss << " Вт·год" << endl;

    cout << fixed << setprecision(2);
    cout << "Час роботи:               " << T << " год = " << h << " год " << setfill('0') << setw(2) << m << " хв" << endl;
    
    return 0;
}