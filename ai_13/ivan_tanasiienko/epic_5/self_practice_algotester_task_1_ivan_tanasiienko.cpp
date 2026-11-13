/*
    Epic 5, Self Practice 1 — «Космозаправки»
    Танасієнко Іван, ШІ-13
*/
#include<iostream>


int main()
{
    bool simpleNums[1000008];
    int a, b, k;
    std::cin >> a >> b >> k;
    simpleNums[1] = false;
    bool allowed[1000008];
    for (bool& x : allowed)
    {
        x = true;
    }
    for(int i = 2; i <= 1000004; i++)
    {
        simpleNums[i] = true;
        for(int j = 2; j*j <= i; j++)
        {
            if(i % j == 0)
            {
                simpleNums[i] = false;
                break;
            }
        }
    }
    if(k > 1000)
    {
        std::cout << 0 << std::endl;
        return 0;
    }
    for(int i = a; i <= 1000004; i++)
    {
        if(simpleNums[i])
        {
            int lim = i - k;
            int upLim = i + k;
            if(i + k > 1000001)
            {
                upLim = 1000001;
            }
            if(lim <= 0)
            {
                lim = 1;
            }
            for(int j = lim; j <= upLim; j++)
            {
                allowed[j] = false;
            }
        }
        if(simpleNums[i] && i > b)
        {
            break;
        }
    }
    int allowedStantions = 0;
    for(int i = a; i <= b; i++)
    {
        if(allowed[i])
        {
            allowedStantions++;
        }
    }
    std::cout << allowedStantions << std::endl;
    return 0;
}
