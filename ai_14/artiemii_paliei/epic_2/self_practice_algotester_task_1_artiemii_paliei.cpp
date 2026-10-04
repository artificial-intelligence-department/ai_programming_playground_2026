#include <iostream>

int main()
{
    int l, w, u, d;
    std::cin >> l >> w >> u >> d;
    if (l <= w && l <= (u + d))
        std::cout << "Three times Sex on the Beach, please!" << std::endl;
    else
        std::cout << "Forget about the cocktails, man!" << std::endl;
    return 0;
}