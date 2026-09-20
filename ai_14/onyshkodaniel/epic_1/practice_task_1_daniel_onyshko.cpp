/*Epic_1 (Автономність портативної зарядної станції),
Онишко Даніель, ШІ-14*/
#include <iostream>

using namespace std;

int main() {
    string model;
    double C, years, charge, eff, P;

    cout << "Vvedit model stantsii: ";
    cin >> model;

    cout << "Vvedit pasportnu emnist (Vt*god): ";
    cin >> C;

    cout << "Vvedit vik stantsii (rokiv): ";
    cin >> years;

    cout << "Vvedit riven zaryadu (%): ";
    cin >> charge;

    cout << "Vvedit KKD (%): ";
    cin >> eff;

    cout << "Vvedit potuzhnist priladu (Vt): ";
    cin >> P;

    // Це перевірка чи будуть помилки
    if (C <= 0 || years < 0 || charge < 0 || eff <= 0 || P <= 0) {
        cout << "Error: Nekorektni dani!" << endl;
        return 0;
    }

    // Розрахунки
    double C_eff = C * (1.0 - 0.02 * years);      // Ємність з урахуванням віку
    double E_stored = C_eff * (charge / 100.0);    // Запас енергії
    double E_useful = E_stored * (eff / 100.0);    // Корисна енергія
    double E_loss = E_stored - E_useful;          // Втрати
    double T = E_useful / P;                      // Час у годинах

    int hours = T;                                // Цілі години
    int minutes = (T - hours) * 60;               // Хвилини

    // Виводить результатию 
    cout << "\n--- REZULTAT ---" << endl;
    cout << "Model: " << model << endl;
    cout << "Faktychna emnist: " << C_eff << " Vt*god" << endl;
    cout << "Korysna enerhiya: " << E_useful << " Vt*god" << endl;
    cout << "Vtraty: " << E_loss << " Vt*god" << endl;
    cout << "Chas roboty: " << hours << " god " << minutes << " khv" << endl;

    return 0;
}