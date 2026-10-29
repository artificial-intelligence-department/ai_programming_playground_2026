/*
    Цікавий масив, Танасієнко Іван, ШІ-13
*/
#include<iostream>

int main()
{
    int len;
    std::cin >> len;
    int* arr = new int[len];
    for(int i = 0; i < len; i++)
    {
        std::cin >> *(arr + i);
    }
    for(int k = 0; k < len; k++)
    {
        int sumL = 0;
        int sumR = 0;
        for(int i = 0; i <= k; i++)
        {
            sumL = sumL + *(arr + i);
        }
        for(int i = len - 1; i > k; i--)
        {
            sumR = sumR + *(arr + i);
        }
        if(sumL == sumR)
        {
            std::cout << "TAK" << std::endl;
            delete[] arr;
            return 0;
        }
    }
    std::cout << "NI" << std::endl;
    delete[] arr;
    return 0;
}