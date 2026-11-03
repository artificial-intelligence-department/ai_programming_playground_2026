/*
* Задача: Редактор монохромного зображення
* Поліщук Вероніка
* Група 14
*/
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Пункт 1: Показати зображення у вигляді чисел та символьної палітри
void picture(int rows, int cols, int **img) {
    cout << "Зображення " << rows << "x" << cols << ":" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "Малюнок:" << endl;
    // Палітра, де індекс символу (0-9) відповідає яскравості пікселя
    string palette = " .:-=+*#%@";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << palette[img[i][j]];
        }
        cout << endl;
    }
    cout << "Розміри: " << rows << " x " << cols << endl;
}

// Пункт 2: Пошук координат найтемнішого та найсвітлішого пікселів
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0; minCol = 0;
    maxRow = 0; maxCol = 0;

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
    cout << "Найтемніший піксель: " << img[minRow][minCol] << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol] << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
}

// Пункт 2: Обчислення середньої яскравості з використанням арифметики вказівників
void average(int **img, int rows, int cols) {
    double totalSum = 0;

    for (int i = 0; i < rows; i++) {
        // Створюємо вказівник на перший елемент поточного рядка
        int *row = img[i]; 
        for (int j = 0; j < cols; j++) {
            // Звертаємося до пам'яті через зсув вказівника замість img[i][j]
            totalSum += *(row + j); 
        }
    }
    double totalAvg = totalSum / (rows * cols);
    cout << "Середня яскравість: " << fixed << setprecision(2) << totalAvg << endl;

    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        double rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        double rowAvg = rowSum / cols;
        cout << defaultfloat << setprecision(6) << rowAvg << " ";
    }
    cout << endl;
}

// Пункт 3: Інвертування кольорів (виконується у тому самому масиві)
void invert(int rows, int cols, int **img) {
    cout << "Яскравість інвертовано." << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Формула інверсії: 0 стає 9, 9 стає 0
            img[i][j] = 9 - img[i][j];
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

// обмін двох значень у пам'яті через їхні адреси (вказівники)
void swapPixels(int *a, int *b) {
    int temp = *a; // Розіменовуємо вказівник, щоб отримати саме значення
    *a = *b;
    *b = temp;
}

// Пункт 4: Віддзеркалення зображення по горизонталі
void mirrorHorizontal(int rows, int cols, int **img) {
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;
    // Вивід початкового стану перед змінами
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }

    // Віддзеркалення
    for (int i = 0; i < rows; i++) {
        // Йдемо лише до половини, щоб не переставити пікселі назад
        for (int j = 0; j < cols / 2; j++) {
            // Передаємо адреси & лівого та відповідного йому правого пікселя
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    
    cout << "Результат:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

// Пункт 5: Поворот масиву на 90 градусів праворуч
int** rotateRight(int** img, int rows, int cols) {
    // Виділяємо нову пам'ять, де кількість рядків = старій ширині (cols)
    int** newImg = new int*[cols];
    for (int i = 0; i < cols; ++i) {
        newImg[i] = new int[rows]; // Довжина кожного рядка = старій висоті (rows)
    }

    // Переносимо пікселі
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    // Обов'язкове звільнення старого масиву
    for (int i = 0; i < rows; i++) {
        delete[] img[i]; // Видаляємо кожен рядок
    }
    delete[] img; // Видаляємо масив вказівників

    // Повертаємо адресу нового масиву
    return newImg;
}

// Пункт 6: Безпечне очищення виділеної динамічної пам'яті
void freeMemory(int** &arr, int rows) {
    if (arr != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] arr[i];
        }
        delete[] arr;
        // Обнуляємо вказівник, щоб уникнути помилок доступу після видалення
        arr = nullptr; 
    }
}

int main() {
    int origRows, origCols;

    cout << "Висота зображення: ";
    if (!(cin >> origRows) || origRows < 1 || origRows > 20) {
        cout << "Помилка вводу! Некоректна висота зображення." << endl;
        return 0;
    }

    cout << "Ширина зображення: ";
    if (!(cin >> origCols) || origCols < 1 || origCols > 20) {
        cout << "Помилка вводу! Некоректна ширина зображення." << endl;
        return 0;
    }

    // Виділення динамічної пам'яті під оригінальний масив
    int **image = new int*[origRows];
    for (int i = 0; i < origRows; ++i) {
        image[i] = new int[origCols];
    }

    cout << "Яскравість пікселів (0..9): " << endl;
    for (int i = 0; i < origRows; i++) {
        for (int j = 0; j < origCols; j++) {
            if (!(cin >> image[i][j]) || image[i][j] < 0 || image[i][j] > 9) {
                cout << "Помилка вводу! Яскравість пікселя поза межами 0..9." << endl;
                // Звільняємо пам'ять перед виходом
                for (int k = 0; k <= i; k++) delete[] image[k];
                delete[] image;
                return 0;
            }
        }
    }

    // Створення копії img
    int rows = origRows;
    int cols = origCols;
    int **img = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        img[i] = new int[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = image[i][j];
        }
    }

    int choice;
    do {
        cout << "\n1 - Показати зображення\n2 - Статистика яскравості\n3 - Інвертувати яскравість\n4 - Віддзеркалити по горизонталі\n5 - Повернути на 90 градусів праворуч\n0 - Вийти\n";
        cout << "Ваш вибір: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Невірний пункт!\n";
            continue;
        }

        switch (choice) {
            case 1:
                picture(rows, cols, img);
                break;
            case 2: {
                int minR, minC, maxR, maxC;
                findExtremes(img, rows, cols, minR, minC, maxR, maxC);
                average(img, rows, cols);
                break;
            }
            case 3:
                invert(rows, cols, img);
                break;
            case 4:
                mirrorHorizontal(rows, cols, img);
                break;
            case 5: {
                // Перезаписуємо вказівник img адресою нового, повернутого масиву
                img = rotateRight(img, rows, cols);
                // Розміри змінюються місцями (висота стає шириною і навпаки)
                int temp = rows;
                rows = cols;
                cols = temp;
                
                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
                // Вивід повернутого масиву чисел
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        cout << img[i][j] << " ";
                    }
                    cout << endl;
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "Невірний пункт!\n";
        }
    } while (choice != 0);

    // Звільняємо пам'ять і для копії, і для оригіналу перед завершенням програми
    freeMemory(img, rows);
    freeMemory(image, origRows);

    return 0;
}