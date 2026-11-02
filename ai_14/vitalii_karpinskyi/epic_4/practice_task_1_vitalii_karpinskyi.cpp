#include <iostream>
#include <iomanip>

using namespace std;

void choice_1(int **image, int rows, int cols) {
    cout << "Зображення " << rows << " x " << cols << ":\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }

    char draw[] = " .:-=+*#%@";
    cout << "Малюнок: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int pixel = image[i][j];
            cout << draw[pixel];
        }
        cout << endl;
    }
}

void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    int min = image[0][0];
    int max = image[0][0];

    for (int i = 0; i < rows; i++) {
        int *row = image[i];
        for (int j = 0; j < cols; j++) {

            if (min > *(row + j)) {
                min = *(row + j);
                minRow = i;
                minCol = j;
            }
            if (max < *(row + j)) {
                max = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void choice_2(int **image, int rows, int cols) {
    int minRow = 0;
    int minCol = 0;
    int maxRow = 0;
    int maxCol = 0;

    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
    int minVal = *(image[minRow] + minCol);
    int maxVal = *(image[maxRow] + maxCol);

    cout << "Найтемніший піксель: " << minVal << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << maxVal << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    double sum = 0;
    double rowSum = 0;

    for (int i = 0; i < rows; i++) {
        int *row = image[i];
        for (int j = 0; j < cols; j++) {
            sum += *(row + j);
        }
    }
    double average = sum / (rows*cols);
    cout << "Середня яскравість: " << fixed << setprecision(2) << average << endl;

    cout << "Середня по рядках: " << fixed << setprecision(1);
    for (int i = 0; i < rows; i++) {
        int *row = image[i];
        rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        double rowAverage = rowSum / cols;
        cout << rowAverage << " ";
    } 
    cout << endl;
}

void imageDelete(int **&image, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] image[i];
        image[i] = nullptr;
    }
    delete[] image;
    image = nullptr;
}

void choice_3(int **image, int rows, int cols) {
    cout << "Яскравість інвертовано:" << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            image[i][j] = 9 - image[i][j];
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

void swapPixels(int *a, int *b) {
    int change = *a;
    *a = *b;
    *b = change;
}

void choice_4(int **image, int rows, int cols) {
    cout << "Зображення віддзеркалено" << endl;
    cout << "Початкове:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Результат:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&image[i][j], &image[i][cols - j - 1]);
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

int **rotateRight(int **image, int rows, int cols) {
    int ** image2 = new int *[cols];
    for (int i = 0; i < cols; i++) {
        image2[i] = new int [rows];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image2[j][rows - 1 - i] = image[i][j];
        }
    }
    imageDelete(image, rows);
    cout << "Зображення перевернуто. Нові розміри: " << cols << " x " << rows << endl;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            cout << image2[i][j] << " ";
        }
        cout << endl;
    }
    return image2;
}

int main() {
    int rows = 0;
    int cols = 0;

    cout << "Висота зображення: ";
    cin >> rows;
    if (cin.fail() || rows < 1 || rows > 20) {
        cout << "Помилка: висота повинна бути числом в діапазоні від 1 до 20" << endl;
        return 0;
    }

    cout << "Ширина зображення: ";
    cin >> cols;
    if (cin.fail() || cols < 1 || cols > 20) {
        cout << "Помилка: ширина повинна бути числом в діапазоні від 1 до 20" << endl;
        return 0;
    }

    int **image = new int *[rows];
    for (int i = 0; i < rows; i++) {
        image[i] = new int [cols];
    }

    cout << "Яскравість пікселів (0..9): " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> image[i][j];
            if (cin.fail() || image[i][j] < 0 || image[i][j] > 9 ) {
                cout << "Помилка: яскравість пікселя повинна бути числом від 0 до 9" << endl;
                imageDelete(image, rows);
                return 0;
            }
        }
    }

    short choice = -1;
    int temp;
    cin.ignore(10000, '\n');

    do {
        cout << "\n==========МЕНЮ==========" << endl;
        cout << "1    Показати зображення" << endl;
        cout << "2    Статистика яскравості" << endl;
        cout << "3    Інвертувати яскравість" << endl;
        cout << "4    Віддзеркалити по горизонталі" << endl;
        cout << "5    Повернути на 90 градусів праворуч" << endl;
        cout << "0    Вийти" << endl;

        cout << "Виберіть пункт: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Помилка: некоректний ввід" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
            continue;
        }

        switch (choice){
            case 1:
                choice_1(image, rows, cols);
                break;
            case 2:
                choice_2(image, rows, cols);
                break;

            case 3:
                choice_3(image, rows, cols);
                break;
            case 4:
                choice_4(image, rows, cols);
                break;
            case 5: 
                image = rotateRight(image, rows, cols);
                temp = rows;
                rows = cols;
                cols = temp;
                break;
            
            case 0:
                break;
            default:
                cout << "Помилка: невідомий пункт" << endl;
                cin.ignore(10000, '\n');   
        }
    } while (choice != 0);

    imageDelete(image, rows);

    cout << "==========Завершення роботи==========\n" << endl;

    return 0;
}