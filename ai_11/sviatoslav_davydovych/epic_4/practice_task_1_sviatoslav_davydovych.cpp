/* 
Practice task
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int getValidInteger(bool isPrompt, string prompt = "") {
    int input;

    while (true) {
        if (isPrompt) cout << prompt;
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        } 
        else {
            cin.ignore(1000, '\n');
            return input;
        }
    }
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    int minX = 0, minY = 0, maxX = 0, maxY = 0; // x - row, y - col
    for (int i = 0; i<rows; i++){
        int *row = img[i];
        for (int j = 0; j<cols; j++){
            // запис *(*(img+minX)+minY) розіменовує елемент (X, Y) 
            if (*(*(img+minX)+minY)>*(row+j)){
                minX = i;
                minY = j;
            }
            if (*(*(img+maxX)+maxY)<*(row+j)){
                maxX = i;
                maxY = j;
            }
        }
    }
    minRow = minX;
    minCol = minY;

    maxRow = maxX;
    maxCol = maxY;
}

// можна використовувати для будь-яких змінних(не тільки пікселі)
void swapPixels(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printImage(int **matrix, int rows, int cols, string *symbols){
    cout << "Таблиця яскравості:\n";
    for (int i = 0; i<rows; i++){
        for (int j = 0; j<cols; j++){
            cout << setw(2) << matrix[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "Зображення:\n";
    for (int i = 0; i<rows; i++){
        for (int j = 0; j<cols; j++){
            // викоорстовуємо symbols як словник
            cout << symbols[matrix[i][j]]; 
        }
        cout << "\n";
    }

    cout << "Розмір: " << rows << "x" << cols << "\n";
}

void statystic(int **matrix, int rows, int cols){
    int minRow, minCol, maxRow, maxCol;
    findExtremes(matrix, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "Найбільш яскравий піксель: (" << maxRow << "," << maxCol <<  ")\n"; 
    cout << "Найменш яскравий піксель: (" << minRow << "," << minCol << ")\n";
    
    cout << "Середня яскравість\n";
    float average = 0;
    for (int i = 0; i<rows; i++){
        int *row = matrix[i];
        float rowAverage = 0;
        for (int j = 0; j<cols; j++){
            rowAverage+=*(row+j);
        }
        cout << "Рядок " << i << ": " << (rowAverage/cols) << "\n";
        average+=rowAverage;
    }
    cout << "Загалом: " << average/rows << "\n";
}

void invertImage(int **image, int rows, int cols){
    for (int i = 0; i<rows; i++){
        for (int j = 0; j<cols; j++){
            image[i][j] = 9-image[i][j];
        }
    }
}

void mirrorOY(int **image, int rows, int cols){
    for (int i = 0; i<rows; i++){
        // у внутрішньому циклі cols/2 ітерацій для запобігання повторній зміні пікселів
        for (int j = 0; j<cols/2; j++){
            swapPixels(&image[i][j], &image[i][cols-j-1]);
        }
    }
}

int** rotateRight(int** img, int rows, int cols){
    int **rotated = new int*[cols];
    for (int i = 0; i<cols; i++){
        rotated[i] = new int[rows];
    }

    for (int i = 0; i<rows; i++){
        for (int j = 0; j<cols; j++){
            /* рядки відзеркалюються, перш ніж перейти у стовпці */
            rotated[j][i] = img[rows-i-1][j]; 
        }
    }
    
    for (int i = 0; i<rows; i++){
        delete[] img[i];
    }
    delete[] img;

    return rotated;
}

int main(){
    const int MinLen = 1;
    const int MaxLen = 20;
    const int MinBright = 0;
    const int MaxBright = 9;

    // символи " .:-=+*#%@""
    string symbols[10] = {" ", ".", ":", "-", "=", "+", "*", "#", "%", "@"};

    int rows;
    do rows = getValidInteger(true, "Висота зображення: ");
    while(rows<MinLen || rows>MaxLen);

    int cols;
    do cols = getValidInteger(true, "Ширина зображення: ");
    while(cols<MinLen || cols>MaxLen);

    int **image = new int*[rows];

    for (int i = 0; i<rows; i++){
        image[i] = new int[cols];
    }

    cout << "Пікселі зображення:\n";
    for (int i = 0; i<rows; i++){
        for (int j = 0; j<cols; j++){
            cin >> image[i][j];
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');

    // меню у вигляді R-префіксних рядків
    string menu = R"(1 - Показати зображення
2 - Статистика яскравості
3 - Інвертувати яскравість
4 - Віддзеркалити по горизонталі
5 - Повернути на 90 градусів праворуч
0 - Вийти)";
        
    cout << fixed << setprecision(2);
    
    bool loop = true;
    do {
        cout << menu << "\n";
        int action = getValidInteger(true, "Оберіть дію: "); 

        // кожен пункт меню реалізований функцією
        switch (action) {
            case 0:
                loop = false;
                break;
            case 1:
                printImage(image, rows, cols, symbols);
                break;
            case 2:
                statystic(image, rows, cols);
                break;
            case 3:
                invertImage(image, rows, cols);
                break;
            case 4:
                mirrorOY(image, rows, cols);
                break;
            case 5: 
                image = rotateRight(image, rows, cols);
                swapPixels(&rows, &cols); // коректно обміняє значення змінних
                break; 
            default: 
                cout << "Хибна операція!\n";
                break;
        }
    } while (loop);

    for (int i = 0; i<rows; i++){
        delete[] image[i];
    }
    delete[] image;
}