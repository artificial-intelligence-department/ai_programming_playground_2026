/*  Практична робота
    "Редактор монохромного зображення"
    Ярошик Наталія
    ШІ-14 */
#include <iostream>
#include <iomanip>
using namespace std;

// 1. Показати зображення
void showImage(int **image, int rows, int cols){
    // Таблиця чисел
    cout << "Зображення " << rows << " x " << cols << '\n';
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << image[i][j] << " ";
        }
        cout << '\n';
    }
    // Таблиця символів
    cout << "\nМалюнок:\n";
    const char symbols[] = " .:-=+*#%@";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << symbols[image[i][j]] << " ";
        }
        cout << '\n';
    }
}

// 2. Ститистика яскравості
void findExtremes(int **img, int rows, int cols, int &minRow, 
    int &minCol, int &maxRow, int &maxCol){
        int minVal = 10, maxVal = -1;
        for(int i = 0; i < rows; i++){
            int *row = img[i];
            for(int j = 0; j < cols; j++){
                int val = *(row + j);

                // Якщо знайшли новий мінімум
                if(val < minVal){
                    minVal = val;
                    minRow = i;
                    minCol = j;
                }

                // Якщо знайшли новий максимум
                if(val > maxVal){
                    maxVal = val;
                    maxRow = i;
                    maxCol = j;
                }
            }
        }
    }

void braightnessStat(int **image, int rows, int cols){
    int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;

    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "Найтемніший піксель: " << image[minRow][minCol] 
    << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")\n";
    cout << "Найсвітліший піксель: " << image[maxRow][maxCol] 
    << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")\n";\

    double totalSum = 0;
    cout << "Середня по рядках: ";
    for(int i = 0; i < rows; i++){
        int *row = image[i];
        double rowSum = 0;
        for(int j = 0; j < cols; j++){
            rowSum += *(row + j);
        }
        totalSum += rowSum;
        cout << fixed << setprecision(1) << rowSum / cols << " ";
    }

    cout << "\nСередня яскравість: " << fixed << setprecision(2) << totalSum / (rows * cols) << '\n';
}

// 3. Інвертувати яскравість
void invertBrightness(int **image, int rows, int cols){
    cout << "Яскравість інвертовано.\n";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            image[i][j] = 9 - image[i][j];
            cout << image[i][j] << " ";
        }
        cout << '\n';
    }
}

// 4. Віддзеркалити по горизонталі
void swapPixels(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void flipHorizontally(int **image, int rows, int cols){
    cout << "Зображення віддзеркалено.\n";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols / 2; j++){
            swapPixels(&image[i][j], &image[i][cols - j - 1]);
        }
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << image[i][j] << " ";
        }
        cout << '\n';
    }
}

// 5. Повернути на 90 градусів праворуч
int** rotateRight(int **img, int rows, int cols){
    int **newImg = new int*[cols];
    for(int i = 0; i < cols; i++){
        newImg[i] = new int[rows];
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    for(int i = 0; i < rows; i++){
        delete[] img[i];
    }
    delete[] img;

    return newImg;
}

int main(){
    int num, rows, cols;
    cout << "Висота зображення: ";
    if(!(cin >> rows) || rows > 20 || rows < 1){
        cout << "Введено некоректні дані\n";
        return 0;
    }
    cout << "Ширина зображення: ";
    if(!(cin >> cols) || cols > 20 || cols < 1){
        cout << "Введено некоректні дані\n";
        return 0;
    }

    int **image = new int*[rows];

    for(int i = 0; i < rows; i++){
        image[i] = new int[cols];
    }

    cout << "Яскравість пікселів (0..9): \n";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(!(cin >> image[i][j]) || image[i][j] < 0 || image[i][j] > 9){
            cout << "Введено некоректні дані\n";
                for(int k = 0; k < rows; k++){
                    delete[] image[k];
                }
                delete[] image;
                return 0;
            }
        }
    }
    do{
        menu:
        cout << '\n';
        cout << "1\t" << "Показати зображення\n";
        cout << "2\t" << "Статистика яскравості\n";
        cout << "3\t" << "Інвертувати яскравість\n";
        cout << "4\t" << "Віддзеркалити по горизонталі\n";
        cout << "5\t" << "Повернути на 90 градусів праворуч\n";
        cout << "0\t" << "Вийти\n";

        cout << "\nВведіть номер пункту: ";
        if(!(cin >> num) || (num != 1 && num != 2 && num != 3 
            && num != 4 && num != 5 && num != 0)){
                cin.clear();
                cin.ignore(10000, '\n');
                goto menu;
            } 
        
        switch(num){
            case 1:
                showImage(image, rows, cols);
                break;
            case 2:
                braightnessStat(image, rows, cols);
                break;
            case 3:
                invertBrightness(image, rows, cols);
                break;
            case 4:
                flipHorizontally(image, rows, cols);
                break;
            case 5:
                cout << "Зображення повернуто." << '\n';
                image = rotateRight(image, rows, cols);
                swap(rows, cols);
                for(int i = 0; i < rows; i++){
                    for(int j = 0; j < cols; j++){
                        cout << image[i][j] << " ";
                    }
                    cout << '\n';
                }
                cout << "Нові розміри: " << rows << " x " << cols << '\n';
                break;
            case 0:
                break;
        }
    }while(num != 0);

    // Звільнення пам'яті
    for(int i = 0; i < rows; i++){
        delete[] image[i];
    }

    delete[] image;
    image = nullptr;
    return 0;
}