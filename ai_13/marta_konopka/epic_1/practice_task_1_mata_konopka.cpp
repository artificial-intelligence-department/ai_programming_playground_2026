/*
Автономність зарядної станції
Конопка Марта СШІ-13
*/


// підключаємо потрібні бібліотеки та стандартний простір імен
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    // оголошуємо змінні для вхідних даних
    string station_model;
    double c ;
    double years;
    double charge;
    double eff;
    double P;

    cout << "Модель станції(введіть одне слово без пробілів): ";
    cin >> station_model; 


    if (station_model.length() > 31 ) {
        cout << " Помилка: Модель станції не повинна перевищувати 31 символ." ;
        return 1;
    }
   

    cout << "Паспортна ємність (Вт·год) : ";
     
    if (!(cin >> c)) {
        cout << "Помилка: Паспортна ємність повинна бути числом." ;
        return 1;
    }
    if (c <=0) {
        cout << "Помилка: Паспортна ємність повинна бути більша за нуль." ;
        return 1;
    }

    cout << "Вік станції (років) :";
    
    if (!(cin >> years)){
        cout << "Помилка: Вік станції повинен бути числом." ;
        return 1;
    }
    if (years!= static_cast<int>(years)) {
        cout << "Помилка: Вік станції повинен бути цілим числом.";
    return 1;

    }
     if (years < 0 || years > 20 ) {
        cout << "Помилка: Вік станції повинен бути в межах від 0 до 20 років." ;
        return 1;

    }

    cout << "Рівень заряду (%) : ";
     
     if (!(cin >> charge)){
        cout << "Помилка: Рівень заряду повинен бути числом." ;
        return 1;
    }
    if (charge != static_cast<int>(charge)) {
        cout << "Помилка: Рівень заряду повинен бути цілим числом.";
    return 1;

    }

    if(charge < 0 || charge > 100) {
        cout << "Помилка: Рівень заряду повинен бути в межах від 0 до 100%." ;
        return 1;

    }

    cout << "ККД інвертора (%) : ";
     
    if (!(cin >> eff)){
        cout << "Помилка: ККД інвертора повинен бути числом." ;
        return 1;
    }
    if(eff<=0 || eff>100) {
        cout << "Помилка: ККД інвертора повинен бути в межах більше 0 і не більше 100%." ;
        return 1;

    }

    cout << "Потужність приладу (Вт) : ";

    if (!(cin >> P)){
        cout << "Помилка: Потужність приладу повинна бути числом." ;
        return 1;
    }
    if (P <= 0) {
        cout << "Помилка: Потужність приладу повинна бути більша за нуль." ;
        return 1;
    }

    const double degradation_percent = 2.0; // відсоток втрати ємності за рік.

    //обчислюємо фактичну ємність з урахуванням віку, Вт·год
    double C_eff = c * pow(1.0 - degradation_percent / 100.0, years);

    //обчислюємо запас енергії при поточному заряді, Вт·год
    double E_stored = C_eff * charge / 100.0;

    //обчислюємо корисну енергію, що дійде до приладу, Вт·год
    double E_useful = E_stored * eff / 100.0;

    //обчислюємо втрати на перетворенні напруги, Вт·год
    double E_loss = E_stored - E_useful ;

    //обчислюємо час роботи, годин
    double T = E_useful / P;

    //обчислюємо повні години
    int h = static_cast<int>(T);

    //обчислюємо хвилини, що залишились
    int n = static_cast<int>((T-h) * 60);

    cout << left << setw (30) << "Модель: " << station_model << "\n";
    cout << left << setw (40) << "Паспортна ємність: " << fixed << setprecision(1) << c << " Вт·год" << "\n";
    cout << left << setw (40) << "Вік станції: " << fixed << setprecision(0) << years << " р." << "\n";
    cout << left << setw (39) << "Фактична ємність: " << fixed << setprecision(1) << C_eff << " Вт·год" << "\n";
    cout << left << setw (40) << "Рівень заряду: " << fixed << setprecision(0) << charge << " %" << "\n";
    cout << left << setw (40) << "ККД інвертора: " << fixed << setprecision(2) << eff << " %" << "\n";
    cout << left << setw (40) << "Запас енергії: " << fixed << setprecision(1) << E_stored << " Вт·год" << "\n";
    cout << left << setw (40) << "Корисна енергія: " << fixed << setprecision(1) << E_useful << " Вт·год" << "\n";
    cout << left << setw (46) << "Втрати на перетворенні: " << fixed << setprecision(1) << E_loss << " Вт·год" << "\n";
    cout << left << setw (35) << "Час роботи: " << fixed << setprecision(2) << T << " год" << " = " << h << " год" << ' ' << setfill('0') << setw(2) << n <<
" хв" << "\n"; 

    return 0;
}