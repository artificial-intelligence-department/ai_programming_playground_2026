/*
Practice task
Лисюк Андріана
ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int** allocateImage(int rows, int cols) {
    int** img = new int*[rows];
    for (int i = 0; i < rows; i++) {
        img[i] = new int[cols];
    }
    return img;
}

void freeImage(int** img, int rows) {
    if (img != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] img[i];
        }
        delete[] img;
    }
}

void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void printMatrixOnly(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << "\n";
    }
}

void showImage(int** img, int rows, int cols) {
    string palette = " .:-=+*#%@";
    cout << "\nЗображення " << rows << " x " << cols << ":\n";
    printMatrixOnly(img, rows, cols);
    cout << "\nМалюнок:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << palette[img[i][j]];
        }
        cout << "\n";
    }
}

void findExtremes(int** img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0; minCol = 0;
    maxRow = 0; maxCol = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (img[i][j] < img[minRow][minCol]) {
                minRow = i; minCol = j;
            }
            if (img[i][j] > img[maxRow][maxCol]) {
                maxRow = i; maxCol = j;
            }
        }
    }
}

void showStats(int** img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "Найтемніший піксель: " << img[minRow][minCol] 
         << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")\n";
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol] 
         << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")\n";
    double totalSum = 0;
    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        for (int j = 0; j < cols; j++) {
            totalSum += *(row + j);
        }
    }
    double totalAvg = totalSum / (rows * cols);
    cout << "Середня яскравість: " << fixed << setprecision(2) << totalAvg << "\n";
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++) {
        double rowSum = 0;
        int* row = img[i];
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        cout << fixed << setprecision(1) << (rowSum / cols) << " ";
    }
    cout << "\n";
}

void invertImage(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "Яскравість інвертовано.\n";
    printMatrixOnly(img, rows, cols);
}

void flipHorizontal(int** img, int rows, int cols) {
    cout << "Зображення віддзеркалено.\n";
    cout << "Початкове:\n";
    printMatrixOnly(img, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    cout << "\nРезультат:\n";
    printMatrixOnly(img, rows, cols);
}

int** rotateRight(int** img, int &rows, int &cols) {
    int newRows = cols;
    int newCols = rows;
    int** newImg = allocateImage(newRows, newCols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }
    freeImage(img, rows);
    rows = newRows;
    cols = newCols;
    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << "\n";
    printMatrixOnly(newImg, rows, cols);
    return newImg;
}

int main() {
    int rows, cols;
    cout << "Висота зображення: ";
    if (!(cin >> rows) || rows < 1 || rows > 20) {
        cout << "Помилка: Некоректний розмір зображення!\n";
        return 0;
    }
    cout << "Ширина зображення: ";
    if (!(cin >> cols) || cols < 1 || cols > 20) {
        cout << "Помилка: Некоректний розмір зображення!\n";
        return 0;
    }
    int** img = allocateImage(rows, cols);
    cout << "Яскравість пікселів (0..9):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(cin >> img[i][j]) || img[i][j] < 0 || img[i][j] > 9) {
                cout << "Помилка: Некоректне значення пікселя!\n";
                freeImage(img, rows);
                img = nullptr;
                return 0;
            }
        }
    }
    int choice;
    do {
        cout << "\n--- МЕНЮ ---\n";
        cout << "1. Показати зображення\n";
        cout << "2. Статистика яскравості\n";
        cout << "3. Інвертувати яскравість\n";
        cout << "4. Віддзеркалити по горизонталі\n";
        cout << "5. Повернути на 90 градусів праворуч\n";
        cout << "0. Вийти\n";
        cout << "Ваш вибір: ";
        if (!(cin >> choice)) {
            cout << "Помилка: введіть число від 0 до 5!\n";
            clearInput();
            continue;
        }
        switch (choice) {
            case 1:
                showImage(img, rows, cols);
                break;
            case 2:
                showStats(img, rows, cols);
                break;
            case 3:
                invertImage(img, rows, cols);
                break;
            case 4:
                flipHorizontal(img, rows, cols);
                break;
            case 5:
                img = rotateRight(img, rows, cols);
                break;
            case 0:
                cout << "Завершення роботи...\n";
                break;
            default:
                cout << "Некоректний пункт меню! Спробуйте ще раз.\n";
        }
    } while (choice != 0);
    freeImage(img, rows);
    img = nullptr;
    return 0;
}