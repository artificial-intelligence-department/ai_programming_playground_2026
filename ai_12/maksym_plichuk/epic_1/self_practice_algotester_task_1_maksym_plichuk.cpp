#include <iostream>

int main()
{
    int a, b;
    std::cin >> a;
    std::cin >> b;

    if (a < 0 || a > 100 || b < 0 || b > 100)
    {
        return 0;
    }
    std::cout << a + b;
    return 0;
}