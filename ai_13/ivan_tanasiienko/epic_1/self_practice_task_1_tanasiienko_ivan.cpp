#include <iostream>
#include<cmath>

int main()
{
    long h, m, h1, h2, h3, m1, m2, m3;
    const long LIMIT = std::pow(10, 12);
    std::string result;
    std::cin >> h;
    std::cin >> m;
    std::cin >> h1;
    std::cin >> m1;
    std::cin >> h2;
    std::cin >> m2;
    std::cin >> h3;
    std::cin >> m3;

    if(h > LIMIT || m > LIMIT || h < 1 || m < 1 
        || h1 > LIMIT || m1 > LIMIT || h1 < 0 || m1 < 0 
        || h2 > LIMIT || m2 > LIMIT || h2 < 0 || m2 < 0
        || h3 > LIMIT || m3 > LIMIT || h3 < 0 || m3 < 0)
    {
        std::cout << "NO" << std::endl;
        return 0;
    }

    long spells[3][2] = {
        {h1, m1}, 
        {h2, m2},
        {h3, m3}
    };

    for(int i = 0; i < 3; i++)
    {
        if((spells[i][0] != 0 && spells[i][1] != 0))
        {
            result = "NO";

            std::cout << result << std::endl;

            return 0;
        }
        h = h - spells[i][0];
        m = m - spells[i][1];
    }
    if(h > 0 && m > 0)
    {
        result = "YES";
    }
    else
    {
        result = "NO";
    }

    std::cout << result << std::endl;

    return 0;
}