/*
Задача:Редактор монохромного зображення
Виконав:Андрій Шикоряк , ШІ-13
*/

#include <iostream>
#include <iomanip>
using namespace std;

void ShowImage(int **image, int rows, int cols);
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void InvertPixels(int **img, int rows, int cols);
void SwapPixels(int *a, int *b);
void PrintReference(int **image, int rows, int cols);
void MirrorPixels(int **img, int rows, int cols);
int** rotateRight(int** img, int rows, int cols);


int main() 
{
    int rows, cols, minCol, maxCol, minRow, maxRow;
    HEIGHT:
    cout << "Висота зображення (1-20): ";
    cin >> rows;
    if(rows > 20 || rows < 1 || cin.fail()){
        cin.clear();
        cin.ignore(10000,'\n');
        cout << endl;
        cout << "Введено невірне значення, значення має бути в межах 1-20, та бути числом" << endl;
        goto HEIGHT;
    }
    WIDTH:
    cout << "Ширина зображення (1-20): ";
    cin >> cols;
    if(cols > 20 || cols < 1 || cin.fail()){
        cin.clear();
        cin.ignore(10000,'\n');
        cout << endl;
        cout << "Введено neвірне значення, значення має бути в межах 1-20, та бути числом" << endl;
        goto WIDTH;
    }

    int **image = new int *[rows];
    for (int i = 0; i < rows; i++) {
        image[i] = new int [cols];
    }
    PIXELS:

    cout << "Яскравість пікселів (0..9): ";
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++){
            cin >> image[i][j];
            if(image[i][j] < 0 || image[i][j] > 9 || cin.fail()){
                cin.clear();
                cin.ignore(10000,'\n');
                cout << "Введено невірне значення, значення має бути в межах 0-9, та бути числом" << endl;
                goto PIXELS;
                
            }
        }
    }
    
    int choice = -1;
    MENU:
    do{
        cout << "Виберіть дію: " << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" << endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;
        if(cin.fail()){
            cin.clear();
            cin.ignore(10000,'\n');
            goto MENU;
        }
        switch (choice){
            case 1:
                ShowImage(image, rows, cols);
                break;
            case 2:
                findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
                break;
            case 3:
                InvertPixels(image, rows, cols);
                break;
            case 4:
                MirrorPixels(image, rows, cols);
                break;
            case 5:{
                cout << "Зображення повернуто. Нові розміри " << cols << " x " << rows << endl;
                image = rotateRight(image, rows, cols);
                int temp = rows;
                rows = cols;
                cols = temp;
                PrintReference(image, rows, cols);
                break;
            }
            case 0:
                cout << "Вихід.";
                break;
            default:
                cout << "Введено невірне значення, спробуйте ще раз" << endl;
                goto MENU;
                break;
        }
    }
    while(choice != 0);

    for (int i = 0; i < rows; i++)
    {
        delete[] image[i];
        image[i] = nullptr;
    }
    delete[] image;
    image=nullptr;
    return 0;
}

// Допоміжний вивід зображення
void PrintReference(int **image, int rows, int cols){
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++){
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
// виведння іншого сприйнятта зображення
void ShowImage(int **image, int rows, int cols){
    string palitre = " .:-=+*#%@";
    cout << "Зображення " << rows << "x" << cols << ":" << endl;
    PrintReference(image, rows, cols);
    cout << "Малюнок: " << endl;
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++){
            cout << palitre[image[i][j]];
        }
        cout << endl;
    }
}
// Пошук і виведння інформації по зображенню
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    int darkest = *(*(img+0) + 0);
    int brightest = *(*(img+0) + 0);
    double *AverageOnRow = new double[rows]();
    minCol = 1; 
    minRow = 1;
    maxCol = 1; 
    maxRow = 1;

    double average_brightness = 0.0;
    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        for(int j = 0; j < cols; j++){
            int current_pixel = *(row + j);
            AverageOnRow[i] += current_pixel;
            if(current_pixel < darkest){
                darkest = current_pixel;
                minRow = i + 1;
                minCol = j + 1; 
            }
            if(current_pixel > brightest){
                brightest = current_pixel;
                maxRow = i + 1;
                maxCol = j + 1;
            }
            average_brightness += current_pixel;
        }
    }

    cout << "Середня яскравість: " << fixed << setprecision(2) << (average_brightness / (cols * rows)) << endl;
    cout << "Найтемніший піксель: " << darkest << ", рядок " << minRow << ", стовпець " << minCol << endl;
    cout << "Найсвітліший піксель: " << brightest << ", рядок " << maxRow << ", стовпець " << maxCol << endl;
    cout << "Середня яскравість по рядку: ";
    for (int i = 0; i < rows; i++) {
        cout << fixed << setprecision(1) << AverageOnRow[i] / cols << " ";
    }
    cout << endl;
    delete[] AverageOnRow;
}
// Інвертування пікселів
void InvertPixels(int **img, int rows, int cols){
    cout << "Яскравість інвертовано" << endl;
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++){
            img[i][j] = 9 - img[i][j];
        }
    }
    PrintReference(img,rows,cols);
}

void SwapPixels(int *a, int *b){
    int x = *a;
    *a = *b;
    *b = x;
}
// Віддзеркалення зображення
void MirrorPixels(int **img, int rows, int cols){
    cout << "Зображення віддзеркалено:" << endl;
    cout << "Початкове: " << endl;
    PrintReference(img,rows,cols);
    cout << endl;
    cout << "Результат: "<<endl;
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols / 2; j++){
            SwapPixels(&img[i][j], &img[i][cols - j - 1]);
        }
    }
    PrintReference(img, rows, cols);
}
// Поворот на 90 градусів
int** rotateRight(int** img, int rows, int cols){
    int **rotated_array = new int*[cols];
    for (int i = 0; i < cols; i++) {
        rotated_array[i] = new int[rows];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            rotated_array[j][rows - i - 1] = img[i][j];
        }       
    }
    
    for (int i = 0; i < rows; i++)
    {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img=nullptr;
    
    return rotated_array;
}
