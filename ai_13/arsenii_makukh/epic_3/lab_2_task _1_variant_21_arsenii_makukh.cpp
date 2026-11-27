/*
Назва: Lab 2 - Task 1-21
Автор: Макух Арсеній
Група: ШІ-13
*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    const int N = 13;
    double sum = 0;
    double factorial = 1;

    for (int n = 1; n <= N; n++) {
        factorial *= n;

        double a = log(factorial) / (n * n);
        sum += a;
    }

    cout << "Сума 13 членів ряду: " << sum << endl;

    return 0;
}
