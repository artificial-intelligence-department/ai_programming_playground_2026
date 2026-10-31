#include <iostream>
#include <iomanip>

using namespace std;

// Палітра символів (0 - пробіл, 9 - '@')
const char PALETTE[] = " .:-=+*#%@";

// Функція для очищення потоку cin у разі некоректного вводу
void clearInput() {
    cin.clear();
    while (cin.get() != '\n');
}

// 1. Показати зображення
void printImage(int** img, int rows, int cols) {
    cout << "\n--- Зображення " << rows << " x " << cols << " ---\n";
    // Вивід чисел
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << "\n";
    }

    // Вивід символів палітри
    cout << "\nМалюнок:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << PALETTE[img[i][j]];
        }
        cout << "\n";
    }
    cout << "------------------------\n";
}

// 2. Статистика яскравості
void findExtremes(int** img, int rows, int cols, int& minRow, int& minCol, int& maxRow, int& maxCol) {
    int minVal = 10;
    int maxVal = -1;

    for (int i = 0; i < rows; i++) {
        int* row = img[i]; // Обхід рядка через вказівник за вимогою ТЗ
        for (int j = 0; j < cols; j++) {
            int current = *(row + j);
            if (current < minVal) {
                minVal = current;
                minRow = i;
                minCol = j;
            }
            if (current > maxVal) {
                maxVal = current;
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void showStatistics(int** img, int rows, int cols) {
    int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "\nНайтемніший піксель: " << img[minRow][minCol]
        << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")\n";
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol]
        << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")\n";

    double totalSum = 0;
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        double rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        totalSum += rowSum;
        cout << fixed << setprecision(1) << (rowSum / cols) << " ";
    }
    cout << "\nСередня яскравість: " << fixed << setprecision(2) << (totalSum / (rows * cols)) << "\n";
}

// 3. Інвертувати яскравість
void invertBrightness(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "\nЯскравість інвертовано.\n";
}

// 4. Віддзеркалити по горизонталі
void swapPixels(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mirrorHorizontal(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    cout << "\nЗображення віддзеркалено.\n";
}

// 5. Повернути на 90 градусів праворуч
int** rotateRight(int** img, int rows, int cols) {
    // Виділяємо новий масив розміром cols на rows
    int** newImg = new int* [cols];
    for (int i = 0; i < cols; i++) {
        newImg[i] = new int[rows];
    }

    // Перенесення пікселів
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    // Звільнення старого масиву
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
    }
    delete[] img;

    cout << "\nЗображення повернуто.\n";
    return newImg;
}

// 6. Звільнення всієї динамічної пам'яті
void freeImage(int**& img, int rows) {
    if (img != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] img[i];
            img[i] = nullptr;
        }
        delete[] img;
        img = nullptr;
    }
}

int main() {
    // Налаштування локалі для виведення українського тексту
    setlocale(LC_ALL, "Ukrainian");

    int rows = 0, cols = 0;

    // Валідація вводу розмірів
    while (true) {
        cout << "Висота зображення (1..20): ";
        if (cin >> rows && rows >= 1 && rows <= 20) break;
        cout << "Помилка! Введіть ціле число від 1 до 20.\n";
        clearInput();
    }

    while (true) {
        cout << "Ширина зображення (1..20): ";
        if (cin >> cols && cols >= 1 && cols <= 20) break;
        cout << "Помилка! Введіть ціле число від 1 до 20.\n";
        clearInput();
    }

    // Динамічне виділення пам'яті під зображення rows x cols
    int** image = new int* [rows];
    for (int i = 0; i < rows; i++) {
        image[i] = new int[cols];
    }

    // Введення пікселів з валідацією межі 0..9
    cout << "Введіть яскравість пікселів (" << rows << " рядків по " << cols << " чисел від 0 до 9):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            while (true) {
                if (cin >> image[i][j] && image[i][j] >= 0 && image[i][j] <= 9) {
                    break;
                }
                cout << "Помилка в пікселі [" << i + 1 << "][" << j + 1 << "]! Має бути число від 0 до 9. Спробуйте ще раз: ";
                clearInput();
            }
        }
    }

    int choice;
    // Головний цикл меню do-while
    do {
        cout << "\n=== МЕНЮ ===\n"
            << "1. Показати зображення\n"
            << "2. Статистика яскравості\n"
            << "3. Інвертувати яскравість\n"
            << "4. Віддзеркалити по горизонталі\n"
            << "5. Повернути на 90 градусів праворуч\n"
            << "0. Вийти\n"
            << "Обраний пункт: ";

        if (!(cin >> choice)) {
            cout << "Некоректний вибір! Оберіть число з меню.\n";
            clearInput();
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            printImage(image, rows, cols);
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
            // Після повороту міняємо розміри місцями
            int temp = rows;
            rows = cols;
            cols = temp;
            break;
        case 0:
            cout << "Вихід з програми...\n";
            break;
        default:
            cout << "Такого пункту меню немає!\n";
            break;
        }
    } while (choice != 0);

    // Звільнення пам'яті перед виходом
    freeImage(image, rows);

    return 0;
}