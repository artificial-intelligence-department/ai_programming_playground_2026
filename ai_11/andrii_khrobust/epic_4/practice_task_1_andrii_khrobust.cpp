#include <iostream>
using namespace std;

//кнопка 1(виведення зображення, яскравості)
void createImage(int **img, int rows, int cols){
   cout << "Зображення " <<rows<<" х "<<cols<<":" <<endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    cout<<"Малюнок"<<endl;
    char symbols[] = " .:-=+*#%@";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << symbols[img[i][j]];
        }
        cout << endl;
    }        
}

//кнопка 2, статистика
void findExtremes(int **img, int rows, int cols,int &minRow, int &minCol,
int &maxRow, int &maxCol){
    int minValue = img[0][0];
    int maxValue = img[0][0];
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(img[i][j] < minValue){
                minValue = img[i][j];
                minRow = i;
                minCol = j;
            }
            if(img[i][j] > maxValue){
                maxValue = img[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }
    double sum = 0;
    double *averages = new double[rows];
    for(int i = 0; i < rows; i++){
        int *row = img[i];
        double rowSum = 0;
        for(int j = 0; j < cols; j++){
            rowSum += *(row + j);
        }
        averages[i] = rowSum / cols;
        sum += rowSum;
    }
    cout << "Найтемніший піксель: " << minValue<< " (рядок " << minRow + 1
    << ", стовпець " << minCol + 1 <<")"<< endl;
    cout << "Найсвітліший піксель: " << maxValue<< ", (рядок " << maxRow + 1
    << ", стовпець " << maxCol + 1 <<")"<< endl;
    cout << "Середня яскравість: "<< sum / (rows * cols) << endl;
    cout << "Середня по рядках: ";
    for(int i = 0; i < rows; i++){
        cout << averages[i]<<" ";
    }
    delete[] averages;
    averages = nullptr;
}


//кнопка 3, інвертація яскравості
void invertImage(int **img, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            img[i][j] = 9 - img[i][j];
        }
    }
    cout<<"Яскравять інвертовано."<<endl; 
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

//функція обміну пікселів
void swapPixels(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//кнопка 4, відзеркалення зображення
void mirrorImage(int **img, int rows, int cols){
    cout << "Початкове:" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Результат:" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols / 2; j++){
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

//Кнопка 5,перевернення зображення на 90 градусів праворуч
void rotateRight(int **&img, int &rows, int &cols){
    int newRows = cols;
    int newCols = rows;
    int **newImg = new int*[newRows];
    for(int i = 0; i < newRows; i++){
        newImg[i] = new int[newCols];
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }
    for(int i = 0; i < rows; i++){
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
    img = newImg;
    newImg = nullptr;
    rows = newRows;
    cols = newCols;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

 
int main() {
    int rows, cols;
     int minRow, minCol, maxRow, maxCol;
cout << "Висота зображення(від 1 до 20) ";
if(!(cin >> rows) ||rows < 1 || rows > 20){
    cout << "Помилка! Введіть розміри від 1 до 20: ";
    return 1;
}
cout << "Ширина зображення(від 1 до 20) ";
if(!(cin >> cols) ||cols < 1 || cols > 20){
    cout << "Помилка! Введіть розміри від 1 до 20: ";
    return 1;
}
int **img = new int*[rows];
for(int i = 0; i < rows; i++){
    img[i] = new int[cols];
}
cout << "Яскравість пікселів (0..9):" << endl;
for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
        if(!(cin >> img[i][j]) || img[i][j] < 0 || img[i][j] > 9){
            cout << "Помилка! Ваші значення виходять за допустимі межі" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            for(int k = 0; k < rows; k++){
                delete[] img[k];
                img[k] = nullptr;
            }
            delete[] img;
            img = nullptr;
            return 1;
        }
    }
}
    int choice;
    do {
        menu:
        cout << endl;
        cout << "===== РЕДАКТОР ЗОБРАЖЕНЬ =====" << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" << endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вийти" << endl;
        cout << "Ваш вибір: ";
        if (!(cin >> choice)) {
        cout << "Помилка! Введіть ціле число." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto menu;
        }
        switch (choice) {
            case 1:
            createImage(img, rows, cols);
                break;
            case 2:
            findExtremes(img, rows, cols,minRow, minCol, maxRow, maxCol);
                break;
            case 3:
            invertImage(img, rows, cols);
                break;
            case 4:
            mirrorImage(img,rows,cols);
                break;
            case 5:
            rotateRight(img, rows, cols);    
                break;
            case 0:
            cout << "Завершення роботи програми." << endl;
                break;

            default:
             cout << "Помилка! Такого пункту меню не існує." << endl;
                goto menu;
        }

    } while (choice != 0);
    for(int i = 0; i < rows; i++){
    delete[] img[i];
    img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;

    return 0;
}