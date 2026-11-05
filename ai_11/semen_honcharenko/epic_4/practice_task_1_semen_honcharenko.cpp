/*
    Практичне завдання. Завдання 1.
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAXSIZE = 20;
const int MINSIZE = 1;
const int MAXBRIGHT = 9;
const int MINBRIGHT = 0;
const string symbol = " .:-=+*#%@";

void printMenu() { // print menu
    cout << "\n========== Меню ==========\n"
         << "1 - Показати зображення\n"
         << "2 - Статистика яскравості\n"
         << "3 - Інвертувати яскравість\n"
         << "4 - Віддзеркалити по горизонталі\n"
         << "5 - Повернути на 90 градусів праворуч\n"
         << "0 - Вийти\n"
         << "Вибір: ";
}
void clearImage(int **&image, int rows_) { // heap clear
    if (image == nullptr) {
        return;
    }
    for (int i = 0; i < rows_; ++i) {
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;
}
void printTable(int rows_, int cols_, int **image) { // print only current table(numbers)
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (j > 0) {
                cout << " ";
            }
            cout << image[i][j];
        }
        cout << "\n";
    }
}
void printImage(int rows_, int cols_, int **image) { // print current table(numbers) and image(symbols)
    cout << "\n=====================================\n";
    cout << "Зображення " << rows_ << " x " << cols_ << ":\n";
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (j > 0) {
                cout << " ";
            }
            cout << image[i][j];
        }
        cout << "\n";
    }
    cout << "\nМалюнок:\n";
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            cout << symbol[image[i][j]];
        }
        cout << "\n";
    }
}
void invertImage(int rows_, int cols_, int **image) { // invert current table(numbers)
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            image[i][j] = MAXBRIGHT - image[i][j];
        }
    }
    cout << "\n=====================================\n";
    cout << "Яскравість інвертовано.\n";
}
void swapPixels(int *a, int *b) { // swap two pixels by adresses
    int temp = *a;
    *a = *b;
    *b = temp;
}
void mirrorImage(int rows_, int cols_, int **image) { // mirror image horizontally
    cout << "\n=====================================\n";
    cout << "Зображення віддзеркалено.\nПочаткове:\n";
    printTable(rows_, cols_, image);

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_/2; ++j) {
            swapPixels(&image[i][j], &image[i][cols_-1-j]);
        }
    }
    cout << "\nРезультат:\n";
}
void findExtremes(int **image, int rows_, int cols_, int &minRow, int &minCol, int &maxRow, int &maxCol) { // find min/max brightness pixels
    int min = **image;
    int max = **image;
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    for (int i = 0; i < rows_; ++i) {
        int *row = image[i];
        for (int j = 0; j < cols_; ++j) {
            int val = *(row + j);
            if (val < min) {
                min = val;
                minRow = i;
                minCol = j;
            }
            if (val > max) {
                max = val;
                maxRow = i;
                maxCol = j;
            }
        }
    }
}
void statsImage(int rows_, int cols_, int **image) { // print brightness stats
    int minRow = 0;
    int minCol = 0;
    int maxRow = 0;
    int maxCol = 0;
    findExtremes(image, rows_, cols_, minRow, minCol, maxRow, maxCol);

    cout << "\n=====================================\n";
    cout << "Найтемніший піксель: " << *(*(image + minRow) + minCol)
         << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")\n";
    cout << "Найсвітліший піксель: " << *(*(image + maxRow) + maxCol)
         << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")\n";

    double totalBrightness = 0;
    double count = 0;
    for (int i = 0; i < rows_; ++i) {
        int *row = image[i];
        for (int j = 0; j < cols_; ++j) {
            totalBrightness += *(row + j);
            ++count;
        }
    }
    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << totalBrightness/count << "\n";
    totalBrightness = 0;

    cout << fixed << setprecision(1);
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows_; ++i) {
        int *row = image[i];
        for (int j = 0; j < cols_; ++j) {
            totalBrightness += *(row + j);
        }
        if (i > 0) {
            cout << " ";
        }
        cout << totalBrightness/cols_;
        totalBrightness = 0;
    }
    cout << "\n";
}
int** rotateRight(int **image, int rows_, int cols_) { // rotate 90 degrees right
    int **result = new int *[cols_];
    for (int i = 0; i < cols_; ++i) {
        result[i] = new int[rows_];
    }
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result[j][rows_-1-i] = image[i][j];
        }
    }
    clearImage(image, rows_);
    return result;
}
int main() {
    int rows = 0;
    int cols = 0;

    // inputs
    cout << "Висота зображення: ";
    cin >> rows;
    if (rows < MINSIZE or rows > MAXSIZE or cin.fail()) {
        cout << "Помилка. Число має бути від 1 до 20\n";
        return 0;
    }
    cin.clear();
    cin.ignore(1000, '\n');

    cout << "Ширина зображення: ";
    cin >> cols;
    if (cols < MINSIZE or cols > MAXSIZE or cin.fail()) {
        cout << "Помилка. Число має бути від 1 до 20\n";
        return 0;
    }
    cin.clear();
    cin.ignore(1000, '\n');

    // creating raw rows x cols table
    int **image = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        image[i] = new int[cols];
    }

    // filling table
    cout << "Яскравість пікселів (0..9):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> image[i][j];
            if (image[i][j] < MINBRIGHT or image[i][j] > MAXBRIGHT or cin.fail()) {
                cout << "Помилка. Яскравість має бути числом від 0 до 9\n";
                clearImage(image, rows);
                return 0;                        
            }
        }
    }
    int choice = -1;
    int tempSwap = 0;
    do {
        printMenu();
        cin >> choice;
        if (cin.fail()) {
            cout << "Помилка. Вибір має бути числом від 0 до 5\n";
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
            continue;
        }
        switch (choice) {
            case 1:
                printImage(rows, cols, image);
                break;
            case 2:
                statsImage(rows, cols, image);
                break;
            case 3:
                invertImage(rows, cols, image);
                printTable(rows, cols, image);
                break;
            case 4:
                mirrorImage(rows, cols, image);
                printTable(rows, cols, image);
                break;
            case 5:
                image = rotateRight(image, rows, cols);
                tempSwap = rows;
                rows = cols;
                cols = tempSwap;
                cout << "\n=====================================\n";
                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << "\n";
                printTable(rows, cols, image);
                break;
            case 0:
                cout << "Завершення програми...\n";
                clearImage(image, rows);
                return 0;
            default:
                cout << "Помилка. Вибір має бути числом від 0 до 5\n";
        }
    } while (choice != 0);
    clearImage(image, rows);
    return 0;
}