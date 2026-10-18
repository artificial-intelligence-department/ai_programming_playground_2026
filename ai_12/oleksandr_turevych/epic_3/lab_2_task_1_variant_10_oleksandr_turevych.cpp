#include <iostream>
using namespace std;

int main()
{
    double eps = 0.0001;
    double a = 0.5; // Перший член ряду a_1 = 1! / 2! = 0.5
    double n = 1; // Номер поточного члена ряду
    double sum;

    while (a > eps)
    {
        sum += a;
        n++;
        a = 1.0 / (n * (n + 1)); // Обчислення наступного члена ряду
    }
    cout << "Сума ряду = " << sum << endl;
    return 0;
}