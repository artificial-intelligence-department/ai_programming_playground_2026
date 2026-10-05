#include <iostream>

int main()
{
    int n, m;
    std::cin >> n >> m;
    if ((n * m) % 2 == 0)
    {
        std::cout << "Dragon\n";
    }else {
        std::cout << "Imp\n";
    }
    return 0;
}