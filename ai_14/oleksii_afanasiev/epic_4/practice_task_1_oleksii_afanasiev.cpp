/*
Задача: Редактор монохромного зображення
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_ROWS = 100;
const int MAX_COLS = 100;
const string color_scheme = " .:-=+*#%@";

// Прототипи функцій
void showMatrix(int **img, int rows, int cols);
void showMenu();
void showImage(int **img, int height, int width);
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void findAverages(int **img, int rows, int cols, float &average, float *rowAverage);
void showBrightnessStats(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol, float &average, float *rowAverage);
void invertBrightness(int **img, int rows, int cols);
void swapPixels(int *a, int *b);
void mirrorHorizontally(int **img, int rows, int cols);
int** rotateRight(int** img, int rows, int cols);

int main() 
    {
        cout << fixed << setprecision(2); // Виведення у форматі 2 цифр після коми

        int rows, cols;

        //Введення і валідація необхідних змінних. При помилці вводу - програма припиняє роботу
        cout << "Image height: ";
        if(!(cin >> rows) || rows < 1 || rows > 20)
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Error: you must enter a number in the range from 1 to 20" << endl;
            return 1;
        }

        cout << "Image width: ";
        if(!(cin >> cols) || cols < 1 || cols > 20)
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Error: you must enter a number in the range from 1 to 20" << endl;
            return 1;
        }

        //Ініціалізація динамічної матриці
        int **image = new int *[rows];
        for(int i = 0; i < rows; i++)
        {
            image[i] = new int[cols];
        }

        cout << "Pixels brightness (0..9):" << endl;

        //Введення значень яскравості пікселей зображення, валідація
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if( !(cin >> image[i][j]) || image[i][j] < 0 || image[i][j] > 9)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    for(int k = 0; k < rows; k++) delete[] image[k];
                    delete[] image;

                    cout << "Error: you must enter numbers in the range from 0 to 9";
                    
                    return 1;
                }
            }
        }

        int choice = -1;

        //Показ інтерфейсу меню
        do
        {
            showMenu();

            // Введення бажаної операції, її валідація
            cout << "Enter your operation: ";
            if(!(cin >> choice))
            {
                cin.clear();
                cin.ignore(10000, '\n');

                cout << "Error: wrong operation selected";
                choice = -1;

                continue;
            }

            cout << endl;

            switch (choice)
            {
                case 1: //Показ зображення
                    showImage(image, rows, cols);
                    break;
                case 2: //Статистика яскравості
                {
                    int minRow, maxRow, minCol, maxCol;
                    float average;
                    float *rowAverage = new float[rows];

                    showBrightnessStats(image, rows, cols, minRow, minCol, maxRow, maxCol, average, rowAverage);

                    delete[] rowAverage;
                    break;
                }
                case 3: //Інвертувати яскравість
                    invertBrightness(image, rows, cols);
                    break;
                case 4: //Відзеркалити по горизонталі
                    mirrorHorizontally(image, rows, cols);
                    break;
                case 5: //Повернути на 90 градусів праворуч
                {
                    image = rotateRight(image, rows, cols);
                    int t = rows;
                    rows = cols;
                    cols = t;
                    break;
                }
                case 0: //Вихід з програми
                    cout << "Exit..." << endl;
                    break;

                default:
                    cout << "Unknown operation selected";
                    continue;
            }
        }
        while(choice != 0);

        for(int i = 0; i < rows; i++)
        {
            delete[] image[i];
        }

        delete[] image;
        
        return 0;
    }

void showMatrix(int **img, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cout << img[i][j] << " ";
        }
        cout << endl;
    } 
}

void showMenu()
{
    cout << endl;
    cout << left << setw(3) << "1" << right << setw(40) << "Show image" << endl;
    cout << left << setw(3) << "2" << right << setw(40) << "Brightness statistics" << endl;
    cout << left << setw(3) << "3" << right << setw(40) << "Invert brightness" << endl;
    cout << left << setw(3) << "4" << right << setw(40) << "Mirror horizontally" << endl;
    cout << left << setw(3) << "5" << right << setw(40) << "Rotate 90 degrees clockwise" << endl;
    cout << left << setw(3) << "0" << right << setw(40) << "Exit" << endl;
}

void showImage(int **img, int height, int width)
{
    cout << "Image " << height << " x " << width << ":" << endl;
    showMatrix(img, height, width);

    cout << endl;

    cout << "Picture:" << endl;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            cout << color_scheme[ img[i][j] ];
        }
        cout << endl;
    } 
    
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    int max = -1;
    int min = 10;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            int *row = img[i];
            if(*(row + j) > max)
            {
                max = *(row + j);
                maxRow = i;
                maxCol = j;
            }
            if(*(row + j) < min)
            {
                min = *(row + j);
                minRow = i;
                minCol = j;
            }
        }
    }
}

void findAverages(int **img, int rows, int cols, float &average, float *rowAverage)
{
    int sum = 0;
    for(int i = 0; i < rows; i++)
    {
        int row_sum = 0;
        int *row = img[i];

        for(int j = 0; j < cols; j++)
        {
            row_sum += *(row + j);
        }
        *(rowAverage + i) = row_sum / (float)(cols);
        sum += row_sum;
    }

    average = sum / (float)(rows * cols);

}

void showBrightnessStats(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol, float &average, float *rowAverage)
{
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    findAverages(img, rows, cols, average, rowAverage);

    cout << "Darkest pixel: " << img[minRow][minCol] << "(row " << minRow + 1 <<", column " << minCol + 1 << ")" << endl;
    cout << "Brightest pixel: " << img[maxRow][maxCol] << "(row " << maxRow + 1<<", column " << maxCol + 1<< ")" << endl;
    cout << "Average brightness: " << average << endl;
    cout << "Average by rows: ";
    
    for(int i = 0; i < rows; i++)
    {
        cout << rowAverage[i] << " ";
    }
    
    cout << endl;
}

void invertBrightness(int **img, int rows, int cols)
{

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            img[i][j] = 9 - img[i][j];
        }
    }

    cout << "Brightness was inverted." << endl;
    showMatrix(img, rows, cols);
}

void swapPixels(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void mirrorHorizontally(int **img, int rows, int cols)
{
    cout << "Image was mirrored" << endl;
    cout << "Original:" << endl;
    showMatrix(img, rows, cols);

    for(int j = 0; j < cols / 2; j++)
    {
        for(int i = 0; i < rows; i++)
        {
            swapPixels( *(img + i) + j, *(img + i) + (cols - 1 - j) );
        }
    }

    cout << endl;
    cout << "Result:" << endl;
    showMatrix(img, rows, cols);
}

int** rotateRight(int** img, int rows, int cols)
{
    int** img_new = new int*[cols];
    for(int i = 0; i < cols; i++)
    {
        img_new[i] = new int[rows];
        
        for(int j = 0; j < rows; j++)
        {
            img_new[i][j] = img[rows - j - 1][i];
        }
    }

    for(int i = 0; i < rows; i++)
    {
        delete[] img[i];
    }

    delete[] img;

    img = img_new;

    cout << "Image was rotated. New shape: " << cols << " x " << rows << endl;
    showMatrix(img, cols, rows);

    return img;

}
