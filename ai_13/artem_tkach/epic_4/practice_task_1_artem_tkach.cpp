/*
 * Практична робота: Редактор монохромного зображення
 * Ткач Артем
 * ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_SIZE = 20;
const char PALETTE[] = " .:-=+*#%@";

// Зчитує невід'ємне ціле число як рядок, щоб відсікти нечислові символи
bool readInt(int &value) {
    string token;
    cin >> token;
    int len = token.length();
    if (len == 0 || len > 9) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (token[i] < '0' || token[i] > '9') {
            return false;
        }
    }
    value = stoi(token);
    return true;
}

// Звільняє кожен рядок, потім масив вказівників, і обнуляє вказівник
void freeImage(int **&img, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
}

// Читає та перевіряє висоту або ширину зображення
bool readSize(const char *name, int &value) {
    cout << name << " зображення (1-" << MAX_SIZE << "): ";
    bool ok = readInt(value);
    if (!ok || value < 1 || value > MAX_SIZE) {
        cout << "Помилка: " << name << " має бути цілим числом від 1 до " << MAX_SIZE << "." << endl;
        return false;
    }
    return true;
}

// Виділяє динамічний двовимірний масив rows x cols
int **createImage(int rows, int cols) {
    int **img = new int *[rows];
    for (int i = 0; i < rows; i++) {
        img[i] = new int[cols];
    }
    return img;
}

// Читає яскравість усіх пікселів і перевіряє діапазон 0..9
bool readPixels(int **img, int rows, int cols) {
    cout << "Яскравість пікселів (0..9):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            bool ok = readInt(img[i][j]);
            if (!ok || img[i][j] > 9) {
                cout << "Помилка: яскравість має бути цілим числом від 0 до 9." << endl;
                return false;
            }
        }
    }
    return true;
}

void showMenu() {
    cout << endl << "Меню:" << endl;
    cout << "1 - Показати зображення" << endl;
    cout << "2 - Статистика яскравості" << endl;
    cout << "3 - Інвертувати яскравість" << endl;
    cout << "4 - Віддзеркалити по горизонталі" << endl;
    cout << "5 - Повернути на 90 градусів праворуч" << endl;
    cout << "0 - Вийти" << endl;
}

// Читає пункт меню; при помилці повертає -1, а при кінці вводу - 0
int readChoice() {
    int choice;
    cout << "Ваш вибір: ";
    bool ok = readInt(choice);
    if (!ok) {
        bool eof = cin.eof();
        choice = -1;
        if (eof) {
            choice = 0;
        }
    }
    return choice;
}

void showNumbers(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j];
            if (j < cols - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void showPicture(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << PALETTE[img[i][j]];
        }
        cout << endl;
    }
}

void showImage(int **img, int rows, int cols) {
    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    showNumbers(img, rows, cols);
    cout << endl << "Малюнок:" << endl;
    showPicture(img, rows, cols);
    cout << "Поточні розміри: " << rows << " x " << cols << endl;
}

// Координати найтемнішого й найсвітлішого пікселів повертаються через посилання
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    int minValue = img[0][0];
    int maxValue = img[0][0];
    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        for (int j = 0; j < cols; j++) {
            if (*(row + j) < minValue) {
                minValue = *(row + j);
                minRow = i;
                minCol = j;
            }
            if (*(row + j) > maxValue) {
                maxValue = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void printExtremes(int **img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "Найтемніший піксель: " << *(*(img + minRow) + minCol) << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << *(*(img + maxRow) + maxCol) << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
}

// Заповнює середні по рядках (обхід рядка через вказівник), повертає суму всіх пікселів
int computeRowAverages(int **img, int rows, int cols, double averages[]) {
    int total = 0;
    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        int rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        total += rowSum;
        averages[i] = (double)rowSum / cols;
    }
    return total;
}

void printAverages(int **img, int rows, int cols) {
    double rowAverages[MAX_SIZE];
    int total = computeRowAverages(img, rows, cols, rowAverages);
    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << (double)total / (rows * cols) << endl;
    cout << setprecision(1) << "Середня по рядках:";
    for (int i = 0; i < rows; i++) {
        cout << " " << rowAverages[i];
    }
    cout << endl;
}

void showStatistics(int **img, int rows, int cols) {
    printExtremes(img, rows, cols);
    printAverages(img, rows, cols);
}

void invertImage(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "Яскравість інвертовано." << endl;
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
    cout << "Зображення віддзеркалено." << endl;
}

// Створює новий масив cols x rows, переносить пікселі й лише потім звільняє старий
int **rotateRight(int **img, int rows, int cols) {
    int **rotated = new int *[cols];
    for (int j = 0; j < cols; j++) {
        rotated[j] = new int[rows];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            rotated[j][rows - 1 - i] = img[i][j];
        }
    }
    freeImage(img, rows);
    return rotated;
}

// Виконує операцію, обрану в меню
void processChoice(int **&image, int &rows, int &cols, int choice) {
    if (choice == 1) {
        showImage(image, rows, cols);
    } else if (choice == 2) {
        showStatistics(image, rows, cols);
    } else if (choice == 3) {
        invertImage(image, rows, cols);
    } else if (choice == 4) {
        mirrorImage(image, rows, cols);
    } else if (choice == 5) {
        image = rotateRight(image, rows, cols);
        swap(rows, cols);
        cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    } else if (choice == 0) {
        cout << "Вихід з програми." << endl;
    } else {
        cout << "Помилка: оберіть пункт меню від 0 до 5." << endl;
    }
}

int main() {
    int rows, cols;
    bool ok = readSize("Висота", rows);
    if (!ok) {
        return 0;
    }
    ok = readSize("Ширина", cols);
    if (!ok) {
        return 0;
    }

    int **image = createImage(rows, cols);
    ok = readPixels(image, rows, cols);
    if (!ok) {
        freeImage(image, rows);
        return 0;
    }

    int choice;
    do {
        showMenu();
        choice = readChoice();
        processChoice(image, rows, cols, choice);
    } while (choice != 0);

    freeImage(image, rows);
    return 0;
}
