/*
Епік 4. Практичне завдання: Редактор монохромного зображення
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
#include<iomanip>
using namespace std;

void showImage(int** image, int rows, int cols, char palitra[]);
void brightnessStatistics(int** image, int rows, int cols);
void findExtremes(int** image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
float findAverageBrightness(int** image, int rows, int cols);
void findAverageBrightnessRow(int** image, int rows, int cols);
void invertBrightness(int** image, int rows, int cols);
void toMirror(int** image, int rows, int cols);
void swapPixels(int* a, int* b);
int** rotateRight(int** image, int &rows, int &cols);
void deleteImage(int** &image, int rows);

int main () {

    int rows, cols, choice;
    char palitra[10] = {' ', '.', ':', '-','=', '+', '*', '#', '%', '@'};

    cout << "Введіть висоту пікселів (ціле число): ";
    cin >> rows;
    if (cin.fail() || rows > 20 || rows < 1) {
        cout << "Помилка! Введіть ціле число, напр. 4, від 1 до 20\n";
        return 1;
    }

    cout << "Введіть ширину пікселів (ціле число): ";
    cin >> cols;
    if (cin.fail() || cols > 20 || cols < 1) {
        cout << "Помилка! Введіть ціле число, напр. 5, від 1 до 20\n";
        return 1;
    }
    
    int **image = new int*[rows];
    for (int i = 0; i < rows; i++) {
        image[i] = new int[cols];
    }

    for (int i = 0; i<rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Введіть елемент " << i+1 << " рядка " << j+1 << " стопця (від 0 до 9): ";
            cin >> image[i][j];
            if (cin.fail() || image[i][j] < 0 || image[i][j] > 9 || cin.peek() != '\n') {
                cout << "Помилка! Введіть ціле число, напр. 7, від 0 до 9\n";
                deleteImage(image, rows);
                return 1;
            }
        }
    }

    bool menuIsAlive = true;

    do {

        cout << "\n============== Меню ============== \n";
        cout << "1    Показати зображення\n";
        cout << "2    Статистика яскравості\n";
        cout << "3    Інвертувати яскравість\n";
        cout << "4    Віддзеркалити по горизонталі\n";
        cout << "5    Повернути на 90 градусів праворуч\n";
        cout << "0    Вийти\n";

        cout << "Виберіть операцію: ";
        cin >> choice;

        if (cin.fail() || cin.peek() != '\n') {
            cout << "Помилка! Введіть ціле число від 0 до 5\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        else if (choice == 1) showImage(image, rows, cols, palitra);
        else if (choice == 2) brightnessStatistics(image, rows, cols);
        else if (choice == 3) invertBrightness(image, rows, cols);
        else if (choice == 4) toMirror(image, rows, cols);
        else if (choice == 5) image = rotateRight(image, rows, cols);
        else if (choice == 0) menuIsAlive = false;
        else cout << "\nПомилка! Введіть ціле число, від 0 до 5\n";

    } while (menuIsAlive);

    deleteImage(image, rows);

    return 0;
}

void showImage(int** image, int rows, int cols, char palitra[]) {

    cout << "\n=========== Зображення =========== \n";
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n====== Символьне зображення ====== \n";
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            cout << palitra[image[i][j]] << " ";
        }
        cout << "\n";
    }
    cout << "Розмір зображення: " << rows << "x" << cols << "\n";
}

void brightnessStatistics(int** image, int rows, int cols){

    int minRow = 0;
    int minCol = 0;
    int maxRow = 0;
    int maxCol = 0;

    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "\nНайтемніший піксель: " << image[minRow][minCol] << " з координатами " << minRow + 1 << " та " << minCol + 1;
    cout << "\nНайсвітліший піксель: " << image[maxRow][maxCol] << " з координатами " << maxRow + 1 << " та " << maxCol + 1;
    
    float averageBrightness = findAverageBrightness(image, rows, cols);

    cout << "\nСередня яскравість усього зображення: " << fixed << setprecision(2) << averageBrightness << endl;

    findAverageBrightnessRow(image, rows, cols);

}

void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {

    int minVal = image[0][0];
    int maxVal = image[0][0];

    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            if (image[i][j] < minVal) {
                minVal = image[i][j];
                minRow = i;
                minCol = j;
            }
            if (image[i][j] > maxVal) {
                maxVal = image[i][j];
                maxRow = i;
                maxCol = j;
            } 
        }
    }

}

float findAverageBrightness(int** image, int rows, int cols) {

    int sumAllVall = 0;
    float averageBrightness = 0;

    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            sumAllVall += image[i][j];
        }
    }

    averageBrightness = (float)sumAllVall / (rows * cols);

    return averageBrightness;
}

void findAverageBrightnessRow(int** image, int rows, int cols) {

    for (int i = 0; i<rows; i++) {

        int sumRow = 0;
        int* row = image[i];

        for (int j = 0; j<cols; j++) {
            sumRow += *(row + j);
        }

        cout << "Середня яскравість " << i+1 << " рядка: " << (float)sumRow/cols << "\n";
    }
}

void invertBrightness(int** image, int rows, int cols) {

    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            *(*(image + i) + j) = 9 - *(*(image + i) + j);
        }
    }
}

void toMirror(int** image, int rows, int cols) {

    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols/2; j++) {    
            swapPixels(*(image + i) + j, *(image + i) + cols - 1 - j);
        }
    }

}

void swapPixels(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int** rotateRight(int** image, int &rows, int &cols) {

    int newRows = cols;
    int newCols = rows;

    int** imageRotated = new int*[newRows];
    for (int i = 0; i<newRows; i++) {
        imageRotated[i] = new int[newCols];
    }

    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            imageRotated[j][rows - 1 - i] = image[i][j];
        }
    }

    deleteImage(image, rows);

    rows = newRows;
    cols = newCols;

    return imageRotated;

}

void deleteImage(int** &image, int rows) {

    for (int i = 0; i < rows; i++) {
        delete[] image[i];
        image[i] = nullptr;
    }

    delete[] image;
    image = nullptr;

}