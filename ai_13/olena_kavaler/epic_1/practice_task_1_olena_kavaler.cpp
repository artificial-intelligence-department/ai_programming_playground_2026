
/*
Назва задачі: Автономність портативної зарядної станції
Автор: Кавалер Олена
Група: ШІ-13
*/

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;
int main() 
{
string model;
double C;
int years;
int charge;
double C_eff;
double eff;
double E_stored;
double E_useful;
double E_loss;
double T;
int m;
double P;
int h;

// Ввід даних і перевірка
cout << "Введіть модель зарядної станції: ";
cin >> model;

if (model.length() > 31)
{
    cout << "Помилка: назва моделі не повинна перевищувати 31 символ." << endl;
    return 1;
}

cout << "Введіть ємність батареї у Вт·год: ";
cin >> C;

if (C <= 0)
{
    cout << "Помилка: ємність батареї повинна бути додатнім числом." << endl;
    return 1;
}

cout << "Введіть кількість років використання: ";
cin >> years;

if (years < 0 || years > 20)
{
    cout << "Помилка: кількість років використання повинна бути в межах від 0 до 20." << endl;
    return 1;
}

cout << "Введіть рівень заряду батареї у відсотках: ";
cin >> charge;

if (charge < 0 || charge > 100)
{
    cout << "Помилка: рівень заряду батареї повинен бути в межах від 0 до 100." << endl;
    return 1;
}

cout << "Введіть ККД інвертора у відсотках: ";
cin >> eff;

if (eff <= 0 || eff > 100)
{
    cout << "Помилка: ККД інвертора повинен бути в межах від 0 до 100." << endl;
    return 1;
}

cout << "Введіть потужність навантаження у Вт: ";
cin >> P;

if (P <= 0)
{
    cout << "Помилка: потужність навантаження повинна бути додатнім числом." << endl;
    return 1;
}

// Формула деградації батареї (2% на рік)
C_eff = C * pow(1.0 - 0.02, years);

// Обчислення корисної енергії та втрат
E_stored = C_eff * (charge / 100.0);
E_useful = E_stored * (eff / 100.0);
E_loss = E_stored - E_useful;

// Переведення часу в години і хвилини
T = E_useful / P;
h = static_cast<int>(T);
m = static_cast<int>((T - h) * 60);

// Вивід результатів обчислень
cout << fixed << setprecision(1);

cout << "\nМодель: " << model << endl;
cout << "Паспортна ємність: " << C << " Вт * год" << endl;
cout << "Вік станції: " << years << " р." << endl;
cout << "Рівень заряду батареї: " << charge << " %" << endl;
cout << "Потужність навантаження: " << P << " Вт" << endl;
cout << "Фактична ємність: " << C_eff << " Вт * год" << endl;

cout << setprecision(2);
cout << "ККД інвертора: " << eff << "%" << endl;

cout << setprecision(1);
cout << "Запас енергії: " << E_stored << " Вт * год" << endl;
cout << "Корисна енергія: " << E_useful << " Вт * год" << endl;
cout << "Втрати на перетворенні: " << E_loss << " Вт * год" << endl;

cout << setprecision(2);
cout << "Час роботи: " << T << " год = " << h << " год ";

// Додаю 0, якщо хвилин менше 10
if (m < 10)
{
    cout << "0";
}
cout << m << " хв" << endl;

return 0;
}
