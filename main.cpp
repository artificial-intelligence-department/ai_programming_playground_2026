#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    string model;
    double capacity;
    int years;
    int charge;
    double eff;
    double power;

    const double degradation = 2.0;

    cout << "Модель станції:";
    if (!(cin >> model) || model.length() > 31) { 
        cout << "Помилка: неправильно вказана модель станції." << endl;
        return 1;
    }
    
    cout << "Паспортна ємність (Вт·год):";
    if (!(cin >> capacity) || capacity <= 0) { 
        cout << "Помилка: паспортна ємність має бути числом, більшим за нуль." << endl;
        return 1;
    }

    cout << "Вік станції (років):";
    if (!(cin >> years) || years < 0 || years > 20) { 
        cout << "Помилка: вік станції має бути числом від 0 до 20." << endl;
        return 1;
    }

    cout << "Рівень заряду (%):";
    if (!(cin >> charge) || charge < 0 || charge > 100) { 
        cout << "Помилка: рівень заряду має бути числом від 0 до 100." << endl;
        return 1;
    }
    
    cout << "ККД інвертора (%):";
    // Виправлено: ККД може дорівнювати 100% за ТЗ
    if (!(cin >> eff) || eff <= 0 || eff > 100) { 
        cout << "Помилка: ККД інвертора має бути більше 0 та не більше 100." << endl;
        return 1;
    }

    cout << "Потужність приладу (Вт):";
    if (!(cin >> power) || power <= 0) { 
        cout << "Помилка: потужність приладу має бути більше 0." << endl;
        return 1;
    }

    // Обчислення
    double c_eff = capacity * pow(1.0 - degradation / 100.0, years);
    double e_stored = c_eff * (charge / 100.0);
    double e_useful = e_stored * (eff / 100.0);
    double e_loss = e_stored - e_useful;
    double time = e_useful / power;

    int hours = static_cast<int>(time);
    int minutes = static_cast<int>((time - hours) * 60.0);

    // Згрупований вивід в один cout для зручності побудови блок-схеми
    cout << "\n"
            << "Модель:                 " << model << "\n"
            << "Паспортна ємність:      " << right << setw(8) << fixed << setprecision(1) << capacity << " Вт·год\n"
            << "Вік станції:            " << right << setw(8) << years << " р.\n"
            << "Фактична ємність:       " << right << setw(8) << fixed << setprecision(1) << c_eff << " Вт·год\n"
            << "Рівень заряду:          " << right << setw(8) << charge << " %\n"
            << "ККД інвертора:          " << right << setw(8) << fixed << setprecision(2) << eff << "% \n"
            << "Запас енергії:          " << right << setw(8) << fixed << setprecision(1) << e_stored << " Вт·год\n"
            << "Корисна енергія:        " << right << setw(8) << fixed << setprecision(1) << e_useful << " Вт·год\n"
            << "Втрати на перетворенні: " << right << setw(8) << fixed << setprecision(1) << e_loss << " Вт·год\n"
            << "Час роботи:             " << right << setw(8) << fixed << setprecision(2) << time << " год = " 
            << hours << " год " << setfill('0') << setw(2) << minutes << " хв" << setfill(' ') << endl;
    return 0;
}