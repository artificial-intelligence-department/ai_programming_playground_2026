/*
Епік 1. Практичне завдання: Автономність портативної зарядної станції
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream> //Додаємо основні бібліотеки
#include<string>
#include<cmath>
#include<iomanip>

using namespace std;


int main() {

    string model; //Створюємо змінні
    int years = 0;
    int charge = 0;
    double C = 0.0;
    double eff = 0.0;
    double P = 0.0;
  
    const double a = 2.0; //Відсоток втрати ємності за рік


    cout << "Введіть модель станції: "; cin >> model; //Вводимо змінні та перевіряємо їх
    if (model.length() > 31) {
        cout << "Помилка! Кількість символів не може бути більша за 31.\n";
        return 1;
    }
    cout << "Введіть паспортну ємність (Вт·год): "; cin >> C;
    if (cin.fail() || C <= 0) {
        cout << "Помилка! Введіть значення більше за 0.\n";
        return 1;
    }
    cout << "Введіть вік станції (років): "; cin >> years;
    if (cin.fail() || years < 0 || years > 20) {
        cout << "Помилка! Введіть значення від 0 до 20.\n";
        return 1;
    }
    cout << "Введіть рівень зарядки (%): "; cin >> charge;
    if (cin.fail() || charge < 0 || charge > 100) {
        cout << "Помилка! Введіть значення від 0 до 100.\n";
        return 1;
    }
    cout << "Введіть ККД інвертора (%): "; cin >> eff;
    if (cin.fail() || eff <= 0 || eff > 100) {
        cout << "Помилка! Введіть значення від 0 до 100.\n";
        return 1;
    }
    cout << "Введіть потужність приладу (Вт): "; cin >> P;
    if (cin.fail() || P <= 0) {
        cout << "Помилка! Введіть значення більше за 0.\n";
        return 1;
    }
    
    float C_eff = C * pow((1-a/100), years); //Обчислюємо фактичну ємність
    float E_stored = C_eff * charge / 100; //Обчислюємо запас енергії
    float E_useful = E_stored * eff / 100; //Обчислюємо корисну енергію
    float E_loss = E_stored - E_useful; //Обчислюємо втрату енергії
    float T = E_useful / P; //Обчислюємо час
    int h = int(T); //Обчислюємо кількість цілих годин
    int m = int((T-h) * 60); //Обчислюємо кількість цілих хвилин

    cout << endl; //Виводимо всю інформацію про зарядну станцію користувачу
    cout << "Модель станції: " << setw(24) << model << endl;
    cout << "Паспортна ємність: " << setw(15) << fixed << setprecision(1) << C << " Вт·год" << endl; 
    cout << "Вік станції: " << setw(21) << years << " р." << endl;
    cout << "Фактична ємність: " << setw(16) << fixed << setprecision(1) << C_eff << " Вт·год" << endl;
    cout << "Рівень заряду: " << setw(19) << charge << " %" << endl;
    cout << "ККД інвертора: " << setw(19) << fixed << setprecision(2) << eff << " %" << endl;
    cout << "Запас енергії: " << setw(19) << fixed << setprecision(1) << E_stored << " Вт·год" << endl;
    cout << "Корисна енергія: " << setw(17) << fixed << setprecision(1) << E_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні: " << setw(10) << fixed << setprecision(1) << E_loss << " Вт·год" << endl;
    cout << "Час роботи: " << setw(22) << fixed << setprecision(2) << T << " год = " << h << " год " << setfill('0') << setw(2) << m << " хв" << endl;

    return 0;
}
