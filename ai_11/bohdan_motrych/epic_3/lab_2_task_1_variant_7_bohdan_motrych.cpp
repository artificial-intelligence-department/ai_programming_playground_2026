#include <iostream>

int main() {
    const double eps = 0.0001;
    double a_n = 0.25;
    int n = 1;
    double sum = a_n;

    for(n = 1; a_n > eps; n++) {
        a_n *= (double) (3 * n - 2) / (3 * n + 4);
        sum += a_n;
    }

    std::cout << "Сума ряду a_n = 1/((3*n-2)*(3*n+1)) з точністю ε = 0.0001: " << std::fixed << sum << std::endl;
    std::cout << "n = " << n << std::endl;

    return 0;
}