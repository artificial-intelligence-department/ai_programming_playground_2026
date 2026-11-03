/*
Задача: Редактор монохромного зображення
Виконав: Сукач Андрій (ШІ-14)
*/
#include <iostream>
#include <string>
using namespace std;

void showMenu ();
void printImage(int** img, int rows, int cols);
void brightStats(int** img, int rows, int cols);
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void invertBright(int** img, int rows, int cols);
void swapPixels(int *a, int *b);
void horizontMirror(int** img, int rows, int cols);
int** rotateRight(int** img, int rows, int cols);

int main() {
    int rows, cols;
    int** image = nullptr;
     cout << "Введіть Висоту зображення, пікселів: ";
    cin >> rows;
    if( cin.fail() ||rows <= 0 || rows > 20)
    {
    
    cout << "Помилка! Введіть ціле число(1-20)" << endl;
    return 1;
    }


     cout << "Введіть Ширину зображення, пікселів: ";
    cin >> cols;
    if(cin.fail() || cols <= 0 || cols > 20)
    {
    
    cout << "Помилка! Введіть ціле число(1-20)" << endl;
    return 1;
    }

    image = new int*[rows];
    for(int i = 0; i < rows; i++) {
        image[i] = new int[cols];
    }

    cout << "Введіть значення пікселів зображення (0-9):" << endl;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cin >> image[i][j];
            if(cin.fail() || image[i][j] < 0 || image[i][j] > 9)
            {
                cout << "Помилилка! Введіть ціле число(0-9)" << endl;
                // Звільняємо виділену пам'ять перед виходом
            for (int k = 0; k < rows; k++) {
            delete[] image[k];
            }
            delete[] image;
            image = nullptr;
                return 1;
            }
        }
    }
    int choice; 
    do {
        showMenu();
         cout << "Введіть ваш вибір" << endl;

    while(!(cin >> choice) || choice < 0 || choice > 5)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка! Введіть ціле число(0-5)" << endl;
        showMenu();
        cout << "Введіть ваш вибір" << endl;
    }

    switch(choice){
        case 1:
            printImage(image, rows, cols);
            break;
        case 2:
            brightStats(image, rows, cols);
            break;
        case 3:
            invertBright(image, rows, cols);
            printImage(image, rows, cols);
            break;
        case 4:
            horizontMirror(image, rows, cols);
            printImage(image, rows, cols);
            break;
        case 5: 
        image = rotateRight(image, rows, cols);
    // Після повороту розміри обов'язково міняються місцями!
    int temp = rows;
    rows = cols;
    cols = temp;
    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    printImage(image, rows, cols);
    break;
    }


    }

 while (!(choice ==0 ));
for (int k = 0; k < rows; k++) {
            delete[] image[k];
            }
            delete[] image;
            image = nullptr;
            cout << "Вихід з програми..." << endl;
return 0;

}


void showMenu () {
    cout << "Меню:" << endl;
    cout << "1 " << ". Показати зображення" << endl;
    cout << "2 " << ". Статистика яскравості" << endl;
    cout << "3 " << ". Інвертувати яскравість" << endl;
    cout << "4 " << ". Віддзеркалити по горизонталі" << endl;
    cout << "5 " << ". Повернути на 90 градусів праворуч" << endl;
    cout << "0 " << ". Вийти" << endl;
}

void printImage(int** img, int rows, int cols) {
    cout << "Зображення:" << endl;
    cout << "таблиця чисел: " << endl;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    string pallet = " .:-=+*#%@";
    cout << "Зображення з використанням символів палітри: " << endl;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << pallet[img[i][j]];
        }
        cout << endl;
    }
    cout << endl;
    cout << "розмір зображення: " << rows << "x" << cols << endl;
  cout << endl;
}

void brightStats(int** img, int rows, int cols) {
    // 1. Спочатку шукаємо координати екстремумів
    int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    // 2. Тепер, коли координати відомі, беремо їхні значення
    int minVal = *(img[minRow] + minCol);
    int maxVal = *(img[maxRow] + maxCol);

    // 3. Виводимо екстремуми (+1 для нумерації з 1)
    cout << "Найтемніший піксель: " << minVal 
         << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << maxVal 
         << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    // 4. В один цикл рахуємо суми та середні значення
    double totalSum = 0;
    cout << "Середня по рядках: ";
    
    for (int i = 0; i < rows; i++) {
        int *row = img[i]; // вказівник на початок i-го рядка
        double rowSum = 0;

        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j); // обхід суворо через *(row + j)
        }

        totalSum += rowSum;
        cout << rowSum / cols << " "; // середня яскравість рядка
    }
    cout << endl;

    // 5. Загальна середня яскравість
    double averageBrightness = totalSum / (rows * cols);
    cout << "Середня яскравість: " << averageBrightness << endl;
}

 void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
     minRow = 0;
     minCol = 0;
     maxRow = 0;
     maxCol = 0;

    int minVal = *img[0];
    int maxVal = *img[0];

     for (int i = 0; i < rows; i++) {
    int *row = img[i]; // вказівник на початок i-го рядка
    for (int j = 0; j < cols; j++) {
        int val = *(row + j);
        if (val < minVal) {
            minVal = val;
            minRow = i;
            minCol = j;
        }
        if (val > maxVal) {
            maxVal = val;
            maxRow = i;
            maxCol = j;
        }
    }
}

 }

 void invertBright(int** img, int rows, int cols) {
    cout << "Яскравість інвертовано:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j]; // Інвертуємо яскравість
        }
    }
    cout << endl;
}

void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void horizontMirror(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - j - 1]); //інвертуємо по горизонталі за формулою
        }
    }
    cout << "Зображення віддзеркалено по горизонталі." << endl;
}

int** rotateRight(int** img, int rows, int cols){
    //Виділення пам'яті під новий масив
   int** newImg = new int*[cols];
    for (int i = 0; i < cols; i++) {
    newImg[i] = new int[rows];
}
// треба перенести пікселі за формулою повороту
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        newImg[j][rows - 1 - i] = img[i][j];
    }
}

//звільнення пам'яті
for (int i = 0; i < rows; i++) {
    delete[] img[i];
}
delete[] img;

return newImg;
}