/*
Олексійчук Захар ШІ-14
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    // Ініціалізація епсилона, суми, початкового члена
    const double E = 0.0001;
    double sum = 0.0;
    int n = 2;
    double a_n = 0;
    
    // Перший член суми
    a_n = ((double)n) / pow(n - 1, 2);

    while (fabs(a_n) > E) {
        sum += a_n;
        n++;
        a_n = ((double)n) / pow(n - 1, 2);  
    }

    cout << "Сума (Варіант 19): " << sum << ". Доданків використано: " << n-2 << endl;
}