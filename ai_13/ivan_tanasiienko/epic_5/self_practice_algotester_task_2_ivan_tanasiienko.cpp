/*
    Epic 5, Self Practice 1 — «Фібонета»
    Танасієнко Іван, ШІ-13
*/
#include<iostream>

int main()
{
    long n, a0, a1, c0, c1;
    std::cin >> n >> a0 >> a1;
    c0 = a0;
    c1 = a1;
    if(n == 0)
    {
        if(a0 > 0)
        {
            std::cout << '+' << std::endl;
        }
        if(a0 < 0)
        {
            std::cout << '-' << std::endl;
        }
        if(a0 == 0)
        {
            std::cout << '0' << std::endl;
        }
        return 0;
    }
    if(n == 1)
    {
        if(a1 > 0)
        {
            std::cout << '+' << std::endl;
        }
        if(a1 < 0)
        {
            std::cout << '-' << std::endl;
        }
        if(a1 == 0)
        {
            std::cout << '0' << std::endl;
        }
        return 0;
    }
    if(n < 20 && n > 1)
    {
        for(int i = 0; i < n - 1; i++)
        {
            c1 = c1 + c0;
            c0 = c1 - c0;
        }
        if(c1 > 0)
        {
            std::cout << '+' << std::endl;
        }
        if(c1 < 0)
        {
            std::cout << '-' << std::endl;
        }
        if(c1 == 0)
        {
            std::cout << '0' << std::endl;
        }
        return 0;
    }
    long i = 1;
    while(i < n && !((c1 > 0 && c0 > 0) || (c1 < 0 && c0 < 0) || (c1 == 0 && c0 == 0)))
    {
        c1 = c1 + c0;
        c0 = c1 - c0;
        i++;
    }
    if(c1 > 0)
    { 
        std::cout << '+' << std::endl;
    }
    else if(c1 < 0)
    {
        std::cout << '-' << std::endl;
    }
    else
    {
        std::cout << '0' << std::endl;
    }
    return 0;
}