#include <iostream>
#include <iomanip>

using namespace std;

const char* PALETTE = " .:-=+*#%@";

// Допоміжні функції

int** allocateImage(int rows, int cols) {
    int** img = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        img[i] = new int[cols];
    }
    return img;
}

void freeImage(int**& img, int rows) {
    if (img == nullptr) return;
    for (int i = 0; i < rows; ++i) {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
}

void swapPixels(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ---------- Основні операції ----------

void showImage(int** img, int rows, int cols) {
    cout << "\nЗображення " << rows << " x " << cols << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << img[i][j];
            if (j + 1 < cols) cout << ' ';
        }
        cout << '\n';
    }

    cout << "Малюнок:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << PALETTE[img[i][j]];
        }
        cout << '\n';
    }
    cout << "Розміри: " << rows << " x " << cols << "\n";
}

void findExtremes(int** img, int rows, int cols,
                  int& minRow, int& minCol,
                  int& maxRow, int& maxCol) {
    minRow = minCol = 0;
    maxRow = maxCol = 0;
    int minVal = img[0][0];
    int maxVal = img[0][0];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (img[i][j] < minVal) {
                minVal = img[i][j];
                minRow = i;
                minCol = j;
            }
            if (img[i][j] > maxVal) {
                maxVal = img[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void showStatistics(int** img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "\nНайтемніший піксель: " << img[minRow][minCol]
         << " (рядок " << (minRow + 1) << ", стовпець " << (minCol + 1) << ")\n";
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol]
         << " (рядок " << (maxRow + 1) << ", стовпець " << (maxCol + 1) << ")\n";

    // Середня яскравість усього зображення
    double sum = 0.0;
    for (int i = 0; i < rows; ++i) {
        int* row = img[i];                  // обхід через вказівник
        for (int j = 0; j < cols; ++j) {
            sum += *(row + j);
        }
    }
    double avg = sum / (rows * cols);
    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << avg << "\n";

    // Середня по рядках (теж через вказівник)
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; ++i) {
        int* row = img[i];
        double rowSum = 0.0;
        for (int j = 0; j < cols; ++j) {
            rowSum += *(row + j);
        }
        cout << (rowSum / cols);
        if (i + 1 < rows) cout << ' ';
    }
    cout << "\n";
}

void invertBrightness(int** img, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "\nЯскравість інвертовано.\n";
}

void mirrorHorizontal(int** img, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols / 2; ++j) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    cout << "\nЗображення віддзеркалено.\n";
}

int** rotateRight(int** img, int rows, int cols) {
    // Новий масив: cols рядків, rows стовпців
    int** newImg = allocateImage(cols, rows);

    // Перший рядок старого → останній стовпець нового
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    // Звільняємо старий масив
    freeImage(img, rows);

    return newImg;
}

// ---------- Валідація вводу ----------

bool readInt(int& value, int minVal, int maxVal, const char* prompt) {
    cout << prompt;
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка: очікувалося ціле число.\n";
        return false;
    }
    if (value < minVal || value > maxVal) {
        cout << "Помилка: значення має бути в діапазоні від "
             << minVal << " до " << maxVal << ".\n";
        return false;
    }
    return true;
}

// ---------- Головна програма ----------

int main() {
    int rows, cols;

    if (!readInt(rows, 1, 20, "Висота зображення: ")) return 1;
    if (!readInt(cols, 1, 20, "Ширина зображення: ")) return 1;

    int** image = allocateImage(rows, cols);

    cout << "Яскравість пікселів (0..9):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int val;
            if (!(cin >> val) || val < 0 || val > 9) {
                cout << "Помилка: піксель має бути числом від 0 до 9.\n";
                freeImage(image, rows);
                return 1;
            }
            image[i][j] = val;
        }
    }

    int choice;
    do {
        cout << "\n=== Меню ===\n"
             << "1. Показати зображення\n"
             << "2. Статистика яскравості\n"
             << "3. Інвертувати яскравість\n"
             << "4. Віддзеркалити по горизонталі\n"
             << "5. Повернути на 90 градусів праворуч\n"
             << "0. Вийти\n"
             << "Ваш вибір: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Невірний пункт меню.\n";
            continue;
        }

        switch (choice) {
            case 1:
                showImage(image, rows, cols);
                break;
            case 2:
                showStatistics(image, rows, cols);
                break;
            case 3:
                invertBrightness(image, rows, cols);
                break;
            case 4:
                mirrorHorizontal(image, rows, cols);
                break;
            case 5: {
                image = rotateRight(image, rows, cols);
                // Міняємо місцями розміри
                int tmp = rows;
                rows = cols;
                cols = tmp;
                cout << "\nЗображення повернуто. Нові розміри: "
                     << rows << " x " << cols << "\n";
                break;
            }
            case 0:
                cout << "Завершення роботи.\n";
                break;
            default:
                cout << "Невірний пункт меню. Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    // Обов’язкове звільнення пам’яті
    freeImage(image, rows);

    return 0;
}