/*
    Гори акумуляторів, Танасієнко Іван, ШІ-13
*/
#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    int x[n];

    for (int i = 0; i < n; i++) std::cin >> x[i];

    int platform;
    std::cin >> platform;

    int left = platform;
    int right = platform;
    int answer = 0;

    for (int i = 0; i < n; i++)
    {
        if (x[i] > right || x[i] + 1 < left) continue;
        if (x[i] < left) left = x[i];
        if (x[i] + 1 > right) right = x[i] + 1;
        answer++;
    }

    std::cout << answer << '\n';
    return 0;
}