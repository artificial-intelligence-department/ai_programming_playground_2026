#include <iostream>
#include <cmath>

using namespace std;

int main()
{

    double epsilon = 0.0001;
    double n = 1;
    double res = exp(n) * pow(100,-pow(n, 2));
    double sum = 0.00;
    
    while (res >= epsilon)
    {
        sum += res;
        n++;
        res = exp(n) * pow(100,-pow(n, 2));
    }

    cout << "Сума ряду: " << sum;
    
}