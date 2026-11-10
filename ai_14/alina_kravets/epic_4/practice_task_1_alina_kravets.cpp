/*Редактор монохромного зображення
ШІ-14
Кравець Аліна*/
#include <iostream>

using namespace std;

void showPicture(int** image, int rows, int cols) //функція, яка виводить зображення
{
    cout << "Зображення " << rows << "x" << cols << ": " << endl;
    for (int i = 0; i < rows; i++) //виведення пікселів у числах
    {
        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Малюнок: " << endl;
    for (int i = 0; i < rows; i++) //виведення пікселів у символах
    {
        for (int j = 0; j < cols; j++)
        {
            if (image[i][j] == 0) cout << " ";
            else if (image[i][j] == 1) cout << ".";
            else if (image[i][j] == 2) cout << ":";
            else if (image[i][j] == 3) cout << "-";
            else if (image[i][j] == 4) cout << "=";
            else if (image[i][j] == 5) cout << "+";
            else if (image[i][j] == 6) cout << "*";
            else if (image[i][j] == 7) cout << "#";
            else if (image[i][j] == 8) cout << "%";
            else if (image[i][j] == 9) cout << "@";
        }
        cout << endl;
    }
}

//функція, яка повертає координати перших максимуму і мінімуму через посилання
void findExtremes (int** image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    int max = image[0][0];
    int min = image[0][0];
    bool maxFound = false;
    bool minFound = false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (image[i][j] > max) max = image[i][j];
            else if (image[i][j] < min) min = image[i][j];
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (image[i][j] == max)
            {
                maxRow = i;
                maxCol = j;
                maxFound = true;
                break;
            }
        }
        if (maxFound) break;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (image[i][j] == min)
            {
                minRow = i;
                minCol = j;
                minFound = true;
                break;
            }
        }
        if (minFound) break;
    }

}

void brightnessStats (int** image, int rows, int cols)//функція, яка виводить статистику яскравості
{
    int minRow = 0;
    int minCol = 0;
    int maxRow = 0;
    int maxCol = 0;
    double sum = 0;

    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "Найтемніший піксель: " << image[minRow][minCol] << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << image[maxRow][maxCol] << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sum += image[i][j];
        }
    }

    double avg_brightness = sum / (rows * cols); //rows*cols - загальна кількість пікселів
    cout << "Середня яскравість: " << avg_brightness << endl;

    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++)
    {
        double r_sum = 0;
        int *row = image[i];
        for (int j = 0; j < cols; j++)
        {
            r_sum += *(row + j);
        }
        double r_avg_brightness = r_sum / cols; //cols - кількість пікселів в одному рядку
        cout << r_avg_brightness << " ";
    }
    cout << endl;   
}

void flippedBrightness(int** image, int rows, int cols) //функція, яка інвертує яскравість
{
    cout << "Яскравість інвертовано." << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            image[i][j] = 9 - image[i][j];
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

void swapPixels(int* a, int* b) //функція, яка міняє два пікселі місцями
{
    int x = *a;
    *a = *b;
    *b = x;
}

void invertedImage(int** image, int rows, int cols) //функція, яка віддзеркалює зображення
{
    if (cols == 1) cout << "Зображення не віддзеркалюється" << endl; //зображення в один стовпчик завузьке для віддзеркалення
    else
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
            for (int j = 0; j < cols/2; j++) //треба дійти до середини зображення
            {
                swapPixels(&image[i][j], &image[i][cols - j - 1]);
            }
        }
        cout << "Результат: " << endl;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << image[i][j] << " ";
            }
            cout << endl;
        }
    }
}

int** rotateRight(int** image, int rows, int cols) //функція, яка повертає зображення прокручене на 90 градусів
{
    int **rotated = new int*[cols]; //створюємо нову динамічну матрицю
    for (int i = 0; i < cols; i++)
    {
        rotated[i] = new int[rows];
    }

    for (int i = 0; i < cols; i++) //переносимо дані зі старої матриці в нову
    {
        for (int j = 0; j < rows; j++)
        {
            rotated[i][j] = image[rows - j - 1][i];
        }
    }

    for (int i = 0; i < rows; i++) //видаляємо стару динамічну матрицю, коли вона уже не потрібна
    {
        delete[] image[i];
    }
    delete[] image;

    return rotated;
}

void rotatedImage(int** &image, int &rows, int &cols) //функція, яка друкує повернуте зображення
{
    if (rows == 1 && cols == 1) cout << "Зображення не повертається" << endl; //зображення 1х1 замале
    else
    {
        image = rotateRight(image, rows, cols);

        int x = rows;
        rows = cols;
        cols = x;

        cout << "Зображення повернуто. Нові розміри: " << rows << "x" << cols << endl;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << image[i][j] << " ";
            }
            cout << endl;
        }
    }
}

int main()
{
    int rows = 0; //створюємо змінні
    int cols = 0;
    int choice = 0;
    
    cout << "Висота зображення: ";
    cin >> rows;
    if (rows <= 0) //висота мусить бути додатньою
    {
        cout << "Помилка: неправильна висота зображення" << endl;
        return 1;
    }

    cout << "Ширина зображення: ";
    cin >> cols;
    if (cols <= 0) //ширина мусить бути додатньою
    {
        cout << "Помилка: неправильна ширина зображення" << endl;
        return 1;
    }

    int **image = new int*[rows]; //створюємо динамічний двовимірний масив
    for (int i = 0; i < rows; i++)
    {
        image[i] = new int[cols];
    }

    cout << "Яскравість пікселів (0..9): " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> image[i][j];
            if (image[i][j] < 0 || image[i][j] > 9) //яскравість мусить бути від 0 до 9
            {
                cout << "Помилка: неправильна яскравість" << endl;
                return 1;
            }
        }
    }

    do {
        menu:
        cout << "---Меню---" << endl;
        cout << "1 - Показати зображення" << endl;
        cout << "2 - Статистика яскравості" << endl;
        cout << "3 - Інвертувати яскравість" << endl;
        cout << "4 - Віддзеркалити по горизонталі" << endl;
        cout << "5 - Повернути на 90 градусів праворуч" << endl;
        cout << "0 - Вийти" << endl;

        cout << "Виберіть дію: ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Помилка: невідома дія" << endl;
            goto menu;
        }

        switch (choice)
        {
            case 0:
            break;
            case 1:
            showPicture(image, rows, cols);
            break;
            case 2:
            brightnessStats(image, rows, cols);
            break;
            case 3:
            flippedBrightness(image, rows, cols);
            break;
            case 4:
            invertedImage(image, rows, cols);
            break;
            case 5:
            rotatedImage(image, rows, cols);
            break;
            default:
            cout << "Помилка: невідома дія" << endl;
            break;
        }
    } while (choice != 0);

    for (int i = 0; i < rows; i++) //видаляємо динамічну матрицю, коли вона уже не потрібна
    {
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;

    return 0;
}
