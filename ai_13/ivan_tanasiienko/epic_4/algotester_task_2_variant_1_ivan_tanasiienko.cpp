/*
    Algotester Lab 2v1, Танасієнко Іван, ШІ-13
*/
#include<iostream>

int main()
{
    int len;
    std::cin >> len;
    int road[len];
    int sorted[len];
    for(int i = 0; i < len; i++)
    {
        std::cin >> road[i];
        sorted[i] = road[i];
    }
    for(int i = 0; i < len; i++)
    {
        int buffer;
        for(int j = 0; j < len - 1; j++)
        {
            if(sorted[j] > sorted[j + 1])
            {
                buffer = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = buffer;
            }
        }
    }
    if(len == 1)
    {
        std::cout << 0 << std::endl;
        return 0;
    }
    if((sorted[len - 2] - sorted[0]) > (sorted[len - 1] - sorted[1]))
    {
        std::cout << (sorted[len - 1] - sorted[1]) << std::endl;
    }
    else
    {
        std::cout << (sorted[len - 2] - sorted[0]) << std::endl;
    }
    return 0;
}