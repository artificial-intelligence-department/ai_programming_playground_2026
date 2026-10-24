#include <iostream>
#include <iomanip>

using namespace std;

void printMatrix(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

void printImg(int** img, int rows, int cols) {
    const char symbols[] = " .:-=+*#%@";
    cout << "Зображення " << rows << " x " << cols << ':' << endl;
    printMatrix(img, rows, cols);

    cout << "Малюнок: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int symbolInd = img[i][j];
            cout << symbols[symbolInd];
        }
        cout << endl;
    }
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (img[i][j] < img[minRow][minCol]) {
                minRow = i;
                minCol = j;
            }
            if (img[i][j] > img[maxRow][maxCol]) {
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void showStatistics(int **img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    int minVal = *(img[minRow] + minCol);
    int maxVal = *(img[maxRow] + maxCol);

    cout << "Найсвітліший піксель: " << maxVal << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
    cout << "Найтемніший піксель: " << minVal << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;

    double totalSum = 0;
    int totalElements = rows*cols;
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++) {
        int *row = img[i]; 
        double rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        totalSum += rowSum;
        cout << (rowSum / cols) << (i == rows - 1 ? "" : "  ");
    }
    cout << endl;

    double totalAvg = totalSum / totalElements;
    cout << "Середня яскравість: " << fixed << setprecision(2) << totalAvg << endl;
}

void invertBrightness(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        for (int j = 0; j < cols; j++) {
            *(row+j) = 9 - *(row+j);
        }
    }

    cout << "Яскравість інвертовано." << endl;
    printMatrix(img, rows, cols);
}

void swapPixels(int *a, int *b) {
    int temp =  *a;
    *a = *b;
    *b = temp;
}

void mirrorImg(int** img, int rows, int cols) {
    cout << "Зображення віддзеркалено.\nПочаткове:" << endl;
    printMatrix(img, rows, cols);
    cout << "\nРезультат:" << endl;
    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        for (int j = 0; j < cols/2; j++) {
            swapPixels((row+j), (row+cols-j-1));
        }
    }
    printMatrix(img, rows, cols);
}

int** rotateRight(int** img, int rows, int cols) {
    int newRows = cols;
    int newCols = rows;

    int** newImg = new int*[newRows];
    for (int i = 0; i < newRows; i++) {
        newImg[i] = new int[newCols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newImg[j][rows-i-1] = img[i][j];
        }
    }

    for (int i = 0; i < rows; i++) {
        delete[] img[i];
    }
    delete[] img;

    cout << "Зображення повернуто. Нові розміри: " << newRows << " x " << newCols << endl;
    printMatrix(newImg, newRows, newCols);
    return newImg;
}

int main() {
    int rows;
    int cols;
    cout << "Висота зображення: ";
    if (!(cin>>rows) || rows <= 0 || rows > 20) {
        cout << "Помилка вводу." << endl;
        for (int i = 0; i < rows; i++) {
            delete[] image[i];
        }
        delete[] image;
        image = nullptr;
        return 0;
    }
    cout << "Ширина зображення: ";
    if (!(cin>>cols) || cols <= 0 || cols > 20) {
        cout << "Помилка вводу." << endl;
        for (int i = 0; i < rows; i++) {
            delete[] image[i];
        }
        delete[] image;
        image = nullptr;
        return 0;
    }

    int** image = new int*[rows];
    for (int i=0; i<rows; i++) {
        image[i] = new int[cols];
    }

    cout << "Яскравість пікселів (0..9):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(cin >> image[i][j]) || image[i][j] < 0 || image[i][j] > 9) {
                cout << "Яркість повинна мати значенні 0-9." << endl;
                for (int i = 0; i < rows; i++) {
                    delete[] image[i];
                }
                delete[] image;
                image = nullptr;
                return 0;
            }
        }
    }



    int choice;
    do {
        cout << "\n=== МЕНЮ РЕДАТОРА ЗОБРАЖЕННЯ ===" << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" << endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вийти" << endl;
        cout << "Оберіть пункт меню: ";

        if (!(cin >> choice)) {
            cout << "Помилка вводу. Введіть число від 0 до 5." << endl;
            cin.clear(); 
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\n--- 1: Показати зображення ---\n";
                printImg(image, rows, cols);
                break;

            case 2:
                cout << "\n--- 2: Статистика яскравості ---\n";
                showStatistics(image, rows, cols);
                break;

            case 3:
                cout << "\n--- 3: Інвертувати яскравість ---\n";
                invertBrightness(image, rows, cols);
                break;

            case 4:
                cout << "\n--- 4: Віддзеркалити по горизонталі ---\n";
                mirrorImg(image, rows, cols);
                break;

            case 5: {
                cout << "\n--- 5: Повернути на 90 градусів ---\n";
                image = rotateRight(image, rows, cols);
                int temp = rows;
                rows = cols;
                cols = temp;
                break;
            }
                
            case 0:
                cout << "Вихід з програми." << endl;
                break;

            default:
                cout << "Спробуйте ще раз (0-5)." << endl;
        }

    } while (choice != 0);

    for (int i = 0; i < rows; i++) {
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;
    return 0;

}