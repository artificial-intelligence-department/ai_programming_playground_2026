/*
Задача: Розрахувати автономність портативної зарядної станції
Автор: Дрогомирецька Ольга Дмитрівна
Група: ШІ-13
*/
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;
int main () {
const double YEARLY_CAPACITY_LOSS = 0.02; //частка втрати ємності за один рік
const int MAX_MODEL_LENGTH = 31; //максимальна довжина назви моделі
const int MAX_AGE = 20; // максимальний вік станції, років
const int MAX_PERCENT = 100; // максимальне значення відсотка
const int MINUTES_PER_HOUR = 60; // кількість хвилин в одній годині

string model; 
double capacity = 0.0;
int age = 0;
int charge = 0;
double efficiency = 0.0;
double power = 0.0;

cout << "Модель станції ";
cin >> model;
//Перевіряємо, що довжина назви ноделі не перевищує 31 символ.
if (model.length() > MAX_MODEL_LENGTH) {
    cout << "Помилка: назва моделі не повинна перевищувати 31 символ" << endl;
    return 1;
}

cout << "Паспортна ємність (Вт•год):";
cin >> capacity;
//Перевіряємо, що введено число і паспортна ємність є додатною.
if (!cin || capacity <= 0) {
cout << "Помилка: ємність повинна бути більше 0" << endl;
    return 1; }

cout << "Вік станції (років): ";
cin >> age;
//Перевіряємо, що введено число знаходиться в межах від 0 до 20 років.
if (!cin || age < 0 || age > MAX_AGE) {
cout << "Помилка: вік станції повинен бути в межах від 0 до 20" << endl;
    return 1; 
}

cout << "Рівень заряду (%): ";
cin >> charge;
//Перевіряємо, що введено число і рівень заряду знаходиться в межах від 0 до 100%
if (!cin || charge < 0 || charge > MAX_PERCENT) {
cout << "Помилка: рівень заряду повинен бути в межах від 0 до 100" << endl;
    return 1; 
}

cout << "KKД інвертора (%): ";
cin >> efficiency;
//Перевіряємо, що введене число і ККД знаходиться в межах від 0% до 100%.
if (!cin || efficiency <= 0 || efficiency > MAX_PERCENT) {
    cout << "Помилка: KKД інвертора повинен бути більше 0 і не більше 100" << endl;
    return 1;
}

cout << "Потужність приладу (Вт): ";
cin >> power;
//Перевіряємо, що введене число і потижність приладу є додатною.
if (!cin || power <= 0)
{
    cout << "Помилка: потужність пристрою повинна бути більше 0" << endl;
    return 1;
}
// Обчислюємо фактичну ємність станції з урахуванням віку, Вт•год
double effective_capacity = capacity * pow(1 - YEARLY_CAPACITY_LOSS, age);

// Розраховуємо запас енергії при поточному заряді, Вт•год
double stored_energy = effective_capacity * charge / MAX_PERCENT;

//Розраховуємо корисну енергію, що дійде до приладу, Вт•год
double useful_energy = stored_energy * efficiency / MAX_PERCENT;

//Обчислюємо втрати на перетворенні напруги, Вт•год
double lost_energy = stored_energy - useful_energy;

//Визначаємо час роботи, год
double runtime = useful_energy / power;

// Виділення цілої кількості годин роботи
int hours = static_cast<int>(runtime);

// Перетворюємо дробову частину часу роботи у хвилини
int minutes = static_cast<int>((runtime - hours) * MINUTES_PER_HOUR);
//Виведення результатів
cout <<"Модель:  " << model << endl;
cout << fixed << setprecision(1);
cout <<"Паспортна ємність:  " << capacity << " Вт•год " << endl;
cout <<"Вік станції:  " << age << " р. " << endl;
cout <<"Фактична ємність:  " << effective_capacity << " Вт•год " << endl;
cout << "Рівень заряду:  " << charge << "%" << endl;
cout << fixed << setprecision(2);
cout << "ККД інвертора:  " << efficiency << "%" << endl;
cout << fixed << setprecision(1);
cout << "Запас енергії:  " << stored_energy << " Вт•год " << endl;
cout << "Корисна енергія:  " << useful_energy << " Вт•год " << endl;
cout << "Втрати на перетворенні:  " << lost_energy << " Вт•год " << endl;
cout << fixed << setprecision(2);
cout << "Час роботи:  " << runtime << " год = " << hours << " год " << setfill('0') << setw(2) << minutes << "хв" << endl;
return 0;
} 