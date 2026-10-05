#include <iostream>

int main()
{
    long long a1, a2, a3, a4, a5;

    std::cin >> a1;
    if (a1 <= 0) { std::cout << "ERROR"; return 0; }

    std::cin >> a2;
    if (a2 <= 0) { std::cout << "ERROR"; return 0; }
    if (a1 < a2) { std::cout << "LOSS"; return 0; }

    std::cin >> a3;
    if (a3 <= 0) { std::cout << "ERROR"; return 0; }
    if (a2 < a3) { std::cout << "LOSS"; return 0; }

    std::cin >> a4;
    if (a4 <= 0) { std::cout << "ERROR"; return 0; }
    if (a3 < a4) { std::cout << "LOSS"; return 0; }

    std::cin >> a5;
    if (a5 <= 0) { std::cout << "ERROR"; return 0; }
    if (a4 < a5) { std::cout << "LOSS"; return 0; }
    std::cout << "WIN";
    return 0;
}

