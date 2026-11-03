#include <iostream>

using namespace std;

//Оголошення змінних для роботи функцій
int rows, cols, i, j, image;

//Показ зображення
void showImg(int** img, int rows,int cols){
    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\n" << "Малюнок:" << endl;
    char q;
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            switch (img[i][j]) {
                case 0: q = ' '; break;
                case 1: q = '.'; break;
                case 2: q = ':'; break;
                case 3: q = '-'; break;
                case 4: q = '='; break;
                case 5: q = '+'; break;
                case 6: q = '*'; break;
                case 7: q = '#'; break;
                case 8: q = '%'; break;
                case 9: q = '@'; break;
                default: break;
            }
            cout << q << " ";
        }
        cout << endl;
    }
    return;
}

//Координати найтемнішого і найсвітлішого пікселів
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;
    int minVal = **img, maxVal = **img;
    for(i=0;i<rows;i++){
        int *row = img[i];
        for(j=0;j<cols;j++){
            if(maxVal < *(row+j)){
                maxVal = *(row+j); maxRow = i; maxCol = j;
            }
            if(minVal > *(row+j)){
             minVal = *(row+j); minRow = i; minCol = j;
            }
        }
    }
    return;
}

//Середня яскравість всього зображення
void avgImg(int **img, int rows, int cols, float &avgA){
    avgA = 0; 
    for(i=0;i<rows;i++){
        int *row = img[i];
        for(j=0;j<cols;j++){
            avgA += *(row+j);
        }
    }
    avgA = (float)avgA/(rows*cols);
    return;
}

//Середня яскравість по рядках
void avgRows(int **img, int rows, int cols, float &avgR){ 
    cout << "Середня яскравість по рядках: ";
    for(i=0;i<rows;i++){
        avgR = 0;
        int *row = img[i];
        for(j=0;j<cols;j++){
            avgR += *(row+j);
        }
        avgR = (float)avgR/(cols);
        cout << avgR << " ";
    }
    cout << endl;
    return;
}

//Інверсія яскравості
void invert(int** img, int rows,int cols){
    cout << "Яскравість інвертовано: " << endl;
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            img[i][j] = 9 - img[i][j];
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

//Обмін пікселями
void swapPixels(int *a, int *b) {
    if (a == nullptr || b == nullptr) return;
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//Віддзеркалення по горизонталі
void flipHorizontal(int **img, int rows, int cols) {
    if (img == nullptr || rows <= 0 || cols <= 0) return;

    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(row + j, row + (cols - 1 - j));
        }
    }
}

//Поворот на 90 градусів праворуч
int** rotateRight(int** img, int rows, int cols){
    int** bigger = new int*[cols];
    for(i=0;i<cols;i++){
        bigger[i] = new int[rows];
    }
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            bigger[j][rows-1-i] = img[i][j];
        }
    }
    for(i=0;i<rows;i++){
        delete[] img[i];
    }
    delete[] img;
    return bigger;
}

int main() {
    cout << "Висота зображення, введіть ціле число від 1 до 20: ";
    cin >> rows;
    if(cin.fail() || rows < 1 || rows > 20){
        cout << "Помилка: введіть ціле число від 1 до 20." << endl;
        return 0;
    }
    cout << "Ширина зображення, введіть ціле число від 1 до 20: ";
    cin >> cols;
    if(cin.fail() || cols < 1 || cols > 20){
        cout << "Помилка: введіть ціле число від 1 до 20." << endl;
        return 0;
    }
    //Виділення пам'яті під масив зображення
    int **img = new int*[rows];
    for(i=0;i<rows;i++){
        img[i] = new int[cols];
    }
    cout << "Введіть яскравість кожного пікселя цілим числом від 0(чорний) до 9(найсвітліший) по черзі через пробіл: ";
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            cin >> img[i][j];
            if(cin.fail() || cols < 1 || cols > 20){
                cout << "Помилка: введіть рядки цілих чисел від 0 до 9 через пробіл." << endl;
                return 0;
            }
        }
    }
    bool exit = 0;
    //Меню операцій
    do {
        int action;
        cout << "\nВиберіть операцію:" << endl;
        cout << "1 - Показати зображення" << endl;
        cout << "2 - Статистика яскравості" << endl;
        cout << "3 - Інвертувати яскравість" << endl;
        cout << "4 - Віддзеркалити по горизонталі" << endl;
        cout << "5 - Повернути на 90 градусів праворуч" << endl;
        cout << "0 - Вийти" << endl;
//Валідація вибору операції з goto
WrongAction:
        cin >> action;
        if(cin.fail() || cols < 0 || cols > 5){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка: введіть ціле число від 0 до 5." << endl;
            goto WrongAction;
        }
        //Операції, кожен пункт окремим case
        switch (action) {
            case 1: {
                showImg(img, rows, cols);
                break;
            }
            case 2: {
                int minR, minC, maxR, maxC, darkest, brightest;
                findExtremes(img, rows, cols, minR, minC, maxR, maxC);
                darkest = img[minR][minC]; brightest = img[maxR][maxC];
                float avga, avgr;
                avgImg(img, rows, cols, avga);
                cout << "Найтемніший піксель: " << darkest << "(рядок " << minR+1 << ", стовпець " << minC+1 << ")\n";
                cout << "Найсвітліший піксель: " << brightest << "(рядок " << maxR+1 << ", стовпець " << maxC+1 << ")\n";
                cout << "Середня яскравість: " << avga << '\n';
                avgRows(img, rows, cols, avgr);
                break;
            }
            case 3: {
                invert(img, rows, cols);
                break;
            }
            case 4: {
                cout << "Зображення віддзеркалено: " << '\n' << "Початкове:" << '\n';
                for(i=0;i<rows;i++) {
                    for(j=0;j<cols;j++) {
                        cout << img[i][j] << " ";
                    }
                    cout << '\n';
                }
                flipHorizontal(img, rows, cols);
                cout << '\n' << "Віддзеркалене:" << '\n';
                for(i=0;i<rows;i++) {
                    for(j=0;j<cols;j++) {
                        cout << img[i][j] << " ";
                    }
                    cout << '\n';
                }
                break;
            }
            case 5: {
                int q;
                img = rotateRight(img, rows, cols);
                q = rows; rows = cols; cols = q;
                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << '\n';
                for(i=0;i<rows;i++) {
                    for(j=0;j<cols;j++) {
                        cout << img[i][j] << " ";
                    }
                    cout << '\n';
                }
                break;
            }
            case 0: {
                exit = 1;
                break;
            }
            default: {
                break;
            }
        }
    }
    while (exit != 1);
    //Звільнення пам'яті для уникнення витоку
    for(i=0;i<rows;i++){
        delete[] img[i];
    }
    delete[] img;
    img = nullptr;
    return 0;
}