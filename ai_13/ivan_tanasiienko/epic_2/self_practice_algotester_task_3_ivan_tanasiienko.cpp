/*
Хелловін, Танасієнко Іван, ШІ-13
*/
#include<iostream>

int main()
{
    int candiesAm1, candiesAm2, cheapest1, cheapest2;
    std::cin >> candiesAm1;
    std::cin >> candiesAm2;
    int candies1[candiesAm1], candies2[candiesAm2];

    for(int i = 0; i < candiesAm1; i++)
    {
        std::cin >> candies1[i];
    }
    for(int i = 0; i < candiesAm2; i++)
    {
        std::cin >> candies2[i];
    }
    cheapest1 = candies1[0];
    cheapest2 = candies2[0];
    for(int i = 1; i < candiesAm1; i++)
    {
        if(candies1[i] < cheapest1)
        {
            cheapest1 = candies1[i];
        }
    }
    for(int i = 0; i < candiesAm2; i++)
    {
        if(candies2[i] < cheapest2)
        {
            cheapest2 = candies2[i];
        }
    }
    std::cout << cheapest1 + cheapest2 << std::endl;

    return 0;
}