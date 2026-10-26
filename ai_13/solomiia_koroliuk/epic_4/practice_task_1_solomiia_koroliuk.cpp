/* 
    Class Practice task 
    Соломія Королюк 
    ШІ-13
*/

#include <iostream>
#include <iomanip>   // для setprecision та fixed

using namespace std;

// ---------- Прототипи функцій ----------
int** createImage(int rows, int cols);
void freeImage(int** img, int rows);

void printImage(int** img, int rows, int cols, bool asSymbols = false);
void findExtremes(int** img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void swapPixels(int* a, int* b);

void showImage(int** img, int rows, int cols);
void showStats(int** img, int rows, int cols);
void invertImage(int** img, int rows, int cols);
void mirrorImage(int** img, int rows, int cols);
int** rotateRight(int** img, int rows, int cols);

// Палітра: позиція символу відповідає яскравості
const char palette[] = " .:-=+*#%@";

int main() {
    cout << "Висота зображення (1-20): ";
    int rows;
    cin >> rows;

    if (cin.fail() || rows < 1 || rows > 20) {
        cout << "Значення повинно бути в діапазоні від 1 до 20." << endl;
        return 1;
    }

    cout << "Ширина зображення (1-20): ";
    int cols;
    cin >> cols;

    if (cin.fail() || cols < 1 || cols > 20) {
        cout << "Значення повинно бути в діапазоні від 1 до 20." << endl;
        return 1;
    }

    // Виділяємо динамічну памʼять під зображення
    int** image = createImage(rows, cols);

    cout << "Яскравість пікселів (0..9): " << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> image[i][j];

            if (cin.fail() || image[i][j] < 0 || image[i][j] > 9) {
                cout << "Помилка вводу! Введіть число від 0 до 9." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                freeImage(image, rows);   //звільняємо памʼять перед виходом
                return 1;
            }
        }
    }

    short choise;

    do {
        cout << "\n===== МЕНЮ =====" << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" << endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";

        cin >> choise;

        // Перевірка на некоректний ввід
        if (cin.fail()) {
            cin.clear();               // скидаємо прапорець помилки
            cin.ignore(10000, '\n');   // очищаємо буфер від некоректних символів
            cout << "Помилка: введіть число від 0 до 5!" << endl;
            choise = -1;               // щоб цикл не завершився випадково
            continue;                  // переходимо на наступну ітерацію циклу
        }
        cin.ignore(10000, '\n');       // прибираємо зайве в кінці рядка

        switch (choise) {
            case 1:
                showImage(image, rows, cols);
                break;
            case 2:
                showStats(image, rows, cols);
                break;
            case 3:
                invertImage(image, rows, cols);
                break;
            case 4:
                mirrorImage(image, rows, cols);
                break;
            case 5: {
                image = rotateRight(image, rows, cols);

                int temp = rows;
                rows = cols;
                cols = temp;

                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
                printImage(image, rows, cols, false);
                break;
            }
            case 0:
                cout << "Ви здійснили вихід." << endl;
                break;
            default:
                cout << "Невірний пункт меню! Введіть число від 0 до 5." << endl;
        }

    } while (choise != 0);

    freeImage(image, rows);
    image = nullptr;

    return 0;
}


// ---------- Робота з памʼяттю ----------

// Створює двовимірний динамічний масив rows x cols
int** createImage(int rows, int cols) {
    int** img = new int*[rows];          // масив вказівників на рядки
    for (int i = 0; i < rows; i++) {
        img[i] = new int[cols];          // кожен рядок окремо
    }
    return img;
}

// Звільняє памʼять: спочатку кожен рядок, потім масив вказівників
void freeImage(int** img, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
}


// ---------- Допоміжні функції ----------

// Функція для показу зображення 
void printImage(int** img, int rows, int cols, bool asSymbols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            int val = img[i][j];

            if (asSymbols) cout << palette[val];
            else cout << val << " ";

        }
        cout << endl;
    }
}

// Обмін двох пікселів через вказівники
void swapPixels(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Шукає найтемніший і найсвітліший піксель
void findExtremes(int** img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0; minCol = 0;
    maxRow = 0; maxCol = 0;

    for (int i = 0; i < rows; i++) {
        int* row = img[i]; // вказівник на поточний рядок
        for (int j = 0; j < cols; j++) {
            if (*(row + j) < img[minRow][minCol]) {
                minRow = i;
                minCol = j;
            }
            if (*(row + j) > img[maxRow][maxCol]) {
                maxRow = i;
                maxCol = j;
            }
        }
    }
}


// ---------- Пункти меню ----------

// Пункт 1: показати зображення числами і символами + розміри
void showImage(int** img, int rows, int cols) {
    cout << "\nЗображення:" << rows << " x " << cols << endl;
    printImage(img, rows, cols, false);

    cout << "\nМалюнок:" << endl;
    printImage(img, rows, cols, true);
}

// Пункт 2: статистика яскравості
void showStats(int** img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "Найтемніший піксель: " << img[minRow][minCol]
         << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol]
         << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    // Рахуємо суму всього зображення та кожного рядка
    double* rowAvg = new double[rows];   // середні по рядках
    int total = 0;

    for (int i = 0; i < rows; i++) {
        int* row = img[i];               // обхід через вказівник
        int rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        total += rowSum;
        rowAvg[i] = double(rowSum) / cols;
    }

    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << double(total) / (rows * cols) << endl;

    cout << setprecision(1);
    cout << "Середня по рядках:";
    for (int i = 0; i < rows; i++) {
        cout << " " << rowAvg[i];
    }
    cout << endl;

    delete[] rowAvg; // звільняємо тимчасовий масив
    rowAvg = nullptr;
}

// Пункт 3: інверсія 
void invertImage(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }

    cout << "Яскравість інвертовано." << endl;
    printImage(img, rows, cols, false);
}

// Пункт 4: віддзеркалення по горизонталі
void mirrorImage(int** img, int rows, int cols) {
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;
    printImage(img, rows, cols, false);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }

    cout << "Результат:" << endl;
    printImage(img, rows, cols, false);
}

// Пункт 5: поворот на 90 градусів праворуч.
int** rotateRight(int** img, int rows, int cols) {

    int** result = createImage(cols, rows);

    // перший рядок старого -> останній стовпець нового
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][rows - 1 - i] = img[i][j];
        }
    }

    freeImage(img, rows);

    return result;
}
