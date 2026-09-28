/* 
Епік 1. Практичне завдання: Автономність портативної зарядної станції
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream> //потоки вводу і виводу
#include <iomanip> //форматування тексту і чисел
#include <cmath> //математична бібліотека
#include <string> //текст

using namespace std;

int main() {
    //втрата ємності на рік
    const double DEGRADATION_PER_YEAR = 2.0;

    //дільник для переведення відсотків у частку
    const double PERCENT = 100.0;

    //кількість хвилин в одній годині
    const int MINUTES_IN_HOUR = 60;

    //максимальна довжина назви моделі
    const int MODEL_MAX_LENGTH = 31;

    //межі вікових значень станції
    const int MIN_YEARS = 0, MAX_YEARS = 20;

    //межі рівня заряду
    const int MIN_CHARGE = 0, MAX_CHARGE = 100;

    //обмеження ККД
    const double MAX_EFF = 100.0;

    //змінна для назви моделі
    string model_name;

    //паспортна ємність
    double capacity = 0.0;

    //вік станції
    int years = 0;

    //рівень заряду
    int charge = 0;

    //ККД інвертор
    double efficiency = 0.0;

    //потужність приладу
    double power = 0.0;

    cout << "Введіть модель Вашої станції: ";
    cin >> model_name;
    if (!cin || model_name.length() > MODEL_MAX_LENGTH) {
        cout << "Помилка: назва моделі мусить бути одним словом, не довшим 31 символу." << endl;
        return 1;    
    }

    cout << "Введіть паспортну ємність (Вт*год): ";
    cin >> capacity;
    if (!cin || capacity <= 0.0 ) {
        cout << "Помилка: значення ємності має бути більшим за нуль." << endl;
        return 1;        
    }

    cout << "Введіть вік Вашої станції: ";
    cin >> years;
    if (!cin || years < MIN_YEARS || years > MAX_YEARS) {
        cout << "Помилка: вік станції має бути від 0 до 20." << endl;
        return 1;    
    }

    cout << "Введіть рівень заряду Вашої станції: ";
    cin >> charge;
    if (!cin || charge < MIN_CHARGE || charge > MAX_CHARGE) {
        cout << "Помилка: рівень заряду має бути від 0 до 100" << endl;
        return 1;    
    }

    cout << "Введіть ККД інвертора Вашої станції: ";
    cin >> efficiency;
    if (!cin || efficiency <= 0.0 || efficiency > MAX_EFF) {
        cout << "Помилка: значення ККД інвертора має бути більшим за нуль і не перевищувати 100."  << endl;
        return 1;    
    }

    cout << "Введіть потужність приладу: ";
    cin >> power;
    if (!cin || power <= 0.0) {
        cout << "Помилка: значення потужності має бути більшим за 0." << endl;
        return 1;    
    }

    //обрахування фактичної ємності з урахуванням віку (Вт*год)
    double c_eff = capacity * pow(1 - DEGRADATION_PER_YEAR / PERCENT, years);
    
    //запас енергії при поточному заряді (Вт*год)
    double e_stored = c_eff * charge / PERCENT; 

    //корисна енергія, що дійде до приладу (Вт*год)
    double e_useful = e_stored * efficiency / PERCENT;

    //втрати на перетворенні напруги (Вт*год)
    double e_loss = e_stored - e_useful;

    //час роботи (год)
    double t = e_useful / power;

    //повні години 
    int h = (int)t;

    //хвилини, що залишились
    int m = (int)((t - h) * MINUTES_IN_HOUR);


    cout << fixed;

    cout << endl << "Модель:             " << setw(10) << model_name << endl;
    
    cout << "Паспортна ємність: " << setw(10) << setprecision(1) << capacity << " Вт*год" << endl;

    cout << "Вік станції:       " << setw(10) << years << " р." << endl;

    cout << "Фактична ємність:  " << setw(10) << setprecision(1) << c_eff << " Вт*год" << endl;

    cout << "Рівень заряду:     " << setw(10) << charge << " %" << endl ;

    cout << "ККД інвертора:     " << setw(10) << setprecision(2) << efficiency << " %" << endl;

    cout << "Запас енергії:     " << setw(10) << setprecision(1) << e_stored << " Вт*год" << endl;

    cout << "Корисна енергія:   " << setw(10) << setprecision(1) << e_useful << " Вт*год" << endl;

    cout << "Втрати:            " << setw(10) << setprecision(1) << e_loss << " Вт*год" << endl;

    cout << "Час роботи:        " << setw(10) << setprecision(2) << t << " год = " << h << " год " << setw(2) << setfill('0') << m << " хв" << endl;

    return 0;

}


