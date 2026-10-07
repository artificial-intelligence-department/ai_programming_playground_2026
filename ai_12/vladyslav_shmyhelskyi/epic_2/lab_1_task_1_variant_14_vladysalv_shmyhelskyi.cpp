#include <iostream>
#include <cmath>
#include <iomanip>
int main()
{
    using namespace std;
    // Вводим змінні для Double
    double a = 1000;
    double b = 0.0001;
    double topleft = pow(a + b, 3.0);
    double a3 = pow(a, 3.0); // Обчислюємо значення виразу (a+b)^3 - a^3 - 3*a^2*b / 3*a*b^2 + b^3 для double
    double b3 = pow(b, 3.0);
    double topright = a3 + (3.0 * a * a * b);
    double top = topleft - topright;
    double bottom = (3.0 * a * (b * b)) + b3;
    double resD = top / bottom;
    // те саме для float

    float a_f = 1000.0f;
    float b_f = 0.0001f;
    float topleft_f = pow(a_f + b_f, 3.0f); 
    float a3_f = powf(a_f, 3.0f);
    float b3_f = powf(b_f, 3.0f); // обчислення того ж виразу  для float
    float topright_f = a3_f + (3.0f * a_f * a_f * b_f);
    float top_f = topleft_f - topright_f;
    float bottom_f = (3.0f * a_f * (b_f * b_f)) + b3_f;
    float resF = top_f / bottom_f;

    cout << fixed << setprecision(6); // для виводу результатів з 6 знаками після коми(для точності)
    cout << "Double result: " << resD << endl;
    cout << "Float result: " << resF << endl;
}