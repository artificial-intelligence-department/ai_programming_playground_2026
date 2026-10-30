/*
    Задача: Редактор монохромного зображення
    Михайловська Анна
    ШІ-14
*/

#include <iostream>

using namespace std;

void showImage (int ** image, int rows, int cols);
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void brightnessStatistics(int ** image, int rows, int cols);
void invertBrightness(int ** image, int rows, int cols);
void swapPixels(int *a, int *b);
void flipHorizontally (int ** image, int rows, int cols);
int** rotateRight(int** image, int rows, int cols);

int main(){
    int rows, cols;

    int const N = 20; // Максимальна шорина та висота зображення

    cout << "Введіть висоту зображення: ";

    //Перевірка вводу користувача та завершення програми у разі некоректного вводу
    if (!(cin >> rows) || rows < 1 || rows > N ){
        cout << "Помилка: кількість рядків має бути числом від 1 до 20" << endl;
        return 1;
    }

    cout << "Введіть ширину зображення: ";

     //Перевірка вводу користувача та завершення програми у разі некоректного вводу
    if (!(cin >> cols) || cols < 1 || cols > N ){
        cout << "Помилка: кількість cтовпців має бути числом від 1 до 20" << endl;
        return 1;
    }

    //Cтворення динамічного двовимірного масиву
    int ** image = new int*[rows];

    for (int i = 0; i < rows; i++){
        image[i] = new int[cols];
    }

    cout << "Введіть скравість пікселів (0..9): " << endl;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){

             //Перевірка вводу користувача та завершення програми у разі некоректного вводу
            if (!(cin >> image[i][j]) || image[i][j] < 0 || image[i][j] > 9){
                cout << "Помилка: введіть число від 0 до 9 " << endl;

                //Звільнення памʼяті
                for (int i = 0; i < rows; i++) {
                    delete[] image[i];
                    image[i] = nullptr;
                }

                delete[] image;
                image = nullptr;
                return 1;
            }
        }
    }

    int choice;

    //Пункти меню
    do {
        cout << "\n1 - Показати зображення" << endl;
        cout << "2 - Статистика яскравості" << endl;
        cout << "3 - Інвертувати яскравість" << endl;
        cout << "4 - Віддзеркалити по горизонталі" << endl;
        cout << "5 - Повернути на 90 градусів праворуч " << endl;
        cout << "0 - Вийти\n" << endl;

        cout << "Ваш вибір: ";

        //Перевіпка вводу користувача
        while (!(cin >> choice) || choice < 0 || choice > 5 ){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка: введіть число від 0 до 5 " << endl;
            cout << "Ваш вибір: "; 
        }

        switch (choice) {

        case 1:
            showImage (image, rows, cols);
            break;
        
        case 2:
            brightnessStatistics (image, rows, cols);
            break;

        case 3:
            invertBrightness (image, rows, cols);
            break;

        case 4:
            flipHorizontally(image, rows, cols);
            break;

        case 5: {
            image = rotateRight(image, rows, cols);
            int temp = rows;
            rows = cols;
            cols = temp;

            cout << "\nЗображення повернуто. Нові розміри: "<< rows <<  " x " << cols << endl;

            //Виведення перевернутого зображення
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                    cout << image[i][j] << " ";
                }
                cout << '\n';
            }
            break;
        }
        case 0:
            break;
        }

    } while (choice != 0);

    //Звільнення памʼяті ;
    for (int i = 0; i < rows; ++i) {
        delete[] image[i];
        image[i] = nullptr;
    }

    delete[] image;
    image = nullptr;

    return 0;

}
// Функція для показу зображення
void showImage (int ** image, int rows, int cols){
    cout << "\nЗображення: " << rows <<  " x " << cols << endl;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << image[i][j] << " ";
        }

        cout << '\n';
    }

    cout << "Малюнок: " << endl;

    //Виведення малюнку з символів
    char symbols[] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};
     for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << symbols[image[i][j]];
        }
        cout << '\n';
    }
}

// Функція знакодження найяскравішого та найткмнішого пікселя
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    int min = *image[0];
    int max = *image[0];

    for (int i = 0; i < rows; i++){
        int *row = image[i];
        for (int j = 0; j < cols; j++){

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

//Функція показу статистики яскравості
void brightnessStatistics(int ** image, int rows, int cols){
    int minRow, minCol, maxRow, maxCol;

    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "\nНайтемніший піксель: " << *(image[minRow] + minCol) << " (рядок " << minRow + 1 <<  ", стовпець " << minCol +1 << ")" << endl;
    cout << "Найсвітліший піксель: " << *(image[maxRow] + maxCol) << " (рядок " << maxRow + 1 <<  ", стовпець " << maxCol  +1 << ")" << endl;

    double sum = 0;

    cout << "Середня яскравість по рядках: ";

    for (int i = 0; i < rows; i++){
        int *row = image[i];
        double rowsSum = 0;
        for (int j = 0; j < cols; j++){
            rowsSum += *(row + j);
        }

        cout << rowsSum / cols << " ";

        sum += rowsSum;
    }

    cout << "\nСередня яскравість: " << sum / (rows * cols) << endl;
}

//Функція для інвертації яскравості
void invertBrightness(int ** image, int rows, int cols){
    cout << "\nЯскравість інвертовано." << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            image[i][j] = 9 - image[i][j];
            cout << image[i][j] << " ";
        }
        cout << '\n';
    }
}

//Функція для обміну двох пікселів
void swapPixels(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Функція віддзеркалення
void flipHorizontally (int ** image, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols / 2; j++)
            swapPixels(&image[i][j], &image[i][cols - (j+1)]);
    }

    cout << "\nЗображення віддзеркалено: " << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << image[i][j] << " ";
        }

        cout << '\n';
    }
}

//Функція яка повертає перевернуте зображення
int** rotateRight(int** image, int rows, int cols){

    int ** rotate = new int* [cols];

    for (int i = 0; i < cols; i++)
        rotate[i] = new int[rows];

    for (int i = 0; i < cols; i++){
        for (int j = 0; j < rows; j++){
            rotate [i][j] = image [rows- 1 - j][i];  
        }
    }

    //Звільнення памʼяті
    for (int i = 0; i < rows; i++) {
        delete[] image[i];
        image[i] = nullptr;
    }

    delete[] image;
    image = nullptr;
        
    return rotate; 
}

