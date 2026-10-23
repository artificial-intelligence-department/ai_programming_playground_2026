/*Лабораторна 2, варіант 13
Група: ШІ-11
Автор: Юлія Шведько*/

#include <iostream>
using namespace std;

int main()
{
    int n = 1;
    double a = 0.5; // Бо вираз при n = 1 дорівнює 0.5
    double e = 0.0001;
    double sum = 0.0;

    while(a >= e)
    {
        sum += a;
        a = a/((3.0*n + 1.0)*(3.0*n + 2.0)); // Бо a(n + 1)/a(n) = 1/((3*n + 1)*(3*n + 2))
        n++;
    }

    cout << "Сума ряду: " << sum << endl;

    return 0;

}