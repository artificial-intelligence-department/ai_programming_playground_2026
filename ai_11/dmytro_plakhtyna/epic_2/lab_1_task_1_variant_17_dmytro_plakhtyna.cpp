#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // Введення двох чисел a і b (float) та пишемо обчислення виразу (a-b)^3 - a^3 + 3ab^2 / b^3 - 3a^2b
    float a, b;
    cout << "Введіть два числа a i b (float): ";
    cin >> a >> b;
float d1 = pow(a-b, 3);
float d2 = pow(a, 3);
float d3 = 3 * a * b * b;
float d4 = pow (b, 3);
float d5 = 3 * a * a * b;
float chys = d1 - d2 + d3;
float znam = d4 - d5;
float result = chys / znam;
cout << "Чисельник (float): " << chys << endl;
cout << "Знаменник (float): " << znam << endl;
cout << "Результат (float): " << result << endl;
// Введення двох чисел a і b (double) та пишемо обчислення виразу (a-b)^3 - a^3 + 3ab^2 / b^3 - 3a^2b
double a2, b2;
cout << "Введіть два числа a i b (double): ";
cin >> a2 >> b2;
double d12 = pow(a2-b2, 3);
double d22 = pow(a2, 3);
double d32 = 3 * a2 * b2 * b2;
double d42 = pow (b2, 3);
double d52 = 3 * a2 * a2 * b2;
double chys2 = d12 - d22 + d32;
double znam2 = d42 - d52;
double result2 = chys2 / znam2;
cout.precision(10);
cout << "Чисельник (double): " << chys2 << endl;
cout << "Знаменник (double): " << znam2 << endl;
cout << "Результат (double): " << result2 << endl;
    return 0;
}