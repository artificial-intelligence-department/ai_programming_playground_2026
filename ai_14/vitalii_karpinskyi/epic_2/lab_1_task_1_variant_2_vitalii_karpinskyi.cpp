#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    // Обчислення виразу типу float
    float af = 1000.0f;
    float bf = 0.0001f;

    float f_1 = pow(af - bf, 2);
    float f_2 = pow(af, 2);
    float f_3 = 2 * af * bf;
    float f_4 = f_2 - f_3;
    float num_f = f_1 - f_4;
    float den_f = pow (bf, 2);
    float result_f = num_f / den_f;

    // Обчислення виразу типу double
    double ad = 1000.0;
    double bd = 0.0001;

    double d_1 = pow(ad - bd, 2);
    double d_2 = pow(ad, 2);
    double d_3 = 2 * ad * bd;
    double d_4 = d_2 - d_3;
    double num_d = d_1 - d_4;
    double den_d = pow (bd, 2);
    double result_d = num_d / den_d;

    // Виведення результатів
    cout << fixed << setprecision(6);
    cout << "Результат float: " << result_f << endl;
    cout << "Результат double: " << result_d << endl; 

    return 0;
}