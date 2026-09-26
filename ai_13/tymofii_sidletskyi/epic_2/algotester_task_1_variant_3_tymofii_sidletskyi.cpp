#include <iostream>
#include <cmath>
using namespace std;
/* Задача 1 алготестер лаб 1 варіант 3
   Сідлецький Тимофій ШІ-13*/

int main () {
    const long long constraint1 = -1 * pow(10, 12); //Змінні обмежень сторони куба
    const long long constraint2 = pow(10, 12);
    const int constraint3 = 0;
    long long a1, a2, a3, a4, a5;

    cout << "Введіть сторону першого куба: ";
    cin >> a1;

    if (a1 <= constraint1 || a1 >= constraint2 || a1 <= constraint3) {
        cout << "ERROR" << endl;
        return 0;
    }

    cout << "Введіть сторону другого куба: ";
    cin >> a2;

    if (a2 <= constraint1 || a2 >= constraint2 || a2 <= constraint3) {
        cout << "ERROR" << endl;
        return 0;
    }

    if (a2 > a1) {
        cout << "LOSS" << endl;
        return 0;
    }

    cout << "Введіть сторону третього куба: ";
    cin >> a3;

    if (a3 <= constraint1 || a3 >= constraint2 || a3 <= constraint3) {
        cout << "ERROR" << endl;
        return 0;
    }

    if (a3 > a2) {
        cout << "LOSS" << endl;
        return 0;
    }

    cout << "Введіть сторону четвертого куба: ";
    cin >> a4;

    if (a4 <= constraint1 || a4 >= constraint2 || a4 <= constraint3) {
        cout << "ERROR" << endl;
        return 0;
    }

    if (a4 > a3) {
        cout << "LOSS" << endl;
        return 0;
    }

    cout << "Введіть сторону п'ятого куба: ";
    cin >> a5;

    if (a5 <= constraint1 || a5 >= constraint2 || a5 <= constraint3) {
        cout << "ERROR" << endl;
        return 0;
    }

    if (a5 > a4) {
        cout << "LOSS" << endl;
        return 0;
    }

    cout << "WIN" << endl;

    return 0;
}
