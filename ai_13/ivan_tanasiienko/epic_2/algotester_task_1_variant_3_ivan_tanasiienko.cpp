/*
Algotster Lab 1v3, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<cmath>

int main()
{
    long cubes[5];
    long prevCube = -1;
    for(int i = 0; i < 5; i++)
    {
        std::cin >> cubes[i];
    }
    for(int i = 0; i < 5; i++)
    {
        if(cubes[i] > std::pow(10, 12) || cubes[i] <= 0)
        {
            std::cout << "ERROR" << std::endl;
            return 0;
        }
        if(prevCube == -1 || cubes[i] <= prevCube)
        {
            prevCube = cubes[i];
        }
        else
        {
            std::cout << "LOSS" << std::endl;
            return 0;
        }
    }

    std::cout << "WIN" << std::endl;

    return 0;
}