/*
    Лаб2 вараінт 22
    Автор: Дмитро Надвірний
    Група: 12
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double sum = 0;
    for (int n = 2; n <= 16; n++) {   // 15 членів: n = 2..16
        double a_n = pow(n, log(n)) / pow(log(n), n);
        sum += a_n;
    }
    cout << "Сума 15 членів ряду = " << fixed << setprecision(4) << sum << endl;
    return 0;
}