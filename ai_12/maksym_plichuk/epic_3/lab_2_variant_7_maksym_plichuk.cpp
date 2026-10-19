#include <iostream>
#include <iomanip>

int main()
{
    const double eps = 0.0001;
    double sum = 0.0;

    int n = 1;
    double an = 1.0 / ((3 * n - 2) * (3 * n + 1));

    while (an >= eps)
    {
        sum += an;
        an *= (double)(3 * n - 2) / (3 * n + 4);
        n++;
    }

    std::cout << "Сума ряду з " << n - 1 << " членів: " << std::fixed << std::setprecision(7) << sum;
    return 0;
}