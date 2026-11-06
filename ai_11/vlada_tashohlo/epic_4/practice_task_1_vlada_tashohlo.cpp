
/*
Епік 4. Практичне завдання: Редактор монохромного зображення
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// Оголошення функцій програми.
int inputInt();
void inputImage(int** img, int rows, int cols);
void menu();
void showImage(int** image, int rows, int cols);
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void brightnessStatistics(int** img, int rows, int cols);
void invertBrightness(int** img, int rows, int cols);
void swapPixels(int *a, int *b);
void mirrorHorizontally(int** img, int rows, int cols);
int** rotateRight(int** img, int rows, int cols);

int main(){

    // Введення висоти зображення з перевіркою допустимого діапазону.
    int rows;
    do {
        cout << "Висота зображення: ";
        rows = inputInt();

        if (rows < 1 || rows > 20) {
            cout << "Помилка! Висота має бути від 1 до 20.\n";
        }
    } while (rows < 1 || rows > 20);

    // Введення ширини зображення з перевіркою допустимого діапазону.
    int cols;
    do {
        cout << "Ширина зображення: ";
        cols = inputInt();

        if (cols < 1 || cols > 20) {
            cout << "Помилка! Ширина має бути від 1 до 20.\n";
        }
    } while (cols < 1 || cols > 20);

    // Виділення пам'яті під двовимірний масив пікселів.
    int** img = new int*[rows];

    for (int i = 0; i < rows; ++i){
        img[i] = new int[cols];
    }

    // Заповнення зображення значеннями яскравості.
    inputImage(img, rows, cols);

    int action = -1;

    // Головний цикл меню редактора.
    do{

        menu();
        action = inputInt();

        switch (action){

            case 1:
                showImage(img, rows, cols);
                break;

            case 2:
                brightnessStatistics(img, rows, cols);
                break;

            case 3:
                invertBrightness(img, rows, cols);
                break;

            case 4:
                mirrorHorizontally(img, rows, cols);
                break;

            case 5:{
                // Після повороту розміри матриці міняються місцями.
                img = rotateRight(img, rows, cols);
                int tmp = rows;
                rows = cols;
                cols = tmp;
                break;
            }

            case 0:
                cout << "Вихід із програми.\n";
                break;

            default:
                cout << "Помилка! Невідомий пункт меню.\n";
                break;
        }

    } while (action != 0);

    // Звільнення пам'яті перед завершенням програми.
    for (int i = 0; i < rows; ++i){
        delete[] img[i];
    }

    delete[] img;
    img = nullptr;

    return 0;
}

// Функція для читання одного цілого числа з перевіркою формату введення.
int inputInt() {

    string line;
    int x;
    char extra;

    while (true) {
        getline(cin, line);

        stringstream ss(line);

        if (ss >> x && !(ss >> extra)) {
            return x;
        }

        cout << "Помилка! Потрібно ввести одне ціле число.\n";
    }
}

// Зчитує рядок пікселів для одного рядка зображення.
void inputImage(int** img, int rows, int cols) {

    string line;
    int x;
    char extra;

    cout << "Яскравість пікселів (0..9):\n";

    for (int i = 0; i < rows; ++i) {

        while (true) {
            getline(cin, line);
            stringstream ss(line);

            int* temp = new int[cols];
            bool valid = true;

            for (int j = 0; j < cols; ++j) {
                if (!(ss >> x) || x < 0 || x > 9) {
                    valid = false;
                    break;
                }

                temp[j] = x;
            }

            if (valid && !(ss >> extra)) {
                for (int j = 0; j < cols; ++j) {
                    img[i][j] = temp[j];
                }

                delete[] temp;
                break;
            }

            delete[] temp;

            cout << "Помилка! Введіть рівно " << cols << " цілих чисел від 0 до 9:\n";
        }
    }
}

// Виводить на екран список доступних команд редактора.
void menu(){

    cout << "===== Меню =====" << endl;

    cout << left << setw(8) << "Пункт   " << setw(35) << "Операція\n";
    cout << left << setw(8) << '1' << setw(35) << "Показати зображення\n";
    cout << left << setw(8) << '2' << setw(35) << "Статистика яскравості\n";
    cout << left << setw(8) << '3' << setw(35) << "Інвертувати яскравість\n";
    cout << left << setw(8) << '4' << setw(35) << "Віддзеркалити по горизонталі\n";
    cout << left << setw(8) << '5' << setw(35) << "Повернути на 90 градусів праворуч\n";
    cout << left << setw(8) << '0' << setw(35) << "Вийти\n";
}

// Виводить зображення у числовому вигляді та у вигляді ASCII-графіки.
void showImage(int** img, int rows, int cols){

    const char ch[] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};

    cout << "Зображення " << rows << " x " << cols << ':\n';

    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            cout << img[i][j] << '\n';
        }
        cout << '\n';
    }

    cout << "Малюнок:\n";

    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            cout << ch[img[i][j]] << '\n';
        }
        cout << '\n';
    }
}

// Пошук координат найтемнішого та найсвітлішого пікселів.
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){

    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    int min = img[0][0];
    int max = img[0][0];

    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){

            if (img[i][j] < min){
                min = img[i][j];
                minRow = i;
                minCol = j;
            }

            if (img[i][j] > max){
                max = img[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

// Підрахунок найтемнішого, найсвітлішого та середньої яскравості рядків.
void brightnessStatistics(int** img, int rows, int cols){
    int minRow, minCol, maxRow, maxCol;

    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "Найтемніший піксель: " << img[minRow][minCol]
         << " (рядок " << minRow + 1
         << ", стовпець " << minCol + 1 << ")\n";

    cout << "Найсвітліший піксель: " << img[maxRow][maxCol]
         << " (рядок " << maxRow + 1
         << ", стовпець " << maxCol + 1 << ")\n";

    cout << "Середня яскравість рядків: ";

    for (int i = 0; i < rows; ++i) {
        int* row = img[i];
        int rowSum = 0;

        for (int j = 0; j < cols; ++j) {
            rowSum += *(row + j);
        }

        double rowAverage = static_cast<double>(rowSum) / cols;
        cout << fixed << setprecision(1) << rowAverage;

        if (i < rows - 1) {
            cout << ", ";
        }
    }

    cout << endl;
}

// Зміна яскравості пікселів за формулою 9 - значення.
void invertBrightness(int** img, int rows, int cols){

    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            img[i][j] = 9 - img[i][j];
            cout << img[i][j] << '\t';
        }
        cout << '\n';
    }
}

// Обмінює значення двох пікселів місцями.
void swapPixels(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Віддзеркалює зображення по горизонталі: міняє місцями пікселі
// симетрично відносно центральної вертикалі.
void mirrorHorizontally(int** img, int rows, int cols){

    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols / 2; ++j){
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
}

// Повертає зображення на 90 градусів праворуч.
// Створюється новий масив розміром cols x rows, бо після повороту
// ширина і висота міняються місцями.
int** rotateRight(int** img, int rows, int cols){

    int** newImg = new int*[cols];

    for (int i = 0; i < cols; ++i){
        newImg[i] = new int[rows];
    }

    // Кожен елемент старого зображення записується у нове місце
    // після повороту на 90° за годинниковою стрілкою.
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    // Очищення старого масиву пікселів після створення нового.
    for (int i = 0; i < rows; ++i){
        delete[] img[i];
    }

    delete[] img;

    return newImg;
}