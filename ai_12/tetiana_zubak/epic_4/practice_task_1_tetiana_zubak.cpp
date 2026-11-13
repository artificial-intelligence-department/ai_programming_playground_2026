/*
Редактор монохромного зображення
Зубак Тетяна
ШІ-12
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <locale>

using namespace std;

const int max_size = 20;
const string pal = " .:-=+*#%@";

bool readInt(int &value) {
    string token;
    if (!(cin >> token)) {
        return false;
    }

    for (int i = 0; i < token.length(); i++) {
        if (token[i] < '0' || token[i] > '9') {
            return false;
        }
    }

    if (token.length() > 9) {
        return false;
    }

    value = 0;
    for (int i = 0; i < (int)token.length(); i++) {
        value = value * 10 + (token[i] - '0');
    }

    return true;
}

int dim(string name) {
    int N = 0;
    cout << name;
    
    if (!readInt(N)) {
        cout << "Помилка: введіть значення цілим додатним числом." << endl;
        return 0;
    }

    if (N < 1 || N > max_size) {
        cout << "Помилка: значення має бути від 1 до 9." << endl;
        return 0;
    }
    
    return N;
}

void freeImg(int **&img, int rows) {
    if (img == nullptr) return;
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
}

bool pixels(int **img, int rows, int cols) {
    int num = 0;
    cout << "Яскравість пікселів (0..9): " << endl;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!readInt(num)) {
                cout << "Помилка: яскравість має бути цілим числом." << endl;
                return false;
            }

            if (num < 0 || num > 9) {
                cout << "Помилка: яскравість має бути від 0 до 9." << endl;
                return false;
            }
            
            img[i][j] = num;
        }
    }
    return true;
}

void numbers(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j];
            if (j < cols - 1) cout << " ";
        }
        cout << endl;
    }
}

void show(int **img, int rows, int cols) {
    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    numbers(img, rows, cols);

    cout << "Малюнок:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << pal[img[i][j]];
        }
        cout << endl;
    }
    cout << "Поточні розміри: " << rows << " x " << cols << endl;
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    int min = 9, max = 0;
    minRow = 0; minCol = 0; maxRow = 0; maxCol = 0;
    
    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        for (int j = 0; j < cols; j++) {
            if (*(row + j) < min) {
                min = *(row + j);
                minRow = i;
                minCol = j;
            }
            if (*(row + j) > max) {
                max = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void statistic(int **img, int rows, int cols) {
    int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;
    int sum = 0;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    int *row = img[minRow];
    cout << "Найтемніший піксель: " << *(row + minCol) << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    row = img[maxRow];
    cout << "Найсвітліший піксель: " << *(row + maxCol) << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    double *mid = new double[rows];
    for (int i = 0; i < rows; i++) {
        int rowSum = 0;
        row = img[i];
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        sum += rowSum;
        mid[i] = (double)rowSum / cols;
    }

    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << (double)sum / (rows * cols) << endl;
    cout << setprecision(1);
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++) {
        cout << mid[i];
        if (i < rows - 1) cout << " ";
    }
    cout << endl;

    delete[] mid;
    mid = nullptr;
}

void invert(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "Яскравість інвертовано." << endl;
    numbers(img, rows, cols);
}

void swapPixels(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void mirror(int **img, int rows, int cols) {
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;
    numbers(img, rows, cols);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    
    cout << "Результат:" << endl;
    numbers(img, rows, cols);
}

int** rotateRight(int** img, int rows, int cols) {
    int **newImg = new int*[cols];
    for (int i = 0; i < cols; i++) {
        newImg[i] = new int[rows];
    }

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    freeImg(img, rows);
    return newImg;
}

bool status(int **&img, int &rows, int &cols, int &def) {
    int menu = 0;

    cout << endl << "1 - Показати зображення " << endl 
         << "2 - Статистика яскравості " << endl 
         << "3 - Інвертувати яскравість " << endl 
         << "4 - Віддзеркалити по горизонталі" << endl 
         << "5 - Повернути на 90 градусів праворуч" << endl 
         << "0 - Вийти " << endl;
         
    if (!readInt(menu)) {
        cout << "Помилка: пункт меню має бути цілим числом." << endl;
        return false;
    }

    switch (menu) {
        case 1:
            show(img, rows, cols);
            break;
        case 2:
            statistic(img, rows, cols);
            break;
        case 3:
            invert(img, rows, cols);
            break;
        case 4:
            mirror(img, rows, cols);
            break;
        case 5: {
            img = rotateRight(img, rows, cols);
            int t = rows;
            rows = cols;
            cols = t;
            cout << "Зображення повернуто." << endl << "Нові розміри: " << rows << " x " << cols << endl;
            numbers(img, rows, cols);
            break;
        }
        case 0:
            def = 1;
            break;
        default:
            cout << "Помилка: неіснуючий пункт меню." << endl;
            return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "uk_UA");
    int def = 0;
    
    int rows = dim("Висота зображення: ");
    if (rows == 0) return 0;
    
    int cols = dim("Ширина зображення: ");
    if (cols == 0) return 0;

    int **img = new int*[rows];
    for (int i = 0; i < rows; i++) {
        img[i] = new int[cols];
    }

    if (!pixels(img, rows, cols)) {
        freeImg(img, rows);
        return 0;
    }

    do {
        if (!status(img, rows, cols, def)) {
            freeImg(img, rows);
            return 0;
        }
    } while (def != 1);

    freeImg(img, rows);
    return 0;
}