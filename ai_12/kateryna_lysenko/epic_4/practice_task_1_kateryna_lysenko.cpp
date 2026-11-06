/*
Назва:Редактор монохромного зображення
Автор: Катерина Лисенко
Група: ШІ-12
*/
#include <iostream>
#include <iomanip>
using namespace std;

// Виділення пам'яті
int** allocateImage(int rows, int cols) {
    int** img = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        img[i] = new int[cols];
    }
    return img;
}

// Звільнення пам'яті
void freeMemory(int**& img, int rows) {
    if (img == nullptr) return;
    for (int i = 0; i < rows; ++i) {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
}

// Таблиця чисел
void showTable(int** img, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << img[i][j] << (j == cols - 1 ? "" : " ");
        }
        cout << "\n";
    }
}

// Показати зображення
void showImage(int** img, int rows, int cols) {
    const char palette[] = " .:-=+*#%@";
    cout << "\nЗображення " << rows << " x " << cols << ":\n";
    showTable(img, rows, cols);
    cout << "\nМалюнок:\n";

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << palette[img[i][j]];
        }
        cout << "\n";
    }
}

// Пошук найтемнішого та найсвітлішого пікселів
void findExtremes(int** img, int rows, int cols,
    int& minRow, int& minCol, int& maxRow, int& maxCol) {

    int minVal = img[0][0];
    int maxVal = img[0][0];

    minRow = minCol = maxRow = maxCol = 1;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {

            if (img[i][j] < minVal) {
                minVal = img[i][j];
                minRow = i + 1;
                minCol = j + 1;
            }

            if (img[i][j] > maxVal) {
                maxVal = img[i][j];
                maxRow = i + 1;
                maxCol = j + 1;
            }
        }
    }
}

// Статистика яскравості
void showStatistics(int** img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;

    findExtremes(img, rows, cols,
        minRow, minCol, maxRow, maxCol);

    int minVal = img[minRow - 1][minCol - 1];
    int maxVal = img[maxRow - 1][maxCol - 1];

    cout << "\nНайтемніший піксель: " << minVal
         << " (рядок " << minRow
         << ", стовпець " << minCol << ")\n";

    cout << "Найсвітліший піксель: " << maxVal
         << " (рядок " << maxRow
         << ", стовпець " << maxCol << ")\n";

    double totalSum = 0;
    double* rowAvg = new double[rows];

    for (int i = 0; i < rows; ++i) {
        int* row = img[i];
        double rowSum = 0;

        for (int j = 0; j < cols; ++j) {
            rowSum += *(row + j);
        }

        totalSum += rowSum;
        rowAvg[i] = rowSum / cols;
    }

    cout << fixed << setprecision(2);
    cout << "Середня яскравість: "
         << totalSum / (rows * cols) << "\n";

    cout << setprecision(1);
    cout << "Середня по рядках: ";

    for (int i = 0; i < rows; ++i) {
        cout << rowAvg[i] << (i == rows - 1 ? "" : " ");
    }

    cout << "\n";
    cout.unsetf(ios::fixed);

    delete[] rowAvg;
}

// Інверсія
void invertImage(int** img, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            img[i][j] = 9 - img[i][j];
        }
    }

    cout << "\nЯскравість інвертовано.\n";
    showTable(img, rows, cols);
}

// Обмін двох пікселів
void swapPixels(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Віддзеркалення по горизонталі
void mirrorHorizontal(int** img, int rows, int cols) {
    cout << "\nПочаткове:\n";
    showTable(img, rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols / 2; ++j) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }

    cout << "\nЗображення віддзеркалено.\n\nРезультат:\n";
    showTable(img, rows, cols);
}

// Поворот на 90 градусів вправо
int** rotateRight(int** img, int rows, int cols) {
    int** newImg = allocateImage(cols, rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    freeMemory(img, rows);
    return newImg;
}

// Поворот та зміна розмірів
void rotateImage(int**& img, int& rows, int& cols) {
    img = rotateRight(img, rows, cols);

    int temp = rows;
    rows = cols;
    cols = temp;

    cout << "\nЗображення повернуто. Нові розміри: "
         << rows << " x " << cols << "\n";

    showTable(img, rows, cols);
}


int main() {
    int** img = nullptr;
    int rows = 0, cols = 0;

    cout << "Редактор монохромного зображення\n";

    // Введення висоти
    cout << "\nВведіть висоту зображення (1-20): ";

    if (!(cin >> rows) || rows < 1 || rows > 20) {
        cout << "Помилка вводу! Некоректна висота зображення.\n";
        return 0;
    }

    // Введення ширини
    cout << "Введіть ширину зображення (1-20): ";

    if (!(cin >> cols) || cols < 1 || cols > 20) {
        cout << "Помилка вводу! Некоректна ширина зображення.\n";
        return 0;
    }

    img = allocateImage(rows, cols);

    cout << "\nЯскравість пікселів (0..9):\n";

    // Введення пікселів
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {

            if (!(cin >> img[i][j]) ||
                img[i][j] < 0 || img[i][j] > 9) {

                cout << "Помилка! Піксель має бути числом від 0 до 9.\n";

                freeMemory(img, rows);
                return 0;
            }
        }
    }

    // Меню
int choice = -1;
do {
cout << "\n МЕНЮ \n";
cout << "1. Показати зображення\n";
cout << "2. Статистика яскравості\n";
cout << "3. Інвертувати яскравість\n";
cout << "4. Віддзеркалити по горизонталі\n";
cout << "5. Повернути на 90 градусів вправо\n";
cout << "0. Вийти\n";
cout << "Виберіть пункт: ";

// Валідація пункту меню
if (!(cin >> choice) || choice < 0 || choice > 5) {

    if (cin.eof()) {
        cout << "\nКінець вводу.\n";
        freeMemory(img, rows);
        return 0;
    }

    cout << "Помилка! Введіть число від 0 до 5.\n";
    cin.clear();
    cin.ignore(10000, '\n');
    choice = -1;
    continue;
}

switch (choice) {
    case 1:
        showImage(img, rows, cols);
        break;
    case 2:
        showStatistics(img, rows, cols);
    break;
    case 3:
        invertImage(img, rows, cols);
        break;
    case 4:
        mirrorHorizontal(img, rows, cols);
        break;
    case 5:
        rotateImage(img, rows, cols);
        break;
    case 0:
        cout << "\nЗавершення роботи.\n";
        break;
}
} while (choice != 0);

// Звільнення пам'яті
freeMemory(img, rows);

return 0; } 