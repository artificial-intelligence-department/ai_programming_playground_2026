/*
    Lab 5 - Task 1-9, Танасієнко Іван, ШІ-13
*/
#include<iostream>

int sum(int** matrix, int len)
{
    int sum = 0;
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            if(j < i)
            {
                sum += *(*(matrix + i) + j);
            }
        }
    }
    return sum;
}
int main()
{
    int len, amount;
    int max = 0;
    std::cout << "Кількість матриць: ";
    std::cin >> amount;
    for(int x = 0; x < amount; x++)
    {
        std::cout << "Довжина матриці: ";
        std::cin >> len;
        int** matrix = new int*[len];
        for(int i = 0; i < len; i++)
        {
            int* row = new int[len];
            for(int j = 0; j < len; j++)
            {
                std::cin >> *(row + j);
            }
            *(matrix + i) = row;
        }
        int mSum = sum(matrix, len);
        if (x == 0 || mSum > max)
        {
            max = mSum;
        }
        for(int i = 0; i < len; i++)
        {
            delete[] *(matrix + i);
        }
        delete[] matrix;
    }
    std::cout << "Максимальне значення суми в " << amount << " матрицях: " << max << std::endl;
    return 0;
}