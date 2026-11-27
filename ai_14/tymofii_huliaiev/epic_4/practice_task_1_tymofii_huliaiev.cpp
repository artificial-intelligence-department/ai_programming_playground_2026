#include <iostream>
using namespace std;

    void showImage(int **image, int rows, int cols)
    {
        cout << "Таблиця чисел: \n";
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                cout << image[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\nЗображення:\n";

        for(int i = 0; i < rows; ++i)
            {
                for(int j = 0; j < cols; ++j)
                {
                    char symbol = ' ';
                    switch (image[i][j])
                    {
                        case 0:
                        symbol = ' ';
                        break;
                        case 1:
                        symbol = '.';
                        break;
                        case 2:
                        symbol = ':';
                        break;
                        case 3:
                        symbol = '-';
                        break;
                        case 4:
                        symbol = '=';
                        break;
                        case 5:
                        symbol = '+';
                        break;
                        case 6:
                        symbol = '*';
                        break;
                        case 7:
                        symbol = '#';
                        break;
                        case 8:
                        symbol = '%';
                        break;
                        case 9:
                        symbol = '@';
                        break;
                    }
                    cout << symbol << " ";
                }
                cout << "\n";
            }
        cout << "\nРозмір зображення: рядків - " << rows << ", стовбців - " << cols << "\n";
    }       








    void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
    {
        int minValue = img[0][0];
        int maxValue = img[0][0];
            minRow = 1;
            minCol = 1;
            maxRow = 1;
            maxCol = 1;

            for(int i = 0; i < rows; ++i)
            {
                int *row = img[i];
                for(int j = 0; j < cols; ++j)
                {
                    int val = *(row + j);

                    if (val < minValue)
                    {
                        minValue = val;
                        minRow = i + 1;
                        minCol = j +1;
                    }

                    if (val > maxValue)
                    {
                        maxValue = val;
                        maxRow = i + 1;
                        maxCol = j + 1;
                    }
                }
            }
            cout << "\nНайтемніший піксель: " << minRow << " рядок " << minCol << " стовбець";
            cout << "\nНайсвітліший піксель: " << maxRow << " рядок " << maxCol << " стовбець";
    }








    void calculateAverages(int **img, int rows, int cols)
    {
        int matSize = rows * cols;
        int matSum = 0;
        for(int i = 0; i < rows; ++i)
        {
            int *row = img[i];
                for(int j = 0; j < cols; ++j)
                {
                    int val = *(row + j);
                    matSum = matSum + val;
                }
        }   
        double totalAverage = (matSum * 1.0) / matSize;

        double rowSum = 0;
        double rowAverage = 0;
        for(int i = 0; i < rows; ++i)
        {
            int *row = img[i];
                for(int j = 0; j < cols; ++j)
                {
                    int val = *(row + j);
                    rowSum = rowSum + val;
                }
                rowAverage = (rowSum * 1.0) / (cols * 1.0); 
                
            cout << "\nСередня яскравість " << i + 1 << " рядку матриці: " << rowAverage;
            rowSum = 0;
            rowAverage = 0;
        }   
        cout << "\nСередня яскравість матриці: " << totalAverage;
    }

    void invertBright(int **img, int rows, int cols)
    {
        for(int i = 0; i < rows; ++i)
        {
            int *row = img[i];
                for(int j = 0; j < cols; ++j)
                {
                    *(row + j) = 9 - *(row + j);
                }
        }  
        cout << "Оновлена матриця: \n";
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                cout << img[i][j] << " ";
            }
            cout << "\n";
        }
    }






    void swapPixels(int *a, int *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void flipHorizontal(int **img, int rows, int cols)
    {
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols / 2; ++j)
            {
                swapPixels (&img[i][j], &img[i][cols - j - 1]);
            }
        }
        cout << "Оновлена матриця: \n";
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                cout << img[i][j] << " ";
            }
            cout << "\n";
        }
    }






    int** rotateRight(int **img, int rows, int cols)
    {
        int newRows = cols;
        int newCols = rows;

        int **rotated = new int*[newRows];
        for(int i = 0; i < newRows; ++i)
        {
            rotated[i] = new int[newCols];
        }

        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                rotated[j][rows - 1 - i] = img[i][j];
            }
        }

        for(int i = 0; i < rows; ++i)
        {
            delete[] img[i];
        }
        delete[] img;

       return rotated;
    }











int main()
{
    int rows;
    int cols;
    int choice;
    int **image = nullptr;

    cout << "Введіть висоту зображення(від 1 до 20): \n";
    if(!(cin >> rows) || rows > 20 || rows < 1) 
    {
        cout << "Помилка!";
        return 1;
    }

    cout << "Введіть ширину зображення(від 1 до 20): \n";
    if(!(cin >> cols) || cols > 20 || cols < 1)
    {
        cout << "Помилка!";
        return 1;
    }

    image = new int*[rows];
        for(int i = 0; i < rows; ++i)
        {
            image[i] = new int[cols];
        }

        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                cout << "Введіть яскравість пікселя " << i + 1 << " рядку " << j + 1 << " стовбцю(від 0 до 9): \n";
                if (!(cin >> image[i][j]) || image[i][j] < 0 || image[i][j] > 9)
                {
                cout << "Помилка!";
                for(int r = 0; r < rows; ++r)
                {
                    delete[] image[r];
                }
                delete[] image;
                image = nullptr;
                return 1;
                }
            }
        }
    do
    {
        cout << "\nМЕНЮ\n";
        cout << "1) Показати зображення\n";
        cout << "2) Статистика яскравості\n";
        cout << "3) Інвертувати яскравість\n";
        cout << "4) Віддзеркалити по горизонталі\n";
        cout << "5) Повернути на 90 градусів праворуч\n";
        cout << "0) Вийти\n";
        cout << "Введіть ваш вибір: ";
        if(!(cin >> choice) || choice < 0 || choice > 5) 
        {
        cout << "Помилка!";
        return 1;
        }
        switch(choice)
    {
        case 1:
            cout << "\n";
            showImage(image, rows, cols);
            break;
        case 2:
        {
            int minRow = 1;
            int minCol = 1;
            int maxRow = 1;
            int maxCol = 1;
            findExtremes(image, rows, cols, minRow, minCol,maxRow, maxCol);
            calculateAverages(image, rows, cols);
            break;
        }
        case 3:
        invertBright(image, rows, cols);
        break;
        case 4:
        flipHorizontal(image, rows, cols);
        break;
        case 5:
        {
        image = rotateRight(image, rows, cols);
        int temp = rows;
        rows = cols;
        cols = temp;
        break;
        }
        case 0:
        break;
        default:
        cout << "Помилка!";
    }

    }
    while (choice != 0);

    for(int i = 0; i < rows; ++i)
    {
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;

    return 0;







}