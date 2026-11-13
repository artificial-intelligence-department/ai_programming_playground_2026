/*Епік 4. Задача: Редактор монохромного зображення
Автор: Матішак Михайло
Група: ШІ-11*/
#include <iostream>
#include <iomanip>

using namespace std;

void showImage(int **image, int rows, int cols){
    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    for(int i = 0; i < rows; i++){
        if(i > 0){
            cout << endl;
        }
        for(int j = 0; j < cols; j++){
            cout << image[i][j] << " ";
        }
    }
    cout << endl;
    cout << "Малюнок:" << endl;
    for(int i = 0; i < rows; i++){
        if(i > 0){
            cout << endl;
        }
        for(int j = 0; j < cols; j++){
            if (image[i][j] == 0){
                cout << " ";
            }
            if (image[i][j] == 1){
                cout << ".";
            }
            if (image[i][j] == 2){
                cout << ":";
            }
            if (image[i][j] == 3){
                cout << "-";
            }
            if (image[i][j] == 4){
                cout << "=";
            }
            if (image[i][j] == 5){
                cout << "+";
            }
            if (image[i][j] == 6){
                cout << "*";
            }
            if (image[i][j] == 7){
                cout << "#";
            }
            if (image[i][j] == 8){
                cout << "%";
            }
            if (image[i][j] == 9){
                cout << "@";
            }
        }
    }
    cout << endl;
}

void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    int minovr = **image;
    int maxovr = **image;
    minCol = 0;
    minRow = 0;
    maxRow = 0;
    maxCol = 0;
    for(int i = 0; i < rows; i++){
        int *row = image[i];
        for(int j = 0; j < cols; j++){
            if (maxovr < *(row + j)){
                maxovr = *(row + j);
                maxCol = j;
                maxRow = i;
            }
            if(minovr > *(row + j)){
                minovr = *(row + j);
                minCol = j;
                minRow = i;
            }
        }
    }
    
    
}

void findAverage(int **image, int rows, int cols){
    float average;
    average = 0;
    float rowsaverage[rows];
    for(int i = 0; i < rows; i++){
        int *row = image[i];
        for(int j = 0; j < cols; j++){
            average = average + *(row + j);
        }
    }
    for(int i = 0; i < rows; i++){
        int *row = image[i];
        rowsaverage[i] = 0;
        for(int j = 0; j < cols; j++){
            rowsaverage[i] += *(row + j);
        }
    }
    average = average / (rows * cols);
    setprecision(2);
    cout << "Середня яскравість: " << fixed << setprecision(2) << average << endl;
    cout << "Середня по рядках: ";
    for(int i = 0; i < rows; i++){
        cout << fixed << setprecision(2) << rowsaverage[i] / cols << " ";
    }
    cout << endl;
}

void invertImage(int **image, int rows, int cols){
    for(int i = 0; i < rows; i++){
        int *row = image[i];
        for(int j = 0; j < cols; j++){
            *(row + j) = 9 - *(row + j);
        }
    }
    cout << "Яскравість інвертовано." << endl;
    for(int i = 0; i < rows; i++){
        int * row = image[i];
        if(i > 0){
            cout << endl;
        }
        for(int j = 0; j < cols; j++){
            cout << *(row + j) << " ";
        }
        cout << endl;
    }
}

void swapPixels(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void flipImage(int **image, int rows, int cols){
    for(int i = 0; i < rows; i++){
        int *row = image[i];
        for(int j = 0; j < cols / 2; j++){
            swapPixels(&row[j], &row[cols - 1 - j]);
        }
    }
}

int** rotateRight(int **image, int rows, int cols){
    int **rimage = new int*[cols];
    for(int i = 0; i < cols; i++){
        rimage[i] = new int[rows];
    }
    for(int i = 0; i < cols; i++){
        int *row = rimage[i];
        for(int j = 0; j < rows; j++){
            *(row + j) = image[rows - 1 - j][i];
        }
    }
    for(int i = 0; i < rows; i++){
        delete[] image[i];
    }
    delete[] image;

    return rimage;
}

int main(){
    int rows, cols, minRow, minCol, maxRow, maxCol;

    while(true){
        cout << "Висота зображення: ";
        cin >> rows;
        if(cin.fail() || rows > 20 || rows < 1){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Висота повинна бути цілим числом від 1 до 20." << endl;
        }
        else{
            break;
        }
    }
    while(true){
        cout << "Ширина зображення: ";
        cin >> cols;
        if(cin.fail() || cols > 20 || cols < 1){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ширина повинна бути цілим числом від 1 до 20." << endl;
        }
        else{
            break;
        }
    }
    int **image = new int*[rows];
    for(int i = 0; i < rows; i++){
        image[i] = new int[cols]{};
    }
    cout << "Яскравість пікселів (0..9): " << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            while(true){
                cin >> image[i][j];
                if(cin.fail() || image[i][j] > 9 || image [i][j] < 0){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Яскравість пікселів повинна бути числом від 0 до 20." << endl;
                } 
            else{
                break;
            }
            }
        }
    }
    int choice;
    do{
        cout << "===Меню===" << endl;
        cout << "1 - Показати зображення" << endl;
        cout << "2 - Статистика яскравості" << endl;
        cout << "3 - Інвертувати яскравість" << endl;
        cout << "4 - Віддзеркалити по горизонталі" << endl;
        cout << "5 - Повернути на 90 градусів праворуч" << endl; 
        cout << "0 - Вийти" << endl;
        
        while(true){
            cin >> choice;
            if(cin.fail()){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Введіть число" << endl;
                }
            else{
                break;
            }
        }
        if(choice < 0 || choice > 5){
            cout << "Такого пункту немає в меню" << endl;
        }
        if(choice == 1){
            showImage(image, rows, cols);
        }
        if(choice == 2){
            findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
            cout << "Найтемніший піксель: " << *(image[minRow] + minCol) << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
            cout << "Насвітліший піксель: " << *(image[maxRow] + maxCol) << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
            findAverage(image, rows, cols);
        }
        if(choice == 3){
            invertImage(image, rows, cols);
        }
        if(choice == 4){
            flipImage(image, rows, cols);
            for(int i = 0; i < rows; i++){
                if(i > 0){
                    cout << endl;
                }
                int *row = image[i];
                for(int j = 0; j < cols; j++){
                    cout << *(row + j) << " ";
                }
            }
            cout << endl;
        }
        if(choice == 5){
            image = rotateRight(image, rows, cols);
            int tmp = rows;
            rows = cols;
            cols = tmp;
            cout << "Зображення повернуто. Нові розміри " << rows << " х " << cols << endl;
            for(int i = 0; i < rows; i++){
                int *row = image[i];
                if(i > 0){
                    cout << endl;
                }
                for(int j = 0; j < cols; j++){
                    cout << *(row + j) << " ";
                }
            }
            cout << endl;
        }
        }
        while(choice != 0);
        for (int i = 0; i < rows; i++){
            delete[] image[i];
            image[i] = nullptr;}
        delete[] image;
        image = nullptr;
    return 0;
}