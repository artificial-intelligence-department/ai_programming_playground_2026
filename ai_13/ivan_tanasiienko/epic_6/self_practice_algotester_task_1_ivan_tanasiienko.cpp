/*
    Сет, Танасієнко Іван, ШІ-13
*/
#include <iostream>

bool isSet(int a, int b, int c)
{
    for (int i = 0; i < 4; i++)
    {
        int x = a % 3;
        int y = b % 3;
        int z = c % 3;

        bool same = (x == y && y == z);
        bool different = (x != y && x != z && y != z);

        if (!same && !different) return false;
        a /= 3;
        b /= 3;
        c /= 3;
    }
    return true;
}

int main()
{
    int n;
    std::cin >> n;

    long long freq[81] = {};

    const char options[4][4] = {
        "123",
        "RGB",
        "FPE",
        "DSO"
    };

    for (int i = 0; i < n; i++)
    {
        char card[5];
        std::cin >> card;

        int id = 0;

        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (card[j] == options[j][k])
                {
                    id = id * 3 + k;
                    break;
                }
            }
        }
        freq[id]++;
    }
    long long answer = 0;

    for (int i = 0; i < 81; i++)
    {
        if (freq[i] >= 3) answer += freq[i] * (freq[i] - 1) * (freq[i] - 2) / 6;
        for (int j = i + 1; j < 81; j++) for (int k = j + 1; k < 81; k++) if (isSet(i, j, k)) answer += freq[i] * freq[j] * freq[k];
    }
    std::cout << answer << '\n';

    return 0;
}