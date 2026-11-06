/*
Задача: Редактор монохромного зображення
Автор: Дрогомирецька Ольга
Група: ШІ - 13
*/
#include <iostream>
#include <iomanip>

using namespace std;

void showImage(int** image, int rows, int cols);
void showStatistics(int** image, int rows, int cols);
void invertImage(int** image, int rows, int cols);
void mirrorImage(int** image, int rows, int cols);
int** rotateRight(int** image, int rows, int cols);
void findExtremes(int** image, int rows, int cols,
                  int& minRow, int& minCol, int& maxRow, int& maxCol);
void swapPixels(int* a, int* b);

int main() {
    int rows;
    int cols;

    cout << "Висота зображення: ";
    cin >> rows;
    if (cin.fail() || rows < 1 || rows > 20) {
        cout << "Помилка. Висота має бути цілим числом від 1 до 20." << endl;
        return 1;
    }

    cout << "Ширина зображення: ";
    cin >> cols;
    if (cin.fail() || cols < 1 || cols > 20) {
        cout << "Помилка. Ширина має бути цілим числом від 1 до 20." << endl;
        return 1;
    }

    int** image = new int*[rows]; //створюю місця в пам'яті для адрес рядків
    for (int i = 0; i < rows; i++) {
        image[i] = new int[cols]; //місце в пам'яті для чисел кожного рядка
    }

    cout << "Яскравість пікселів (0..9):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> image[i][j];
            if (cin.fail() || image[i][j] < 0 || image[i][j] > 9) {
                cout << "Помилка. Введіть значення від 0 до 9." << endl;

                //усі рядки вже виділені, тому звільняю кожен із них
                for (int k = 0; k < rows; k++) {
                    delete[] image[k];
                    image[k] = nullptr;
                }
                delete[] image;
                image = nullptr;
                return 1;
            }
        }
    }

    int choice = 0;
    do {
        cout << "\nПункт    " << "Операція" << endl;
        cout << "1         Показати зображення" << endl;
        cout << "2         Статистика яскравості" << endl;
        cout << "3         Інвертувати яскравість" << endl;
        cout << "4         Віддзеркалювати по горизонталі" << endl;
        cout << "5         Повернути на 90 градусів праворуч" << endl;
        cout << "0         Вийти" << endl;
        cout << "Ваш вибір: ";

        while (!(cin >> choice) || choice < 0 || choice > 5) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка. Введіть число від 0 до 5: ";
        }

        switch (choice) {
            case 1:
                showImage(image, rows, cols);
                break;

            case 2:
                showStatistics(image, rows, cols);
                break;

            case 3:
                invertImage(image, rows, cols);
                break;

            case 4:
                mirrorImage(image, rows, cols);
                break;

            case 5: {
                //функція звільняє старий масив і повертає адресу нового
                image = rotateRight(image, rows, cols);

                int temp = rows;
                rows = cols;
                cols = temp;

                cout << "Зображення повернуто. Нові розміри: "
                     << rows << " x " << cols << endl;

                //показую зображення після повороту
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        cout << image[i][j];
                        if (j < cols - 1) {
                            cout << " ";
                        }
                    }
                    cout << endl;
                }
                break;
            }

            case 0:
                break;

            default:
                cout << "Невідомий пункт меню." << endl;
                break;
        }
    } while (choice != 0);

    //після поворотів rows містить актуальну кількість рядків
    for (int k = 0; k < rows; k++) {
        delete[] image[k];
        image[k] = nullptr;
    }
    delete[] image; //масив адрес звільняю після самих рядків
    image = nullptr;

    return 0;
}

//функція для показу зображення
void showImage(int** image, int rows, int cols) {
    cout << "Зображення " << rows << " x " << cols << ":" << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j];
            if (j < cols - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    const char palette[] = " .:-=+*#%@";

    cout << "\nМалюнок:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << palette[image[i][j]];
        }
        cout << endl;
    }
}

//замінює кожен піксель на різницю між 9 та його значенням
void invertImage(int** image, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image[i][j] = 9 - image[i][j];
        }
    }

    cout << "Яскравість інвертовано." << endl;

    //показую результат інверсії
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j];
            if (j < cols - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

//знаходить координати найтемнішого та найсвітлішого пікселів
void findExtremes(int** image, int rows, int cols,
                  int& minRow, int& minCol, int& maxRow, int& maxCol) {
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    int minValue = *image[0];
    int maxValue = *image[0];

    for (int i = 0; i < rows; i++) {
        int* row = image[i];
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

//виводить мінімум, максимум, координати та середню яскравість
void showStatistics(int** image, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;

    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "Найтемніший піксель: " << *(image[minRow] + minCol)
         << " (рядок " << minRow + 1
         << ", стовпець " << minCol + 1 << ")" << endl;

    cout << "Найсвітліший піксель: " << *(image[maxRow] + maxCol)
         << " (рядок " << maxRow + 1
         << ", стовпець " << maxCol + 1 << ")" << endl;

    double totalSum = 0;
    for (int i = 0; i < rows; i++) {
        int* row = image[i];
        for (int j = 0; j < cols; j++) {
            totalSum += *(row + j); //обхід через вказівник
        }
    }

    cout << "Середня яскравість: " << fixed << setprecision(2)
         << totalSum / (rows * cols) << endl;

    cout << "Середня по рядках:";
    for (int i = 0; i < rows; i++) {
        int* row = image[i];
        double rowSum = 0; //для кожного нового рядка сума починається з нуля

        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j); //обхід через вказівник
        }

        cout << " " << fixed << setprecision(1) << rowSum / cols;
    }
    cout << endl;
}

//обмінює два пікселі через адреси
void swapPixels(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//віддзеркалює по горизонталі
void mirrorImage(int** image, int rows, int cols) {
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;

    //показую початкове зображення до обміну пікселів
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j];
            if (j < cols - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++) {
        //лише половина рядка, інакше обмін повториться у інший бік
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&image[i][j], &image[i][cols - 1 - j]);
        }
    }

    cout << "\nРезультат:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j];
            if (j < cols - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

//повертає праворуч на 90 градусів
int** rotateRight(int** image, int rows, int cols) {
    //нові розміри: cols рядків по rows пікселів
    int** rotated = new int*[cols];
    for (int i = 0; i < cols; i++) {
        rotated[i] = new int[rows];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            //старий рядок стає новим стовпцем, але у зворотному порядку
            rotated[j][rows - 1 - i] = image[i][j];
        }
    }

    //звільняю старе зображення тільки після перенесення всіх пікселів
    for (int k = 0; k < rows; k++) {
        delete[] image[k];
        image[k] = nullptr;
    }
    delete[] image;
    image = nullptr;

    return rotated;
}