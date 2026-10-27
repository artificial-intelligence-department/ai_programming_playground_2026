/*
Редактор монохромного зображення
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
const string palitra = " .:-=+*#%@";

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    minRow = 0; 
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (img[i][j] < img[minRow][minCol]){
                minRow = i;
                minCol = j;
            }

            if (img[i][j] > img[maxRow][maxCol]){
                maxRow = i;
                maxCol = j;
            }
        }
    }

}

float averageBrightness (int **img, int r, int c){
    float averBright = 0;
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            averBright += img[i][j];
        }
    }

    return averBright/(r*c);
}
void averageBrightByRow (int **img, int r, int c){
    cout << "Середня по рядках: " << fixed << setprecision(1);
    for (int i = 0; i < r; i++) {
        int *row = img[i]; 
        float rowSum = 0;
        for (int j = 0; j < c; j++) {
            rowSum += *(row + j); 
        }
        cout << rowSum / c << "  ";
    }
    cout << endl;

}

void inventor (int **img, int r, int c){
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            img[i][j] = 9 - img[i][j]; 
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << setw(2) << img[i][j]; 
        }
        cout << endl;
    }
}

void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void flipHorizontal(int **img, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c / 2; j++) {
            swapPixels(&img[i][j], &img[i][c - 1 - j]);
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << setw(2) << img[i][j];
        }
        cout << endl;
    }
}


int **rotateRight(int** img, int r, int c) {
    int new_r = c;
    int new_c = r;

    int** new_img = new int*[new_r];
    for (int i = 0; i < new_r; i++) {
        new_img[i] = new int[new_c];
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            new_img[j][r - 1 - i] = img[i][j];
        }
    }

    for (int i = 0; i < r; i++) {
        delete[] img[i];
    }
    delete[] img;

    return new_img;
}



int main () {

    int rows = 0;
    cout << "Введіть висоту зобрвження (від 0 до 20): ";
    cin >> rows;
    if (cin.fail() || rows < 1 || rows > 20){
        cout << "Дані введені некоректно." << endl;
        return 1;
    }

    cout << "Введіть ширину зображення (від 0 до 20): ";
    int cols = 0;
    cin >> cols;
    if(cin.fail() || cols < 1 || cols > 20){
        cout << "Дані введені некоректно." << endl;
        return 1;
    }

    int **image = new int*[rows];
    for (int i = 0; i < rows; i++) {
        image[i] = new int[cols];
    }
    
    cout << "Яскравість пікселів (0...9): " << endl;
    for (int i = 0; i < rows; i ++){
        for (int j = 0; j < cols; j++){
            cin >> image[i][j];
            if (cin.fail() || image[i][j] < 0 || image[i][j] > 9){
                cout << "Дані введені некоректно." << endl;
                for (int k = 0; k < rows; k++) {
                    delete[] image[k];
                }
                delete[] image;
                return 1;
            }

        }
    }
    
    int doWhile = 0;
    do {

    cout << endl;
    int choice;
    cout << "Меню: " << endl;
    cout << " 1 - Показати зображення" << endl;
    cout << " 2 - Статистика яскравості" << endl;
    cout << " 3 - Інвертувати яскравість" << endl;
    cout << " 4 - Віддзеркалити по горизонталі" << endl;
    cout << " 5 - Повернути на 90 градусів праворуч" << endl;
    cout << " 0 - Вийти" << endl;
    cout << " > ";
    cin >> choice;
    if ( cin.fail() || choice < 0 || choice > 5){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Некоректний ввід." << endl;
        continue;
        

    }

    cout << endl;

    
        switch (choice){
        case 1:
            cout << "Зображення " << rows << " x " << cols << endl;
            for (int i = 0; i < rows; i ++){
                for (int j = 0; j < cols; j++){
                    cout << setw(2) << image[i][j] ;
                }
                cout << endl;
            }

            cout << "Малюнок:" << endl;        
            for (int i = 0; i < rows; i ++){
                for (int j = 0; j < cols; j++){
                    int brightness = image[i][j];
                    cout << setw(2) << palitra[brightness];
                }
                cout << endl;
            }

            cout << endl;
            break;
            
        
        case 2: {
            int minR, minC, maxR, maxC;
            findExtremes(image, rows, cols, minR, minC, maxR, maxC);
            cout << "Найтемніший піксель: " << image[minR][minC] << " (рядок " << minR + 1 << ", стовпець " << minC + 1 << ")" << endl;
            cout << "Найсвітліший піксель: " << image[maxR][maxC] << " (рядок " << maxR + 1 << ", стовпець " << maxC + 1 << ")" << endl;
            cout << "Середня яскравість: "<< fixed << setprecision(2) << averageBrightness(image, rows, cols) << endl;
            averageBrightByRow (image, rows, cols);
            cout << endl;
            break;
            }


        case 3:
            cout << "Яскравіть інвертовано." << endl;
            inventor (image, rows, cols);
            cout << endl;
            break;
            


        case 4:
            cout << "Зображення віддзеркалено.";
            cout << "Початкове:" << endl;
            for (int i = 0; i < rows; i ++){
                for (int j = 0; j < cols; j++){
                    cout << setw(2) << image[i][j] ;
                }
                cout << endl;
            }
            cout << endl;

            cout << "Результат:" << endl;
            flipHorizontal(image, rows, cols);
            cout << endl;
            break;
            

        case 5: {
            int old_r = rows;
            int old_c = cols;
            image = rotateRight(image, rows, cols); 
            
            rows = old_c;
            cols = old_r;

            cout << "Зображення перевернуто. Нові розміри: " << rows << " x " << cols << endl;
            
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    cout << setw(2) << image[i][j];
                }
                cout << endl;
            }
            cout << endl;
            break;
            }


        case 0:
            doWhile = 1;
            break;


        default:
            cout << "Некоректний ввід." << endl;
            break;
        
        }
        


    } while (doWhile == 0);

    for (int i = 0; i < rows; i++) {
        delete[] image[i];
        image[i] = nullptr;
    }
    delete[] image;
    image = nullptr;

    return 0;
}