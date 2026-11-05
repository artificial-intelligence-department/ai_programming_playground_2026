#include <iostream>
#include <string>
#include <limits>

using namespace std;

void findExtremes(int **img, int row, int col, int &minRow, int &minCol, int &maxRow, int &maxCol){
    int min = *(img[0]+0);
    int max = *(img[0]+0);

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            int* row = img[i];
            if(*(row + j) < min){
                min = *(row + j);
                minRow = i;
                minCol = j;
            }
            if(*(row + j) > max){
                max = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void swapPixels(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int** rotateRight(int** img, int row, int col){
    int** img1 = new int*[col];
    for(int i = 0; i < col; i++){
        img1[i] = new int[row];
    }

    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            img1[i][j] = img[row-1-j][i];
        }
    }

    for(int i = 0; i < row; i++){
        delete[] img[i];
    }
    delete[] img;

    return img1;
}

void showImage(int** img,int row,int col){
    const string pixels = " .:-=+*#%@";

    cout << "Зображення " << row << " x " << col << ":" << endl;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Малюнок:" << endl;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout << pixels[img[i][j]];
        }
        cout << endl;
    }
}

void brightStatistics(int** img, int row, int col){
    int minRow=0,minCol=0,maxRow=0,maxCol=0;

    findExtremes(img, row, col, minRow, minCol, maxRow, maxCol);
    cout << "Найтемніший піксель: " << img[minRow][minCol] << "(рядок " << minRow+1 << ", стовпець " << minCol+1 << ")" << endl;
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol] << "(рядок " << maxRow+1 << ", стовпець " << maxCol+1 << ")" << endl;

    int sum = 0;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            int* row = img[i];
            sum += *(row + j);
        }
    }
    cout << "Середня яскравість: " << double(sum)/(row*col) << endl;

    cout << "Середня по рядках: ";
    for(int i = 0; i < row; i++){
        sum = 0;
        for(int j = 0; j < col; j++){
            int* row = img[i];
            sum += *(row + j);
        }
        cout << double(sum)/col << " ";
    }
    cout << endl;
}

void invert(int** img, int row, int col){
    cout << "Яскравість інвертовано." << endl;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            img[i][j] = 9 - img[i][j];
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

void reflect(int** img, int row, int col){
    cout << "Зображення віддзеркалено." << endl << "Початкове:" << endl;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < (col+1)/2; j++){
            swapPixels(&img[i][j], &img[i][col-1-j]);
        }
    }
    cout << "Результат:" << endl;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

int** rotate(int** img, int* row, int* col){
    img = rotateRight(img, *row, *col);
    cout << "Зображення повернуто. Нові розміри: " << *col << " x " << *row << endl;
    for(int i = 0; i < *col; i++){
        for(int j = 0; j < *row; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    int temp = *row;
    *row = *col;
    *col = temp;

    return img;
}

int main(){
    double tmp;
    int rows, cols;
    bool show = true;

    cout << "Висота зображення: ";
    cin >> tmp;
    if(cin.fail() || tmp < 1 || tmp != static_cast<int>(tmp)){cout << "Помилка! Введіть натуральне число." << endl; return 1;}
    rows = static_cast<int>(tmp);
    cout << "Ширина зображення: ";
    cin >> tmp;
    if(cin.fail() || tmp < 1 || tmp != static_cast<int>(tmp)){cout << "Помилка! Введіть натуральне число." << endl; return 1;}
    cols = static_cast<int>(tmp);

    int** image = new int*[rows];
    for(int i = 0; i < rows; i++){
        image[i] = new int[cols];
    }
    cout << "Яскравість пікселів (0..9):" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cin >> tmp;
            if(cin.fail() || tmp > 9 || tmp < 0 || tmp != static_cast<int>(tmp)){cout << "Помилка!"; goto freeMem;}
            image[i][j] = static_cast<int>(tmp);
        }
    }

    do{
        int action = 0;
        cout << "Оберіть дію: ";
        cin >> tmp;
        if(cin.fail() || tmp < 0 || tmp > 5 || tmp != static_cast<int>(tmp)){
            cout << "Помилка! Введіть коректне число." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        action = tmp;

        switch(action){
            case 1: showImage(image, rows, cols); break;
            case 2: brightStatistics(image, rows, cols); break;
            case 3: invert(image, rows, cols); break;
            case 4: reflect(image, rows, cols); break;
            case 5: image = rotate(image, &rows, &cols); break;
            case 0: show = false; break;
        }
    } while(show);


    freeMem:
    for(int i = 0; i < rows; i++){
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;
    return 0;
}