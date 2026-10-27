#include <iostream>
#include <iomanip>
using namespace std;    

void read(int** a, const int rows, const int cols ){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << "Введіть яскравість пікселя № "<< i * cols + j + 1 << endl;
            cin >> a[i][j];
            while(cin.fail() || a[i][j] < 0 || a[i][j] > 9){
                cout << "Помилка введення!" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Введіть яскравість пікселя   № "<< i * cols + j + 1 << endl;
                cin >> a[i][j];
            }
        }
    }
}

void delete_arr(int **&a, const int rows){
    for(int i = 0; i < rows; i++){
        delete[] a[i];
    }
    delete[] a;
    a = nullptr;
}

char interpret(int a){
    switch(a){
                case 0:
                    return ' ';
                case 1:
                    return '.';
                case 2:
                    return ':';
                case 3:
                    return '-';
                case 4:
                    return '=';
                case 5:
                    return '+';
                case 6:
                    return '*';
                case 7:
                    return '#';
                case 8:
                    return'%';
                case 9:
                    return '@';
                default:
                    return ' ';
            }
}

void print_matrix(int** a, const int rows, const int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void print_image(int** a, const int rows, const int cols){
    cout << "Зображення " << rows << " x " << cols << endl;
    print_matrix(a, rows, cols);
    cout << endl << "Малюнок:" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << interpret(a[i][j]);
        }
        cout << endl;
    }
}

void avg(int **img, const int rows, const int cols){
    int sum = 0;
    cout << "Середня по рядках: " << endl;
    for (int i = 0; i < rows; ++i) {
        int *row = img[i];
        int rowSum = 0;
        for(int j = 0; j < cols; ++j) {
            rowSum += *(row + j);
        }
        sum += rowSum;
        double rowAvg = rowSum / (double)cols;
        cout << rowAvg << " ";
    }
    double average = (double)sum / (rows * cols);
    cout << endl << "Середня яскравість: " << average << endl;
}

void inversion_brightness(int **img, const int rows, const int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "Яскравість інвертовано. " << endl;
    print_matrix(img, rows, cols);
}

void swapPixels(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int** rotateRight(int** img, int rows, int cols){
    int **a = new int*[cols];
    for(int i = 0; i < cols; i++){
        a[i] = new int[rows];
    }
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            a[i][j] = img[ rows - j - 1][i];
        }
    }
    delete_arr(img, rows);
    return a;
}

void mirror(int** img, const int rows, const int cols) {
    cout << "Зображення віддзеркалено.\n Початкове:" << endl;
    print_matrix(img, rows, cols);
    cout << "\nРезультат:" <<endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols / 2; ++j) {
            swapPixels(&img[i][j], &img[i][cols - j - 1]);
        }
    }
    print_matrix(img, rows, cols);
}

void findExtremes(int **img, const int rows, const int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    for (int i = 0; i < rows; ++i){
        int *row = img[i];
        for (int j = 0; j < cols; ++j) {
            if (*(row+j) < img[minRow][minCol]){
                minRow = i; 
                minCol = j; 
            }
            else if (*(row + j) > img[maxRow][maxCol]){ 
                maxRow = i;  
                maxCol = j; 
            }
        }
    }    
}

void stats(int **image, const int rows, const int cols) {
    int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;
    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "Найтемніший піксель: " << image[minRow][minCol]
         << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << image[maxRow][maxCol]
         << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
    avg(image, rows, cols);
}

int main() {

    cout << fixed << setprecision(2);
    
    int rows = 0;
    cout << "Введіть висоту зображення" << endl;
    cin >> rows;
    while(cin.fail() || rows <= 0 || rows > 20){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка введення!" << endl;
        cout << "Введіть висоту зображення" << endl;
        cin >> rows;
    }

    int cols = 0;
    cout << "Введіть ширину зображення" << endl;
    cin >> cols;
    while(cin.fail() || cols <= 0 || cols > 20){    
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка введення!" << endl;
        cout << "Введіть ширину зображення" << endl;
        cin >> cols;
    }

    int **image = new int*[rows];
    for(int i = 0; i < rows; i++){
        image[i] = new int[cols];
    }
    read(image, rows, cols);

    int menu_option = -1;
    do{
        cout << left << setw(10) << "\nПункт     " << "Операція" << endl;
        cout << left << setw(10) << "1" << "Показати зображення" << endl;
        cout << left << setw(10) << "2" << "Статистика яскравості" << endl;
        cout << left << setw(10) << "3" << "Інвертувати яскравість" << endl;
        cout << left << setw(10) << "4" << "Віддзеркалити по горизонталі" << endl;
        cout << left << setw(10) << "5" << "Повернути на 90 градусів праворуч" << endl;
        cout << left << setw(10) << "0" << "Вийти" << endl;
        cout << "Ваш вибір: ";

        cin >> menu_option;

        cout << "\n";

        if (cin.fail() || menu_option > 5 || menu_option < 0) {
            cout << "Помилка введення!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            menu_option = -1;
            continue;
        }

        switch(menu_option){
            case 1:
                print_image(image, rows, cols);
                break;
            case 2:{
                stats(image,rows, cols);
                break;
            }
            case 3:
                inversion_brightness(image, rows, cols);
                break;
            case 4:{
                mirror(image, rows, cols);
            }
                break;
            case 5:{
                image = rotateRight( image, rows, cols);
                int tmp = rows;
                rows = cols;
                cols = tmp;
                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
                print_matrix(image, rows, cols);
                break;
            }
            default:
                continue;
        }
    }while(menu_option != 0);

    delete_arr(image, rows);
    return 0;
}