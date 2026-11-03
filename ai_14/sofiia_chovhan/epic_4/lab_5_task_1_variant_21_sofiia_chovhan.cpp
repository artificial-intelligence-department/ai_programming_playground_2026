/*Sofiia Chovhan
AI 14
Lab 5 Variant 21
*/

#include <iostream>
using namespace std;

bool findLargestRepeated(int **numbers, int height, int width, int &largest)
{
    bool exists = false;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            for (int nextRow = 0; nextRow < height; nextRow++)
            {
                for (int nextCol = 0; nextCol < width; nextCol++)
                {
                    if ((row != nextRow || col != nextCol) &&
                        numbers[row][col] == numbers[nextRow][nextCol])
                    {
                        if (!exists || numbers[row][col] > largest)
                        {
                            largest = numbers[row][col];
                            exists = true;
                        }
                    }
                }
            }
        }
    }

    return exists;
}

int main()
{
    int height, width;

    cout << "Enter number of rows: ";
    if (!(cin >> height) || height <= 0)
    {
        cout << "Invalid number of rows." << endl;
        return 1;
    }

    cout << "Enter number of columns: ";
    if (!(cin >> width) || width <= 0)
    {
        cout << "Invalid number of columns." << endl;
        return 1;
    }

    int **numbers = new int *[height];

    for (int row = 0; row < height; row++)
    {
        numbers[row] = new int[width];
    }

    cout << "Enter matrix elements:" << endl;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            if (!(cin >> numbers[row][col]))
            {
                cout << "Invalid element." << endl;

                for (int k = 0; k < height; k++)
                {
                    delete[] numbers[k];
                }

                delete[] numbers;
                return 1;
            }
        }
    }

    int largest;

    if (findLargestRepeated(numbers, height, width, largest))
    {
        cout << "Largest repeated element: " << largest << endl;
    }
    else
    {
        cout << "There are no repeated elements." << endl;
    }

    for (int row = 0; row < height; row++)
    {
        delete[] numbers[row];
    }

    delete[] numbers;

    return 0;
}
