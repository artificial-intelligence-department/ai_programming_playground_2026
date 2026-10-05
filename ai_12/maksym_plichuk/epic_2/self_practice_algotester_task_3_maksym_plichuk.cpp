#include <iostream>
#include <iomanip>

int main()
{
    const double len = 225000000.0;

    long speed;
    std::cin >> speed;

    double res = len / speed;
    std::cout << std::fixed << std::setprecision(4) << res;
}
