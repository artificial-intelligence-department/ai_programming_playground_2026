
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {

    int n = 7;
    double a = exp(-1.0);  // перший член: 1^2 * e^(-1)
    double sum = a;        

    for (int i = 2; i <= n; i++) {
        // поточний член множу на формулу і виходить наступний (і він стає a)
        a = a * pow((double)i / (i - 1), 2) * exp(sqrt(i - 1) - sqrt(i));

        sum += a;  
    }

    cout << "Сума перших " << n << " членів ряду: " << sum << endl;

    return 0;

}
