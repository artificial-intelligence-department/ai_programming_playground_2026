
/*
    Редактор монохромного зображення
    Автор: Рубаха Олексій
    Група: ШІ-13
*/

#include <iostream>
#include <iomanip>

using namespace std;

// Прототипи функцій
int** createImage(int rows, int cols);
void freeImage(int** img, int rows);
void showImage(int** img, int rows, int cols);
void showImageData(int** img, int rows, int cols);
void showImagePixels(int** img, int rows, int cols);
void showStatistics(int** img, int rows, int cols);
void findExtremes(int** img, int rows, int cols, int& minRow, int& minCol, int& maxRow, int& maxCol);
void invertImage(int** img, int rows, int cols);
void swapPixels(int* a, int* b);
void mirrorImage(int** img, int rows, int cols);
int** rotateRight(int** img, int rows, int cols);
void showMenu();

// Створення динамічного двовимірного масиву
int** createImage(int rows, int cols) {
    int** img = new int*[rows];

    for (int i = 0; i < rows; i++) {
        img[i] = new int[cols];
    }
    
    return img;
}

// Звільнення пам'яті
void freeImage(int** img, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }

    delete[] img;
    img = nullptr;
}

// Виведення таблиці чисел
void showImageData(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j];

            if (j < cols - 1) {
                cout << ' ';
            }
        }

        cout << '\n';
    }
}

// Виведення зображення символами
void showImagePixels(int** img, int rows, int cols) {
    const char palette[] = " .:-=+*#%@";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << palette[img[i][j]];
        }

        cout << '\n';
    }
}

// Пункт 1. Показати зображення
void showImage(int** img, int rows, int cols) {
    cout << "\nЗображення " << rows << " x " << cols << ":\n";
    showImageData(img, rows, cols);

    cout << "\nМалюнок:\n";
    showImagePixels(img, rows, cols);

    cout << "\nПоточні розміри: "
         << rows << " x " << cols << '\n';
}

// Пошук найтемнішого та найсвітлішого пікселів
void findExtremes(int** img, int rows, int cols, int& minRow, int& minCol, int& maxRow, int& maxCol) {
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    int minValue = img[0][0];
    int maxValue = img[0][0];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (img[i][j] < minValue) {
                minValue = img[i][j];
                minRow = i;
                minCol = j;
            }

            if (img[i][j] > maxValue) {
                maxValue = img[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

// Пункт 2. Статистика яскравості
void showStatistics(int** img, int rows, int columns) {
    int minRow, minColumn, maxRow, maxColumn;
    findExtremes(img, rows, columns, minRow, minColumn, maxRow, maxColumn);

    cout << "\nНайтемніший піксель: " << img[minRow][minColumn] << " (рядок " << minRow + 1
        << ", стовпець " << minColumn + 1 << ")\n";
    cout << "Найсвітліший піксель: " << img[maxRow][maxColumn] << " (рядок " << maxRow + 1
        << ", стовпець " << maxColumn + 1 << ")\n";

    //знаходимо суму елемнтів для пошуку середнього
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        int* row = img[i];

        for (int j = 0; j < columns; j++) {
            sum += *(row + j);
        }
    }

    double average = (double)sum / (rows * columns);
    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << average << '\n';

    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        int rowSum = 0;

        for (int j = 0; j < columns; j++) {
            rowSum += *(row + j);
        }

        double rowAverage = (double)rowSum / columns;
        cout << setprecision(1) << rowAverage;

        if (i < rows - 1) {
            cout << ' ';
        }
    }

    cout << '\n';
    cout << setprecision(2);
}

// Пункт 3. Інвертувати яскравість
void invertImage(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }

    cout << "\nЯскравість інвертовано.\n";
    showImageData(img, rows, cols);
}

// Обмін двох пікселів через вказівники
void swapPixels(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Пункт 4. Віддзеркалити по горизонталі
void mirrorImage(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols-j-1]);
        }
    }

    cout << "\nЗображення віддзеркалено.\n";
    showImageData(img, rows, cols);
}

// Пункт 5. Поворот на 90 градусів праворуч
int** rotateRight(int** img, int rows, int cols) {
    int** rotated = createImage(cols, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            rotated[j][rows-i-1] = img[i][j];
        }
    }

    freeImage(img, rows);

    return rotated;
}

// Виведення меню
void showMenu() {
    cout << "\n========== МЕНЮ ==========\n";
    cout << "1. Показати зображення\n";
    cout << "2. Статистика яскравості\n";
    cout << "3. Інвертувати яскравість\n";
    cout << "4. Віддзеркалити по горизонталі\n";
    cout << "5. Повернути на 90 градусів праворуч\n";
    cout << "0. Вийти\n";
    cout << "Ваш вибір: ";
}

int main() {
    int rows, columns;

    //коректне введення Rows
    cout << "Висота зображення: ";
    cin >> rows;
    if (cin.fail()) {
        cout << "Помилка: висота має бути цілим числом.\n";
        return 1;
    }
    if (rows < 1 || rows > 20) {
        cout << "Помилка: висота має бути від 1 до 20.\n";
        return 1;
    }

    //коректне введення columns
    cout << "Ширина зображення: ";
    cin >> columns;
    if (cin.fail()) {
        cout << "Помилка: ширина має бути цілим числом.\n";
        return 1;
    }
    if (columns < 1 || columns > 20) {
        cout << "Помилка: ширина має бути від 1 до 20.\n";
        return 1;
    }

    int** img = createImage(rows, columns); //створення зображення
    cout << "Яскравість пікселів (0..9):\n";

    //Введення значень таблиці (0-9)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cin>>img[i][j];

            if (cin.fail()){
                cout << "Помилка: яскравість має бути цілим числом";

                freeImage(img, rows);
                return 1;
            }
            if (img[i][j] < 0 || img[i][j] > 9) {
                cout << "Помилка: яскравість має бути від 0 до 9.\n";

                freeImage(img, rows);
                return 1;
            }
        }
    }


    int choice;
    bool running = true;

    do {
        showMenu();

        cin >> choice;
        if (cin.fail()){
            cout << "Помилка: введіть ціле число від 0 до 5.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
            continue;
        }


        switch (choice) {
            case 1:
                showImage(img, rows, columns);
                break;

            case 2:
                showStatistics(img, rows, columns);
                break;

            case 3:
                invertImage(img, rows, columns);
                break;

            case 4:
                mirrorImage(img, rows, columns);
                break;

            case 5:{
                img = rotateRight(img, rows, columns);
                
                int temp = rows;
                rows = columns;
                columns = temp;

                cout << "\nЗображення повернуто. Нові розміри: " << rows << " x " << columns << '\n';
                showImageData(img, rows, columns);
                break;
            }

            case 0:
                running = false;
                break;

            default:
                cout << "Помилка: такого пункту меню немає.\n";
                break;
        }

    } while (running);

    freeImage(img, rows);
    img = nullptr;

    cout << "Пам'ять звільнено. Програму завершено.\n";

    return 0;
}