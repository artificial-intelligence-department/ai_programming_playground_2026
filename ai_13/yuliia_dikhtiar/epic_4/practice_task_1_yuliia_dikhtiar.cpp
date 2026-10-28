/*
Назва задачі: Редактор монохромного зображення
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

bool validInput(int &number) {
    string input;
    cin >> input;

    stringstream ss(input);
    int value;
    char extra;

    if (!(ss >> value) || (ss >> extra)) {
        return false;
    }

    number = value;
    return true;
}

void showImage (int **img, int rows, int cols) {

    cout << "Зображення " << rows << "х" << cols << ": " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    cout << "Малюнок: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            switch (img[i][j]) {
                case 0:
                cout << ' ';
                break;

                case 1:
                cout << '.';
                break;

                case 2:
                cout << ':';
                break;

                case 3:
                cout << '-';
                break;

                case 4:
                cout << '=';
                break;

                case 5:
                cout << '+';
                break;

                case 6:
                cout << '*';
                break;

                case 7:
                cout << '#';
                break;

                case 8:
                cout << '%';
                break;

                case 9:
                cout << '@';
                break;
            }
        }
        cout << endl;
    }
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {

    int lowestBrightness = 10;
    int highestBrightness = 0;
    double sumAll = 0;
    double sumRows = 0;
    double averageAll = 0;
    int countAll = 0;
    int countRows = 0;
    double *row = new double[rows]; // Масив зберігає середню яскравість кожного рядка

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        int *row = img[i];

        if(*(row + j) < lowestBrightness) {
            lowestBrightness = *(row + j);
            minRow = i;
            minCol = j;
        }

        if(*(row + j) > highestBrightness) {
            highestBrightness = *(row + j);
            maxRow = i;
            maxCol = j;
        }

        countAll++;
        sumAll += *(row + j);
        averageAll = sumAll/countAll;

        }
    }

    for (int i = 0; i < rows; i++) {
        sumRows = 0;
        countRows = 0;
        for (int j = 0; j < cols; j++) {
            int *row = img[i];
            sumRows += *(row + j);
            countRows++;
        }
        row[i] = sumRows/countRows;
    }

    cout << "Найтемніший піксель: " << lowestBrightness << " " << "(рядок " << minRow + 1 << ',' << " " << "стовпець " << minCol + 1 << ')' << endl;
    cout << "Найсвітліший піксель: " << highestBrightness << " " << "(рядок " << maxRow + 1 << ',' << " " << "стовпець " << maxCol + 1 << ')' << endl;
    cout << "Середня яскравість: " << fixed << setprecision(2) << averageAll << endl;
    cout << defaultfloat;
    cout << "Середня по рядках: ";

    for (int i = 0; i < rows; i++) {
        cout << row[i] << " ";
    }

    cout << endl;

    delete[] row;
    row = nullptr;
}

void invert (int **img, int rows, int cols) {
    cout << "Яскравість інвертовано." << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        img[i][j] = 9 - img[i][j];
        cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mirror (int **img, int rows, int cols) {
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
            }
        cout << endl;
    }
    cout << endl;

    cout << "Результат:" << endl;

    // Змінила місцями симетричні пікселі до середини рядка
       for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
            }
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
            }
        cout << endl;
    }
}

int** rotateRight(int** img, int rows, int cols) {

    cout << "Зображення повернуто. Нові розміри: " << cols << " x " << rows << endl;

    // Створила новий масив зі зміненими місцями розмірами
    int **newImage = new int*[cols];
        for (int i = 0; i < cols; i++) {
            newImage [i] = new int[rows];
        }

    // Транспонувала масив
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            newImage[i][j] = img [j][i];
            }
    }

   // Змінила порядок елементів у кожному рядку на зворотний
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows/2; j++) {
            int swap = rows - j - 1;
            int temp = newImage[i][j];
            newImage[i][j] = newImage[i][swap];
            newImage[i][swap] = temp;
        }
    }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            cout << newImage[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }

    delete[] img;
    img = nullptr;

    return newImage;
}

// Функція звільнює динамічну пам'ять
void freeImage(int **img, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }

    delete[] img;
    img = nullptr;
}

int main() {

    int minRow = 0;
    int minCol = 0;
    int maxRow = 0;
    int maxCol = 0;

    cout << "Висота зображення: "<< endl;
    int rows = 0;

    if (!validInput(rows) || rows < 1 || rows > 20) {
        cout << "Некоректна висота зображення" << endl;
        return 1;
    }

    cout << "Ширина пікселів: "<< endl;
    int cols = 0;

    if (!validInput(cols) || cols < 1 || cols > 20) {
        cout << "Некоректна ширина зображення" << endl;
        return 1;
    }

    // Виділила пам'ять для масиву вказівників і кожного рядка
    int **arr = new int*[rows];

    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
    }

    cout << "Яскравість пікселів (0..9): " << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!validInput(arr[i][j]) || arr[i][j] < 0 || arr[i][j] > 9) {
                cout << "Некоректна яскравість пікселя" << endl;
                freeImage(arr, rows);
                arr = nullptr;
                return 1;
            }
        }
    }

    int choice = 0;

    do {
        mainMenu:
        cout << endl;
        cout << "Введіть пункт меню:" << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" << endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вийти" << endl;

        if (!validInput(choice) || choice < 0 || choice > 5) {
        cout << "Введіть число від 0 до 5" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto mainMenu;
        }

        cout << endl;

        switch(choice) {
            case 1:
            showImage(arr, rows, cols);
            break;

            case 2:
            findExtremes(arr, rows, cols, minRow, minCol, maxRow, maxCol);
            break;

            case 3:
            invert(arr, rows, cols);
            break;

            case 4:
            mirror(arr, rows, cols);
            break;

            case 5: {
            arr = rotateRight(arr, rows, cols);

            // Після повороту змінила висоту й ширину місцями
            int temp = rows;
            rows = cols;
            cols = temp;
            break;
            }

            case 0:
            break;

            default:
            cout << "Помилка: введіть число від 0 до 5." << endl;
            goto mainMenu;
        }

    } while (choice != 0);

    freeImage(arr, rows);
    arr = nullptr;

    return 0;
}