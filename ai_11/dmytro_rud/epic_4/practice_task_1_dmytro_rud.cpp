#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

bool endOfToken() {
    int c = cin.peek();

    return c == '\n' || c == ' ' || c == '\t' ||
           c == '\r' || c == EOF;
}

bool readInt(int& value) {
    if (cin >> value && endOfToken()) {
        return true;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return false;
}

void freeMemory(int**& image, int rows) {
    if (image == nullptr) {
        return;
    }

    for (int a = 0; a < rows; a++) {
        delete[] image[a];
        image[a] = nullptr;
    }

    delete[] image;
    image = nullptr;
}
void showImage(int** &image, int rows, int cols) {

    
    for(int i = 0;i < rows;i++) {
        for (int j = 0;j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "зображення " << rows << "х" << cols << "\n\n";
    cout << "Малюнок" << "\n";

    for(int i = 0;i < rows;i++) {
        for (int j = 0;j < cols; j++) {
            switch(image[i][j]){
                case 0:
                    cout << " ";
                    break;
                case 1:
                    cout << ".";
                    break;
                case 2:
                    cout << ":";
                    break;
                case 3:
                    cout << "-";
                    break;
                case 4:
                    cout << "=";
                    break;
                case 5:
                    cout << "+";
                    break;
                case 6:
                    cout << "*";
                    break;
                case 7:
                    cout << "#";
                    break;
                case 8:
                    cout << "%";
                    break;
                case 9:
                    cout << "@";
                    break;
            }
        }
        cout << "\n";
    }
}

void findExtremes(
    int** image,
    int rows,
    int cols,
    int& minRow,
    int& minCol,
    int& maxRow,
    int& maxCol
) {
    int minValue = 10;
    int maxValue = -1;
    for(int i = 0;i < rows;i++) {
        int* row = image[i];
        for (int j = 0; j < cols;j++) {
            int x = *(row + j);
            if (x < minValue) {
                minRow = i;
                minCol = j;
                minValue = x;
            } 
            if (x > maxValue) {
                maxRow = i;
                maxCol = j;
                maxValue = x;
            }

        }
    }
    

}
void mid(    
    int** image,
    int rows,
    int cols,
    float* &middle,
    float& midValue
) {
    float sum = 0;
    for (int i = 0; i < rows; i++) {
        float sum_row =0;
        int* row = image[i];
        for (int j = 0; j < cols; j++) {
            sum += *(row + j);
            sum_row += *(row + j);
        }
        middle[i] = sum_row / cols;
    }
    midValue = sum / (cols * rows);
}
void showStats(int** image, int rows, int cols) {

    int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;

    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
    // min
    cout << "Найтемніший піксель: " << image[minRow][minCol] << "\n";
    cout << "Координати: рядок " << minRow + 1 << ", стовпець " << minCol + 1 << "\n\n";
    // max
    cout << "Найсвітліший піксель: " << image[maxRow][maxCol] << "\n";
    cout << "Координати: рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << "\n\n";
    // middle
    float midValue = 0;
    float* middle = new float[rows];
    mid(image, rows, cols, middle, midValue);
    cout << fixed << setprecision(2);
    cout << "Середня яскравість усього зображення: " << midValue << "\n\n";
    cout << "Середня яскравість кожного рядка: " << "\n";
    for (int i = 0; i < rows;i++) {
        cout << "Рядок "<< i+1 << ": " << middle[i] << "\n";
    }
    delete[] middle;
    middle = nullptr;
}

void invert(int** &image, int rows, int cols) {
    for (int i = 0; i < rows;i++) {
        for (int j = 0; j < cols; j++) {
            image[i][j] = 9 - image[i][j];
        }
    }
    cout << "Яскравість інвертовано." << "\n";
}
void swapPixels(int* a, int* b) {
    int x = *a;
    *a = *b;
    *b = x;
}

void mirror(int** &image, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&image[i][j], &image[i][cols - 1 - j]);
        }
    }
    cout << "Зображення віддзеркалено по горизонталі.\n";
}
int** rotateRight(int** image, int rows, int cols) {
    int** rotated = new int*[cols];   // нова кількість рядків = старій ширині
    for (int i = 0; i < cols; i++) {
        rotated[i] = new int[rows];   // нова кількість стовпців = старій висоті
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        rotated[j][rows - 1 - i] = image[i][j];
        }
    }
    for (int i = 0; i < rows; i++) {
        delete[] image[i];
    }
    delete[] image;

    return rotated;
}

int main() {
    int rows;
    int cols;
    int** image = nullptr;

    cout << "Введіть висоту зображення (1..20): ";

    if (!readInt(rows) || rows < 1 || rows > 20) {
        cout << "Помилка: висота повинна бути цілим числом від 1 до 20.\n";
        return 0;
    }

    cout << "Введіть ширину зображення (1..20): ";

    if (!readInt(cols) || cols < 1 || cols > 20) {
        cout << "Помилка: ширина повинна бути цілим числом від 1 до 20.\n";
        return 0;
    }

    // Виділення динамічної пам'яті для зображення.
    image = new int*[rows];

    for (int a = 0; a < rows; a++) {
        image[a] = new int[cols];
    }

    // Введення яскравості кожного пікселя.
    for (int a = 0; a < rows; a++) {
        for (int b = 0; b < cols; b++) {
            cout << "Введіть яскравість image["
                 << a << "][" << b << "] (0..9): ";

            if (!readInt(image[a][b]) ||
                image[a][b] < 0 ||
                image[a][b] > 9) {
                cout << "Помилка: яскравість повинна бути "
                     << "цілим числом від 0 до 9.\n";
           
                freeMemory(image, rows);
                return 0;
            }
        }
    }

    int choice;

    do {
        cout << "\n--- Меню ---\n";
        cout << "1 - Показати зображення\n";
        cout << "2 - Статистика яскравості\n";
        cout << "3 - Інвертувати яскравість\n";
        cout << "4 - Віддзеркалити по горизонталі\n";
        cout << "5 - Повернути на 90 градусів праворуч\n";
        cout << "0 - Вийти\n";
        cout << "Ваш вибір: ";

        if (!readInt(choice)) {
            cout << "Помилка: введіть ціле число від 0 до 5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                showImage(image, rows, cols);
                break;

            case 2:
                showStats(image, rows, cols);
                break;

            case 3:
                invert(image, rows, cols);
                break;

            case 4:
                mirror(image, rows, cols);
                break;
            case 5:
                image = rotateRight(image, rows, cols);
                swap(rows, cols);
                break;

            case 0:
                cout << "Роботу програми завершено.\n";
                break;

            default:
                cout << "Помилка: такого пункту меню не існує.\n";
                break;
        }

    } while (choice != 0);

    // Перед завершенням звільняємо всю пам'ять.
    freeMemory(image, rows);

    return 0;
}