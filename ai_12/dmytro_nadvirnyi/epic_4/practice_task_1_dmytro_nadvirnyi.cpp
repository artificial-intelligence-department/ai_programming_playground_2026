/*
    Редактор монохромного зображення
    Автор: Дмитро Надвірний
    Група: 12
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Валідація вводу. Повертає true, якщо число зчитано і воно в межах [minVal, maxVal].
// retry = true  -> при помилці просимо ввести ще раз (меню);
// retry = false -> повідомляємо про помилку і повертаємо false (розміри, пікселі).
// Кінець вводу (EOF) також повертає false, щоб програма не зациклилась.
bool getValidInt(int& value, int minVal, int maxVal, const string& errorMsg, bool retry) {
    while (true) {
        if (cin >> value && value >= minVal && value <= maxVal) {
            return true;
        }
        if (cin.eof()) {
            cout << "\nКінець вводу.\n";
            return false;
        }
        cout << errorMsg;
        if (!retry) {
            return false;
        }
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Виділення пам'яті
int** allocateImage(int rows, int cols) {
    int** img = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        img[i] = new int[cols];
    }
    return img;
}

// Звільнення пам'яті
void freeImage(int**& img, int rows) {
    if (img == nullptr) return;
    for (int i = 0; i < rows; ++i) {
        delete[] img[i];
    }
    delete[] img;
    img = nullptr;
}

// Таблиця чисел (рядок за рядком, числа через пробіл)
void printTable(int** img, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << img[i][j] << (j == cols - 1 ? "" : " ");
        }
        cout << "\n";
    }
}

// Пункт 1: показати зображення
void printImage(int** img, int rows, int cols) {
    const char palette[] = " .:-=+*#%@";

    cout << "\nЗображення " << rows << " x " << cols << ":\n";
    printTable(img, rows, cols);

    cout << "\nМалюнок:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << palette[img[i][j]];
        }
        cout << "\n";
    }
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    int minVal = img[0][0];
    int maxVal = img[0][0];

    // Стартові координати (з 1)
    minRow = minCol = maxRow = maxCol = 1;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Строге порівняння: при однакових значеннях лишається перше в порядку обходу
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

// Пункт 2: статистика яскравості
void printStatistics(int **img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    int minVal = img[minRow - 1][minCol - 1];
    int maxVal = img[maxRow - 1][maxCol - 1];

    cout << "\nНайтемніший піксель: " << minVal
         << " (рядок " << minRow << ", стовпець " << minCol << ")\n";
    cout << "Найсвітліший піксель: " << maxVal
         << " (рядок " << maxRow << ", стовпець " << maxCol << ")\n";

    double totalSum = 0;
    double* rowAvg = new double[rows];

    for (int i = 0; i < rows; ++i) {
        int *row = img[i]; // обхід рядка через вказівник
        double rowSum = 0;

        for (int j = 0; j < cols; ++j) {
            rowSum += *(row + j);
        }

        totalSum += rowSum;
        rowAvg[i] = rowSum / cols;
    }

    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << totalSum / (rows * cols) << "\n";

    cout << setprecision(1);
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; ++i) {
        cout << rowAvg[i] << (i == rows - 1 ? "" : " ");
    }
    cout << "\n";
    cout.unsetf(ios::fixed);

    delete[] rowAvg;
}

// Пункт 3: інверсія
void invertImage(int** img, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
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

// Пункт 4: віддзеркалення по горизонталі
void mirrorHorizontal(int** img, int rows, int cols) {
    cout << "\nПочаткове:\n";
    printTable(img, rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols / 2; ++j) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }

    cout << "\nЗображення віддзеркалено.\n\nРезультат:\n";
    printTable(img, rows, cols);
}

int** rotateRight(int** img, int rows, int cols) {
    int** newImg = allocateImage(cols, rows);

    // Спочатку переносимо пікселі (обхід зі зміною порядку індексів)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    // І лише потім звільняємо старий масив
    freeImage(img, rows);

    return newImg;
}

// Пункт 5: поворот + обмін розмірів
void rotateImage(int**& img, int& rows, int& cols) {
    img = rotateRight(img, rows, cols);

    int temp = rows;
    rows = cols;
    cols = temp;

    cout << "\nЗображення повернуто. Нові розміри: " << rows << " x " << cols << "\n";
    printTable(img, rows, cols);
}

int main() {
    int** img = nullptr;
    int rows = 0, cols = 0;
    bool ok = true;

    cout << "Введіть висоту зображення (1..20): ";
    ok = getValidInt(rows, 1, 20, "Помилка! Висота має бути числом від 1 до 20.\n", false);

    if (ok) {
        cout << "Введіть ширину зображення (1..20): ";
        ok = getValidInt(cols, 1, 20, "Помилка! Ширина має бути числом від 1 до 20.\n", false);
    }

    if (ok) {
        // Виділяємо пам'ять один раз
        img = allocateImage(rows, cols);

        cout << "Введіть пікселі зображення (значення від 0 до 9):\n";
        for (int i = 0; i < rows && ok; ++i) {
            for (int j = 0; j < cols && ok; ++j) {
                ok = getValidInt(img[i][j], 0, 9, "Помилка! Яскравість пікселя має бути числом від 0 до 9.\n", false);
            }
        }
    }

    if (ok) {
        int choice = -1;
        do {
            cout << "\n--- МЕНЮ ---\n";
            cout << "1. Показати зображення\n";
            cout << "2. Статистика яскравості\n";
            cout << "3. Інвертувати яскравість\n";
            cout << "4. Віддзеркалити по горизонталі\n";
            cout << "5. Повернути на 90° праворуч\n";
            cout << "0. Вийти\n";
            cout << "Виберіть пункт: ";

            if (!getValidInt(choice, 0, 5, "Помилка! Виберіть число від 0 до 5: ", true)) {
                ok = false;
                break;
            }

            switch (choice) {
                case 1: printImage(img, rows, cols); break;
                case 2: printStatistics(img, rows, cols); break;
                case 3: invertImage(img, rows, cols); break;
                case 4: mirrorHorizontal(img, rows, cols); break;
                case 5: rotateImage(img, rows, cols); break;
                case 0: cout << "\nЗавершення роботи. До побачення!\n"; break;
            }
        } while (choice != 0);
    }

    // Пам'ять звільняється в будь-якому випадку (nullptr, якщо не виділяли)
    freeImage(img, rows);

    if (!ok) {
        cout << "Програму завершено через некоректні дані.\n";
    }
    return 0;
}