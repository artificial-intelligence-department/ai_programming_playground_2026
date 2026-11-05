/*
Редактор монохромного зображення
Цебуля Вадим
ШІ-12
*/
#include <iostream>
#include <iomanip>

using namespace std;

void printImg(int **img, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

// Звільнення динамічної пам'яті, виділеної під двовимірний масив
void freeImg(int **img, int rows){
    if (img == nullptr) return; 
    for (int i = 0; i < rows; i++){
        delete[] img[i]; // Звільняємо пам'ять для кожного рядка
    }
    delete[] img;       // Звільняємо масив вказівників
    img = nullptr; 
}

void showImg(int **img, int rows, int cols){
        // Набір символів для градації яскравості від 0 (найнайтемніший) до 9 (найсвітліший)
        const char symbol[10] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};
        
        cout << "Зображення:" << rows << "x" << cols << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << img[i][j] << " ";
            } cout << endl;
        }
        
        cout << "Малюнок: " << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++){
                cout << symbol[img[i][j]];
            }
            cout << endl;
        }
}

// Пошук значень найменшого (найтемнішого) і найбільшого (найсвітлішого) пікселя
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
        minRow = 0, maxRow = 0;
        minCol = 0, maxCol = 0;
        int minValue = img[0][0];
        int maxValue = img[0][0];
        
        for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                        if (img[i][j] < minValue){
                            minValue = img[i][j];
                            minRow = i;
                            minCol = j;
                        }
                        if (img[i][j] > maxValue){
                            maxValue = img[i][j];
                            maxRow = i;
                            maxCol = j;
                        }
                }
        }
}

// Обчислення та вивід статистики: екстремуми, середня яскравість по рядках і всього матриці
void Stats(int **img, int rows, int cols){
        int minRow, maxRow;
        int minCol, maxCol;
        findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
        
        int minValue = img[minRow][minCol];
        int maxValue = img[maxRow][maxCol];
        
        cout << "Найтемніший піксель: " << minValue  << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
        cout << "Найсвітліший піксель: " << maxValue << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

        double sum = 0;
        double *avgRow = new double[rows]; 
        double avgBrightness;

        for (int i = 0; i < rows; i++){
                int *row = img[i];
                double sumRow = 0;
                for (int j = 0; j < cols; j++){
                        sumRow += *(row + j); 
                }
                avgRow[i] = sumRow / cols;
                sum += sumRow;
        }
        
        avgBrightness = sum / (rows * cols); 
        cout << fixed << setprecision(2);
        cout << "Середня яскравість: " << avgBrightness << endl;

        cout << setprecision(1);
        cout << "Середня по рядках: ";
        for (int i = 0; i < rows; i++){
                cout << avgRow[i] << " ";
        }
        cout << endl;
        
        delete[] avgRow; 
        avgRow = nullptr;
}

// Інверсія яскравості зображення (0 стає 9, 1 стає 8 і т.д.)
void invertImg(int **img, int rows, int cols){
        for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                        img[i][j] = 9 - img[i][j];
                }
        }
        cout << "Яскравість інвертовано." << endl;
        printImg(img, rows, cols);
}

void swapPixels(int *pixel1, int *pixel2){
        int temp = *pixel1;
        *pixel1 = *pixel2;
        *pixel2 = temp;
}

// Горизонтальне віддзеркалення зображення (перевертання зліва направо)
void mirrorImg(int **img, int rows, int cols){
        cout << "Зображення віддзеркалено." << endl;
        cout << "Початкове: " << endl;
        printImg(img, rows, cols);
        
        for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols / 2; j++){ 
                        swapPixels(&img[i][j], &img[i][cols - j - 1]);
                }
        }
        cout << "Результат: " << endl;
        printImg(img, rows, cols);
}

// Поворот матриці на 90 градусів праворуч
int** rotateRight(int **img, int rows, int cols){
        // Створення нової транспонованої динамічної матриці (розміри cols x rows)
        int **rotatedImg = new int*[cols];
        for (int i = 0; i < cols; i++){
                rotatedImg[i] = new int[rows];
        }
        
        // Перенесення елементів у нову матрицю
        for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                        rotatedImg[j][rows - 1 - i] = img[i][j];
                }
        }
        
        freeImg(img, rows); 
        return rotatedImg;  
}

void rotateImg(int **&img, int &rows, int &cols){
        img = rotateRight(img, rows, cols);
        
        int temp = rows;
        rows = cols;
        cols = temp;
        
        cout << "Зображення повернуто. Нові розміри: " << rows << "x" << cols << endl;
        printImg(img, rows, cols);
}

int main(){
        int **img = nullptr;
        
        // Ввід та валідація розмірів матриці
        cout << "Введіть висоту зображення: (від 1 до 20): " << endl;
        int rows;
        if (!(cin >> rows) || rows < 1 || rows > 20){
                cout << "Помилка: введено некоректне значення висоти." << endl;
                return 1;
        }

        cout << "Введіть ширину зображення: (від 1 до 20): " << endl;
        int cols;
        if (!(cin >> cols) || cols < 1 || cols > 20){
                cout << "Помилка: введено некоректне значення ширини." << endl;
                return 1;
        }

        img = new int*[rows];
        for (int i = 0; i < rows; i++){
                img[i] = new int[cols];
        }
        
        cout << "Введіть яскравість пікселів (від 0 до 9): " << endl;
        for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                        if (!(cin >> img[i][j]) || img[i][j] < 0 || img[i][j] > 9){
                                cout << "Помилка: введено некоректне значення яскравості." << endl;
                                freeImg(img, rows);
                                return 1;
                        }
                }
        }

        // Головне інтерактивне меню програми
        int choice;
        do {
        menu:
                cout << "=== Меню ===" << endl;
                cout << "1. Показати зображення" << endl;
                cout << "2. Статистика яскравості" << endl;
                cout << "3. Інвертувати яскравість" << endl;
                cout << "4. Віддзеркалити по горизонталі" << endl;
                cout << "5. Повернути на 90 градусів праворуч" << endl;
                cout << "0. Вийти" << endl;
                cout << "Оберіть пункт меню: ";
                
                if (!(cin >> choice)){
                        cout << "Помилка: оберіть меню від 0 до 5." << endl;
                        cin.clear();
                        cin.ignore(6769, '\n');
                        goto menu;
                }
                
                switch (choice){
                        case 1:
                                showImg(img, rows, cols);
                                break;
                        case 2:
                                Stats(img, rows, cols);
                                break;
                        case 3:
                                invertImg(img, rows, cols);
                                break;
                        case 4:
                                mirrorImg(img, rows, cols);
                                break;
                        case 5:
                                rotateImg(img, rows, cols);
                                break;
                        case 0:
                                cout << "Вихід з програми." << endl;
                                break;
                        default:
                                cout << "Помилка: Невірний пункт!" << endl;
                                cin.clear();
                                cin.ignore(6769, '\n');
                                goto menu;
                        }       
        } while (choice != 0);

        freeImg(img, rows);
        return 0;
}

