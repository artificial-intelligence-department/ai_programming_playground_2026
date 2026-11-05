#include <iostream>
#include <limits>
using namespace std;

/*
 * Задача: Class Practice Work
 * Щербак Орислав
 * Група ШІ-11
 */

const char symbols[] = " .:-=+*#%@";
void showImage(int** image, int rows, int cols, const char* symbols){
    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Малюнок: " << endl;
    for(int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << symbols[image[i][j]];
        }
        cout << endl;
    }
    cout << endl;
    cout << "Поточні розміри: " << rows << " x " << cols << endl;
}
void findExtremes(int** image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    minRow = 0;
    maxRow = 0;
    minCol = 0;
    maxCol = 0;
    for(int i = 0; i < rows; i++){
        int* row = image[i];
        for (int j = 0; j < cols; j++){
            if(*(row + j) < *(*(image + minRow) + minCol)){
                minRow = i;
                minCol = j; 
            }
            if(*(row + j) > *(*(image + maxRow) + maxCol)){
                maxRow = i;
                maxCol = j;
            }
        }
    }
}
void showStatistic(int ** image, int rows, int cols){
    int minRow, minCol, maxRow, maxCol;
    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
    int minValue = *(*(image +minRow) + minCol);
    int maxValue = *(*(image +maxRow) + maxCol);
    cout << "Найтемніший піксель: " << minValue << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")"<< endl;
    cout << "Найсвітліший піксель: " << maxValue << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")"<< endl;
    int sum = 0;
    cout << "Середня по рядках: ";
    for(int i =0; i < rows; i++){
        int* row = image[i];
        int rowSum = 0;
        for(int j = 0; j < cols; j++){
            rowSum += *(row + j);
        }
        sum += rowSum;
        double rowAverage = static_cast<double> (rowSum) / cols;
        cout << rowAverage << " ";
    }
    double average = static_cast<double>(sum) / (rows * cols);
    cout << endl << "Середня яскравість: " << average << endl;
}
void invertBrightness(int** image, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            image[i][j] = 9 - image[i][j];
        }
    }
}
void swapPixels(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void swapImage(int** image, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols / 2; j++){
            swapPixels(&image[i][j], &image[i][cols -1 -j]);
        }
    }
}
int** rotateRight (int** image, int rows, int cols){
    int** rotated = new int*[cols];
    for(int i = 0; i < cols; i++){
        rotated[i] = new int[rows];
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            rotated[j][rows - 1 - i] = image [i][j];
        }
    }
    for(int k = 0; k < rows; k++){
        delete[] image[k];
    }
    delete[] image;
    return rotated;
}
int main(){
    int rows, cols;
    cout << "Висота зображення: ";
    if(!(cin >> rows && rows >= 1 && rows <= 20)){
        cout << "Помилка: висота повинна бути від 1 до 20" << endl;
        return 1;
    }
    cout << "Ширина зображення: ";
    if(!(cin >> cols && cols >= 1 && cols <= 20)){
        cout << "Помилка: ширина повинна бути від 1 до 20" << endl;
        return 1;
    }
    int** image = new int*[rows];
    for(int i = 0; i < rows; i++){
        image[i] = new int[cols];
    }
    cout << "Яскравість пікселів (0..9):" << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(!(cin >> image[i][j] && image[i][j] >= 0 && image[i][j] <= 9)){
                cout << "Помилка: яскравість повинна бути від 0 до 9" << endl;
                for(int k = 0; k < rows; k++){
                    delete[] image[k];
                    image[k] = nullptr;
                }
                delete[] image;
                image = nullptr;
                return 1;
            }
        }
    }
    int choice = -1;
    do{
        cout << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" << endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вийти" << endl;
        cout << "Ваш вибip: " << endl;
        if (!(cin >> choice)){
            cout << "Помилка, введіть номер пункту меню" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }
        switch(choice){
            case 0: 
                break;
            case 1:
                showImage(image, rows, cols, symbols);
                break;
            case 2:
                showStatistic(image, rows, cols);
                break;
            case 3: 
                invertBrightness(image, rows, cols);
                cout << "Яскравість інвертовано." << endl;
                for(int i = 0; i < rows; i++){
                    for(int j =0; j < cols; j++){
                        cout << image[i][j] << " ";
                    }
                    cout << endl;
                }
                break;
            case 4: 
                cout << "Зображення відзеркалено." << endl;
                cout << "Початкове:" << endl;
                for(int i = 0; i < rows; i++){
                    for(int j =0; j < cols; j++){
                        cout << image[i][j] << " ";
                    }
                    cout << endl ;
                }
                cout << endl << "Результат:" << endl;
                swapImage(image, rows, cols);
                for(int i = 0; i < rows; i++){
                    for(int j =0; j < cols; j++){
                        cout << image[i][j] << " ";
                    }
                    cout << endl;
                }
                break;
            case 5:{
                image = rotateRight(image, rows, cols);
                int temp = rows;
                rows = cols;
                cols = temp;
                cout << "Зображенння повернуто. Нові розміри: " << rows << " x " << cols << endl;   
                for(int i = 0; i < rows; i++){
                    for(int j = 0; j < cols; j++){
                        cout << image[i][j] << " ";
                    }
                    cout << endl;
                }
                break;
            }
                default: 
                    cout << "Немає такого пункту меню." << endl;
                break;
        }
    } while (choice != 0);
    for(int k = 0; k < rows; k++){
        delete[] image[k];
        image[k] = nullptr;
    }
        delete[] image;
        image = nullptr;
        return 0;
}