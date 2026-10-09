#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    // Обчислення для даних типу float
    float a1 = 0;
    float b1 = 0;
 
    cout << "Введіть значення a1:";
    cin >> a1;
    cout << "Введіть значення b1:";
    cin >> b1;

    float c = a1 + b1;
    float d = pow(c, 3);
    float e = pow(a1, 3) + 3*a1*a1*b1;
    float f = d - e;
    float g = 3*a1*b1*b1;
    float h = pow(b1, 3);
    float i = g + h;
    float j = f / i;

    // Обчислення для даних типу double
    double a2 = 0;
    double b2 = 0;

    cout << "Введіть значення a2:";
    cin >> a2;
    cout << "Введіть значення b2:";
    cin >> b2;

    double n = a2 + b2;
    double o = pow(n, 3);
    double p = pow(a2, 3) + 3*a2*a2*b2;
    double q = o - p;
    double r = 3*a2*b2*b2;
    double s = pow(b2, 3);
    double t = r + s;
    double u = q / t;


     cout << fixed << setprecision(15) << "Результат обчислення для даних типу float: " << j << endl;
     cout << fixed << setprecision(15) << "Результат обчислення для даних типу double: " << u ;


    return 0;
}
