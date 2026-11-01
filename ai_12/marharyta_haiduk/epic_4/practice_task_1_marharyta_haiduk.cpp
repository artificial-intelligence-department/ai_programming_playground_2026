/*
    Задача: Редактор монохромного зображення
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
#include <iomanip>
using namespace std;
//Вивід матриці
void printMatrix(int **image, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}
//Вивід яскравості зоображення
void printImage(int**image, int rows, int cols)
{
    const char palette[] = " .:-=+*#%@";
    cout << "Зображення " << rows << " x " << cols <<":"<<endl;
    printMatrix(image, rows, cols);
    cout << "Малюнок:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << palette[image[i][j]];
        }
        cout << endl;
    }
}
//Пошук найтемніших і найсвітліших пікселів разом з їхніми координатами
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    int *first = image[0];
    int minV = *first; 
    int maxV = *first; 
    minRow = 0; 
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    for (int i = 0; i < rows; i++)
    {
        int *row = image[i]; 
        for (int j = 0; j < cols; j++)
        {
            int value = *(row + j); 
            if (value < minV)
            {
                minV = value; 
                minRow = i; 
                minCol = j; 
            }
            if (value > maxV)
            {
                maxV = value;
                maxRow = i;
                maxCol = j;
            }
        }
    }
}
//Статистика яскравості
void showStatistics(int **image, int rows, int cols)
{
    int minRow, minCol, maxRow, maxCol;
    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
    int *minLine = image[minRow];
    int *maxLine = image[maxRow];
    int minV = *(minLine + minCol);
    int maxV = *(maxLine + maxCol);
    cout << "Найтемніший піксель: "<< minV << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: "<< maxV << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
    int total = 0;
    for (int i = 0; i < rows; i++)
    {
        int *row = image[i];
        for (int j = 0; j < cols; j++)
        {
            total += *(row + j);
        }
    }
    double pixelCount = rows * cols;
    double average = total/ pixelCount;
    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << average << endl;
    cout << fixed << setprecision(1);
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++)
    {
        int *row = image[i];
        int totalRow = 0;
        for (int j = 0; j < cols; j++)
        {
            totalRow += *(row + j);
        } 
        double rowAverage = totalRow / (double)cols;
        cout << rowAverage << " ";
    }
    cout << endl;
}
//Інвертування яскравості
void invertImage(int **image, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            image[i][j] = 9 - image[i][j];
        }
    }
    cout << "Яскравість інвертовано." << endl;
    printMatrix(image, rows, cols);
}
//Обмін двох пікселів
void swapPixels(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
// Віддзеркалення по горизонталі
void mirrorImage(int **image, int rows, int cols)
{
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;
    printMatrix(image, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols / 2; j++)
        {
            swapPixels(&image[i][j], &image[i][cols - 1 - j]);
        }
    }
    cout << "Результат:" << endl;
    printMatrix(image, rows, cols);
}
// Поворот на 90 градусів праворуч
int** rotateRight(int **image, int rows, int cols)
{
    int **newImage = new int*[cols];
    for (int i = 0; i < cols; i++)
    {
        newImage[i] = new int[rows];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            newImage[j][rows - i - 1] = image[i][j];
        }
    }
    for (int i = 0; i < rows; i++)
    {
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;
    return newImage;
}
int main() {
    int rows;
    cout << "Введіть висоту пікселів: ";
    cin >> rows;
    if (cin.fail() || rows < 1 || rows > 20)
    {
        cout << "Помилка: висота пікселів повинна бути числом від 1 до 20." << endl;
        return 1;
    }
    int cols;
    cout << "Введіть ширину пікселів: ";
    cin >> cols;
    if (cin.fail() || cols < 1 || cols > 20)
    {
        cout << "Помилка: ширина пікселів повинна бути числом від 1 до 20." << endl;
        return 1;
    }
    int **image = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        image[i] = new int[cols];
    }
    cout << "Введіть яскравість пікселів: ";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> image[i][j];
            if (cin.fail() || image[i][j] < 0 || image[i][j] > 9)
            {
                for (int k = 0; k < rows; k++)
                {
                    delete[] image[k];
                }
                delete[] image;
                image = nullptr;
                cout << "Помилка: яскравість має бути числом від 0 до 9." << endl;
                return 1;
            } 
        }
    } 
    int choice;
    do 
    {
        cout << "1 - Показати зображення" << endl;
        cout << "2 - Статистика яскравості" << endl;
        cout << "3 - Інвертувати яскравість" << endl;
        cout << "4 - Віддзеркалити по горизонталі" << endl;
        cout << "5 - Повернути на 90 градусів праворуч" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Оберіть пункт: ";
        cin >> choice;
        while (cin.fail() || choice < 0 || choice > 5)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка: потрібно ввести число від 0 до 5." << endl;
            cout << "Оберіть пункт: ";
            cin >> choice;
        }
        switch (choice)
        {
            case 1: printImage(image, rows, cols); break;
            case 2: showStatistics(image, rows, cols); break;
            case 3: invertImage(image, rows, cols); break;
            case 4: mirrorImage(image, rows, cols); break;
            case 5: 
            {
                image = rotateRight(image, rows, cols);
                swapPixels(&rows, &cols);
                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
                printMatrix(image, rows, cols);
                break;
            }
        }
    } while(choice != 0);
    for (int i = 0; i < rows; i++)
    {
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;
    return 0;
}