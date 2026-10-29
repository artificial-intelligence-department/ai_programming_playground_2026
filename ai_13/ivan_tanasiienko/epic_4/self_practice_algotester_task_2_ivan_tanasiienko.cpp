/*
    Обробка масиву, Танасієнко Іван, ШІ-13
*/
#include<iostream>

int main()
{
    int len;
    std::cin >> len;

    int* arr = new int[len];
    bool* seen = new bool[1000001];
    int types = 0;
    for(int i = 0; i < len; i++)
    {
        std::cin >> *(arr + i);

        *(seen + *(arr + i)) = true;
    }
    delete[] arr;
    for(int i = 1; i < 1000001; i++)
    {
        if(*(seen + i))
        {
            types++;
        }
    }
    std::cout << types << std::endl;
    delete[] seen;
    return 0;
}