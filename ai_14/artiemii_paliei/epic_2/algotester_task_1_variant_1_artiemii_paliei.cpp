/*
    Algotester Lab 1 Task 1
    Прізвище: Палєй
    Група: ШІ-14
*/
#include <iostream>

int main()
{
    long long H, M, h, m;
    bool is_it_lose = false;

    std::cin >> H >> M;

    std::cin >> h >> m;
    if (h && m)
        is_it_lose = true;
    H -= h;
    M -= m;

    std::cin >> h >> m;
    if (h && m)
        is_it_lose = true;
    H -= h;
    M -= m;

    std::cin >> h >> m;
    if (h && m)
        is_it_lose = true;
    H -= h;
    M -= m;

    if (H <= 0 || M <= 0)
        is_it_lose = true;

    if (!is_it_lose)
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;

    return 0;
}