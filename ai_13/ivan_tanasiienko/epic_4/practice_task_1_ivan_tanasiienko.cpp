 /*
    Class Practice Work, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<iomanip>


void showImage(int** image, int rows, int columns);
void brightnessStats(int** image, int rows, int columns);
void findExtremes(int** img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void invert(int** image, int rows, int columns);
void mirror(int** image, int rows, int columns);
void swapPixels(int *a, int *b);
void swapAll(int** image, int rows, int columns);
void showPixels(int** image, int rows, int columns);
void rotate(int**& image, int& rows, int& columns);
int** rotateRight(int** img, int rows, int cols);

int main()
{
    //Введення даних та валідація
    int rows, columns;
    do
    {
        std::cout << "Висота зображення: ";
        std::cin >> rows;
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            rows = -1;
            std::cout << "Введено некоректні дані, повторіть спробу" << std::endl;
        }
        else if(rows <= 0 || rows > 20)
        {
            std::cout << "Введіть значення від 1 до 20" << std::endl;
        }
    }while(rows <= 0 || rows > 20);
    do
    {
        std::cout << "Ширина зображення: ";
        std::cin >> columns;
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            columns = -1;
            std::cout << "Введено некоректні дані, повторіть спробу" << std::endl;
        }
        else if(columns <= 0 || columns > 20)
        {
            std::cout << "Введіть значення від 1 до 20" << std::endl;
        }
    }while(columns <= 0 || columns > 20);
    int** image = new int*[rows];
    int* row = nullptr;
    std::cout << "Яскравість пікселів (0..9):" << std::endl;
    //Валідація двовимірного масиву з виведенням інформації про останній зарахований елемент
    for(int i = 0; i < rows; i++)
    {
        row = new int[columns];
        for(int j = 0; j < columns; j++)
        {
            do
            {
                std::cin >> *(row + j);
                if(std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    *(row + j) = -1;
                    std::cout << "Введено некоректні дані, повторіть спробу" << std::endl;
                    if(j > 0)
                    {
                        std::cout << "Останнє зараховане значення: рядок " << i + 1 << 
                        ", стовпець " << j << ": " << row[j - 1] << std::endl;
                    }
                    else if(j == 0 && i > 0)
                    {
                        std::cout << "Останнє зараховане значення: рядок " << i << 
                        ", стовпець " << columns << ": " << image[i-1][columns - 1] << std::endl;
                    }
                }
                else if(*(row + j) < 0 || *(row + j) > 9)
                {
                    std::cout << "Введіть значення від 0 до 9" << std::endl;
                }
            }while(*(row + j) < 0 || *(row + j) > 9);
        }
        *(image + i) = row;
    }

    int choice;
    // Меню
    do
    {
        std::cout << "----------- Меню ------------" << std::endl;
        std::cout << " Пункт |      Операція" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "   1   | Показати зображення" << std::endl;
        std::cout << "   2   | Статистика яскравості" << std::endl;
        std::cout << "   3   | Інвертувати яскравість" << std::endl;
        std::cout << "   4   | Віддзеркалити по горизонталі" << std::endl;
        std::cout << "   5   | Повернути на 90 градусів праворуч" << std::endl;
        std::cout << "   0   | Вийти" << std::endl;
        std::cout << "> ";
        std::cin >> choice;
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = -1;
            std::cout << "Введено некоректні дані, повторіть спробу" << std::endl;
            continue;
        }
        switch(choice)
        {
            case 1:
                showImage(image, rows, columns);
                break;
            case 2:
                brightnessStats(image, rows, columns);
                break;
            case 3:
                invert(image, rows, columns);
                break;
            case 4:
                mirror(image, rows, columns);
                break;
            case 5:
                rotate(image, rows, columns);
                break;
            case 0:
                std::cout << "Вихід..." << std::endl;
                for(int i = 0; i < rows; i++)
                {
                    delete[] *(image + i);
                    *(image + i) = nullptr;
                }
                delete[] image;
                image = nullptr;
                row = nullptr;
                break;
            default:
                std::cout << "Введено неіснуючий пункт меню, повторіть спробу" << std::endl;
                break;
        }
    }while(choice != 0);

    return 0;
}

//Функції, необхідні за умовою
//Функція для пошуку мінімального та максимального значення
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    int max = -1;
    int min = 10;
    for(int i = 0; i < rows; i++)
    {
        //Шукаємо максимально яскравий і мінімально яскравий пікселі
        for(int j = 0; j < cols; j++)
        {
            if(*(*(img + i) + j) > max)
            {
                max = *(*(img + i) + j);
                maxRow = i;
                maxCol = j;
            }
            if(*(*(img + i) + j) < min)
            {
                min = *(*(img + i) + j);
                minRow = i;
                minCol = j;
            }
            // Передчасно закінчуємо цикл, якщо немає необхідності продовжувати його
            if(max == 9 && min == 0)
            {
                return;
            }
        }
    }

    return;
}

//Функція щоб поміняти рядки місцями
void swapPixels(int *a, int *b)
{
    int* temp = new int(*a);
    *a = *b;
    *b = *temp;
    delete temp;
    return;
}
//Функція для безпосереднього повороту праворуч на 90 градусів
int** rotateRight(int** img, int rows, int cols)
{
    int**rotated = new int*[cols];
    
    //Щоб повернути зображення направо потрібно транспонувати зображення і відзеркалити його
    for(int i = 0; i < cols; i++)
    {
        *(rotated + i) = new int[rows];
        for(int j = 0; j < rows; j++)
        {
            *(*(rotated + i) + j) = *(*(img + j) + i);
        }
    }
    swapAll(rotated, cols, rows);
    for(int i = 0; i < rows; i++)
    {
        delete[] *(img + i);
    }
    delete[] img;
    return rotated;
}

//Функції, створені для зручності під час повторного використання
//Функція щоб повністю відзеркалити зображення
void swapAll(int** image, int rows, int columns)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns / 2; j++)
        { 
            swapPixels((*(image + i) + j), (*(image + i) + (columns - j - 1)));
        }
    }

    return;
}
//Функція щоб вивести яскравість пікселів зображення
void showPixels(int** image, int rows, int columns)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        { 
            std::cout << *(*(image + i) + j) << ' ';
        }
        std::cout << std::endl;
    }

    return;
}

//Основні функції
// Функція щоб показати зображення
void showImage(int** image, int rows, int columns)
{
    std::cout << "Зображення " << rows << " x " << columns << std::endl;
    for(int x = 0; x < 2; x++)
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                if(x == 0)
                {
                    std::cout << *(*(image + i) + j) << ' ';
                }
                else
                {
                    std::cout << " .:-=+*#%@"[*(*(image + i) + j)];
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return;
}

void brightnessStats(int** image, int rows, int columns)
{
    int minRow, minColumn, maxRow, maxColumn;
    findExtremes(image, rows, columns, minRow, minColumn, maxRow, maxColumn);


    double sum = 0;
    double* rowAverage = new double[rows]{};
    for(int i = 0; i < rows; i++)
    {
        int* row = *(image + i);
        for(int j = 0; j < columns; j++)
        {
            *(rowAverage + i) += *(row + j);
            sum += *(row + j);
        }
    }
    
    double average = sum / (rows * columns);
    std::cout << "Найтемніший піксель: " << *(*(image + minRow) + minColumn) 
    << " (рядок " << minRow + 1 << ", стовпець " << minColumn + 1 << ')' << std::endl;
    std::cout << "Найсвітліший піксель: " << *(*(image + maxRow) + maxColumn) 
    << " (рядок " << maxRow + 1 << ", стовпець " << maxColumn + 1 << ')' << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Середня яскравість: " << average << std::endl;
    std::cout << "Середня по рядках: ";
    for(int i = 0; i < rows; i++)
    {
        std::cout << *(rowAverage + i) / columns << ' ';
    }
    std::cout << std::endl << std::endl;

    delete[] rowAverage;
    return;
}

void invert(int** image, int rows, int columns)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            *(*(image + i) + j) = 9 - *(*(image + i) + j);
        }
    }
    std::cout << "Яскравість інвертовано." << std::endl;

    showPixels(image, rows, columns);

    return;
}

void mirror(int** image, int rows, int columns)
{
    std::cout << "Початкове: " << std::endl;
    showPixels(image, rows, columns);
    swapAll(image, rows, columns);
    std::cout << std::endl << "Результат: " << std::endl;
    showPixels(image, rows, columns);
    std::cout << std::endl;

    return;
}

void rotate(int**& image, int& rows, int& columns)
{
    image = rotateRight(image, rows, columns);
    int* temp = new int(rows);
    rows = columns;
    columns = *temp;
    delete temp;
    std::cout << "Зображення повернуто. Нові розміри: " << rows << " x " << columns << std::endl;
    showPixels(image, rows, columns);
    std::cout << std::endl;
    return;
}