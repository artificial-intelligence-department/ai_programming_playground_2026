#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    // коефіцієнт деградації акумулятора(% втрати ємності за рік)
    const int degr_coef = 2;
    // ініціалізація змінних
    string model;
    int years, charge, hours, minutes;
    double capacity, real_capacity, eff, power, E_stored, E_useful, E_loss, time; 

    // ВВІД ТА ВАЛІДАЦІЯ
    //------------------
    cout << "Модель станції: ";
    cin >> model;
    
    /* примітка: метод size повертає розмір в байтах,
    тому для коректної валідації вхідний текст має прийти у форматі ASCII(де 1 символ = 1 байт) */
    if (model.size() > 31) {
        cout << "Помилка вводу: Довжина рядка перевищує 31 символ" << endl;
        return 1;
    }

    cout << "Паспортна ємність (Вт·год): ";
    cin >> capacity; 

    if (capacity <= 0) {
        cout << "Помилка вводу: Значення ємності не є додатнім числом" << endl;
        return 1;
    }

    cout << "Вік станції (років): ";
    cin >> years; 

    if (years < 0 || years > 20) {
        cout << "Помилка вводу: Вік станції не є числом в межах від 0 до 20" << endl;
        return 1; 
    }
    
    cout << "Рівень заряду (%): ";
    cin >> charge; 

    if (charge < 0 || charge > 100) {
        cout << "Помилка вводу: Рівень заряду не є числом в межах від 0 до 100" << endl;
        return 1; 
    }

    cout << "ККД інвертора (%): ";
    cin >> eff;

    if (eff <= 0 || eff > 100) {
        cout << "Помилка вводу: КДД не є числом в межах від 0 до 100" << endl;
        return 1; 
    }
    
    cout << "Потужність приладу (Вт): ";
    cin >> power;

    if (power <= 0) {
        cout << "Помилка вводу: потужність приладу не є додатнім числом" << endl;
        return 1; 
    }

    // ОБЧИСЛЕННЯ
    //------------
    //charge, eff та degr_coef - відсоткові значення, їх переводимо у частку діленням на 100.

    // обчислення фактичної ємності(Вт·год): 
    // дільник 100.0 дробовий для уникнення цілочисельного ділення
    real_capacity = capacity*pow(1-degr_coef/100.0, years);

    // обчислення поточного запасу енергії(Вт·год):
    E_stored = real_capacity*charge/100.0;

    // обчислення корисної енергії(Вт·год):
    E_useful = E_stored*eff/100;

    // обчислення витрат енергії(Вт·год):
    E_loss = E_stored - E_useful;

    // обчислення часу роботи(год):
    time = E_useful/power;

    // обчислення повних годин та хвилин, що залишилися:
    hours = (int)(floor(time));
    // рахуємо залишок в хвилинах
    minutes = (int)(floor(((time - hours)*60)));

    // ВИВІД ПРОГРАМИ
    //---------------
    // використовуємо об'єкт setw для задання фіксованої ширини текстового блоку, right - для вирівнювання.
    /* примітка: об'єкт setw виділяє місце в пам'яті, кириличні символи кодуються в UTF-8, тому займають по 2 байти. 
    Через це вихідний текст в терміналі може бути згрупований некоректно.
    Одним із способів вирішення цієї проблеми є додавання відповідної кількості відступів. 
    Для цього рахуємо кількість кириличних символів і додаємо її в аргумент setw*/
    cout << left << setw(50) << "Модель:"  << right << setw(10) << model << endl;
    
    // встановлення точності(кількості знаків після коми)
    cout << fixed << setprecision(1);

    cout << left << setw(45+16) << "Паспортна ємність:" << right << setw(10) << capacity <<  " Вт·год" << endl;

    cout << left << setw(45+10) << "Вік станції:" << right << setw(10) << years << " р." << endl;

    cout << left << setw(45+15) << "Фактична ємність:" << right << setw(10) << real_capacity << " Вт·год" << endl;

    cout << left << setw(45+12) << "Рівень заряду:" << right << setw(10) << charge << " %" << endl;

    cout << setprecision(2);
    cout << left << setw(45+12) << "ККД інвертора:" << right << setw(10) << eff << " %" << endl;

    cout << setprecision(1);
    cout << left << setw(45+12) << "Запас енергії:" << right << setw(10) << E_stored << " Вт·год" << endl;

    cout << left << setw(45+14) << "Корисна енергія:" << right << setw(10) << E_useful << " Вт·год" << endl;

    cout << left << setw(45+20) << "Втрати на перетворенні:" << right << setw(10) << E_loss << " Вт·год" << endl;

    cout << setprecision(2);
    // setfill('0') задає 0 як символ заповнення для setw(2), тому хвилини гарантовано виводяться в дві цифри
    cout << left << setw(45+9) << "Час роботи:" << right << setw(10) << time << " год  = " << hours << " год " << setfill('0') << setw(2) << minutes << "хв" << endl;
}
