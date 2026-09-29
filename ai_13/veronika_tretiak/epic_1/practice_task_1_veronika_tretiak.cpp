/*Задача: Автономність портативної зарядної станції*/
/*Автор: Вероніка Третяк*/
/*Група: ШІ-13*/
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;
int main() {
string model;
double C, eff, P;
int years, charge;
const  double prc = 0.02; //Відсоток втрати ємності за рік

cout << "Введіть модель вашої зарядної станції: ";
cin >> model;
if (model.length() > 31) {
    cout << "Помилка: Не перевищуйте ліміт символів." << endl;
    return 1;
}
cout << "Введіть паспортну ємість у Ват-годинах:";
cin >> C;
if (C <= 0) {
    cout <<"Помилка: Ємність має бути додатнім числом." << endl;
    return 1;
}
cout <<"Введіть вік станції у роках:";
cin >> years;
if (years < 0 || years > 20) {
    cout <<"Помилка: Вік станції має бути від 0 до 20 років." << endl;
    return 1;
}
cout <<"Введіть рівень заряду вашої зарядної станції у відсотках:";
cin >> charge;
if (charge < 0 || charge > 100){
    cout <<"Помилка: Рівень заряду має бути від 0 до 100 відсотків." << endl;
    return 1;
}
cout <<"Введіть ККД вашої зарядної станції у відсотках:";
cin >> eff;
if (eff < 0 || eff > 100){
    cout <<"Помилка: ККД має бути від 0 до 100 відсотків." << endl;
    return 1;
}
cout <<"Введіть потужність вашої зарядної станції у Ватах:";
cin >> P;
if(P <= 0){
    cout <<"Помилка: Потужіність має бути додатнім числом." << endl;
    return 1;
}
double C_eff = C * pow(1 - prc , years); //Обчислюємо фактичну ємність з урахуванням віку у Ват*год
double E_stored = C_eff * charge / 100; //Обчислюємо запас енергії при поточному заряді у Ват*год
double E_useful = E_stored * eff / 100;//Обчислюємо корисну енергія у Ват*год
double E_loss = E_stored - E_useful;// Обчислюємо втрати на перетворенні напруги у Ват*год
double T = E_useful / P;//Обчислюємо час роботи у годинах та хвилинах
int h = int(T);
int m = int((T - h) * 60);
cout << "Модель станції: " << model << endl;
cout << "Паспортна ємність: " << fixed << setprecision(1) << C << " ""Ват*годин" << endl;
cout << "Вік станції: " << years << "p." << endl;
cout << "Фактична ємність з урахуванням віку:" << fixed << setprecision(1) << C_eff << " ""Ват*годин" << endl;
cout << "Рівень заряду станції:" << charge << "%" << endl;
cout << "ККД інвентора: " << fixed << setprecision(2) << eff << "%" << endl;
cout << "Запас енергії: " << fixed << setprecision(1) << E_stored <<" ""Ват*годин" << endl; 
cout << "Корисна енергія: " << fixed << setprecision(1) << E_useful <<" ""Ват*годин" << endl;
cout << "Втрати енергії: " << fixed << setprecision(1) << E_loss << " ""Ват*годин" << endl;
cout << "Час роботи: " << fixed << setprecision(2) << T << " ""год = " << h << "год"" " << m << "хв" << endl;
return 0;
}
