/*
Назва: Редактор монохромного зображення
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
#include <clocale>
#include <iomanip>

using namespace std;

void showImage(int rows, int cols, int** image) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

void charImage(int rows, int cols, int** image) {
    cout << "\nЗображення " << rows << " × " << cols << endl;
    showImage(rows, cols, image);
    cout << "\nМалюнок: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            switch(image[i][j]){
                case 0: cout << ' '; break;
                case 1: cout << '.'; break;
                case 2: cout << ':'; break;
                case 3: cout << '-'; break;
                case 4: cout << '='; break;
                case 5: cout << '+'; break;
                case 6: cout << '*'; break;
                case 7: cout << '#'; break;
                case 8: cout << '%'; break;
                case 9: cout << '@'; break;
                default:  break;
            }
        }
        cout << endl;
    }
}
void findExtremes(int rows, int cols, int** image, int &minRow, int &minCol, int &maxRow, int &maxCol){  
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
     for (int i = 0; i < rows; i++) {
        int* row = image[i];
        for (int j = 0; j < cols; j++) {
            if(*(row + j) > *(*(image + maxRow) + maxCol)){
                maxRow = i;
                maxCol = j;
            }
            if(*(row + j) < *(*(image + minRow) + minCol)){
                minRow = i;
                minCol = j;
            }
        }
    }
    
}

void Stats(int rows, int cols, int** image) {
    
    int minRow = 0;
    int minCol = 0;
    int maxRow = 0;
    int maxCol = 0;
    findExtremes(rows, cols, image, minRow, minCol, maxRow, maxCol);
    cout << "\nНайтемніший піксель: " << image[minRow][minCol] << " (рядок " << minRow+1 << ", стовпець " << minCol+1 <<")"<< endl;
    cout << "Найсвітліший піксель: " << image[maxRow][maxCol] << " (рядок " << maxRow+1 << ", стовпець " << maxCol+1 <<")"<< endl;
    double sum = 0;
    double rowSum[rows];
    for (int i = 0; i < rows; i++) {
        int* row = image[i];
        int x = 0;
        for (int j = 0; j < cols; j++) {
            
            sum += *(row + j);
            x += *(row + j);
        }
        rowSum[i]=x;
    }
    double average = sum /( rows *cols);
    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << average << endl;
    cout << "Середня по рядках:";
    for (int i = 0; i < rows; i++){
        double averageRow = rowSum[i]/cols;
        cout << " " << averageRow;
    }
    cout << endl;
}

void invert(int rows, int cols, int** image) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            image[i][j] = 9 - image[i][j];
        }
    }
    cout << "Яскравість інвертовано."<< endl;
    showImage(rows, cols, image);
}

void swapPixels(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mirror(int rows, int cols, int** image) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols / 2; ++j) {
            swapPixels(&image[i][j], &image[i][cols - 1 - j]);
        }
    }
    cout << "\nРезультат: " << endl;
    showImage(rows, cols, image);
}

int** rotateRight(int rows, int cols, int** image) {
    int new_rows = cols;
    int new_cols = rows;

    int** newArr = new int*[new_rows];
    for (int i = 0; i < new_rows; ++i) {
        newArr[i] = new int[new_cols];
    }

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            newArr[i][j] = image[rows - 1 - j][i];
        }
    }

    for (int i = 0; i < rows; ++i) {
        delete[] image[i];
    }
    delete[] image;

    return newArr;
}

int main() {
    int rows = 0;
    cout << "Висота зображення: ";
    while (!(cin >> rows)||rows < 1 ||rows > 20) {
        cout << "Помилка вводу. Завершення програми." << endl;
                return 0;
    }
    int cols = 0;
    cout << "Ширина зображення: ";
    while (!(cin >> cols)||cols < 1 ||cols > 20) {
        cout << "Помилка вводу. Завершення програми." << endl;
                return 0;
    }
    cout << "Яскравість пікселів (0..9): " << endl ;
    int** image = new int*[rows];

    for (int i = 0; i < rows; i++) {
        image[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(cin >> image[i][j])||image[i][j]<0||image[i][j]>9) {
                cout << "Помилка вводу. Завершення програми."<< endl;
                for (int k = 0; k < rows; k++) {
                    delete[] image[k];
                }
                delete[] image;
                return 0;
            }
        }   
    }

    int choice = -1;
    cin.clear();
    cin.ignore(10000, '\n');
    do{
        
        MENU:
        cout << "\n-------- МЕНЮ --------\n";
        cout << "1 - Показати зображення\n";
        cout << "2 - Статистика яскравості\n";
        cout << "3 - Інвертувати яскравість\n";
        cout << "4 - Віддзеркалити по горизонталі\n";
        cout << "5 - Повернути на 90 градусів праворуч\n";
        cout << "0 - Вийти\n";
        cout << "Введіть номер пункту: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Некоректне введення! Спробуйте ще раз.\n";
            goto MENU;
        }

        if (choice == 0) {
            cout << "Вихід з програми.\n";
            break;
        }

        switch (choice) {
            case 1:
                charImage(rows, cols, image);
                break;
            case 2:
                Stats(rows, cols, image);
                break;
            case 3:
                invert(rows, cols, image);
                break;
            case 4:
                cout << "Зображення віддзеркалено. " << endl;
                cout << "Початкове: " << endl;
                showImage(rows, cols, image);
                mirror(rows, cols, image);
                break;
            case 5: {
                image = rotateRight(rows, cols, image);
                int temp = cols;
                cols = rows;
                rows = temp;
                cout << "Зображення повернуто. Нові розміри: " << rows << " × " << cols << endl;
                showImage(rows, cols, image);
                break;
            }
            default:
                cout << "Неправильний пункт меню. Оберіть число від 0 до 5.\n";
                goto MENU;
                break;
        }
    }while (choice !=0);

    for (int i = 0; i < rows; i++) {
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;
    

    return 0;
}