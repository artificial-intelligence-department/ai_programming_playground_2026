#include <iostream>
#include <cmath>
using namespace std;
/* Задача: Лабораторна робота, завдання 1
* Щербак Орислав
* Група 11
*/

int main() {
    // Варіант 1: double
    double a1 = 1000, b1 = 0.0001;
    double num1 = pow(a1 - b1, 3) - pow(a1, 3); // обчислення чисельника
    double den1 = pow(b1, 3) - 3 * a1 * b1 * b1 - 3 * a1 * a1 * b1; // обчислення знаменника
    cout << "double: " << num1 / den1 << endl; // виведення результату
    // Варіант 2: float
    float a2 = 1000, b2 = 0.0001f;
    float num2 = pow(a2 - b2, 3) - pow(a2, 3); // обчислення чисельника
    float den2 = pow(b2, 3) - 3 * a2 * b2 * b2 - 3 * a2 * a2 * b2; // обчислення знаменника
    cout << "float:  " << num2 / den2 << endl; // виведення результату
    return 0;
}