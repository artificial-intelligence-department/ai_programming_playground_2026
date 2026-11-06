
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
using namespace std;

void DeleteImage(int** image, int rows) {
    
    for (int i = 0; i < rows; i++) {
        delete[] image[i];
    }
    delete[] image;
}

void showImage(int** image, int rows, int cols) {
    const char palette[] = " .:-=+*#%@";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << palette[image[i][j]];
        }
        cout << endl;
    }
    cout << "Зображення " << rows << " x " << cols << endl;
}

void showMenu() {
    cout << "1. Показати зображення" << endl;
    cout << "2. Статистика яскравості" << endl;
    cout << "3. Інвертувати яскравість" << endl;
    cout << "4. Віддзеркалити по горизонталі" << endl;
    cout << "5. Повернути на 90 градусів праворуч" << endl;
    cout << "0. Вийти" << endl;
}

void findExtremes(int** img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {

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

void showStatistics(int** img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "Найтемніший піксель: " << img[minRow][minCol]
         << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol]
         << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    int total = 0;
    double rowAverages[20];

    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        int rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        total += rowSum;
        rowAverages[i] = (double)rowSum / cols;
    }

    cout << fixed;
    cout.precision(2);
    cout << "Середня яскравість: " << (double)total / (rows * cols) << endl;

    cout.precision(1);
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++) {
        cout << rowAverages[i] << " ";
    }
    cout << endl;
}

void invertImage(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "Яскравість інвертовано." << endl;
}

void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mirrorImage(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    cout << "Зображення віддзеркалено." << endl;
}

int** rotateRight(int** img, int rows, int cols) {

    int** result = new int*[cols];
    for (int i = 0; i < cols; i++) {
        result[i] = new int[rows];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][rows - 1 - i] = img[i][j];
        }
    }
    DeleteImage(img, rows);
    return result;
}

int main() {

    int rows, cols;
    cout << "Введіть висоту та ширину: ";
    cin >> rows >> cols;

    if (cin.fail() || rows <= 0 || cols <= 0 || rows > 20 || cols > 20) {
        cout << "Помилка: розміри мають бути цілими числами від 1 до 20" << endl;
        return 0;
    }

    int** image = new int*[rows];
    for (int i = 0; i < rows; i++) {
        image[i] = new int[cols];
    }

    cout << "Введіть пікселі зображення (0-9):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> image[i][j];
            if (cin.fail() || image[i][j] < 0 || image[i][j] > 9) {
                cout << "Помилка: піксель має бути числом від 0 до 9" << endl;
                DeleteImage(image, rows);
                return 0;
            }
        }
    }

    int choice;

    do {
        showMenu();
        cout << "Твій вибір: ";
        cin >> choice;
        if (cin.fail()) {
         cin.clear();
         cin.ignore(10000, '\n');
         choice = -1;
         cout << "Помилка: введіть число від 0 до 5" << endl;
         continue;
        }
         cin.ignore(10000, '\n');

        switch (choice) {
            case 1:
                showImage(image, rows, cols);
                break;
                case 2:
                showStatistics(image, rows, cols);
                break;
                case 3:
                invertImage(image, rows, cols);
                break;
                case 4:
                mirrorImage(image, rows, cols);
                break;
                case 5:
                image = rotateRight(image, rows, cols); 
                {
                    int temp = rows;
                    rows = cols;
                    cols = temp;
                }
                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
                break;
                case 0:
                cout << "Вихід з програми." << endl;
                break;
            default:
            cout << "Неправильний пункт меню. Спробуй ще раз" << endl;
        }
    } while (choice != 0);


    DeleteImage(image, rows);
    image = nullptr;

    return 0;
}