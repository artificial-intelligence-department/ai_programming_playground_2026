// Практичне завдання (Епік 4): Редактор монохромного зображення
#include <iostream>
#include <iomanip>

using namespace std;

// Палітра з десяти символів для відображення яскравості (від 0 до 9)
const string PALETTE = " .:-=+*#%@";

// 1. Вивід зображення
void showImage(int **image, int rows, int cols) {
    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << image[i][j];
            if (j != cols - 1) {
            cout << " ";
            }
        }
        cout << endl;
    }
    
    cout << endl << "Малюнок:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int val = image[i][j];
            if (val >= 0 && val <= 9) {
                cout << PALETTE[val];
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
    cout << endl << "Поточні розміри: " << rows << " x " << cols << endl;
}

// Функція пошуку екстремумів через параметри-посилання
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    int minVal = 10;
    int maxVal = -1;
    minRow = 1;
    minCol = 1;
    maxRow = 1;
    maxCol = 1;

    for (int i = 0; i < rows; ++i) {
        int *row = image[i]; // Отримуємо вказівник на рядок
        for (int j = 0; j < cols; ++j) {
            int val = *(row + j); // Звернення через вказівник
            if (val < minVal) {
                minVal = val;
                minRow = i + 1;
                minCol = j + 1;
            }
            if (val > maxVal) {
                maxVal = val;
                maxRow = i + 1;
                maxCol = j + 1;
            }
        }
    }
}

// 2. Статистика яскравості
void showStatistics(int **image, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);

    int minVal = image[minRow - 1][minCol - 1];
    int maxVal = image[maxRow - 1][maxCol - 1];

    cout << "Найтемніший піксель: " << minVal << " (рядок " << minRow << ", стовпець " << minCol << ")" << endl;
    cout << "Найсвітліший піксель: " << maxVal << " (рядок " << maxRow << ", стовпець " << maxCol << ")" << endl;

    double totalSum = 0;

    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; ++i) {
        int *row = image[i]; // Обхід рядка через вказівник
        double rowSum = 0;
        for (int j = 0; j < cols; ++j) {
            int val = *(row + j);
            rowSum += val;
            totalSum += val;
        }
        cout << fixed << setprecision(1) << (rowSum / cols);
        if (i != rows - 1) {
            cout << " ";
        }
    }
    cout << endl;

    int totalPixels = rows * cols;
    double avgBrightness;
    if (totalPixels > 0) {
        avgBrightness = totalSum / totalPixels;
    } else {
        avgBrightness = 0;
    }
    cout << fixed << setprecision(2) << "Середня яскравість: " << avgBrightness << endl;
}

// 3. Інвертувати яскравість
void invertBrightness(int **image, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            image[i][j] = 9 - image[i][j];
        }
    }
    cout << "Яскравість інвертовано." << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << image[i][j];
            if (j != cols - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

// Функція обміну двох пікселів за їх адресами
void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 4. Віддзеркалити по горизонталі
void mirrorHorizontal(int **image, int rows, int cols) {
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;
    
    // Створюємо тимчасову копію для виводу "Початкове" відповідно до прикладу
    int **tempImg = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        tempImg[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            tempImg[i][j] = image[i][j];
        }
    }

    // Виконуємо віддзеркалення на місці в оригінальному масиві
    for (int i = 0; i < rows; ++i) {
        int *row = image[i];
        for (int j = 0; j < cols / 2; ++j) {
            swapPixels(row + j, row + cols - 1 - j);
        }
    }

    // Вивід початкового стану (з тимчасової копії)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << tempImg[i][j];
            if (j != cols - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    // Звільняємо тимчасову копію
    for (int i = 0; i < rows; ++i) {
        delete[] tempImg[i];
    }
    delete[] tempImg;

    cout << endl << "Результат:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << image[i][j];
            if (j != cols - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

// 5. Повернути на 90 градусів праворуч (int бо повертається в main)
int** rotateRight(int **image, int rows, int cols) { 
    int newRows = cols;
    int newCols = rows;

    int **newImage = new int*[newRows];
    for (int i = 0; i < newRows; ++i) {
        newImage[i] = new int[newCols];
    }

    for (int i = 0; i < newRows; ++i) {
        int *newRow = newImage[i];
        for (int j = 0; j < newCols; ++j) {
            *(newRow + j) = image[rows - 1 - j][i];
        }
    }

    // Звільняємо старий масив перед поверненням нового
    for (int i = 0; i < rows; ++i) {
        delete[] image[i];
    }
    delete[] image;

    return newImage;
}

// Функція безпечного звільнення динамічної пам'яті
void freeMemory(int **&image, int &rows) {
    if (image != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] image[i];
        }
        delete[] image;
        image = nullptr;
        rows = 0;
    }
}

int main() {
    int rows, cols;

    cout << "Висота зображення: ";
    if (!(cin >> rows) || rows < 1 || rows > 20) {
        cout << "Помилка: висота поза допустимими межами (1-20)." << endl;
        return 0;
    }

    cout << "Ширина зображення: ";
    if (!(cin >> cols) || cols < 1 || cols > 20) {
        cout << "Помилка: ширина поза допустимими межами (1-20)." << endl;
        return 0;
    }

    int **image = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        image[i] = new int[cols];
    }

    cout << "Яскравість пікселів (0..9):" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(cin >> image[i][j]) || image[i][j] < 0 || image[i][j] > 9) {
                cout << "Помилка: значення яскравості має бути від 0 до 9." << endl;
                // Звільняємо вже виділену пам'ять до моменту помилки
                for (int k = 0; k <= i; ++k) {
                    delete[] image[k];
                }
                delete[] image;
                return 0;
            }
        }
    }

    int choice;
    do {
        cout << endl << "Меню:" << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" << endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вийти" << endl;
        cout << "Виберіть пункт: ";

        if (!(cin >> choice)) {
            cout << "Помилка вводу. Завершення програми." << endl;
            break;
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
                int oldRows = rows;
                int oldCols = cols;
                image = rotateRight(image, rows, cols);
                rows = oldCols;
                cols = oldRows;
                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
                showImage(image, rows, cols);
                break;
            }
            case 0:
                cout << "Вихід з програми." << endl;
                break;
            default:
                cout << "Невірний пункт меню. Спробуйте ще раз." << endl;
                break;
        }
    } while (choice != 0);
   // Фінальне звільнення пам'яті
    freeMemory(image, rows);

    return 0;
}