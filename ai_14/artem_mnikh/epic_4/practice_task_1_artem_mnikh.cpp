/* Редактор монохромного зображення
Artem Mnikh
AI_14
*/

#include <iomanip>
#include <iostream>

using namespace std;

void showMatrix(int** a, int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << a[i][j] << " ";
        }
        cout << '\n';
    }
}

void showImage(int** a, int rows, int cols)
{
    cout << "Зображення " << rows << " x " << cols << ":\n";
    showMatrix(a, rows, cols);

    const char brightness[] = " .:-=+*#%@";
    cout << '\n' << "Малюнок: " << '\n';
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << brightness[a[i][j]];
        }
        cout << '\n';
    }
}

void findExtremes(int** img, int rows, int cols, int& minRow, int& minCol, int& maxRow, int& maxCol)
{
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (img[i][j] < img[minRow][minCol])
            {
                minRow = i;
                minCol = j;
            }
            if (img[i][j] > img[maxRow][maxCol])
            {
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void showStats(int** a, int rows, int cols)
{
    int minRow, minCol, maxRow, maxCol;
    findExtremes(a, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "Найтемніший піксель: " << a[minRow][minCol] << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1
         << ")\n";
    cout << "Найсвітліший піксель: " << a[maxRow][maxCol] << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1
         << ")\n";
    int sum = 0;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            sum += a[i][j];
        }
    }
    cout << fixed << setprecision(2) << "Середня яскравість: " << sum * 1.0 / (rows * cols) << '\n';
    cout << fixed << setprecision(1) << "Середня по рядках: ";
    for (int i = 0; i < rows; ++i)
    {
        int* row = a[i];
        int sum_of_row = 0;
        for (int j = 0; j < cols; ++j)
        {
            sum_of_row += *(row + j);
        }
        cout << sum_of_row * 1.0 / cols << " ";
    }
    cout << '\n';
}

void invertBrightness(int** a, int rows, int cols)
{
    cout << "Яскравість інвертовано." << '\n';
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            a[i][j] = 9 - a[i][j];
        }
    }
    showMatrix(a, rows, cols);
}

void swapPixels(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reflectImage(int** a, int rows, int cols)
{
    cout << "Зображення віддзеркалено.\nПочаткове: \n";
    showMatrix(a, rows, cols);
    cout << "\nРезультат:\n";
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols / 2; ++j)
        {
            swapPixels(&a[i][j], &a[i][cols - j - 1]);
        }
    }
    showMatrix(a, rows, cols);
}

int** rotateRight(int** a, int& rows, int& cols)
{
    int** temp_pointer = new int*[cols];
    for (int i = 0; i < cols; ++i)
    {
        temp_pointer[i] = new int[rows];
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            temp_pointer[j][rows - 1 - i] = a[i][j];
        }
    }

    for (int i = 0; i < rows; ++i) delete[] a[i];
    delete[] a;

    swapPixels(&rows, &cols);

    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << ":\n";
    showMatrix(temp_pointer, rows, cols);
    return temp_pointer;
}

int main()
{
    int r, c;
    cout << "Висота зображення: ";
    while (!(cin >> r) || r <= 0 || r > 100)
    {
        cout << "Введіть число в межах (0, 100]" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Ширина зображення: ";
    while (!(cin >> c) || c <= 0 || c > 100)
    {
        cout << "Введіть число в межах (0, 100]" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    int** matrix = new int*[r];
    for (int i = 0; i < r; ++i) matrix[i] = new int[c];

    cout << "Яскравість пікселів (0..9):" << '\n';
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            while (!(cin >> matrix[i][j]) || matrix[i][j] < 0 || matrix[i][j] > 9)
            {
                cout << "Введіть число від 0 до 9" << '\n';
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }
    bool isActive = true;
    int userInput;
    do
    {
        cout << "========== Меню ==========" << '\n';
        cout << "1 - Показати зображення" << '\n';
        cout << "2 - Статистика яскравості" << '\n';
        cout << "3 - Інвертувати яскравість" << '\n';
        cout << "4 - Відзеркалити по горизонталі" << '\n';
        cout << "5 - Повернути на 90 градусів праворуч" << '\n';
        cout << "0 - Вийти" << '\n';
        while (!(cin >> userInput) || userInput < 0 || userInput > 5)
        {
            cout << "Введіть число від 0 до 5" << '\n';
            cin.clear();
            cin.ignore(10000, '\n');
        }
        switch (userInput)
        {
            case 1:
            {
                showImage(matrix, r, c);
                break;
            }
            case 2:
            {
                showStats(matrix, r, c);
                break;
            }
            case 3:
                invertBrightness(matrix, r, c);
                break;
            case 4:
                reflectImage(matrix, r, c);
                break;
            case 5:
                matrix = rotateRight(matrix, r, c);
                break;
            case 0:
                isActive = false;
                break;
            default:
                cout << "Введіть ще раз." << '\n';
        }
    } while (isActive);
    for (int i = 0; i < r; ++i) delete[] matrix[i];
    delete[] matrix;
}