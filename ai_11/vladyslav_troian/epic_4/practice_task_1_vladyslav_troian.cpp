#include <iostream>
#include <iomanip>
using namespace std;

void showImage(int **img, int rows, int cols, char *bright)
{
    char **bright_img = new char*[rows];
    for (int i = 0; i < rows; i++){
        bright_img[i] = new char[cols];
    }

    cout << "Зображення " << rows << "x" << cols << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Малюнок: " << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            bright_img[i][j] = bright[img[i][j]];
            cout << bright_img[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++){
        delete[] bright_img[i];
    }
    delete[] bright_img;
    bright_img = nullptr;
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    int min = 9;
    int max = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int *row = img[i];
            if (min > *(row + j)){
                min = *(row + j);
                minRow = i;
                minCol = j;
            }
            if (max < *(row + j)){
                max = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
    cout << "Найтемніший піксель: " << min << " (рядок " << minRow+1 << ", стовпець " << minCol+1 << ")" << endl;
    cout << "Найсвітліший піксель: " << max << " (рядок " << maxRow+1 << ", стовпець " << maxCol+1 << ")" << endl;
}

void findAveraga(int **img, int rows, int cols)
{
    double *average_row_bright = new double[rows];
    double *double_row = nullptr;
    double average_bright;
    int sum = 0;
    int rowsum = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int *row = img[i];
            sum += *(row + j);
            rowsum += *(row + j);
        }
        double_row = &average_row_bright[i];
        *double_row = (double)rowsum/cols;
        average_row_bright[i] = *double_row;
        rowsum = 0;
    }
    average_bright = (double)sum/(rows*cols);
    cout << "Середня яскравість: " << setprecision(3) << average_bright << endl;
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++){
        cout << *(average_row_bright + i) << " ";
    }
    cout << endl;
    delete[] average_row_bright;
    average_row_bright = nullptr;
}

void invertBrightness(int **img, int rows, int cols)
{
    cout << "Яскравість інвертовано: " << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int inverted = 9 - img[i][j];
            img[i][j] = inverted;
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

void swapPixels(int *a, int *b)
{
    int x;
    x = *a;
    *a = *b;
    *b = x;
}

void horizontalReflection(int **img, int rows, int cols)
{
    cout << "Зображення віддзеркалено: " << endl;
    cout << "До віддзеркалення: " << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols/2; j++){
            swapPixels(&img[i][j], &img[i][cols-j-1]);
        }
    }

    cout << "Після віддзеркалення: " << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

int** rotateRight(int** img, int rows, int cols)
{
    int **rotated_img = new int*[cols];
    for (int i = 0; i < cols; i++){
        rotated_img[i] = new int[rows];
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            rotated_img[j][rows-1-i] = img[i][j];
        }
    }

    for (int i = 0; i < rows; i++){
        delete[] img[i];
    }
    delete[] img;
    img = rotated_img;
    img = nullptr;

    cout << "Зображення повернуто. Нові розміри " << cols << "x" << rows << endl;
    for (int i = 0; i < cols; i++){
        for (int j = 0; j < rows; j++){
            cout << rotated_img[i][j] << " ";
        }
        cout << endl;
    }
    return rotated_img;
}

int main()
{
    int rows;
    int cols;
    while (true) {
        cout << "Висота зображення: ";
        cin >> rows;
        if (cin.fail() || cin.peek() != '\n'){
            cout << "Неприпустиме значення!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        } else if(rows < 1 || rows > 20){
            cout << "Висота повинна бути від 1 до 20." << endl;
        } else break;
    }
    
    while (true) {
        cout << "Ширина зображення: ";
        cin >> cols;
        if (cin.fail() || cin.peek() != '\n'){
            cout << "Неприпустиме значення!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        } else if (cols < 1 || cols > 20){
            cout << "Ширина повинна бути від 1 до 20." << endl;
        } else break;
    }

    int **image = new int*[rows];
    for (int i = 0; i < rows; i++){
        image[i] = new int[cols];  
    }

    while (true) {
        bool incorrect = false;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Яскравість пікселів (0..9): " << endl;
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                cin >> image[i][j];
                if (cin.fail() || image[i][j] < 0 || image[i][j] > 9){
                    incorrect = true;
                    cout << "Неприпустиме значення! Уведіть всі значення знову!" << endl;
                    break;
                }
            }
            if (incorrect) break;
        }
        if (!incorrect) break;
    }

    char brightness[10] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};
    int minRow;
    int minCol;
    int maxRow;
    int maxCol; 

    int option;
    bool exit = false;

    do {
        cout << "> Меню" << endl;
        cout << "1 > Показати зображення" << endl;
        cout << "2 > Статистика яскравості" << endl;
        cout << "3 > Інвертувати яскравість" << endl;
        cout << "4 > Віддзеркалити по горизонталі" << endl;
        cout << "5 > Повернути на 90 градусів праворуч" << endl;
        cout << "0 > Вихід" << endl;
        cout << "> ";
        if (!(cin >> option)){
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cout << endl;
        switch (option){
            case 0:
                exit = true;
                break;
            case 1:
                showImage(image, rows, cols, brightness);
                break;
            case 2:
                findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
                findAveraga(image, rows, cols);
                break;
            case 3:
                invertBrightness(image, rows, cols);
                break;
            case 4:
                horizontalReflection(image, rows, cols);
                break;
            case 5:
                image = rotateRight(image, rows, cols);
                swapPixels(&rows, &cols);
                break;
        }
    } while(!exit);

    for (int i = 0; i < rows; i++){
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;

    return 0;
}