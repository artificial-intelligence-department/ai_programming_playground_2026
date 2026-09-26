#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>

int main() {
    using namespace std;
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string model;
    double C;
    int years;
    int charge;
    double eff;
    double P;

    cout << "Модель станції: ";
    getline(cin, model);
    if (model.length() > 31) {
    cout << "Помилка! Введіть значення до 31 символа без пробілів" << endl;
    return 1;
}

    cout << "Паспортна ємність (Вт*год): ";
    cin >> C;
    if (C <= 0) {
        cout << "Помилка! Значення має бути більше 0" << endl;
        return 1;
    }

    cout << "Вік станції (років): ";
    cin >> years;
    if (years < 0 || years > 20) {
        cout << "Помилка! Введіть значення від 0 до 20" << endl;
        return 1;
    }

    cout << "Рівень заряду (%): ";
    cin >> charge;
    if (charge < 0 || charge > 100) {
        cout << "Помилка! Введіть значення від 0 до 100" << endl;
        return 1;
    }

    cout << "ККД інвертора (%): ";
    cin >> eff;
    if (eff <= 0 || eff > 100) {
        cout << "Помилка! Введіть значення від 1 до 100" << endl;
        return 1;
    }

    cout << "Потужність приладу (Вт): ";
    cin >> P;
    if (P <= 0) {
        cout << "Помилка! Введіть значення більше 0" << endl;
        return 1;
    }

    double C_eff = C * pow(0.98, years);
    double E_stored = C_eff * charge / 100.0;
    double E_useful = E_stored * eff / 100.0;
    double E_loss = E_stored - E_useful;
    double T = E_useful / P;

    int h = T;
    int m = round((T - h) * 60);

    if (m == 60) {
        h += 1;
        m = 0;
    }

    cout << "Модель: " << model << endl;
    cout << fixed << setprecision(1);
    cout << "Ефективна ємність: " << C_eff << " Вт*год" << endl;
    cout << "Запас енергії: " << E_stored << " Вт*год" << endl;
    cout << "Корисна енергія: " << E_useful << " Вт*год" << endl;
    cout << "Втрати: " << E_loss << " Вт*год" << endl;
    cout << setprecision(2);
    cout << "Розрахунковий час: " << T << " год" << endl;
    cout << "Час роботи: " << h << " год " << m << " хв" << endl;

    return 0;
}
