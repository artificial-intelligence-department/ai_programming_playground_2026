#include <iostream>
#include <cmath>
using namespace std;

float for_float()
{
    const int a = 1000;
    const float b = 0.0001;

    // Обчислення чисельника
    float c = a + b;
    float d = pow(c,3);
    float e = pow(a,3);
    float numerator = d - e;

    // Обчислення знаменника
    float f = 3*a*b*b;
    float g = pow(b,3);
    float h = 3*a*a*b;
    float denominator = f + g + h;

    return numerator/denominator;
}

double for_double()
{
    const int a = 1000;
    const double b = 0.0001;

    // Обчислення чисельника
    double c = a + b;
    double d = pow(c,3);
    double e = pow(a,3);
    double numerator = d - e;

    // Обчислення знаменника
    double f = 3*a*b*b;
    double g = pow(b,3);
    double h = 3*a*a*b;
    double denominator = f + g + h;

    return numerator/denominator;
}

int main()
{
    cout << for_float() << endl;
    cout << for_double() << endl;
    return 0;
}