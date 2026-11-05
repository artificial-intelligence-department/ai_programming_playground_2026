/*
Редактор монохромного зображення
Шмигельський Владислав
ШІ-12
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void deleteimage(int **&image, int rows) // передаємо оригінальний image
{

    if (image == nullptr)
        return;
    for (int i = 0; i < rows; i++)
    {

        delete[] image[i]; // Звільнення пам'яті i рядка
    }
    delete[] image; // звільнення масиву вказівників
    image = nullptr;
}
int **rotateRight(int **image, int rows, int cols)
{
    int **rotateimage = new int *[cols]; // створюємо масив вказівників довжиною cols
    for (int i = 0; i < cols; i++)
    {
        rotateimage[i] = new int[rows];
    }

    for (int i = 0; i < rows; i++) // Перевертаємо малюнок на 90 градусів
    {
        for (int j = 0; j < cols; j++)
        {
            rotateimage[j][rows - 1 - i] = image[i][j]; // Рядки і стовпці міняються місцями
        }
    }
    deleteimage(image, rows); //очищаємо пам'ять

    return rotateimage;
}
void swapPixels(int *a, int *b)
{
    int copy = *a;
    *a = *b;
    *b = copy;
}
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol, int &maxVal, int &minVal)
{
    minVal = image[0][0];
    minRow = 0;
    minCol = 0;

    maxVal = image[0][0];
    maxRow = 0;
    maxCol = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Перевірка на новий мінімум
            if (image[i][j] < minVal)
            {
                minVal = image[i][j];
                minRow = i;
                minCol = j;
            }

            // Перевірка на новий максимум
            if (image[i][j] > maxVal)
            {
                maxVal = image[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }
}
char brightness(int convert)
{
    char symbolBrightness[10]{' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};
    return symbolBrightness[convert];
}

double averageVal(int rows, int cols, int **image, double rowAverage[])
{
    double sum = 0;
    for (int i = 0; i < rows; i++)
    {
        int *row = image[i]; // Вказівник на початок i-го рядка
        double rowsSum = 0;

        for (int j = 0; j < cols; j++)
        {
            rowsSum += *(row + j); // Звернення через вказівник замість image[i][j]
        }
        sum += rowsSum;
        rowAverage[i] = rowsSum / cols;
    }
    return sum / (rows * cols);
}

void menu(int &option)
{ // функція для виводу меню
    cout << left << setw(12) << "Пункт" << "     Операція" << endl
         << endl;
    cout << left << setw(12) << "1" << "Показати зображення" << endl;
    cout << left << setw(12) << "2" << "Статистика яскравості" << endl;
    cout << left << setw(12) << "3" << "Інвертувати яскравість" << endl;
    cout << left << setw(12) << "4" << "Віддзеркалити по горизонталі" << endl;
    cout << left << setw(12) << "5" << "Повернути на 90 градусів праворуч" << endl;
    cout << left << setw(12) << "0" << "Вийти" << endl;
    cout << "Вибір: ";
    cin >> option;
    if (cin.fail()) // валідація
    {
        cin.clear();
        cin.ignore(10000, '\n');
        option = 6;
    }
}

void case1(int cols, int rows, int **image)
{
    cout << "Зображення " << rows << " x " << cols << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Малюнок:" << endl;

    for (int i = 0; i < rows; i++)
    {

        for (int j = 0; j < cols; j++)
        {
            cout << brightness(image[i][j]); // викликаємо функцію і кожен елемент ясравості міняємо на символ
        }
        cout << endl;
    }
}

void case2(int cols, int rows, int **image)
{
    int minRow, minCol, maxRow, maxCol, maxVal, minVal;
    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol, maxVal, minVal);
    double* rowAverage = new double[rows];
    double average = averageVal(rows, cols, image, rowAverage);
    cout << "Найтемніший піксель: " << minVal << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << maxVal << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
    cout << "Середня яскравість: " << fixed << setprecision(2) << (double)average << endl;
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++)
    {
        cout << fixed << setprecision(1) << (double)rowAverage[i] << " ";
    }
    cout << endl;
    delete[] rowAverage;
}
void case3(int cols, int rows, int **image)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            image[i][j] = abs(image[i][j] - 9); //Кожен піксель замінюється на різницю між девʼяткою та його значенням
        }
    }
    cout << "Яскравість інвертовано." << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

void case4(int cols, int rows, int **image)
{
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols / 2; j++) // Віддзеркалюємо до середини рядка
        {
            swapPixels(&image[i][j], &image[i][cols - 1 - j]);
        }
    }

    cout << "Результат:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j] << " ";     
        }
        cout << endl;
    }
}
void case5(int &cols, int &rows, int **&image)
{
    image = rotateRight(image, rows, cols);
    int copy = rows;
    rows = cols;
    cols = copy;
    cout << "Зображення повернуто.Нові розміри: " << rows << " x " << cols << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }

}

int main()
{
    int rows;
    int cols;
rowsmark:
    cout << "Висота зображення :";
    cin >> rows;
    if (rows < 1 || rows > 20 || cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка.Висота повинна бути від 1 до 20." << endl;
        goto rowsmark;
    }
colsmark:
    cout << "Ширина зображення: ";
    cin >> cols;
    if (cols < 1 || cols > 20 || cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка.Ширина повинна бути від 1 до 20." << endl;
        goto colsmark;
    }
    int **image = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        image[i] = new int[cols]; // Для кожного рядка виділяємо пам'ять під cols елементів
    }
    cout << "Яскравість пікселів (0..9): ";
imagemark:
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {

            cin >> image[i][j];
            if (image[i][j] > 9 || image[i][j] < 0 || cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Яскравіть повинна бути від 0 до 9." << endl;
                goto imagemark;
            }
        }   
    }
    int option;
menumark:
    do
    {
        menu(option);
        switch (option)
        {

        case 1:

            case1(cols, rows, image);
            break;

        case 2:
            case2(cols, rows, image);
            break;

        case 3:
            case3(cols, rows, image);
            break;

        case 4:

            case4(cols, rows, image);
            break;

        case 5:

            case5(cols, rows, image);
            break;

        case 0:
            cout << "Ви вийшли." << endl;
            break;  
        default:
            cout << "Неправильний вибір" << endl;
            goto menumark;
        }
    } while (option != 0);

    deleteimage(image, rows);
    return 0;
}