#include <iostream>
#include <cmath>

using namespace std;

int main() {
    const double eps = 0.0001;
    double a = 1.0 / 3.0;
    double sum = 0.0;
    long n = 1;
    do {
        sum += a;
        a = a * pow(n / (n + 1.0), n);
        n++;
    } while (a >= eps);
    cout << "Сума ряду з точністю eps=0.0001: " << sum << endl;
    return 0;
}
