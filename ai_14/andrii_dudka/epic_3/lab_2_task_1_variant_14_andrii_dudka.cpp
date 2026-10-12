#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    const double eps = 0.0001;
    double term = 1.0 / 3.0; // a_1 = 1! / (3 * 1^1)
    double sum = 0.0;
    int n = 1;

    while (term >= eps) {
        sum += term;
        // a_(n+1) = a_n * (n / (n+1))^n
        term *= pow(n / (n + 1.0), n);
        ++n;
    }

    cout << fixed << setprecision(8);
    cout << sum << '\n';
}
