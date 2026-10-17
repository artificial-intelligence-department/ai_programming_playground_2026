#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    // ---------- Обчислення з типом float ----------
    float af = 1000.0f;
    float bf = 0.0001f;

    float numeratorF = pow(af + bf, 3) - (pow(af, 3) + 3 * pow(af, 2) * bf);
    float denominatorF = 3 * af * pow(bf, 2) + pow(bf, 3);
    float resultF = numeratorF / denominatorF;

    // ---------- Обчислення з типом double ----------
    double ad = 1000.0;
    double bd = 0.0001;

    double numeratorD = pow(ad + bd, 3) - (pow(ad, 3) + 3 * pow(ad, 2) * bd);
    double denominatorD = 3 * ad * pow(bd, 2) + pow(bd, 3);
    double resultD = numeratorD / denominatorD;

    // ---------- Вивід ----------
    cout << fixed << setprecision(10);
    cout << "float:  " << resultF << endl;
    cout << "double: " << resultD << endl;
    cout << "Точне значення: 1" << endl;

    return 0;
}