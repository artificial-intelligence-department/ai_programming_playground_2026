#include <iostream>
#include <iomanip>
using namespace std;

void palette(int **img, int rows, int cols){
    char** paletteArray = new char*[rows];
    const char palette[] = " .:-=+*#%@";
    cout << "Зображення " << rows << " x  " << cols << ":\n";
    for (int i = 0; i < rows; i++){
        paletteArray[i] = new char[cols];
        for (int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
            paletteArray[i][j] = palette[img[i][j]];
        }
    cout << "\n";
    }
    cout << "\n";
    cout << "Малюнок:\n";
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << paletteArray[i][j] << " ";
        }
    cout <<"\n";
    delete[] paletteArray[i];
    }
    delete [] paletteArray;
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    int minVal = img[0][0];
    int maxVal = img[0][0];
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (img[i][j] < minVal){
                minRow = i;
                minCol = j;
                minVal = img[i][j];
                }

            if (img[i][j] > maxVal){
                maxRow = i;
                maxCol = j;
                maxVal = img[i][j];
            }
        }
    }
}

void brightnessStatistics(int** img, int rows, int cols){
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "Найтемніший піксель: " << img[minRow][minCol]
         << "(рядок " << minRow + 1 << ", стовпець " << minCol + 1 << " )" << endl;
    cout << "Найcвітліший піксель: " << img[maxRow][maxCol]
         << "(рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << " )" << endl;
    double* avRows = new double[rows];
    int totalSum = 0;
    for (int i = 0; i < rows; i++){
        int* row = img[i];
        int rowSum = 0;
        for (int j = 0; j < cols; j++){
            rowSum += *(row + j);
        }
        avRows[i] = (double)rowSum / cols;
        totalSum += rowSum;
    }
    double totalAv = (double)totalSum / (rows * cols);
    cout << "Середня яскравість: " << fixed << setprecision(2) << totalAv << endl;
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++){
        cout << avRows[i] << " ";
    }
    cout << "\n";
    delete[] avRows;
}

void invertBrightness(int** img, int rows, int cols){
    const int MAX_BRIGHTNESS = 9;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            img[i][j] = (MAX_BRIGHTNESS - img[i][j]);
            cout << img[i][j] << " ";
        }
    cout << "\n";
    }
}

void swapPixels(int* a, int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void mirrorPixels(int** img, int rows, int cols){
    cout << "Зображення віддзеркалено.\n";
    cout << "Початкове:\n";
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
    cout << "\n";
    }
    cout <<"\n";
    cout << "Результат:\n";
    for (int i = 0; i < rows; i++){
        int* row = img[i];
        for (int j = 0; j < (cols / 2); j++){
            swapPixels(row  + j, row + (cols - 1) - j);
        }
    }
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
    cout << "\n";
    }
}

int** rotateRight(int ** img, int rows, int cols){
    int newRows = cols;
    int newCols = rows;
    cout << "Зображення повернуто. Нові розміри: " << newRows << " x " << newCols << "\n";
    int** imgModified = new int*[newRows];
    for (int i = 0; i < newRows; i++){
        imgModified[i] = new int[newCols]; 
    }

    for (int i = 0; i < rows; i++){
        int* row = img[i];
        for (int j = 0; j < cols; j++){
            imgModified[j][rows - 1 - i] = *(row + j);
        }
    delete[] img[i];
    }
    delete[] img;
    
    return imgModified;
}

int main(){
    int rows, cols, choice;

    cout << "Введіть кількість рядків: ";
    cin >> rows;
    if ((rows < 1) || (rows > 20)){
        cout << "Помилкове значення!" << endl;
        return 1;
    }

    cout << "Введіть кількість стовпців: ";
    cin >> cols;
    if ((cols < 1) || (cols > 20)){
        cout << "Помилкове значення!" << endl;
        return 1;
    }

    int N = rows * cols;
    int** img = new int*[rows];


    cout << "Введіть значення через пробіл: " << endl;
    for (int i = 0; i < rows; i++){
        img[i] = new int[cols];
        for (int j = 0; j < cols; j++){
            cin >> img[i][j];
        }
    }

    do{
        cout << "=====================\n";
        cout << "Пункт      Операція\n";
        cout << "1          Показати зображення\n";
        cout << "2          Статистика яскравості\n";
        cout << "3          Інвертувати яскравість\n";
        cout << "4          Віддзеркалити по горизонталі\n";
        cout << "5          Повернути на 90 градусів праворуч\n";
        cout << "0          Вийти\n"; 
        cout << "Оберіть дію: ";
        if (!(cin >> choice) || choice < 0 || choice > 5) {
            cout << "Некоректний пункт. Спробуйте ще раз.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        switch (choice){
            case 1:
                palette(img, rows, cols);
                break;
            case 2:
                brightnessStatistics(img, rows, cols);
                break;
            case 3:
                invertBrightness(img, rows, cols);
                break;
            case 4:
                mirrorPixels(img, rows, cols);
                break;
            case 5: 
                img = rotateRight(img, rows, cols);
                swapPixels(&rows, &cols);
                for (int i = 0; i < rows; i++){
                    for (int j = 0; j < cols; j++){
                        cout << img[i][j] << " ";
                    }
                cout << "\n";
                }
                break;
            case 0:
                for (int i = 0; i < rows; i++){
                    delete[] img[i];
                }
                delete[] img;
                img = nullptr;
                return 0;
    }
    } while (choice != 0);
}