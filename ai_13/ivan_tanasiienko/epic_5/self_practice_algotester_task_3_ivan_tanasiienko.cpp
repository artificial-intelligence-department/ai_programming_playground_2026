/*
    Epic 5, Self Practice 3 — «Математична задача»
    Танасієнко Іван, ШІ-13
*/
#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    int steps = 0;
    int ans = 1000000000;

    while (n >= 1)
    {
        if ((n - 1) % 7 == 0)
        {
            int current = steps + (n - 1) / 7;

            if (current < ans)
            {
                ans = current;
            }
        }

        int k = (4 - n % 4) % 4;

        if (n - 7 * k <= 0)
        {
            break;
        }

        n = (n - 7 * k) / 4;
        steps += k + 1;
    }

    if (ans == 1000000000)
    {
        std::cout << -1 << '\n';
    }
    else
    {
        std::cout << ans << '\n';
    }

    return 0;
}
