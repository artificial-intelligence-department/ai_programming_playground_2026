#include <iostream>
#include <iomanip>
using namespace::std;
/* Практичне завдання Редактор монохромного зображення
   Сідлецький Тимофій ШІ-13
*/

// функція для виводу матриці
void print_image(int **image, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

// пункт 1 показати зображення
void show_image(int **image, int rows, int cols) {
    cout << "Зображення " << rows << " x " << cols << ": " << endl;
    print_image(image,rows,cols);

    cout << "Малюнок: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            switch(image[i][j]) {
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
        cout << endl;
    }
}

// знаходження найсвітлішого та найтемнішого пікселя, повернення параметром посиланням
void findExtremes (int **image, int rows, int cols, int &maxRow, int &maxCol, int &minRow, int &minCol) {
    int bright_max = 9;
    int bright_min = 0;
    maxRow = 1;
    maxCol = 1;
    minRow = 1;
    minCol = 1;
    for (int i = 0; i < rows; i++) {
        int *row = image[i];
        for (int j = 0; j < cols; j++) {
            if (*(row + j) < bright_max) {
                bright_max = *(row + j);
                maxRow = i + 1;
                maxCol = j + 1;
            }
            if (*(row + j) > bright_min) {
                bright_min = *(row + j);
                minRow = i + 1;
                minCol = j + 1;
            }
        }
    }
    cout << "Найтемніший піксель: " << bright_max << " (рядок " << maxRow << ", стовпець " << maxCol << ")" << endl;
    cout << "Найсвітліший піксель: " << bright_min << " (рядок " << minRow << ", стовпець " << minCol << ")" << endl;
}

// середня яскравість
void avg_brightness (int **image, int rows, int cols) {
    float sum = 0;
    for (int i = 0; i < rows; i++) {
        int *row = image[i];
        for (int j = 0; j < cols; j++) {
            sum += *(row + j);
        }
    }
    cout << fixed << setprecision(2) << "Середня яскравість: " << sum / (rows * cols) << endl;
}

// середня яскравість по рядках
void avg_brightness_by_row (int **image, int rows, int cols) {
    cout << "Середня по рядках: " << fixed << setprecision(1); 
    for (int i = 0; i < rows; i++) {
        int *row = image[i];
        float sum = 0;
        for (int j = 0; j < cols; j++) {
            sum += *(row + j);
        }
        cout << sum / cols << " ";
    }
    cout << endl;
}

// пункт 2 статистика яскравості
void brightness_stats (int **image, int rows, int cols) {
    int maxRow,maxCol,minRow,minCol;
    findExtremes(image, rows, cols, maxRow, maxCol, minRow, minCol);
    avg_brightness(image,rows,cols);
    avg_brightness_by_row(image,rows,cols);
}

// пункт 3 інвертувати яскравість
void invert_brightness (int **image, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image[i][j] = 9 - image[i][j];
        }
    }
    cout << "Яскравість інвертовано: " << endl;
    print_image(image,rows,cols);
    cout << endl;
}

// функція обміну двох пікселів до пункту 4 за умовою практичного завдання 
void swapPixels (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// пункт 4 відзеркалити зображення по горизонталі
void horizontal_reflect(int **image, int rows, int cols) {
    cout << "Зображення відзеркалено." << endl;
    cout << "Початкове: " << endl;
    print_image(image,rows,cols);
    cout << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&image[i][j], &image[i][cols - 1 - j]);
        }
    }
    cout << endl;
    cout << "Результат: " << endl;
    print_image(image,rows,cols);
    cout << endl;
}

// пункт 5 повернути на 90 градусів праворуч
int** rotateRight(int **image, int &rows, int &cols) {
    int temp = rows;
    rows = cols;
    cols = temp;
    int **newimage = new int*[rows];
    for (int i = 0; i < rows; i++) {
        newimage[i] = new int[cols];
    }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            newimage[j][cols - 1 - i] = image[i][j];
        }
    }

    for (int i = 0; i < cols; i++) {
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;

    return newimage;
}


int main () {
    int rows,cols,action;

    cout << "Висота зображення (1-20): ";
    cin >> rows;
    if (rows > 20 || rows < 1 || cin.fail()) {
        cout << "Некоректне значення";
        return 1;
    }
    cout << "Ширина зображення (1-20): ";
    cin >> cols;
    if (cols > 20 || cols < 1 || cin.fail()) {
        cout << "Некоректне значення";
        return 1;
    }

    // оголошення двовимірного динамічного масиву
    int **image = new int*[rows];
    for (int i = 0; i < rows; i++) {
        image[i] = new int[cols];
    }

    cout << "Яскравість пікселів (0-9): " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> image[i][j];
            if (image[i][j] > 9 || image[i][j] < 0 || cin.fail()) {
                cout << "Некоректне значення";
                return 1;
            }
        }
    }
    do {
        menustart: // мітка для повтору меню в разі некоректного значення
        cout << "1 - Показати зображення" << endl;
        cout << "2 - Статистика яскравості" << endl;
        cout << "3 - Інвертувати яскравість" << endl;
        cout << "4 - Відзеркалити по горизонталі" << endl;
        cout << "5 - Повернути на 90 градусів праворуч" << endl;
        cout << "0 - Вийти" << endl;
        cin >> action;
        if (action > 5 || action < 0 || cin.fail()) {
            cout << "Некоректне значення. Спробуйте ще раз" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto menustart; // перехід до початку меню
        }

        switch(action) {
            case 1:
                show_image(image,rows,cols);
                break;
            case 2:
                brightness_stats(image,rows,cols);
                break;
            case 3:
                invert_brightness(image,rows,cols);
                break;
            case 4:
                horizontal_reflect(image,rows,cols);
                break;
            case 5:
                image = rotateRight(image,rows,cols);
                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
                print_image(image,rows,cols);
                break;
        }

    } while (action != 0);

    // видалення двовимірного динамічного масиву
    for (int i = 0; i < cols; i++) {
        delete[] image[i];
    }
    delete[] image;

    return 0;
}