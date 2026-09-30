#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    // Вхідні дані
    double a = 1000.0;
    double b = 0.0001;

    // Обчислення виразу типом double з проміжними змінними
    double first = pow(a - b, 3.0);
    double second = pow(a, 3.0);
    double chyselbnyk = first - second;
    double x = pow(b, 3.0);
    double y = 3.0 * a * b * b;
    double z = 3.0 * a * a * b;
    double znamennyk = x - y - z;
    double res1 = chyselbnyk / znamennyk;

    // Вхідні дані для float
    float a_f = 1000.0f;
    float b_f = 0.0001f;

    // Те саме обчислення типом float — для порівняння точності
    float firs = pow(a_f - b_f, 3.0f);
    float secon = pow(a_f, 3.0f);
    float chyselbn = firs - secon;
    float xf = pow(b_f, 3.0f);
    float yf = 3.0f * a_f * b_f * b_f;
    float zf = 3.0f * a_f * a_f * b_f;
    float znamen = xf - yf - zf;
    float res1_f = chyselbn / znamen;

    // Виведення результатів
    cout << "Result is: " << fixed << setprecision(10) << res1 << endl;
    cout << "Result (float) is: " << fixed << setprecision(10) << res1_f << endl;

    return 0;
}