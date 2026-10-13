#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    long double sum = 0.0L;
    long double eps = 0.0001L;
    int n = 1;

    while (true) {
        long double a = exp(n) * pow(100, -n * n);

        if (std::abs(a) < eps) {
            break;
        }

        n++;
        sum += a;
    }

    std::cout << std::fixed << std::setprecision(4) << sum << std::endl;
    return 0;
}

