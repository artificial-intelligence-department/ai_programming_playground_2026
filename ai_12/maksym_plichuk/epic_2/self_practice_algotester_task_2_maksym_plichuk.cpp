#include <iostream>

int main()
{
    int count;
    std::cin >> count;

    long eatencookies = 0;
    for (int i = 0; i < count; i++)
    {
        long cookiesInPack;
        std::cin >> cookiesInPack;
        if (cookiesInPack > 0)
        {
            eatencookies += cookiesInPack - 1;
        }
    }
    std::cout << eatencookies;
}
