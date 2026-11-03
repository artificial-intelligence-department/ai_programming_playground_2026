#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

void List(int rows, int cols, int **image);
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void statisticsBrightness(int **image, int rows, int cols);
void invertBrightness(int **image, int rows, int cols);
void mirror(int **image, int rows, int cols);
void swapPixels(int *a, int *b);
int** rotateRight(int **image, int rows, int cols);

int main()
{
//cin + check
    int rows;
    int cols;
    cout << "Enter pixel's height: ";
    if (!(cin >> rows) || rows <= 0 || rows > 20)
    {
        cout << "Something went wrong!" << endl;
        return 1;
    }

    cout << "Enter pixel's width: ";
    if (!(cin >> cols) || cols <= 0 || cols > 20)
    {
        cout << "Something went wrong!" << endl;
        return 1;
    }

    int **image = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        image[i] = new int[cols];
    }

    cout << "Enter brightness: " << endl;
    char pixel;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (!(cin >> pixel) || pixel > '9' || pixel < '0')
            {
                for (int k = 0; k < rows; k++)
                {
                    delete[] image[k];
                    image[k] = nullptr;
                }
                delete[] image;
                image = nullptr;
                cout << "Error!" << endl;
                return 1;
            }
            image[i][j] = pixel - '0';
        }
    }
//menu
    int option;
    do
    {
        cout << "\n == Your Menu == " << endl;
        cout << "1 - Show the Image" << endl;
        cout << "2 - Brightness statistics" << endl;
        cout << "3 - Invert Brightness" << endl;
        cout << "4 - Mirror horizontal" << endl;
        cout << "5 - Turn the Image for 90" << endl;
        cout << "0 - Leave the Menu" << endl;
        cout << "Enter Your option: ";

        if (!(cin >> option) || option < 0 || option > 5)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Something went wrong! Try again." << endl;
            option = -1;
            if (cin.eof())
            {
                break;
            }
            continue;
        }

        bool extraInput = false;
        char rest;
        while (cin.get(rest) && rest != '\n')
        {
            if (rest != ' ' && rest != '\t' && rest != '\r')
            {
                extraInput = true;
            }
        }
        if (extraInput)
        {
            cout << "Something went wrong! Try again." << endl;
            option = -1;
            continue;
        }

        switch (option)
        {
            case 1:
                List(rows, cols, image);
                break;
            case 2:
                statisticsBrightness(image, rows, cols);
                break;
            case 3:
                invertBrightness(image, rows, cols);
                break;
            case 4:
                mirror(image, rows, cols);
                break;
            case 5:
            {
                image = rotateRight(image, rows, cols);
                int temp = rows;
                rows = cols;
                cols = temp;
                cout << "Image is turned! New sizes: " << rows << " x " << cols << endl;
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        cout << image[i][j] << " ";
                    }
                    cout << endl;
                }
                break;
            }
            case 0:
                break;
        }
    } while (option != 0);

    for (int i = 0; i < rows; i++)
    {
        delete[] image[i];
        image[i] = nullptr;
    }
    delete[] image;
    image = nullptr;
    return 0;
}
//option1
void List(int rows, int cols, int **image)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j];
            if (j < cols - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << "Image: " << endl;
    const char picture[] = " .:-=+*#%@";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << picture[image[i][j]];
        }
        cout << endl;
    }
    cout << "Size: " << rows << "x" << cols << endl;
}

//option 2
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    int min = *image[0];
    int max = *image[0];
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    for (int i = 0; i < rows; i++)
    {
        int *row = image[i];
        for (int j = 0; j < cols; j++)
        {
            if (min > *(row + j))
            {
                min = *(row + j);
                minRow = i;
                minCol = j;
            }
            if (max < *(row + j))
            {
                max = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void statisticsBrightness(int **image, int rows, int cols)
{
    int minRow;
    int minCol;
    int maxCol;
    int maxRow;
    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "The Darkest pixel: " << *(image[minRow] + minCol) << " (Row: " << minRow + 1 << ", Col: " << minCol + 1 << ")" << endl;
    cout << "The Brightest pixel: " << *(image[maxRow] + maxCol) << " (Row: " << maxRow + 1 << ", Col: " << maxCol + 1 << ")" << endl;
    int totalSum = 0;
    double rowAverages[20];
    for (int i = 0; i < rows; i++)
    {
        int rowsum = 0;
        int *row = image[i];
        for (int j = 0; j < cols; j++)
        {
            rowsum += *(row + j);
        }
        totalSum += rowsum;
        double rowav = static_cast<double>(rowsum) / cols;
        rowAverages[i] = rowav;
    }
    double totalav = static_cast<double>(totalSum) / (rows * cols);
    cout << "Average Brightness: " << fixed << setprecision(2) << totalav << endl;
    cout << "Average Brightness by rows: " << fixed << setprecision(1);
    for (int i = 0; i < rows; i++)
    {
        if (i > 0)
        {
            cout << " ";
        }
        cout << rowAverages[i];
    }
    cout << endl;
}

void invertBrightness(int **image, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            image[i][j] = 9 - image[i][j];
        }
    }
    cout << "Brightness has been inverted!" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (j > 0)
            {
                cout << " ";
            }
            cout << image[i][j];
        }
        cout << endl;
    }
}

void swapPixels(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mirror(int **image, int rows, int cols)
{
    cout << "Image is mirrored!" << endl;
    cout << "Original: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols / 2; j++)
        {
            swapPixels(&image[i][j], &image[i][cols - 1 - j]);
        }
    }
    cout << "Mirrored: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j];
        }
        cout << endl;
    }
}

int** rotateRight(int **image, int rows, int cols)
{
    int** newImage = new int*[cols];
    for (int i = 0; i < cols; i++)
    {
        newImage[i] = new int[rows];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            newImage[j][rows - 1 - i] = image[i][j];
        }
    }
    for (int i = 0; i < rows; i++)
    {
        delete[] image[i];
        image[i] = nullptr;
    }
    delete[] image;
    image = nullptr;
    return newImage;
}

