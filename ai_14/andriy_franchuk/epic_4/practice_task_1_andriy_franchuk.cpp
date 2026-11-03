/*
Редактор монохромного зображення
Франчук Андрій
ШІ-14 (ai_14)
*/
#include <iostream>

using namespace std;

// Палітра символів для відображення яскравості від 0 до 9
const char gradient[] = " .:-=+*#%@";

// Прототипи функцій відповідно до вимог завдання
void validateInput(int &value);
void validateInputImage(int &value);
void imageOutput(int **a, int rows, int cols);
void imageOutput(char **a, int rows, int cols);
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void swapPixels(int *a, int *b);
int** rotateRight(int** img, int rows, int cols);

void option1(int **a, int rows, int cols);
void option2(int **a, int rows, int cols);
void option3(int **a, int rows, int cols);
void option4(int **a, int rows, int cols);
void option5(int **&a, int &rows, int &cols);

int main() {
    int rows, cols;
    cout << "Висота зображення: ";
    validateInput(rows);

    cout << "Ширина зображення: ";
    validateInput(cols);

    // Динамічне виділення пам'яті під двовимірний масив зображення
    int **image = new int*[rows];
    for (int i = 0; i < rows; i++) {
        image[i] = new int[cols];
    }

    cout << "Яскравість пікселів (0..9): " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            validateInputImage(image[i][j]);
        }
    }

    int choice;
    do {
        // Виведення головного меню
        cout << "\nМЕНЮ:" << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" << endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вийти" << endl;
        cout << "Оберіть пункт меню: ";

        // Перевірка коректності введення пункту меню (0 до 5)
        if (!(cin >> choice)) {
            cout << "Помилка, введіть числове значення від 0 до 5." << endl;
            cin.clear();
            while (cin.get() != '\n');
            continue;
        }

        switch (choice) {
            case 0:
                break;
            case 1:
                option1(image, rows, cols);
                break;
            case 2:
                option2(image, rows, cols);
                break;
            case 3:
                option3(image, rows, cols);
                break;
            case 4:
                option4(image, rows, cols);
                break;
            case 5:
                option5(image, rows, cols);
                break;
            default:
                cout << "Неправильний пункт меню." << endl;
                break;
        }

    } while (choice != 0);

    // Повне звільнення динамічної пам'яті та обнулення вказівників через nullptr
    for (int i = 0; i < rows; i++) {
        delete[] image[i];
        image[i] = nullptr;
    }
    delete[] image;
    image = nullptr;

    return 0;
}

// 1. Показати зображення у вигляді таблиці чисел та символів палітри
void option1(int **a, int rows, int cols) {
    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    imageOutput(a, rows, cols);

    cout << "\nМалюнок: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << gradient[a[i][j]];
        }
        cout << endl;
    }
}

// 2. Статистика яскравості (використовує findExtremes та обхід через вказівник)
void option2(int **a, int rows, int cols) {
    int minR, minC, maxR, maxC;
    findExtremes(a, rows, cols, minR, minC, maxR, maxC);

    double totalSum = 0;
    double *avgByRows = new double[rows];

    for (int i = 0; i < rows; i++) {
        int *row = a[i]; // Обхід рядка через вказівник за вимогою
        double rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        avgByRows[i] = rowSum / cols;
        totalSum += rowSum;
    }

    double totalAvg = totalSum / (rows * cols);

    cout << "Найтемніший піксель: " << a[minR][minC] << " (рядок " << minR + 1 << ", стовпець " << minC + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << a[maxR][maxC] << " (рядок " << maxR + 1 << ", стовпець " << maxC + 1 << ")" << endl;
    cout << "Середня яскравість: " << totalAvg << endl;
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++) {
        cout << avgByRows[i] << " ";
    }
    cout << endl;

    delete[] avgByRows;
}

// 3. Інвертування яскравості на місці (без виділення нового масиву)
void option3(int **a, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int *row = a[i];
        for (int j = 0; j < cols; j++) {
            *(row + j) = 9 - *(row + j);
        }
    }
    cout << "Яскравість інвертовано." << endl;
    imageOutput(a, rows, cols);
}

// 4. Віддзеркалення по горизонталі на місці за допомогою swapPixels
void option4(int **a, int rows, int cols) {
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове: " << endl;
    imageOutput(a, rows, cols);

    for (int i = 0; i < rows; i++) {
        int *row = a[i];
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&row[j], &row[cols - 1 - j]);
        }
    }

    cout << "\nРезультат: " << endl;
    imageOutput(a, rows, cols);
}

// 5. Поворот на 90 градусів праворуч
void option5(int **&a, int &rows, int &cols) {
    a = rotateRight(a, rows, cols);
    int temp = rows;
    rows = cols;
    cols = temp;

    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    imageOutput(a, rows, cols);
}

// Функція пошуку екстремумів, що повертає координати через посилання
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0; 
    minCol = 0;
    maxRow = 0; 
    maxCol = 0;
    int minVal = img[0][0];
    int maxVal = img[0][0];

    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        for (int j = 0; j < cols; j++) {
            int val = *(row + j);
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

// Функція обміну двох пікселів за їх адресами
void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Функція повороту: виділяє новий масив, копіює дані, видаляє старий
int** rotateRight(int** img, int rows, int cols) {
    int newRows = cols;
    int newCols = rows;

    int** b = new int*[newRows];
    for (int i = 0; i < newRows; i++) {
        b[i] = new int[newCols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            b[j][rows - 1 - i] = img[i][j];
        }
    }

    // Безпечне звільнення старого масиву
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
    }
    delete[] img;

    return b;
}

void imageOutput(int **a, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void imageOutput(char **a, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << a[i][j];
        }
        cout << endl;
    }
}

void validateInput(int &value) {
    while (true) {
        if (cin >> value && value >= 1 && value <= 20) {
            break;
        } else {
            cout << "Помилка. Введіть ціле число від 1 до 20" << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}

void validateInputImage(int &value) {
    while (true) {
        if (cin >> value && value >= 0 && value <= 9) {
            break;
        } else {
            cout << "Помилка. Введіть ціле число від 0 до 9" << endl; // Виправлено діапазон для чорного пікселя (0)
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}