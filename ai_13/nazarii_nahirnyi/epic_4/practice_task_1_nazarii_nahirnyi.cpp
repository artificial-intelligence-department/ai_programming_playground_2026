/*
    Задача: Редактор монохромного зображення
    Автор: Нагірний Назарій
    Група: СШІ-13
*/
#include <iostream>
#include <iomanip>
using namespace std;

int** allocateM(int rows, int cols) {
    int** img = new int*[rows];
    for (int i = 0; i < rows; i++) {
        img[i] = new int[cols];
    }
    return img;
}

void freeImage(int**& img, int rows) {
    if (img == nullptr) return;
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
}

bool input(int &rows, int &cols, int **&img) {
    cout << "Висота зображення (1..20): ";
    cin >> rows;
    if (cin.fail() || rows < 1 || rows > 20) {
        return false;
    }

    cout << "Ширина зображення (1..20): ";
    cin >> cols;
    if (cin.fail() || cols < 1 || cols > 20) {
        return false;
    }

    img = allocateM(rows, cols);

    cout << "Яскравість пікселів (0..9):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> img[i][j];
            if (cin.fail() || img[i][j] < 0 || img[i][j] > 9) {
                return false;
            }
        }
    }
    return true;
}

void printTable(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << "\n";
    }
}

void punkt1(int** img, int rows, int cols) {
    const char palette[] = " .:-=+*#%@";

    cout << "\nЗображення " << rows << " x " << cols << ":\n";
    printTable(img, rows, cols);

    cout << "\nМалюнок:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << palette[img[i][j]];
        }
        cout << "\n";
    }

    cout << "\nПоточні розміри: " << rows << " x " << cols << "\n";
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0; minCol = 0;
    maxRow = 0; maxCol = 0;

    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        for (int j = 0; j < cols; j++) {
            int currentVal = *(row + j);
            if (currentVal < *(img[minRow] + minCol)) {
                minRow = i;
                minCol = j;
            }
            if (currentVal > *(img[maxRow] + maxCol)) {
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void punkt2(int** img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "\nНайтемніший піксель: " << *(img[minRow] + minCol)
         << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")\n";
    cout << "Найсвітліший піксель: " << *(img[maxRow] + maxCol)
         << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")\n";

    double totalSum = 0;
    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        for (int j = 0; j < cols; j++) {
            totalSum += *(row + j);
        }
    }
    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << totalSum / (rows * cols) << "\n";

    cout << setprecision(1);
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        double rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        cout << rowSum / cols << " ";
    }
    cout << "\n";
}

void punkt3(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "\nЯскравість інвертовано.\n";
    printTable(img, rows, cols);
}

void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void punkt4(int** img, int rows, int cols) {
    cout << "\nЗображення віддзеркалено.\n";
    cout << "Початкове:\n";
    printTable(img, rows, cols);

    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(row + j, row + (cols - 1 - j));
        }
    }

    cout << "\nРезультат:\n";
    printTable(img, rows, cols);
}

int** rotateRight(int** img, int rows, int cols) {
    int** newImg = allocateM(cols, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    freeImage(img, rows);
    return newImg;
}

void punkt5(int** &img, int &rows, int &cols) {
    img = rotateRight(img, rows, cols);
    int temp = rows;
    rows = cols;
    cols = temp;

    cout << "\nЗображення повернуто. Нові розміри: " << rows << " x " << cols << "\n";
    printTable(img, rows, cols);
}

int main() {
    int rows = 0;
    int cols = 0;
    int** img = nullptr;

    if (!input(rows, cols, img)) {
        cout << "Ви ввели некоректні дані! Будь ласка, запустіть програму знову та введіть дані правильно.\n";
        freeImage(img, rows);
        return 1;
    }

    int choice = -1;
    do {
        cout << "\n--- МЕНЮ ---\n"
             << "1. Показати зображення\n"
             << "2. Статистика яскравості\n"
             << "3. Інвертувати яскравість\n"
             << "4. Віддзеркалити по горизонталі\n"
             << "5. Повернути на 90 градусів праворуч\n"
             << "0. Вийти\n"
             << "Ваш вибір: ";

        cin >> choice;

        if (cin.fail()) {
            cout << "Помилка: введіть число від 0 до 5!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: punkt1(img, rows, cols); break;
            case 2: punkt2(img, rows, cols); break;
            case 3: punkt3(img, rows, cols); break;
            case 4: punkt4(img, rows, cols); break;
            case 5: punkt5(img, rows, cols); break;
            case 0: break;
            default:
                cout << "Помилка: такого пункту меню не існує! Введіть число від 0 до 5.\n";
                break;
        }
    } while (choice != 0);

    freeImage(img, rows);

    return 0;
}