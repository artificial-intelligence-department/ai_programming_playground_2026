/*
Епік 4. Практичне завдання: Редактор монохромного зображення
Автор: Туревич Олександр
Група: ШІ-12
*/

#include <iostream>
#include <iomanip>

using namespace std;

// Палітра з 10 символів від темного до світлого
const char symbols[] = " .:-=+*#%@";

// Допоміжна функція обміну двох пікселів за вказівниками
void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 1. Показати зображення
void showImage(int **img, int rows, int cols) {
    cout << "\nЗображення " << rows << " x " << cols << ":" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nМалюнок:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << symbols[img[i][j]];
        }
        cout << endl;
    }
    cout << "Поточні розміри: " << rows << " x " << cols << "\n" << endl;
}

// 2. Найтемніший і найсвітліший пікселі разом з їхніми координатами.

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0; 
    minCol = 0;
    maxRow = 0; 
    maxCol = 0;
    int minVal = *(*(img + 0) + 0);
    int maxVal = *(*(img + 0) + 0);

    for (int i = 0; i < rows; ++i) {
        int *row = *(img + i);
        for (int j = 0; j < cols; ++j) {
            int val = *(row + j); // обхід через вказівник
            if (val < minVal) {
                minVal = val;
                minRow = i;
                minCol = j;
            }
            if (val > maxVal) {
                maxVal = val;
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void showStatistics(int **img, int rows, int cols) {
    int minR, minC, maxR, maxC;
    findExtremes(img, rows, cols, minR, minC, maxR, maxC);

    cout << "\nНайтемніший піксель: " << img[minR][minC] << " (рядок " << minR + 1 << ", стовпець " << minC + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << img[maxR][maxC] << " (рядок " << maxR + 1 << ", стовпець " << maxC + 1 << ")" << endl;

    double totalSum = 0;
    cout << fixed << setprecision(2);

    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; ++i) {
        double rowSum = 0;
        int *row = *(img + i);
        for (int j = 0; j < cols; ++j) {
            rowSum += *(row + j);
        }
        totalSum += rowSum;
        cout << (rowSum / cols) << " ";
    }
    cout << endl;

    cout << "Середня яскравість: " << (totalSum / (rows * cols)) << "\n" << endl;
}

// 3. Інвертувати яскравість (9 - val)
void invertBrightness(int **img, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "\nЯскравість інвертовано." << endl;
}

// 4. Віддзеркалити по горизонталі
void mirrorHorizontal(int **img, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols / 2; ++j) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    cout << "\nЗображення віддзеркалено." << endl;
}

// 5. Повернути на 90 градусів праворуч:

int** rotateRight(int **img, int &rows, int &cols) {
    int newRows = cols;
    int newCols = rows;

    int **newImg = new int*[newRows];
    for (int i = 0; i < newRows; ++i) {
        newImg[i] = new int[newCols];
    }

    // Перенесення пікселів
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    // Звільнення старого масиву
    for (int i = 0; i < rows; ++i) {
        delete[] img[i];
    }
    delete[] img;

    rows = newRows;
    cols = newCols;

    cout << "\nЗображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    return newImg;
}

// Очищення динамічної пам'яті
void delImage(int **&img, int rows) {
    if (img != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] img[i];
        }
        delete[] img;
        img = nullptr;
    }
}

int main() {
    

    int rows, cols;

    cout << "Введіть висоту зображення (rows, 1..20): ";
    if (!(cin >> rows) || rows < 1 || rows > 20) {
        cout << "Помилка: висота має бути числом від 1 до 20." << endl;
        return 1;
    }

    cout << "Введіть ширину зображення (cols, 1..20): ";
    if (!(cin >> cols) || cols < 1 || cols > 20) {
        cout << "Помилка: ширина має бути числом від 1 до 20." << endl;
        return 1;
    }

    // Динамічне виділення пам'яті під зображення
    int **image = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        image[i] = new int[cols];
    }

    cout << "Введіть пікселі (" << rows << " рядків по " << cols << " чисел від 0 до 9):" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(cin >> image[i][j]) || image[i][j] < 0 || image[i][j] > 9) {
                cout << "Помилка: неприпустиме значення яскравості." << endl;
                delImage(image, rows);
                return 1;
            }
        }
    }

    int choice;
    do {
        cout << "\n--- Меню ---" << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" << endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вийти" << endl;
        cout << "Ваш вибір: ";

        if (!(cin >> choice)) {
            cout << "Некоректний ввід. Завершення роботи." << endl;
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
            case 5:
                image = rotateRight(image, rows, cols);
                break;
            case 0:
                cout << "Вихід з програми" << endl;
                break;
            default:
                cout << "Невірний пункт меню, спробуйте ще раз." << endl;
        }
    } while (choice != 0);

    // Звільнення пам'яті перед виходом
    delImage(image, rows);

    return 0;
}
