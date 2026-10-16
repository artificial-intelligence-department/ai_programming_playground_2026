#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double sum = 0;
    double fact = 1;

    for (int n = 1; n <= 10; n++) {
        fact *= n;                       // n!
        sum += fact / pow(n, sqrt(n));   // a_n = n! / n^(sqrt(n))
    }

    cout << "Сума 10 членів ряду = " << sum << endl;
    return 0;
}