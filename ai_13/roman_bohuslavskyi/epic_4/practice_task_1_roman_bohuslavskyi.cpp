/*
Задача:  Редактор монохромного зображення
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int R = 20, C = 20;

bool readInt(int& value);
void printImage(int** sixseven, int rows, int cols);
void findExtremes(int** img, int rows, int cols, int& minRow, int& minCol, int& maxRow, int& maxCol);
void invertBrightness(int** sixseven, int rows, int cols);
void mirrorImage(int** sixseven, int rows, int cols);
void swapPixels(int* a, int* b);
int** rotateRight(int** sixseven, int rows, int cols);

int main() {
    int minRow = 0, minCol = 0;
    int maxRow = 0, maxCol = 0;

    int rows = 0, cols = 0;
    int image[R][C] = {};

    cout << "Введіть кількість рядків: ";

    if (!readInt(rows) || rows < 1 || rows > R) {
        cout << "Помилка: кількість рядків має бути цілим числом від 1 до 20." << endl;
        return 0;
    }

    cout << "Введіть кількість стовпців: ";

    if (!readInt(cols) || cols < 1 || cols > C) {
        cout << "Помилка: кількість стовпців має бути цілим числом від 1 до 20." << endl;
        return 0;
    }

    cout << "Яскравість пікселів (0..9):" << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!readInt(image[i][j]) || image[i][j] < 0 || image[i][j] > 9) {
                cout << "Помилка: яскравість елемента {" << i + 1 << ", " << j + 1 << "} має бути цілим числом від 0 до 9." << endl;
                return 0;
            }
        }
    }

    int** newImage = new int*[rows];

    for (int i = 0; i < rows; i++) {
        newImage[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newImage[i][j] = image[i][j];
        }
    }

    int menuChoice = 0;

    do {
    menu:
        cout << endl;
        cout << "Введіть пункт меню:" << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" << endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вийти" << endl;
        cout << "> ";

        if (!readInt(menuChoice) || menuChoice < 0 || menuChoice > 5) {
            cout << endl;
            cout << "Введіть ціле число від 0 до 5." << endl;
            goto menu;
        }

        cout << endl;

        switch (menuChoice) {
            case 1:
                printImage(newImage, rows, cols);
                break;

            case 2:
                findExtremes(newImage, rows, cols, minRow, minCol, maxRow, maxCol);
                break;

            case 3:
                invertBrightness(newImage, rows, cols);
                break;

            case 4:
                mirrorImage(newImage, rows, cols);
                break;

            case 5: {
                newImage = rotateRight(newImage, rows, cols);

                int temp = rows;
                rows = cols;
                cols = temp;

                break;
            }

            case 0:
                break;
        }
    } while (menuChoice != 0);

    for (int i = 0; i < rows; i++) {
        delete[] newImage[i];
        newImage[i] = nullptr;
    }

    delete[] newImage;
    newImage = nullptr;

    return 0;
}

bool readInt(int& value) {
    string text;

    if (!(cin >> text)) return false;

    istringstream input(text);
    int number;
    char extra;

    if (!(input >> number)) return false;
    if (input >> extra) return false;

    value = number;
    return true;
}

void printImage(int** sixseven, int rows, int cols) {
    cout << "Зображення " << rows << " x " << cols << ":" << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << sixseven[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Малюнок:" << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            switch (sixseven[i][j]) {
                case 0:
                    cout << " ";
                    break;
                case 1:
                    cout << ".";
                    break;
                case 2:
                    cout << ":";
                    break;
                case 3:
                    cout << "-";
                    break;
                case 4:
                    cout << "=";
                    break;
                case 5:
                    cout << "+";
                    break;
                case 6:
                    cout << "*";
                    break;
                case 7:
                    cout << "#";
                    break;
                case 8:
                    cout << "%";
                    break;
                case 9:
                    cout << "@";
                    break;
            }
        }
        cout << endl;
    }
}

void findExtremes(int** sixseven, int rows, int cols, int& minRow, int& minCol, int& maxRow, int& maxCol) {
    int lowestBrightness = 10;
    int highestBrightness = -1;

    double sumAll = 0;
    int countAll = 0;
    double rowStat[R];

    for (int i = 0; i < rows; i++) {
        double sumRow = 0;
        int* row = sixseven[i];

        for (int j = 0; j < cols; j++) {
            if (*(row + j) < lowestBrightness) {
                lowestBrightness = *(row + j);
                minRow = i;
                minCol = j;
            }

            if (*(row + j) > highestBrightness) {
                highestBrightness = *(row + j);
                maxRow = i;
                maxCol = j;
            }

            sumAll += *(row + j);
            countAll++;
            sumRow += *(row + j);
        }

        rowStat[i] = sumRow / cols;
    }

    cout << "Найтемніший піксель: " << lowestBrightness << " (Рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << highestBrightness << " (Рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
    cout << "Середня яскравість: " << sumAll / countAll << endl;

    cout << "Середня по рядках:";

    for (int i = 0; i < rows; i++) {
        cout << " " << rowStat[i];
    }

    cout << endl;
}

void invertBrightness(int** sixseven, int rows, int cols) {
    cout << "Яскравість інвертовано:" << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sixseven[i][j] = 9 - sixseven[i][j];
            cout << sixseven[i][j] << " ";
        }
        cout << endl;
    }
}

void mirrorImage(int** sixseven, int rows, int cols) {
    cout << "Початкове:" << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << sixseven[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++) {
        int* row = sixseven[i];

        for (int j = 0; j < cols / 2; j++) {
            swapPixels(row + j, row + (cols - 1 - j));
        }
    }

    cout << endl;
    cout << "Зображення віддзеркалено. Результат:" << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << sixseven[i][j] << " ";
        }
        cout << endl;
    }
}

void swapPixels(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

int** rotateRight(int** sixseven, int rows, int cols) {
    int** rotatedImage = new int*[cols];

    for (int i = 0; i < cols; i++) {
        rotatedImage[i] = new int[rows];
    }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            rotatedImage[i][j] = sixseven[j][i];
        }
    }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows / 2; j++) {
            int toSwap = rows - 1 - j;
            int temp = rotatedImage[i][j];
            rotatedImage[i][j] = rotatedImage[i][toSwap];
            rotatedImage[i][toSwap] = temp;
        }
    }

    cout << "Зображення повернуто. Нові розміри: " << cols << " x " << rows << endl;

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            cout << rotatedImage[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++) {
        delete[] sixseven[i];
        sixseven[i] = nullptr;
    }

    delete[] sixseven;
    sixseven = nullptr;

    return rotatedImage;
}
