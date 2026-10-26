/*  
Lab 2 Task 1
Дохнюк Богдан 
ШІ-14
Варіант 21 
*/
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    double factorial = 1.0;
    double an;
    double sum = 0.0;

    for (n = 1; n <= 13; n++) {
        factorial = factorial * n;
        an = log(factorial) / (n * n);
        sum = sum + an;
    }

    cout << "Сума 13 членів ряду = " << sum << endl;

    return 0;
}
