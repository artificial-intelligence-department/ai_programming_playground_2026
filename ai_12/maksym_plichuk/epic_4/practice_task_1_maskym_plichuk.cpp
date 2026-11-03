#include <iostream>
using namespace std;

void printImage(int **img, int rows, int cols)
{
    cout << "Зображення: " << rows << " x " << cols << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nМалюнок: " << endl;
    char pallete[] = " .:-=+*#%@";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << pallete[img[i][j]];
        }
        cout << endl;
    }
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    int min = **img;
    int max = **img;
    for (int i = 0; i < rows; i++)
    {
        int *row = *(img + i);
        for (int j = 0; j < cols; j++)
        {
            if (*(row + j) < min)
            {
                min = *(row + j);
                minRow = i;
                minCol = j;
            }
            if (*(row + j) > max)
            {
                max = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void brightnessStats(int **img, int rows, int cols)
{
    int minRow = 0;
    int maxRow = 0;
    int minCol = 0;
    int maxCol = 0;

    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    double *avgByRows = new double[rows];
    int total = 0;

    for (int i = 0; i < rows; i++)
    {
        int *row = *(img + i);
        int rowTotal = 0;
        for (int j = 0; j < cols; j++)
        {
            rowTotal += *(row + j);
        }
        total += rowTotal;
        avgByRows[i] = (double) rowTotal / cols;
    }
    cout << "Найтемніший піксель: " << img[minRow][minCol] << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol] << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
    cout << "Середня яскравість: " << (double) total / (rows*cols) << endl;
    cout << "Середня по рядках: ";
    
    for (int i = 0; i < rows; i++) {
        cout << avgByRows[i] << " ";
    }
    cout << endl;

    delete[] avgByRows;
}

void invertImage(int **img, int rows, int cols)
{
    cout << "Яскравість інвертовано." << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            img[i][j] = 9 - img[i][j];
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

void swapPixels(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void mirrorHorizontaly(int** img, int rows, int cols) { 
    cout << "Зображення віддзеркалено." << endl;

    cout << "Початкове:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - j - 1]);
        }
    }

    cout << "\nРезультат:" << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    
 }

int** rotateRight(int** img, int rows, int cols) {
    int **newImg = new int *[cols];
    for (int i = 0; i < cols; i++)
    {
        newImg[i] = new int[rows];
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newImg[j][rows - i - 1] = img[i][j];
        }
    }
    
    for (int i = 0; i < rows; i++) {
            delete[] img[i];
    }
    delete[] img;
    img = nullptr;
    return newImg;
}
void turn90Deg(int** &img, int& rows, int& cols) {
    img = rotateRight(img, rows, cols);

    int temp = cols;
    cols = rows;
    rows = temp;
    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int rows, cols;
    cout << "Висота зображення: ";
    if (!(cin >> rows) || rows < 1 || rows > 20)
    {
        cout << "Неправильна висота!" << endl;
        return 1;
    }

    cout << "Ширина зображення: ";
    if (!(cin >> cols) || cols < 1 || cols > 20)
    {
        cout << "Неправильна ширина!" << endl;
        return 1;
    }

    int **image = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        image[i] = new int[cols];
    }

    bool isValid = true;

    cout << "Яскравість пікселів (0..9): " << endl;
    for (int i = 0; i < rows && isValid; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (!(cin >> image[i][j]) || image[i][j] < 0 || image[i][j] > 9)
            {
                cout << "Неправильний піксель (0-9)!" << endl;
                isValid = false;
                break;
            }
        }
    }

    if (!isValid)
    {
        for (int i = 0; i < rows; i++) {
            delete[] image[i];
        }
        delete[] image;
        image = nullptr;
        return 1;
    }

    int input_choice;
    do
    {
        while (true)
        {
            cout << "\n====Меню====" << endl;
            cout << "1. Показати зображення" << endl;
            cout << "2. Статистика яскравості" << endl;
            cout << "3. Інвертувати яскравість" << endl;
            cout << "4. Віддзеркалити по горизонталі" << endl;
            cout << "5. Повернути на 90 градусів праворуч" << endl;
            cout << "0. Вийти" << endl;
            cout << "Введіть пункт меню: ";

            if (!(cin >> input_choice) || input_choice < 0 || input_choice > 5)
            {
                cout << "\n\tНеправильний пункт меню!" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else {
                cout << endl;
                break;
            }
            
        }

        switch (input_choice)
        {
        case 1:
            printImage(image, rows, cols);
            break;
        case 2:
            brightnessStats(image, rows, cols);
            break;
        case 3:
            invertImage(image, rows, cols);
            break;
        case 4:
            mirrorHorizontaly(image, rows, cols);
            break;
        case 5:
            turn90Deg(image, rows, cols);
            break;
        case 0:
            cout << "Вихід..." << endl;
            break;
        default:
            break;
        }

    } while (input_choice != 0);

    for (int i = 0; i < rows; i++) {
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;
    return 0;
}