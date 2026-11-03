#include <iostream>
#include <iomanip>
using namespace std;
// функція для безпечного зчитування цілого числа з повідомленням
int readInt(const char* message) {
    int value;
    while (true) {
        cout << message;
        if (cin >> value) {
            return value;
        }

        cout << "Помилка: введіть ціле число.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}
// функція для виділлення пам'яті для зображення
int** createImage(int rows, int cols) {
    int** img = new int*[rows];
// Виділення пам'яті для кожного рядка
    for (int i = 0; i < rows; i++) {
        img[i] = new int[cols];
    }

    return img;
}
//функція для звільнення пам'яті динамічного двовимірного масиву
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
//функція для введення яскравості пікселів
bool inputImage(int** img, int rows, int cols) {
    cout << "Введіть яскравість пікселів (0..9):\n";
//цикл для введення значень пікселів
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            while (true) {
                cout << "Піксель [" << i + 1 << "][" << j + 1 << "]: ";
                if (cin >> img[i][j]) {
                    // перевірка на допустимий діапазон значень
                    if (img[i][j] >= 0 && img[i][j] <= 9) {
                        break;
                    }

                    cout << "Помилка: значення має бути від 0 до 9.\n";
                } else {
                    cout << "Помилка: введіть ціле число.\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }
        }
    }
    return true;
}
//функція для відображення зображення у вигляді таблиці та малюнка
void showImage(int** img, int rows, int cols) {
    const char palette[] = " .:-=+*#%@";
//виведення таблиці чисел
    cout << "\nТаблиця чисел:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << ' ';
        }
        cout << '\n';
    }
//виведення графічного малюнка з використанням символів палітри
    cout << "\nМалюнок:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << palette[img[i][j]];
        }
        cout << '\n';
    }

    cout << "Розміри зображення: " << rows << " x " << cols << "\n";
}
// Функція для знаходження координат найтемнішого та найсвітлішого пікселів
void findExtremes(int** img, int rows, int cols,
                  int& minRow, int& minCol, int& maxRow, int& maxCol) {
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
//цикл для пошуку мінімального та максимального значень пікселів
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (img[i][j] < img[minRow][minCol]) {
                minRow = i;
                minCol = j;
            }

            if (img[i][j] > img[maxRow][maxCol]) {
                maxRow = i;
                maxCol = j;
            }
        }
    }
}
// функція для обчислення статистики яскравості та виведення результатів
void showStatistics(int** img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "\nНайтемніший піксель: " << img[minRow][minCol]
         << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")\n";
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol]
         << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")\n";

    int total = 0;
    //цикл для обчислення середньої яскравості кожного рядка та всього зображення
    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        int rowSum = 0;

        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }

        total += rowSum;
        cout << "Середня яскравість рядка " << i + 1 << ": "
             << fixed << setprecision(2)
             << 1.0 * rowSum / cols << '\n';
    }

    cout << "Середня яскравість усього зображення: "
         << fixed << setprecision(2)
         << 1.0 * total / (rows * cols) << '\n';
}
//функція для інвертування яскравості пікселів (9 - минула яскравіть)
void invertImage(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "Яскравість інвертовано.\n";
}
// функція для обміну значень двох пікселів
void swapPixels(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
//функція для віддзеркалення зображення по горизонталі
void mirrorImage(int** img, int rows, int cols) {
    //цикл для обміну пікселів у кожному рядку з протилежними
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    cout << "Зображення віддзеркалено по горизонталі.\n";
}
//функція для повороту зображення на 90 градусів праворуч
int** rotateRight(int** img, int rows, int cols) {
    int** rotated = createImage(cols, rows);
// Поворот на 90 градусів праворуч, новий рядок стає старим стовпцем у зворотному порядку
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            rotated[j][rows - 1 - i] = img[i][j];
        }
    }

    freeImage(img, rows);
    return rotated;
}

int main() { 
    //зчитування розмірів зображення з перевіркою на допустимий діапазон
    int rows = readInt("Висота зображення (1..20): ");
    if (rows < 1 || rows > 20) {
        cout << "Помилка: висота має бути від 1 до 20.\n";
        return 1;
    }

    int cols = readInt("Ширина зображення (1..20): ");
    if (cols < 1 || cols > 20) {
        cout << "Помилка: ширина має бути від 1 до 20.\n";
        return 1;
    }
//створення динамічного двовимірного масиву для зображення та введення даних
    int** img = createImage(rows, cols);
    if (!inputImage(img, rows, cols)) {
        freeImage(img, rows);
        return 1;
    }

    int choice;
    do { 
        cout << "\n--- МЕНЮ ---\n";
        cout << "1. Показати зображення\n";
        cout << "2. Статистика яскравості\n";
        cout << "3. Інвертувати яскравість\n";
        cout << "4. Віддзеркалити по горизонталі\n";
        cout << "5. Повернути на 90 градусів праворуч\n";
        cout << "0. Вийти\n";

        choice = readInt("Ваш вибір: ");

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
                mirrorImage(img, rows, cols);
                break;
            case 5: {
                img = rotateRight(img, rows, cols);
                int temp = rows;
                rows = cols;
                cols = temp;
                cout << "Зображення повернуто. Нові розміри: "
                     << rows << " x " << cols << '\n';
                break;
            }
            case 0:
                break;
            default:
                cout << "Невірний пункт меню. Виберіть число від 0 до 5.\n";
        }
    } while (choice != 0);

    freeImage(img, rows);
    cout << "Пам'ять звільнено. Роботу завершено.\n";
    return 0;
}
