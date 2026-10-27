#include <iostream>

const int COLUMNS = 40;
const int ROWS = 20;

double average(int matrix[][COLUMNS], int rows, int columns, int column)
{

    double avg = 0, count = 0;
    for (int i = 0; i < rows; i++)
        avg += matrix[i][column];
    return avg / rows;
}

void counter(int matrix[][COLUMNS], int rows, int columns, double avg, int column)
{

    int count = 0;
    for (int j = 0; j < rows; j++)
    {
        if (avg < matrix[j][column + 1])
            count++;
    }
    std::cout << "Number of elements more than average of " << column + 1 << " column in " << column + 2
              << " column: " << count << std::endl;
}

int main()
{
    int td_array[ROWS][COLUMNS] = {0};
    int r, c;

    std::cout << "Enter your 2D array rows and columns: ";
    std::cin >> r >> c;

    if (r < 1 || r > 20 || c < 1 || c > 40)
    {
        std::cout << "Error. You entered invalid array dimensions.";
        return 1;
    }

    std::cout << "Enter elements of your 2D array: ";
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            std::cin >> td_array[i][j];
            if (std::cin.fail())
            {
                std::cout << "Error. Value you entered isn't valid for the field.";
                return 1;
            }
        }
    }

    for (int i = 0; i < c; i++)
    {
        double avg = average(td_array, r, c, i);
        std::cout << "Average of " << i + 1 << " columns is: " << avg << std::endl;
        if (i < c - 1)
            counter(td_array, r, c, avg, i);
    }
    return 0;
}