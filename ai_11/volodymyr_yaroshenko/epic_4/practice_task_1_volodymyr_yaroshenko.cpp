#include <iostream>
#include <iomanip>
using namespace std;
void clear(int** img, int rows) {
    if (img == nullptr) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
    }
    delete[] img;
}

void print(int** img,int rows, int cols) {
    for(int i =0;i<rows; i++) {
        for(int j=0; j<cols; j++) {
            cout << img[i][j] << ' ';
        }
        cout << endl;
    }
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
int min = **img;
int max = **img;
for(int i =0; i<rows; i++){
int* row = img[i];
    for (int j = 0; j < cols; j++){
        if(*(row +j)>max) {
            max = *(row +j);
            maxRow = i;
            maxCol = j;
        }
        if(*(row +j)<min) {
            min = *(row +j);
            minRow = i;
            minCol = j;
        }
    }
}
}

void avgShines(int **img, int rows, int cols, double &avgShine) {
int sum =0;
for(int i =0;i<rows; i++) {
 int *row =img[i];
    for(int j=0; j<cols; j++) {
        sum += *(row + j);
        }
    }
avgShine = (double(sum)) / (double(rows)* double(cols));
}

void swapPixels(int* a, int* b) {
int temp = *a; 
*a = *b;  
*b = temp;
}

int** rotateRight(int** img, int rows, int cols) {
    int** img_new = new int*[cols];
    for(int i = 0; i<cols; i++){
        img_new[i] = new int[rows];
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
img_new[j][rows - 1 - i] = img[i][j];
        }
    }
for(int i =0; i<rows; i++) {
        delete[] img[i];
    }
    delete[] img;
    img = img_new;
    img_new = nullptr; 
    return img;
}

void case1(int** img, int rows, int cols) {
char** pic = new char*[rows];
for(int i =0; i<rows; i++){
    pic[i] = new char[cols];
} 
for(int i= 0;i<rows;i++) {
    for(int j =0; j<cols;j++){
 switch(img[i][j]) {
    case 0: pic[i][j] = ' ';
    break;
    case 1: pic[i][j] = '.';
    break;
    case 2: pic[i][j] = ':';
    break;
    case 3: pic[i][j] = '-';
    break;
    case 4: pic[i][j] = '=';
    break;
    case 5: pic[i][j] = '+';
    break;
    case 6: pic[i][j] = '*';
    break;
    case 7: pic[i][j] = '#';
    break;
    case 8: pic[i][j] = '%';
    break;
    case 9: pic[i][j] = '@';
    break;
    default:
    break;
        }
    }
}
cout << "Зображення " << rows << " x " << cols <<":" <<  endl; 
print(img, rows, cols);
cout << "Малюнок: " << endl;
for(int i =0;i<rows; i++) {
        for(int j=0; j<cols; j++) {
            cout << pic[i][j] << ' ';
        }
        cout << endl;
    }
    for(int i =0; i<rows; i++) {
        delete[] pic[i];
    }
    delete[] pic;
    pic = nullptr;
}

void case2(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
double avgShine =0;

int min = **img;
int max = **img;
for(int i =0; i<rows; i++){
    int* row = img[i];
    for(int j =0; j<cols; j++){
        if(*(row +j)>max) {
            max = *(row +j);
        }
        if(*(row +j)<min) {
            min = *(row +j);
        }
    }
}
findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
avgShines(img, rows, cols, avgShine);
cout << "Найтемніший піксель: " << min << " (рядок " << minRow+1 << ", "  << "стовпець " << minCol+1 << ')' << endl; 
cout << "Насвітліший піксель: " << max << " (рядок " << maxRow+1 << ", " << "стовпець " << maxCol+1 << ')' << endl; 
cout << "Середня яскравість: " <<fixed<<  setprecision(2) << avgShine << endl;
cout << "Середня по рядках: ";
for(int i =0; i <rows; i++) {
int* row = img[i];
double colShine =0;
int colSum =0;
int count =0;
    for(int j=0; j<cols; j++){
        colSum += *(row + j);
        count++;
    }
    colShine = double(colSum) / count;
    cout  << fixed << setprecision(1) << colShine << ' ';
}
cout << endl;
}

void case3(int** img, int rows, int cols) {
for(int i =0; i<rows; i++){
    for(int j =0; j<cols; j++){
        int temp = img[i][j];
        img[i][j] = 9 - temp;
    }
}
print(img, rows, cols);
}

void case4(int** img, int rows, int cols) {
    cout << "Зображення віддзеркалено" << endl << "Початкове: " << endl;
print(img, rows, cols);
for(int i =0; i<rows; i++){
    int* row = img[i];
    for(int j=0; j<(cols/2); j++){
        swapPixels((row +j),(row + (cols - 1-j)));
    }
}
cout << "\nРезультат: " << endl;
print(img, rows,cols);
}

void case5(int** &img, int &rows, int &cols) {
    img = rotateRight(img, rows, cols);
    int temp = rows;    
    rows = cols;
    cols = temp;
    cout << "Зображення перевернуто. Нові його розміри: " << rows << " x " << cols << endl;
    print(img, rows, cols);
}

int main() {
int rows =0;
int cols =0;
int choise;
int minRow =0;
int minCol= 0;
int maxRow= 0;
int maxCol= 0;
cout <<  "Висота зображення: ";
if(!(cin >> rows)) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введіть число!";
    return -1;
}
if(rows<1 || rows > 20) {
    cout << "Введіть коректне значення!" << endl;
    return -1;
}
cout << "Ширина зображення: ";
if(!(cin >> cols)) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введіть число!";
    return -1;
}
if(cols <1 || cols > 20) {
    cout << "Введіть коректне значення!" << endl;
    return -1;
} 
cout << "Яскравіть пікселів (0..9):" << endl;
int** img = new int*[rows];
for(int i = 0; i<rows; i++) {
    img[i] = new int[cols];
}

for(int i =0; i<rows; i++) {
    for(int j=0; j<cols; j++) {
      if(!(cin >> img[i][j])) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введіть число!";
    clear(img, rows);
    return -1;
    }
    if(img[i][j] < 0 || img[i][j] > 9) {
        cout << "Введіть коректне значення!" << endl;
        clear(img, rows);
        return -1;
    }
 }
}
do{ menu:
cout << "1)" << "Показати зображення" << endl;
cout << "2)" << "Статистика яскравості" << endl;
cout << "3)" << "Інвертувати яскравість" << endl;
cout << "4)" << "Віддзеркалити по горизонталі" << endl;
cout << "5)" << "Повернути на 90 градусів праворуч" << endl;
cout << "0)" << "Вийти" << endl;
if(!(cin >> choise)) {
 cin.clear();
 cin.ignore(10000, '\n');
 cout << "Введіть число!" << endl;
 goto menu;
    }
switch(choise) {
case 1:
case1(img, rows, cols);
break;
case 2:
case2(img, rows, cols, minRow, minCol, maxRow, maxCol);
break;
case 3:
case3(img, rows, cols);
break;
case 4:
case4(img, rows, cols);
break;
case 5:
case5(img, rows, cols);
break;
case 0:
cout << "Програму завершено." << endl;
break;
default: 
    cout << "Неправильний пункт меню!" << endl;
    break;
    }
}
while(choise !=0);
clear(img, rows);
    img = nullptr; 
    return 0;
}