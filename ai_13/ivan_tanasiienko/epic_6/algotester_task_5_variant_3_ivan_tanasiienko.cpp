/*
    Algotester Lab 5, Variant 3, Танасієнко Іван, ШІ-13
*/
#include<iostream>

int main()
{
    int rows, cols, x, y;

    std::cin >> rows >> cols;
    int field[rows][cols];
    std::cin >> x >> y;
    x--;
    y--;
    int max = 0;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            field[i][j] = abs((x - i)) + abs((y - j));
            if(field[i][j] > max)
            {
                max = field[i][j];
            }
        }
    }
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            field[i][j] = abs(field[i][j] - max);
            std::cout << field[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}