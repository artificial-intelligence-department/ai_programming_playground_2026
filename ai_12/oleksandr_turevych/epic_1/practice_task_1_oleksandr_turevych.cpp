/* 
Епік 1. Практичне завдання: Автономність портативної зарядної станції
Автор: Туревич Олександр
Група: ШІ-12
*/


#include <iostream> // потоки вводу і виводу
#include <cmath> // математичні функції
#include <iomanip> // для заукруглення дробових чисел
#include <string> // для роботи з рядками

using namespace std;


int main() {
    const double degrad_per_year = 2; // зниження ємності батареї на 2% щорок

    // змінна для назви моделі
    string model_name;
    // паспортна ємність
    double capacity;
    // вік станції
    int years;
    // рівень заряду
    int charge;
    // ККД інвертор
    double efficiency;
    // потужність приладу
    double power;

    cout << "Введіть модель вашої станції: ";
    cin >> model_name;
    if (model_name.length() > 31) {
        cout << "Помилка: назва моделі мусить бути одним словом, не довшим 31 символу." << endl;
        return 1;    
    }

    cout << "Введіть паспортну ємність (Вт*год): ";
    cin >> capacity;
    if (capacity <= 0) {
        cout << "Помилка: значення ємності має бути більшим за нуль." << endl;
        return 1;        
    }

    cout << "Введіть вік вашої станції: ";
    cin >> years;
    if (years < 0 || years > 20) {
        cout << "Помилка: вік станції має бути від 0 до 20." << endl;
        return 1;    
    }

    cout << "Введіть рівень заряду станції: ";
    cin >> charge;
    if (charge < 0 || charge > 100) {
        cout << "Помилка: рівень заряду має бути від 0 до 100" << endl;
        return 1;    
    }

    cout << "Введіть ККД інвертора: ";
    cin >> efficiency;
    if (efficiency <= 0 || efficiency > 100) {
        cout << "Помилка: значення ККД інвертора має бути більшим за ноль та не перевищувати 100."  << endl;
        return 1;    
    }

    cout << "Введіть потужність приладу: ";
    cin >> power;
    if (power <= 0) {
        cout << "Помилка: значення потужності має бути більшим за 0." << endl;
        return 1;    
    }

    double C_eff;
    double E_stored;
    double E_useful;
    double E_loss;
    double T; 

    // Фактична ємність з урахуванням віку, Вт·год
    C_eff = capacity * pow(1 - degrad_per_year / 100.0, years);
    // Запас енергії при поточному заряді, Вт·год
    E_stored = C_eff * charge / 100.0;
    // Корисна енергія, що дійде до приладу, Вт·год
    E_useful = E_stored * efficiency / 100.0;
    // Втрати на перетворенні напруги, Вт·год
    E_loss = E_stored - E_useful;
    // Час роботи приладу, год
    T = E_useful / power;
    // Повні години
    int h;
    h = int(T);
    // Хвилини, що залишились
    int m; 
    m = int((T - h) * 60);

    cout << endl;

    cout << fixed;

    cout << "Модель станції: " << model_name << endl;
    cout << "Паспортна ємність: " << setprecision(1) << capacity << " Вт·год" << endl;
    cout << "Вік станції: " << years << " років" << endl;
    cout << "Фактична ємність: " << setprecision(1) << C_eff << " Вт·год" << endl;
    cout << "Рівень заряду: " << charge << "%" << endl;
    cout << "ККД інвертора: " << setprecision(2) << efficiency << "%" << endl;
    cout << "запас енергії: " << setprecision(1) << E_stored << " Вт·год" << endl;
    cout << "Корисна енергія: " << setprecision(1) << E_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні: " << setprecision(1) << E_loss << " Вт·год" << endl;
    cout << "Час роботи: " << setprecision(2) << T << " год = " << h << " год ";
    if (m < 10) {
        cout << "0" << m << " хв";
    }
    else {
        cout << m << " хв";
    }

    cout << endl;

    return 0;
}