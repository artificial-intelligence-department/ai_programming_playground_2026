/*Автономність портативної зарядної станції, Стехнович Андрій, студент ШІ-11*/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;
int main() {
    string model;
    cout << "Модель станції: ";
    getline(cin, model);
    if (model.find(' ') != string::npos or model.length() > 31) {
        cout << "Помилка: назва моделі повинно бути одне слово не довше 31 символів. "<< endl;
        return 1;
    } // перевіряємо чи модель з одного слова і чи довжина менша за 31 символ
    double C;
    cout << "Паспортна ємність (Вт год): ";
    cin >> C;
    if (cin.fail() or C<=0) {
        cout << "Помилка: Паспортна ємність більше 0. "<< endl;
        return 1;
    } // перевіряємо чи введено число і обмеження
    int years;
    cout << "Вік станції (років): ";
    cin >> years;
    if (cin.fail() or years<0 or years>20) {
        cout << "Помилка: вік станції - ціле число від 0 до 20"<< endl;
        return 1;
    } // перевіряємо чи введено число і обмеження
    int charge;
    cout << "Рівень заряду (%): ";
    cin >> charge;
    if (cin.fail() or charge<0 or charge>100) {
        cout << "Помилка: рівень заряду - ціле чило від 0 до 100"<< endl;
        return 1;
    } // перевіряємо чи введено число і обмеження
    float eff;
    cout << "ККД інвертора (%): ";
    cin >> eff;
    if (cin.fail() or eff<=0 or eff>100)
    {
        cout << "Помилка: ККД інветора - число більше 0, але не більше 100"<< endl;
        return 1;
    } // перевіряємо чи введено число і обмеження
    float P;
    cout << "Потужність приладу (Вт): ";
    cin >>P;
    if (cin.fail() or P<=0)
    {
        cout << "Помилка: Потужність приладу - число більше 0"<< endl;
        return 1;       
    } // перевіряємо чи введено число і обмеження
    float C_eff; // створюємо змінну для фактичної ємності, рахуємо за формулою складних відсотків, де 2 - відсоток втрати ємності за рік
    C_eff = pow(0.98, years)*C;
    float E_stored; // створюємо змінну для запасу енергії, рахуємо за формулою, де charge - поточний заряд
    E_stored=C_eff * charge/100;
    float E_useful; // створюємо змінну для корисної енергії з урахуванням ККД
    E_useful = E_stored * eff/100;
    float E_loss=E_stored-E_useful; // створення змінної для втрат, їх рахунок
    float T=E_useful/P; // створення змінної для часу роботи, переведення в години та хвилини
    int h=(int)T;
    int m=(int)((T-h)*60);
    // виведення даних за зразком
    cout << "Модель станції:         " << model << endl;
    cout << fixed << setprecision(1);
    cout << "Паспортна ємність:      " << C << " Вт・год"<< endl;
    cout << "Вік станції:            " << years << " p."<< endl;
    cout << fixed << setprecision(1);
    cout << "Фактична ємність:       " << C_eff << " Вт・год"<< endl;
    cout << "Рівень заряду:          " << charge << " %"<< endl;
    cout << fixed << setprecision(2);
    cout << "ККД інвентора:          " << eff << " %"<< endl;
    cout << fixed << setprecision(1);
    cout << "Запас енергії:          " << E_stored << " Вт・год"<< endl;
    cout << fixed << setprecision(1);
    cout << "Корисна енергія:        " << E_useful << " Вт・год"<< endl;
    cout << fixed << setprecision(1);
    cout << "Втрати на перетворення: " << E_loss << " Вт・год"<< endl;
    cout << fixed << setprecision(2);
    cout << "Час роботи:             " << T <<" год = "<<h<<" год "<<m<<" хв"<< endl;
    

}