/* 
Епік 4. Практичне завдання: Редактор монохромного зображення.
Авторка: Дячок Маргарита.
Група: ШІ-14.
*/

#include <iostream>
using namespace std;

void showImage(int** image, char** image_char, int rows, int cols) {
cout << "Зображення " << rows << " x " << cols << " :" << endl;

for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++){
        cout << image[i][j] << " ";
    } cout << endl;
}
cout << "Малюнок: \n";
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++){
        switch(image[i][j]) {//перетворюємо цифри на відповідні символи
        case 0 : image_char[i][j] = ' '; break;
        case 1 : image_char[i][j] = '.'; break;
        case 2 : image_char[i][j] = ':'; break;
        case 3 : image_char[i][j] = '-'; break;
        case 4 : image_char[i][j] = '='; break;
        case 5 : image_char[i][j] = '+'; break;
        case 6 : image_char[i][j] = '*'; break;
        case 7 : image_char[i][j] = '#'; break;
        case 8 : image_char[i][j] = '%'; break;
        case 9 : image_char[i][j] = '@'; break;
    }  cout << image_char[i][j];}
    cout << endl;}}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    int min = img[0][0];
    int max = img[0][0];
    minRow = 0; maxRow = 0; minCol = 0; maxCol = 0;
for (int i = 0; i < rows; i++) {int* row = img[i];
for (int j = 0; j < cols; j++) {
    if(*(row + j) < min) {min = *(row + j); minRow = i; minCol = j;}
    if (*(row + j) > max) {max = *(row + j); maxRow = i; maxCol = j;}}}}

double avarageBrightness(int** img, int rows, int cols) {
    double avarage = 0;
for (int i = 0; i < rows; i++) {int* row = img[i];
for (int j = 0; j < cols; j++) {
avarage += *(row + j);
}}
return avarage/(rows * cols);
}

double* avarageBrightnessRows(int** img, double* avarage_rows, int rows, int cols) {
for (int i = 0; i < rows; i++) {int* row = img[i];
double sum = 0;
for (int j = 0; j < cols; j++) {
    sum += *(row + j);}
avarage_rows[i] = (sum/cols);}
return avarage_rows;
}

void brightnessStatistic(int **img, double* avarage_rows, int rows, int cols) {
int minR, maxR, minC, maxC;
findExtremes(img, rows, cols, minR, minC, maxR, maxC);
cout << "Найтемніший піксель: " << img[minR][minC] << " (рядок " << minR + 1 << ", стовпець " << minC + 1 << ") \n";
cout << "Найсвітліший піксель: " << img[maxR][maxC] << " (рядок " << maxR + 1 << ", стовпець " << maxC + 1 << ") \n";
cout << "Середня яскравість: " << avarageBrightness(img, rows, cols) << endl; 
avarageBrightnessRows(img, avarage_rows, rows, cols);
cout << "Середня по рядках: ";
for (int i = 0; i < rows; i++) {
    cout << avarage_rows[i] << " ";
} cout << endl;
}

void invertBrightness(int** image, int rows, int cols) {
    cout << endl << "Яскравість інвертовано." << endl;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
image[i][j] = 9 - image[i][j];
cout << image[i][j] << " ";}
cout << endl;}
}

void swapPixels(int *a, int *b) {
    int copy = *a;
    *a = *b;
    *b = copy;}

void swapHorizontal(int rows, int cols, int** image) {
    if(cols == 1) {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
    cout << image[i][j] << " "; } cout << endl;} return;} 
    for(int i = 0; i < rows; i++){
int start = 0;
int end = cols - 1;
while (start < end) {
 swapPixels(&image[i][start], &image[i][end]);
start++;
end--;}
for(int j = 0; j < cols; j++) {
    cout << image[i][j] << " "; 
}cout << endl;}}

void swapHorizontalResult(int rows, int cols, int** image) {
    cout << "Зображення віддзеркалено.\n";
    cout << "Початкове: \n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++){
        cout << image[i][j] << " ";
} cout << endl;}
    cout << "\nРезультат: \n";
    swapHorizontal(rows, cols, image);}

int** rotateRight(int** img, int rows, int cols) {
    int** image_new = new int*[cols];
    for (int i = 0; i < cols; i++) {
        image_new[i] = new int[rows];}
    for(int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            image_new[i][j] = img[rows - 1 - j][i]; }}
for (int i = 0; i < rows; i++) {
    delete[] img[i];
    img[i] = nullptr;}
    delete[] img;
return image_new;
}

void rotateRightResult(int** &img, int &rows, int &cols) {
    cout << "Зображення повернуто. Нові розміри: " << cols << " x " << rows << "\n";
    img = rotateRight(img, rows, cols); 
    int temp; 
    temp = rows; 
    rows = cols; 
    cols = temp;
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++){
        cout << img[i][j] << " ";
    } cout << endl;}}



int main() {
int rows, cols;
int pomulka = 0;
cout << "Висота зображення (кількість пікселів): ";
cin >> rows;
if (rows < 0 || rows > 20){
    cout << "Помилка. Значення має бути в межах від 0 до 20.";
    return 0;}
cout << "Ширина зображення (кількість пікселів): ";
cin >> cols;
int start_rows = rows; 
if (cols < 0 || cols > 20) {
     cout << "Помилка. Значення має бути в межах від 0 до 20.";
     return 0;}
cout << "Яскравість пікселів (0...9): ";
cout << endl;
int** image = new int*[rows];
for (int i = 0; i < rows; i++) {
    image[i] = new int[cols];
}
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++){
        cin >> image[i][j];
        if (image[i][j] < 0 || image[i][j] > 9) {pomulka = 1; i = rows; break;}
    }
}

int** img = new int*[rows];
for (int i = 0; i < rows; i++) {
    img[i] = new int[cols];
}
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        img[i][j] = image [i][j];
    }
}

double* avarage_rows = new double[rows];
for (int i = 0; i < rows; i++) {
    avarage_rows[i] = 0.0;}//занулюємо елементи масиву, щоб позбутися сміття

char** image_char = new char*[rows];
for (int i = 0; i < rows; i++) {
    image_char[i] = new char[cols];
}
if(pomulka == 1) {
for (int i = 0; i < start_rows; i++) {
    delete[] image[i];
    delete[] image_char[i];}
delete[] image;
delete[] image_char;
delete[] avarage_rows;

for (int i = 0; i < rows; i++) {
    delete[] img[i];}
delete[] img;
return 0;
}
cout << "\nПункт     Операція\n";
cout << "1         Показати зображення\n" << "2         Статистика яскравості\n" << "3         Інвертувати яскравість\n" << "4         Віддзеркалити по горизонталі\n" << "5         Повернути на 90 градусів праворуч\n" << "0         Вийти\n";
int menu = -1;

cin >> menu;
do {
switch(menu) {
case 1 : showImage(image, image_char, rows, cols); break;
case 2 : brightnessStatistic(img, avarage_rows, rows, cols); break;
case 3 : invertBrightness(image, rows, cols); break;
case 4 : swapHorizontalResult(rows, cols, image); break;
case 5 :rotateRightResult(img, rows, cols); break;
case 0 : break;
default : break;

} cin >> menu; }
while (menu != 0);

for (int i = 0; i < start_rows; i++) {
    delete[] image[i];
    delete[] image_char[i];}
delete[] image;
delete[] image_char;
delete[] avarage_rows;

for (int i = 0; i < rows; i++) {
    delete[] img[i];}
delete[] img;

    return 0;
}