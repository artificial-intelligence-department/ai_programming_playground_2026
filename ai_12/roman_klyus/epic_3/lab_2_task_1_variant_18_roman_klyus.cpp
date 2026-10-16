#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    const double eps = 0.0001;
    double suma = 0.0;
    double a_n = 1.0; //вручну пораховане значення a_n для n = 1
    int n = 1;

    while (a_n >= eps) {
        suma += a_n;
        //шукаємо рекуретну формулу( diff = (a_n+1 / a_n) )
        double diff = (pow((n+1), 3) / (pow(n, 3) * (3*n) * (3*n-1) * (3*n-2))); 
        //виражаємо n-ий член послідовності, використовуючи рекурентну формулу
        a_n *= diff;
        ++n;
    }

    cout << fixed << setprecision(4);
    cout << "Сума ряду a_n = n^3/(3n-3)! = " << suma << " з точністю до " << eps << endl;
    cout << "Взято членів для підрахунку: " << (n - 1) << endl;
}