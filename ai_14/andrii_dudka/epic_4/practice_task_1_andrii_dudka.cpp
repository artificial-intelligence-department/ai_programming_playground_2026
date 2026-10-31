#include <iostream>
#include <iomanip>
using namespace std;

bool readNumber(int &value) {
    if (!(cin >> value)) {
        return false;
    }
    if (cin.eof()) {
        return true;
    }

    return true;
}


int** createImage(int rows, int cols) {
    int **img = new int*[rows];
    for (int i = 0; i < rows; i++) {
        img[i] = new int[cols];
    }
    return img;
}

void deleteImage(int **&img, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
}

void showImage(int **img, int rows, int cols) {
    const char palette[] = " .:-=+*#%@";

    cout << "\nТаблиця пікселів:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j];
            if (j < cols - 1) {
                cout << ' ';
            }
        }
        cout << '\n';
    }

    cout << "Малюнок:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << palette[img[i][j]];
        }
        cout << '\n';
    }
    cout << "Розміри: " << rows << " x " << cols << '\n';
}

void findExtremes(int **img, int rows, int cols,
                  int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = minCol = maxRow = maxCol = 0;
    int minValue = *img[0];
    int maxValue = *img[0];

    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        for (int j = 0; j < cols; j++) {
            int pixel = *(row + j);
            if (pixel < minValue) {
                minValue = pixel;
                minRow = i;
                minCol = j;
            }
            if (pixel > maxValue) {
                maxValue = pixel;
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void showStatistics(int **img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "Найтемніший піксель: " << *(img[minRow] + minCol)
         << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")\n";
    cout << "Найсвітліший піксель: " << *(img[maxRow] + maxCol)
         << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")\n";

    int total = 0;
    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        for (int j = 0; j < cols; j++) {
            total += *(row + j);
        }
    }

    cout << fixed;
      cout << setprecision(2);
    cout << "Середня яскравість: " << double(total) / (rows * cols) << '\n';
    cout << "Середня по рядках:";
    for (int i = 0; i < rows; i++) {
        int sum = 0;
        int *row = img[i];
        for (int j = 0; j < cols; j++) {
            sum += *(row + j);
        }
        cout << ' ' << double(sum) / cols;
    }
    cout << '\n';
}

void invertImage(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
}

void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mirrorImage(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
}

int** rotateRight(int **img, int rows, int cols) {
    int **rotated = createImage(cols, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            rotated[j][rows - 1 - i] = img[i][j];
        }
    }

    deleteImage(img, rows);
    return rotated;
}

int main() {
    int rows, cols;

    cout << "Висота зображення (1..20): ";
    if (!readNumber(rows) || rows < 1 || rows > 20) {
        cout << "Помилка: висота має бути цілим числом від 1 до 20.\n";
        return 1;
    }

    cout << "Ширина зображення (1..20): ";
    if (!readNumber(cols) || cols < 1 || cols > 20) {
        cout << "Помилка: ширина має бути цілим числом від 1 до 20.\n";
        return 1;
    }

    int **img = createImage(rows, cols);
    cout << "Яскравість пікселів (цілі числа 0..9):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!readNumber(img[i][j]) || img[i][j] < 0 || img[i][j] > 9) {
                cout << "Помилка: яскравість має бути цілим числом від 0 до 9.\n";
                deleteImage(img, rows);
                return 1;
            }
        }
    }

    int choice = -1;
    do {
        cout << "\n1 - Показати зображення\n"
             << "2 - Статистика яскравості\n"
             << "3 - Інвертувати яскравість\n"
             << "4 - Віддзеркалити по горизонталі\n"
             << "5 - Повернути на 90 градусів праворуч\n"
             << "0 - Вийти\n"
             << "Ваш вибір: ";

        if (!readNumber(choice)) {
            if (cin.eof()) {
                cout << "\nВвід завершено.\n";
                break;
            }

            cout << "Помилка: введіть ціле число від 0 до 5.\n";
            cin.clear();
            char ch;
            while (cin.get(ch) && ch != '\n') {
            }
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
                cout << "Яскравість інвертовано.\n";
                showImage(img, rows, cols);
                break;
            case 4:
                mirrorImage(img, rows, cols);
                cout << "Зображення віддзеркалено.\n";
                showImage(img, rows, cols);
                break;
            case 5: {
                img = rotateRight(img, rows, cols);
                int temp = rows;
                rows = cols;
                cols = temp;
                cout << "Зображення повернуто.\n";
                showImage(img, rows, cols);
                break;
            }
            case 0:
                break;
            default:
                cout << "Помилка: такого пункту немає. Виберіть від 0 до 5.\n";
        }
    } while (choice != 0);

    deleteImage(img, rows);
    cout << "Роботу завершено.\n";
    return 0;
}
