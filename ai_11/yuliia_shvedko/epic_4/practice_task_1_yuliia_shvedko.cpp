/*Редактор монохромного зображення
Група: ШІ-11
Автор: Шведько Юлія*/

#include <iostream>
#include <iomanip>
using namespace std;

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void swapPixels(int *a, int *b);
int** rotateRight(int** img, int rows, int cols);

int main()
{
    int rows;
    int cols;
    cout << "Висота зображення: ";
    cin >> rows;
    if(rows < 1 || rows > 20 || cin.fail())
    {
        cout << "Висота зображення має бути від 1 до 20 пікселів!" << endl;
        return 1;
    }
    cout << "Ширина зображення: ";
    cin >> cols;
    if(cols < 1 || cols > 20 || cin.fail())
    {
        cout << "Ширина зображення має бути від 1 до 20 пікселів!" << endl;
        return 1;
    }
    int **image = new int*[rows];
    for(int i = 0; i < rows; i++)
    image[i] = new int[cols];
    cout << "Яскравість пікселів (0...9): " << endl;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cin >> image[i][j];
            if(image[i][j] < 0 || image[i][j] > 9 || cin.fail())
            {
                cout << "Яскравість пікселя має бути від 0 до 9!" << endl;
                for(int n = 0; n < rows; n++)
                delete[] image[n];
                delete[] image;
                image = nullptr;
                return 1;
            }
        }
    }
    int c;
    do
    {
        cout << endl;
        cout << "Меню: " << endl;
        cout << "1 - Показати зображення" << endl;
        cout << "2 - Статистика яскравості" << endl;
        cout << "3 - Інвертувати яскравість" << endl;
        cout << "4 - Віддзеркалити по горизонталі" << endl;
        cout << "5 - Повернути на 90 градусів праворуч" << endl;
        cout << "0 - Вийти" << endl;
        cout << endl;
        do
        {
            cin.clear();
            cin.ignore();
            cout << "Ваш вибір: ";
            cin >> c;
            if(cin.fail())
            cout << "Виберіть пункт від 0 до 5!" << endl;
            cout << endl;
        }
        while(cin.fail());
        switch(c)
        {
            case 1:
            cout << endl;
            cout << "Зображення: " << rows << " x " << cols << endl;
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    cout << image[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            cout << "Малюнок: " << endl;
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    if(image[i][j] == 0)
                    cout << " ";
                    if(image[i][j] == 1)
                    cout << ".";
                    if(image[i][j] == 2)
                    cout << ":";
                    if(image[i][j] == 3)
                    cout << "-";
                    if(image[i][j] == 4)
                    cout << "=";
                    if(image[i][j] == 5)
                    cout << "+";
                    if(image[i][j] == 6)
                    cout << "*";
                    if(image[i][j] == 7)
                    cout << "#";
                    if(image[i][j] == 8)
                    cout << "%";
                    if(image[i][j] == 9)
                    cout << "@";
                }
                cout << endl;
            }
            cout << endl;
            break;

            case 2:
            {
                cout << endl;
                int minRow = 0;
                int minCol = 0;
                int maxRow = 0;
                int maxCol = 0;
                findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);//Знаходить координати найсвітлішого і найтемнішого пікселя
                int min = *(image[minRow] + minCol);
                int max = *(image[maxRow] + maxCol);
                cout << "Найтемніший піксель: " << min << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
                cout << "Найсвітліший піксель: " << max << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
                double avg = 0;
                double *rowAvg = new double[rows];
                double sum = 0;
                double rowSum = 0;

                for(int i = 0; i < rows; i++)// Шукає середнє значення по рядках
                {
                    int *row = image[i];
                    for(int j = 0; j < cols; j++)
                    {
                        sum += *(row + j);
                        rowSum += *(row + j);
                    }
                    rowAvg[i] = rowSum/cols;
                    rowSum = 0;
                }
                avg = sum/(rows*cols);
                cout << fixed << setprecision(2) << "Середня яскравість: " << avg << endl;
                cout << "Середня яскравість по рядах: ";
                for(int i = 0; i < rows; i++)
                cout << rowAvg[i] << " ";
                delete[] rowAvg;
                rowAvg = nullptr;
                cout << endl;
            }
            break;

            case 3:
            cout << endl;
            cout << "Яскравість інвертовано." << endl;
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    image[i][j] = 9 - image[i][j];
                    cout << image[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            break;

            case 4:
            cout << endl;
            cout << "Зображення відзеркалено." << endl;
            cout << "Початкове:" << endl;
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    cout << image[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            cout << "Результат:" << endl;
            for(int i = 0; i < rows; i++)
            {
                int *row = image[i];
                for(int j = 0; j < cols/2; j++)
                {
                    swapPixels((row + j), (row + cols - 1 - j));
                }
            }
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    cout << image[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            break;

            case 5:
            {
                cout << endl;
                image = rotateRight(image, rows, cols);
                int t = rows;
                rows = cols;
                cols = t;
                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < cols; j++)
                    {
                        cout << image[i][j] << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            break;

            case 0:
            cout << endl;
            for(int n = 0; n < rows; n++)
            delete[] image[n];
            delete[] image;
            image = nullptr;
            cout << "Роботу програми закінчено" << endl;
            cout << endl;
            break;

            default:
            cout << endl;
            cout << "Виберіть пункт від 0 до 5!" << endl;
            cout << endl;
            break;
        }
    }
    while(c != 0);
    return 0;
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    int *m = img[0];
    int min = *m;
    int max = *m; 
    for(int i = 0; i < rows; i++)
    {
        int *row = img[i];
        for(int j = 0; j < cols; j++)
        {
            int pixel = *(row + j);
            if(pixel < min)
            {
                min = pixel;
                minRow = i;
                minCol = j;
            }
            if(pixel > max)
            {
                max = pixel;
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void swapPixels(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int** rotateRight(int** img, int rows, int cols)
{
    int **rotated = new int*[cols];
    for(int j = 0; j < cols; j++)
    {
        rotated[j] = new int[rows];
        for(int i = 0; i < rows; i++)
        *(rotated[j] + (rows - 1 - i)) = *(img[i] + j);
    }

    for(int i = 0; i < rows; i++)
    delete[] img[i];
    delete[] img;
    img = nullptr;

    return rotated;
}