/*
    Lab 4 - Task 1-9, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<random>

int main()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 100);
    int len;
    std::cout << "Довжина масиву: ";
    std::cin >> len;
    int* arr = new int[len];

    for(int i = 0; i < len; i++)
    {
        *(arr + i) = dist(rng);
    }
    for(int i = 0; i < len; i++)
    {
        std::cout << *(arr + i) << ' ';
    }
    int destroy;
    std::cout << std::endl << "Знищити значення: ";
    std::cin >> destroy;
    for(int i = 0; i < len; i++)
    {
        if (arr[i] == destroy)
        {
            for (int j = i; j < len - 1; j++)
            {
                *(arr + j) = *(arr + j + 1);
            }
            len--;
            break;
        }
    }
    int offset;
    std::cout << "Зсув: ";
    std::cin >> offset;
    int* copy = new int[len];
    for(int x = 0; x < offset; x++)
    {
        for(int i = 0; i < len; i++)
        {
            *(copy + i) = *(arr + i);
        }
     
        for(int i = 0; i < len; i++)
        {
            if(i == 0)
            {
                *(arr + i) = *(arr + len -1);
            }
            else
            {
                *(arr + i) =  *(copy + i - 1);
            }
        }
    }
    delete[] copy;
    for(int i = 0; i < len; i++)
    {
        std::cout << *(arr + i) << ' ';
    }
    std::cout << std::endl;
    delete[] arr;
    return 0;
}