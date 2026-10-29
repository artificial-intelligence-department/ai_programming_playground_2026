/*Epic 4 - Редактор монохромного зображення
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <iomanip>

using namespace std;

// Зчитує ціле число
bool readInt(int &value){
    int x = 0;
    int c = 0;
    bool result = false;

    cin >> x;
    if (cin.fail()) {
        // нечислове значення
        cin.clear();
        cin.ignore(1000000, '\n');
    } else {
        c = cin.peek(); // наступний символ після числа
        if (c == EOF || c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            value = x;
            result = true;
        } else {
            // сміття після числа
            cin.clear();
            cin.ignore(1000000, '\n');
        }
    }
    return result;
}

// Виділяє масив rows x cols (спершу масив вказівників, потім кожен рядок)
int **allocateImage(int rows, int cols) {
    int **a = new int*[rows];
    
    for (int i = 0; i < rows; i++) {
        a[i] = new int[cols]();
    }
    return a;
}

// Звільняє кожен рядок, потім масив вказівників
void freeImage(int **&img, int rows) {
    if (img == nullptr) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
}

// Зчитує rows x cols пікселів 0..9 
bool readImage(int **img, int rows, int cols) {
    bool ok = true;
    int v = 0;
    for (int i = 0; ok && i < rows; i++) {
        for (int j = 0; ok && j < cols; j++) {
            ok = readInt(v);
            ok = ok && v >= 0 && v <= 9;
            if (ok) {
                img[i][j] = v;
            }
        }
    }
    return ok;
}

// Виводить таблицю чисел
void printTable(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j > 0) {
                cout << " ";
            }
            cout << img[i][j];
        }
        cout << endl;
    }
}

// Малюнок символами палітри
void printPicture(int **img, int rows, int cols) {
    const char *PALETTE = " .:-=+*#%@";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << PALETTE[img[i][j]];
        }
    cout << endl;
    }
}

// Показати зображення (1)
void showImage(int **img, int rows, int cols) {
    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    printTable(img, rows, cols);
    cout << endl;
    
    cout << "Малюнок:" << endl;
    printPicture(img, rows, cols);
    cout << "Розміри: " << rows << " x " << cols << endl;
}

// Координати першого найсвітлішого й найтемнішого пікселів
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    int minVal = *(img[0]);
    int maxVal = minVal;

    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        for (int j = 0; j < cols; j++) {
            if (*(row + j) < minVal) { // *(row + j) те саме що row[j]
                minVal = *(row + j);
                minRow = i;
                minCol = j;
            }
            if (*(row + j) > maxVal) {
                maxVal = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

// Статистика яскравості (2)
void showStats(int **img, int rows, int cols) {
    int minRow, minCol;
    int maxRow, maxCol;
    int minVal, maxVal;
    long long total = 0;
    double avg, rowAvg;
    int *row = nullptr;

    // Шукає мінімум і максимум
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    
    row = img[minRow];
    minVal = row[minCol];

    row = img[maxRow];
    maxVal = row[maxCol];

    cout << "Найтемніший піксель: " << minVal << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << maxVal << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    // Рахує середню яскравість
    total = 0;
    for (int i = 0; i < rows; i++) {
        row = img[i];
        for (int j = 0; j < cols; j++) {
            total += *(row + j);
        }
    }
    avg = (double)total / (rows * cols);
    cout << "Середня яскравість: " << fixed << setprecision(2) << avg << endl;

    // Рахує середню яскравість по рядках
    cout << "Середня по рядках:";
    for (int i = 0; i < rows; i++) {
        row = img[i];
        int rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        rowAvg = (double)rowSum / cols;
        cout << " " << fixed << setprecision(1) << rowAvg; 
    }
    cout << endl;
}

// Інвертувати яскравість (3)
void invertImage(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "Яскравість інвертовано." << endl;
    printTable(img, rows, cols);
}

// Міняє два пікселі місцями за адресою
void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Віддзеркалити по горизонталі (4)
void mirrorImage(int  ** img, int rows, int cols) {
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;
    printTable(img, rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 -j]);
        }
    }
    cout << endl;
    cout << "Результат:" << endl;
    printTable(img, rows, cols);
}

// Поворот на 90 градусів проворуч, новий масив cols x rows
int **rotateRight(int **img, int rows, int cols) {
    int **res = allocateImage(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res[j][rows - 1 - i] = img[i][j]; // новий рядок = j, новий стовпець = rows - 1 - i
        }
    }
    freeImage(img, rows);
    return res;
}

// Повернути на 90 градусів праворуч (5)
void rotateImage(int **&img, int &rows, int &cols) {
    img = rotateRight(img, rows, cols);

    int t = rows;
    rows = cols;
    cols = t;

    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    printTable(img, rows, cols);
}

int main() {
    int rows = 0;
    int cols = 0;
    int **img = nullptr;
    int choice = -1;
    bool ok = false;
    int code = 0;

    cout << "Висота зображення: ";
    ok = readInt(rows);
    if (!ok || rows < 1 || rows > 20) {
        cout << "Помилка. Висота має бути цілим числом від 1 до 20" << endl;
        code = 1;
    }

    if (code == 0) {
            cout << "Ширина зображення: ";
        ok = readInt(cols);
        if (!ok || cols < 1 || cols > 20) {
            cout << "Помилка. Ширина має бути цілим числом від 1 до 20" << endl;
            code = 1;
        }
    }

    if (code == 0) {
        img = allocateImage(rows, cols);
        cout << "Яскравість пікселів (0..9): " << endl;
        ok = readImage(img, rows, cols);
        if (!ok) {
            cout << "Помилка. Яскравість має бути цілим числом від 0 до 9" << endl;
            code = 1;
        }
    }

    if (code == 0) {
        do {
            cout << "\n================ МЕНЮ ================" << endl;
            cout << "1. Показати зображення" << endl;
            cout << "2. Статистика яскравості" << endl;
            cout << "3. Інвертувати яскравість" << endl;
            cout << "4. Віддзеркалити по горизонталі" << endl;
            cout << "5. Повернути на 90 градусів праворуч" << endl;
            cout << "0. Вийти" << endl;
            cout << "======================================\n";
            cout << "Виберіть пункт: ";

            ok = readInt(choice);
            if (!ok) {
                cout << "Невірний пункт меню. Введіть ціле число від 0 до 5" << endl;
                choice = -1;
            } else {
                cout << "\n======================================\n";
                switch (choice) {
                    case 1:
                        showImage(img, rows, cols);
                        break;
                    case 2:
                        showStats(img, rows, cols);
                        break;
                    case 3:
                        invertImage(img, rows, cols);
                        break;
                    case 4:
                        mirrorImage(img, rows, cols);
                        break;
                    case 5:
                        rotateImage(img, rows, cols);
                        break;
                    case 0:
                        cout << "Вихід з програми." << endl;
                        break;
                    default:
                        cout << "Невірний пункт меню." << endl;
                }
                cout << "======================================\n";
            }
        } while (choice != 0);
    }
    freeImage(img, rows);
    return code;
}