#include <iostream>
#include <iomanip>
#include <cmath>
 
using namespace std;
 
int main() {
    // вхідні дані для float
    float f_a = 1000.0f, f_b = 0.0001f;

    // обраховуємо використовуючи тип даних float
    // обраховуємо проміжні змінні 
    float f_1 = pow(f_a + f_b, 3.0f);     // (a+b)^3
    float f_2 = pow(f_a, 3.0f);          // a^3
    float f_3 = f_1 - f_2;                // чисельник
    float f_4 = 3 * f_a * f_b * f_b;       // 3ab^2
    float f_5 = pow(f_b, 3.0f);          // b^3
    float f_6 = 3 * f_a * f_a * f_b;       // 3a^2b
    float f_7 = f_4 + f_5 + f_6;           // знаменник
    float f_res = f_3 / f_7;
 
    // вхідні дані для double
    double d_a = 1000.0, d_b = 0.0001;

    // обраховуємо використовуючи тип даних double
    double d_1 = pow(d_a + d_b, 3.0);
    double d_2 = pow(d_a, 3.0);
    double d_3 = d_1 - d_2;
    double d_4 = 3 * d_a * d_b * d_b;
    double d_5 = pow(d_b, 3.0);
    double d_6 = 3 * d_a * d_a * d_b;
    double d_7 = d_4 + d_5 + d_6;
    double d_res = d_3 / d_7;
 
    cout << fixed << setprecision(10);
    cout << "(float):" << endl;
    cout << "  (a+b)^3 =   " << f_1 << endl;
    cout << "  a^3     =   " << f_2 << endl;
    cout << "  чисельник = " << f_3 << endl;
    cout << "  знаменник = " << f_7 << endl;
    cout << "  результат = " << f_res << endl;
    cout << "\n(double):" << endl;
    cout << "  (a+b)^3 =   " << d_1 << endl;
    cout << "  a^3     =   " << d_2 << endl;
    cout << "  чисельник = " << d_3 << endl;
    cout << "  знаменник = " << d_7 << endl;
    cout << "  результат = " << d_res << endl;

}