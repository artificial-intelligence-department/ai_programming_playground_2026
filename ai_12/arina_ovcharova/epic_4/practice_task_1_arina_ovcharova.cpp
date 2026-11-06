// Практична робота (Class Practice): редактор монохромного зображення
#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_SIDE = 20;
const char PALETTE[] = " .:-=+*#%@";  // 0 - пробіл, 9 - @

// виділення пам'яті
int **allocateImage(int rows, int cols) {
    int **img = new int *[rows];
    for (int i = 0; i < rows; i++) {
        img[i] = new int[cols];
    }
    return img;
}

// звільняємо спочатку рядки, потім масив вказівників
void freeImage(int **&img, int rows) {
    if (img == nullptr) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
}

void printNumbers(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j];
            if (j + 1 < cols) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void printPicture(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << PALETTE[img[i][j]];
        }
        cout << endl;
    }
}

// шукає мін і макс піксель, координати через &
// без [], тільки вказівники
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol,
                  int &maxRow, int &maxCol) {
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    int minVal = *(*img);
    int maxVal = *(*img);

    for (int i = 0; i < rows; i++) {
        int *row = *(img + i);
        for (int j = 0; j < cols; j++) {
            int v = *(row + j);
            if (v < minVal) {
                minVal = v;
                minRow = i;
                minCol = j;
            }
            if (v > maxVal) {
                maxVal = v;
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

// пункт 2: статистика
void showStatistics(int **img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    int *minRowPtr = *(img + minRow);
    int *maxRowPtr = *(img + maxRow);

    cout << "Найтемніший піксель: " << *(minRowPtr + minCol)
         << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << *(maxRowPtr + maxCol)
         << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    double *rowAvg = new double[rows];
    int total = 0;

    for (int i = 0; i < rows; i++) {
        int *row = *(img + i);
        int rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        total += rowSum;
        rowAvg[i] = (double)rowSum / cols;
    }

    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << (double)total / (rows * cols) << endl;

    cout << setprecision(1);
    cout << "Середня по рядках:";
    for (int i = 0; i < rows; i++) {
        cout << " " << rowAvg[i];
    }
    cout << endl;

    delete[] rowAvg;
    rowAvg = nullptr;
}

// пункт 3: інверсія
void invertImage(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
}

// міняє пікселі місцями
void swapPixels(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// пункт 4: віддзеркалення
void mirrorHorizontal(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
}

// пункт 5: поворот на 90 градусів
int **rotateRight(int **img, int rows, int cols) {
    int **result = allocateImage(cols, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][rows - 1 - i] = img[i][j];
        }
    }

    // старий масив звільняємо після перенесення
    freeImage(img, rows);

    return result;
}

bool readDimension(const char *prompt, int &value) {
    cout << prompt;
    if (!(cin >> value)) {
        cout << "Помилка: потрібно ввести число." << endl;
        return false;
    }
    if (value < 1 || value > MAX_SIDE) {
        cout << "Помилка: значення має бути від 1 до " << MAX_SIDE << "." << endl;
        return false;
    }
    return true;
}

bool readPixels(int **img, int rows, int cols) {
    cout << "Яскравість пікселів (0..9):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int v;
            if (!(cin >> v)) {
                cout << "Помилка: потрібно ввести число." << endl;
                return false;
            }
            if (v < 0 || v > 9) {
                cout << "Помилка: яскравість має бути від 0 до 9." << endl;
                return false;
            }
            img[i][j] = v;
        }
    }
    return true;
}

void printMenu() {
    cout << endl
         << "Меню:" << endl
         << "1 - Показати зображення" << endl
         << "2 - Статистика яскравості" << endl
         << "3 - Інвертувати яскравість" << endl
         << "4 - Віддзеркалити по горизонталі" << endl
         << "5 - Повернути на 90 градусів праворуч" << endl
         << "0 - Вийти" << endl
         << "Ваш вибір: ";
}

int main() {
    int rows, cols;

    if (!readDimension("Висота зображення: ", rows)) {
        return 1;
    }
    if (!readDimension("Ширина зображення: ", cols)) {
        return 1;
    }

    int **img = allocateImage(rows, cols);

    // звільняємо пам'ять перед виходом
    if (!readPixels(img, rows, cols)) {
        freeImage(img, rows);
        return 1;
    }

    int choice;
    do {
        printMenu();
        if (!(cin >> choice)) {
            cout << "Помилка: потрібно ввести число." << endl;
            break;
        }

        switch (choice) {
        case 1:
            cout << "Зображення " << rows << " x " << cols << ":" << endl;
            printNumbers(img, rows, cols);
            cout << "Малюнок:" << endl;
            printPicture(img, rows, cols);
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
            cout << "Початкове:" << endl;
            printNumbers(img, rows, cols);
            mirrorHorizontal(img, rows, cols);
            cout << "Зображення віддзеркалено." << endl;
            cout << "Результат:" << endl;
            printNumbers(img, rows, cols);
            break;
        case 5: {
    // rotateRight повертає новий масив
            img = rotateRight(img, rows, cols);
            int tmp = rows;
            rows = cols;
            cols = tmp;
            cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
            printNumbers(img, rows, cols);
            break;
        }
        case 0:
            break;
        default:
            cout << "Невідомий пункт меню." << endl;
        }
    } while (choice != 0);

    freeImage(img, rows);
    return 0;
}