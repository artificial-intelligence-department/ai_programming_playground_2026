/*Практична задача - "Редактор монохромного зображення"
Швець Аріна - ШІ-13*/

#include <iostream>
#include <iomanip>

using namespace std;

// Створення динамічного двовимірного масиву
int **createImage(int rows, int cols){
    int **img = new int *[rows];

    for (int i = 0; i < rows; i++){
        img[i] = new int[cols];
    }

    return img;
}

// Звільняємо рядки, а потім масив вказівників
void deleteImage(int **&img, int rows){
    if (img == nullptr){
        return;
    }

    for (int i = 0; i < rows; i++){
        delete[] img[i];
        img[i] = nullptr;
    }

    delete[] img;
    img = nullptr;
}

void printNumbers(int **img, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << img[i][j];
            if (j < cols - 1){
                cout << " ";
            }
        }
        cout << endl;
    }
}

// Показуємо числа та малюнок символами
void showImage(int **img, int rows, int cols){
    const char palette[] = " .:-=+*#%@";

    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    printNumbers(img, rows, cols);

    cout << "Малюнок:" << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << palette[img[i][j]];
        }
        cout << endl;
    }

    cout << "Поточні розміри: " << rows << " x " << cols << endl;
}

// Повертаємо координати мінімуму й максимуму
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    minRow = minCol = maxRow = maxCol = 0;
    int minValue = *(img[0] + 0);
    int maxValue = minValue;

    for (int i = 0; i < rows; i++){
        int *row = img[i];
        for (int j = 0; j < cols; j++){
            int value = *(row + j);

            if (value < minValue){
                minValue = value;
                minRow = i;
                minCol = j;
            }
            if (value > maxValue){
                maxValue = value;
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

// Статистика з використанням арифметики вказівників
void showStatistics(int **img, int rows, int cols){
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "Найтемніший піксель: " << *(img[minRow] + minCol) << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << *(img[maxRow] + maxCol) << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    double total = 0;
    for (int i = 0; i < rows; i++){
        int *row = img[i];
        for (int j = 0; j < cols; j++){
            total += *(row + j);
        }
    }

    cout << fixed << setprecision(2) << "Середня яскравість: " << total / (rows * cols) << endl;

    cout << "Середня по рядках: " << setprecision(1);
    for (int i = 0; i < rows; i++){
        int *row = img[i];
        double rowSum = 0;
        for (int j = 0; j < cols; j++){
            rowSum += *(row + j);
        }
        cout << rowSum / cols;
        if (i < rows - 1){
            cout << " ";
        }
    }
    cout << endl;
}

// Інверсія без створення нового масиву
void invertImage(int **img, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            img[i][j] = 9 - img[i][j];
        }
    }
}

// Обмін значень за переданими адресами
void swapPixels(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Горизонтальне віддзеркалення
void mirrorHorizontal(int **img, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols / 2; j++){
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
}

// Створення повернутого зображення і звільнення старого
int **rotateRight(int **img, int rows, int cols){
    int **rotated = createImage(cols, rows);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            rotated[j][rows - 1 - i] = img[i][j];
        }
    }

    deleteImage(img, rows);
    return rotated;
}

void showMenu()
{
    cout << endl;
    cout << "===== МЕНЮ =====" << endl;
    cout << "1 - Показати зображення" << endl;
    cout << "2 - Статистика яскравості" << endl;
    cout << "3 - Інвертувати яскравість" << endl;
    cout << "4 - Віддзеркалити по горизонталі" << endl;
    cout << "5 - Повернути на 90 градусів праворуч" << endl;
    cout << "0 - Вийти" << endl;
    cout << "Ваш вибір: ";
}

int main()
{
    int rows, cols;

    cout << "Висота зображення: ";
    if (!(cin >> rows) || rows < 1 || rows > 20){
        cout << "Помилка: висота має бути цілим числом від 1 до 20." << endl;
        return 1;
    }

    cout << "Ширина зображення: ";
    if (!(cin >> cols) || cols < 1 || cols > 20)
    {
        cout << "Помилка: ширина має бути цілим числом від 1 до 20." << endl;
        return 1;
    }

    int **img = createImage(rows, cols);
    cout << "Яскравість пікселів (0..9):" << endl;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){

            if (!(cin >> img[i][j]) || img[i][j] < 0 || img[i][j] > 9){
                cout << "Помилка: яскравість має бути цілим числом від 0 до 9." << endl;
                deleteImage(img, rows);
                return 1;
            }
        }
    }

    int choice = -1;
    do{
        showMenu();

        while (!(cin >> choice) || choice < 0 || choice > 5){
            cout << "Некоректний ввід" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice){
        case 1:
            showImage(img, rows, cols);
            break;
        case 2:
            showStatistics(img, rows, cols);
            break;
        case 3:
            invertImage(img, rows, cols);
            cout << "Яскравість інвертовано." << endl;
            printNumbers(img, rows, cols);
            break;
        case 4:
            cout << "Зображення віддзеркалено." << endl;
            cout << "Початкове:" << endl;
            printNumbers(img, rows, cols);
            mirrorHorizontal(img, rows, cols);
            cout << "Результат:" << endl;
            printNumbers(img, rows, cols);
            break;
        case 5:{
            img = rotateRight(img, rows, cols);
            int temp = rows;
            rows = cols;
            cols = temp;
            cout << "Зображення повернуто. Нові розміри: "
                 << rows << " x " << cols << endl;
            printNumbers(img, rows, cols);
            break;
        }
        case 0:
            break;
        }

    } while (choice != 0);

    deleteImage(img, rows);
    cout << "Роботу завершено." << endl;
    return 0;
}