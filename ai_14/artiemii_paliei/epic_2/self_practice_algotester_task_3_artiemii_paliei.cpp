// Рейтинг петрика

#include <iostream>

int main()
{
    int x, y, z;
    std::cin >> x >> y >> z;

    if (z < x-y)
        std::cout << -1 << std::endl;
    else
    {
        if (z > x+y)
            std::cout << x+y << std::endl;
        else
            std::cout << z << std::endl;
    }

    return 0;
}