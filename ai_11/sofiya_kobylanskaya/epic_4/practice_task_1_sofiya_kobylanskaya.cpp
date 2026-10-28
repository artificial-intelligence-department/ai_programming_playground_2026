#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void showImage(int rows, int cols, int **image) 
{
    cout << "          Зображення " << rows << " x " << cols << endl;
    cout << "______________________________________" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << "              Малюнок: " << endl;
    cout << "______________________________________" << endl;
    char picture[20][20];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (image[i][j] == 0)
            {
                picture[i][j] = ' ';
            }
            if (image[i][j] == 1)
            {
                picture[i][j] = '.';
            }
            if (image[i][j] == 2)
            {
                picture[i][j] = ':';
            }
            if (image[i][j] == 3)
            {
                picture[i][j] = '-';
            }
            if (image[i][j] == 4)
            {
                picture[i][j] = '=';
            }
            if (image[i][j] == 5)
            {
                picture[i][j] = '+';
            }
            if (image[i][j] == 6)
            {
                picture[i][j] = '*';
            }
            if (image[i][j] == 7)
            {
                picture[i][j] = '#';
            }
            if (image[i][j] == 8)
            {
                picture[i][j] = '%';
            }
            if (image[i][j] == 9)
            {
                picture[i][j] = '@';
            }
            cout << picture[i][j];
        }
        cout << endl;
    }
    cout << "Розміри зображення: " << rows << " x " << cols << endl;
    cout << "______________________________________" << endl;
}

void findExtremes(int **image, int rows, int cols,
                  int &minRow, int &minCol,
                  int &maxRow, int &maxCol)
{
    int minimum = 10;
    int maximum = -1;
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    for (int i = 0; i < rows; i++)
    {
        int *row = image[i];
        for (int j = 0; j < cols; j++)
        {
            if (*(row + j) < minimum)
            {
                minimum = *(row + j);
                minRow = i;
                minCol = j;
            }
            if (*(row + j) > maximum)
            {
                maximum = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }

    cout << "______________________________________" << endl;
    cout << "Найтемніший піксель: " << minimum << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << maximum << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
}

void showStatistics(int rows, int cols, int **image)
{
    double average;
    int sum = 0;
    int count = 0;

    int minRow = 0;
    int minCol = 0;
    int maxRow = 0;
    int maxCol = 0;

    for (int i = 0; i < rows; i++)
    {
        int *row = image[i];
        for (int j = 0; j < cols; j++)
        {
            sum += *(row + j);
            count++;
        }
    }
    average = (double)sum / count;

    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "______________________________________" << endl;
    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << average << endl;
    cout << fixed << setprecision(1);
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++)
    {
        int sumRow = 0;
        int *row = image[i];
        for (int j = 0; j < cols; j++)
        {
            sumRow += *(row + j);
        }
        double averageRow = (double)sumRow / cols;
        cout << averageRow << " ";
    }
    cout << endl;
}

void invertImage(int rows, int cols, int **image)
{
    cout << "Яскравість інвертовано." << endl;
    cout << "______________________________________" << endl;
    for (int i = 0; i < rows; i++)
    {
        int *row = image[i];
        for (int j = 0; j < cols; j++)
        {
            *(row + j) = 9 - *(row + j);
            cout << *(row + j) << " ";
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

void mirrorImage(int rows, int cols, int **image)
{
    cout << "Зображення віддзеркалено." << endl;
    cout << "______________________________________" << endl;
    cout << "Початкове: " << endl;
    for (int i = 0; i < rows; i++)
    {
        int *row = image[i];
        for (int j = 0; j < cols; j++)
        {
            cout << *(row + j) << " ";
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

    cout << "Результат: " << endl;
    for (int i = 0; i < rows; i++)
    {
        int *row = image[i];
        for (int j = 0; j < cols; j++)
        {
            cout << *(row + j) << " ";
        }
        cout << endl;
    }
}

int **rotateRight(int **image, int rows, int cols)
{
    int **rotated = new int *[cols];
    for (int i = 0; i < cols; i++)
    {
        rotated[i] = new int[rows];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            rotated[j][rows - 1 - i] = image[i][j];
        }
    }

    for (int i = 0; i < rows; i++)
    {
        delete[] image[i];
        image[i] = nullptr;
    }
    delete[] image;
    image = nullptr;

    return rotated;
}

int main()
{
    int rows;
    int cols;

    cout << "Введіть висоту зображення: " << endl;
    if (!(cin >> rows) || rows <= 0 || rows > 20)
    {
        cout << "Помилка! Ви маєте ввести число більше 0 і не більше 20." << endl;
        return 1;
    }
    cout << "Введіть ширину зображення: " << endl;
    if (!(cin >> cols) || cols <= 0 || cols > 20)
    {
        cout << "Помилка! Ви маєте ввести число більше 0 і не більше 20." << endl;
        return 1;
    }

    int **image = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        image[i] = new int[cols];
    }

    cout << "Введіть яскравість пікселів (0..9): " << endl;
    for (int i = 0; i < rows; i++)
    {
        string line;
        if (!(getline(cin >> ws, line)) || line.length() != cols)
        {
            cout << "Помилка! Кількість пікселів у рядку має бути " << cols << "." << endl;
            for (int k = 0; k < rows; k++)
            {
                delete[] image[k];
                image[k] = nullptr;
            }
            delete[] image;
            image = nullptr;
            return 1;
        }
        for (int j = 0; j < cols; j++)
        {
            char pixel = line[j];
            if (pixel < '0' || pixel > '9')
            {
                cout << "Помилка! Яскравість має бути числом від 0 до 9." << endl;
                for (int k = 0; k < rows; k++)
                {
                    delete[] image[k];
                    image[k] = nullptr;
                }
                delete[] image;
                image = nullptr;
                return 1;
            }
            image[i][j] = pixel - '0';
        }
    }
    cout << "Зображення збережено!" << endl;

    int action;
    do
    {
        cout << "========== МЕНЮ ==========" << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" << endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вийти" << endl;
        cout << "==========================" << endl;
        cout << "Оберіть пункт меню або введіть 0 щоб вийти: " << endl;
        cin >> action;
        while (cin.fail() || action < 0 || action > 5)
        {
            cout << "Помилка! Ви маєте ввести число від 0 до 5. Введіть ще раз: " << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> action;
        }
        switch (action)
        {
        case 1:
            showImage(rows, cols, image);
            break;
        case 2:
            showStatistics(rows, cols, image);
            break;
        case 3:
            invertImage(rows, cols, image);
            break;
        case 4:
            mirrorImage(rows, cols, image);
            break;
        case 5: 
        image = rotateRight(image, rows, cols);
        int temp = rows;
        rows = cols;
        cols = temp;

        cout << "______________________________________" << endl;
        cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
        showImage(rows, cols, image);
        break;
        }

        string command;
        if (action != 0)
        {
            do
            {
                cout << "Введіть 'menu', щоб повернутися до меню, або 0, щоб вийти: " << endl;
                cin >> command;
                if (command != "menu" && command != "0")
                {
                    cout << "Помилка!" << endl;
                }

            } while (command != "menu" && command != "0");
            if (command == "0")
            {
                action = 0;
            }
        }
    } while (action != 0);

    for (int i = 0; i < rows; i++)
    {
        delete[] image[i];
        image[i] = nullptr;
    }
    delete[] image;
    image = nullptr;

    return 0;
}