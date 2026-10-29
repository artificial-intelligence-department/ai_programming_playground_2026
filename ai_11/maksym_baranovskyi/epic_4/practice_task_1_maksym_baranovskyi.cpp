#include <iostream>
#include <iomanip>
using namespace std;

const char SYMBOLES[10] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};

void printImage(int **img, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

void showImage(int** image, int rows, int cols){
    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << image[i][j] << " ";
        }
    cout << endl;
    }
    cout << "Малюнок:" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << SYMBOLES[image[i][j]];
        }
    cout << endl;
    }
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    minRow = minCol = maxRow = maxCol = 0;
    int minVal = *(*img);
    int maxVal = minVal;
    for(int i = 0; i < rows; i++){
        int *row = img[i];
        for(int j = 0; j < cols; j++){
            if(*(row + j) < minVal){
                minVal = *(row + j);
                minRow = i;
                minCol = j;
            }
            if(*(row + j) > maxVal){
                maxVal = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void findAverages(int **img, int rows, int cols, double *rowAverages, double& overallAverage){
    double overallSum = 0.0;
    for(int i = 0; i < rows; i++){
        int *row = img[i];
        double rowSum = 0.0;
        for(int j = 0; j < cols; j++){
            rowSum += *(row + j);
        }
        *(rowAverages + i) = rowSum / cols;
        overallSum += *(rowAverages + i);
    }
    overallAverage = overallSum / rows;
}

void showStatistics(int **img, int rows, int cols){
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    double *rowAverages = new double[rows];
    double overallAverage;

    findAverages(img, rows, cols, rowAverages, overallAverage);

    cout << "Найтемніший піксель: " << *(*(img + minRow) + minCol) << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << *(*(img + maxRow) + maxCol) << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << overallAverage << endl;
    cout << setprecision(1);
    cout << "Середня по рядках: ";
    for(int i = 0; i < rows; i++){
        cout << *(rowAverages + i) << " ";
    }
    cout << endl;
    
    delete[] rowAverages;
    rowAverages = nullptr;

}

void invertBrightness(int ** img, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "Яскравість інвертовано." << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

void swapPixels(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mirrorImage(int **img, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols / 2; j++){
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
}

void mirrorImageResult(int ** img, int rows, int cols){
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове: " << endl;
    printImage(img, rows, cols);
    mirrorImage(img, rows, cols);
    cout << "Результат: " << endl;
    printImage(img, rows, cols);
}

int** rotateRight(int **img, int rows, int cols){
    int **newImg = new int*[cols];
    for(int j = 0; j < cols; j++){
        newImg[j] = new int[rows];
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            newImg[j][rows - 1 - i] = img[i][j]; 
        }
    }
    for(int i = 0; i < rows; i++){
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;

    return newImg;

}

void rotateRightResult(int **&img, int& rows, int& cols){
    img = rotateRight(img, rows, cols);

    int temp = rows;
    rows = cols;
    cols = temp;
    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    printImage(img, rows, cols);
}
    

int main(){

    cout << "Введіть значення висоти зображення (пікселів від 1 до 20): " << endl;
    int rows;
    if(!(cin >> rows) || rows < 1 || rows > 20){
        cout << "Введено некоректне значення!" << endl;
        return 1;
    }

    cout << "Введіть значення ширини зображення (пікселів від 1 до 20): " << endl;
    int cols;
    if(!(cin >> cols) || cols < 1 || cols > 20){
        cout << "Введено некоректне значення!" << endl;
        return 1;
    }

    cout << "Введіть яскравість пікселів (" << rows << " рядків по " << cols << " чисел від 0 до 9): " << endl;
    int** img = new int*[rows];
    for(int i = 0; i < rows; i++){
        img[i] = new int[cols];
        for(int j = 0; j < cols; j++){
            if(!(cin >> img[i][j]) || img[i][j] < 0 || img[i][j] > 9){
                cout << "Введено некоректне значення!" << endl;
                for (int k = 0; k <= i; k++){
                    delete[] img[k];
                    img[k] = nullptr;
                } 
                delete[] img;
                img = nullptr;
                return 1;
            } 
        }
    }

    int userInput = -1;

    do{

        cout << left;

        menu:
            cout << setw(24) << "Пункт" << "Операція" << endl;
            cout << setw(19) << 1 << "Показати зображення" << endl;
            cout << setw(19) << 2 << "Статистика яскравості" << endl;
            cout << setw(19) << 3 << "Інвертувати яскравість" << endl;
            cout << setw(19) << 4 << "Віддзеркалити по горизонталі" << endl;
            cout << setw(19) << 5 << "Повернути на 90 градусів праворуч" << endl;
            cout << setw(19) << 0 << "Вийти" << endl;
    
        if(!(cin >> userInput)){
            cin.clear();
            cin.ignore(10000, '\n');
            userInput = -1;
        }

        switch(userInput){
            case 0:
                cout << "Завершення програми..." << endl;
                break;
            case 1:
                showImage(img, rows, cols);
                break;
            case 2:
                showStatistics(img, rows, cols);
                break;
            case 3:
                invertBrightness(img, rows, cols);
                break;
            case 4:{
                mirrorImageResult(img, rows, cols);
                break;
            }
            case 5:{
                rotateRightResult(img, rows, cols);
                break;
            }
            default:
                cout << "Введіть коректне значення операції: " << endl;
                goto menu;
                break;
        }
    }
    while (userInput != 0);

    for (int i = 0; i < rows; i++){
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;

    return 0;
}