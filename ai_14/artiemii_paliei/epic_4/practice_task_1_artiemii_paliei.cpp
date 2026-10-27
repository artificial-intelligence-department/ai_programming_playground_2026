#include <iostream>

const char SYMBOLS[10] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};

void option1(int **image, int rows, int cols)
{
    std::cout << "Зображення " << rows << "x" << cols << ":" << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << *(*(image + i) + j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Малюнок:" << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << SYMBOLS[*(*(image + i) + j)];
        }
        std::cout << std::endl;
    }
}

void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    minRow = minCol = maxRow = maxCol = 0;
    int min = 9;
    int max = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (*(*(image + i) + j) < min)
            {
                min = *(*(image + i) + j);
                minRow = i;
                minCol = j;
            }
            if (*(*(image + i) + j) > max)
            {
                max = *(*(image + i) + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void averageBrightness(int **image, int rows, int cols)
{
    double brightness_sum = 0;
    std::cout << "Середня яскравість: ";
    for (int i = 0; i < rows; i++)
    {
        int *row = image[i];
        for (int j = 0; j < cols; j++)
            brightness_sum += *(row + j);
    }
    std::cout << brightness_sum / (rows * cols) << std::endl;

    std::cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++)
    {
        double row_sum = 0;
        int *row = image[i];
        for (int j = 0; j < cols; j++)
        {
            row_sum += *(row + j);
        }
        std::cout << row_sum / cols << " ";
    }
    std::cout << std::endl;
}

void option2(int **image, int rows, int cols)
{
    int min_row, min_col, max_row, max_col;
    findExtremes(image, rows, cols, min_row, min_col, max_row, max_col);
    std::cout << "Найтемніший піксель: " << *(*(image + min_row) + min_col) << " (рядок " << min_row + 1 << ", стовпець "
              << min_col + 1 << ")" << std::endl;
    std::cout << "Найсвітліший піксель: " << *(*(image + max_row) + max_col) << " (рядок " << max_row + 1 << ", стовпець "
              << max_col + 1 << ")" << std::endl;
    averageBrightness(image, rows, cols);
}

void option3(int **image, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(*(image + i) + j) = 9 - *(*(image + i) + j);
        }
    }
    std::cout << "Яскравість інвертовано." << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << *(*(image + i) + j) << " ";
        }
        std::cout << std::endl;
    }
}

void swapPixels(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void option4(int **image, int rows, int cols)
{
    std::cout << "Зображення відзеркалено:" << std::endl
              << "Початкове:" << std::endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << *(*(image + i) + j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Результат" << std::endl;

    for (int k = 0; k < rows; k++)
    {
        int i = 0;
        int j = cols - 1;
        while (i < j)
        {
            swapPixels(*(image + k) + i, *(image + k) + j);
            i++;
            j--;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << *(*(image + i) + j) << " ";
        }
        std::cout << std::endl;
    }
}

int **rotateRight(int **image, int rows, int cols)
{
    int **rotated_image = new int *[cols];
    for (int i = 0; i < cols; i++)
        rotated_image[i] = new int[rows];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(*(rotated_image + j) + (rows - 1 - i)) = *(*(image + i) + j);
        }
    }

    for (int i = 0; i < rows; i++)
    {
        delete[] image[i];
        image[i] = nullptr;
    }
    delete[] image;
    image = nullptr;

    return rotated_image;
}

void option5(int **&image, int &rows, int &cols)
{
    image = rotateRight(image, rows, cols);
    int temp = rows;
    rows = cols;
    cols = temp;
    std::cout << "Зображення перевернуто. Нові розміри: " << rows << "x" << cols << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << *(*(image + i) + j) << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int rows, cols, input;

    std::cout << "Ширина зображення в межах від 1 до 20: ";

    if (!(std::cin >> rows) || rows < 1 || rows > 20)
    {
        std::cout << "Помилка введення. Ви ввели невалідне значення." << std::endl;
        return 1;
    }

    std::cout << "Висота зображення в межах від 1 до 20: ";

    if (!(std::cin >> cols) || cols < 1 || cols > 20)
    {
        std::cout << "Помилка введення. Ви ввели невалідне значення." << std::endl;
        return 1;
    }

    // Вимога #1. Виділення пам’яті

    int **image = new int *[rows];
    for (int i = 0; i < rows; i++)
        image[i] = new int[cols];

    std::cout << "Яскравість зображення (0..9): " << std::endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (!(std::cin >> *(*(image + i) + j)) || *(*(image + i) + j) < 0 || *(*(image + i) + j) > 9)
            {
                std::cout << "Помилка введення. Ви ввели невалідне значення.";
                for (int i = 0; i < rows; i++)
                {
                    delete[] image[i];
                    image[i] = nullptr;
                }

                delete[] image;
                image = nullptr;
                return 1;
            }
        }
    }

    do
    {
        std::cout << "Пункт\tОперація" << std::endl;
        std::cout << "1\tПоказати зображення" << std::endl;
        std::cout << "2\tСтатистика яскравості" << std::endl;
        std::cout << "3\tІнвертувати яскравість" << std::endl;
        std::cout << "4\tВіддзеркалити по горизонталі" << std::endl;
        std::cout << "5\tПовернути на 90 градусів праворуч" << std::endl;
        std::cout << "0\tВихід" << std::endl;
        std::cout << "Ваш вибір: ";
        while (!(std::cin >> input) || input < 0 || input > 5)
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Введіть коректне значення: ";
        }

        switch (input)
        {
        case 1:
            option1(image, rows, cols);
            break;
        case 2:
            option2(image, rows, cols);
            break;
        case 3:
            option3(image, rows, cols);
            break;
        case 4:
            option4(image, rows, cols);
            break;
        case 5:
            option5(image, rows, cols);
            break;
        case 0:
            break;
        default:
            std::cout << "Щось пішло не так..." << std::endl;
            input = 0;
        }

    } while (input != 0);

    // Вимога #1. Звільнення пам’яті
    for (int i = 0; i < rows; i++)
    {
        delete[] image[i];
        image[i] = nullptr;
    }

    delete[] image;
    image = nullptr;
    return 0;
}