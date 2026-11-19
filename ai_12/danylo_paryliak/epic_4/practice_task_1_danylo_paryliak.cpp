#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

void showImage (int** image, int rows, int cols){
    for(int i = 0; i < rows;i++){
        for(int j = 0; j < cols;j++){
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    
    const char palitra[] = " .:-=+*#%@"; // палітра символів для відображення яскравості

    cout <<"Символьне зображення: " << endl;
        for(int i = 0; i < rows;i++){
            for(int j = 0; j < cols;j++){
                cout << palitra[image[i][j]];
            }
            cout << endl;
        }
}

void findExtremes(int** image, int rows, int cols,int &minRow, int &minCol,int &maxRow, int &maxCol){
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    for(int i = 0; i < rows;i++){
        int *row = image[i];
        for(int j = 0; j < cols;j++){
            if(*(row + j)< image[minRow][minCol]){
                minRow = i;
                minCol = j;
            }
            if(*(row + j) > image[maxRow][maxCol]){
                maxRow = i;
                maxCol = j; 
            } 
        }
    }
}

void showStatistics(int** image, int rows, int cols){
    int minRow, minCol, maxRow, maxCol;
    findExtremes(image,rows,cols,minRow,minCol,maxRow,maxCol);

    cout <<"Найтемніший піксель: " << image[minRow][minCol]<< endl;
    cout<< "Рядок: " << minRow + 1 << ", стовпець: " << minCol + 1 << endl;
    cout <<"Найяскравіший піксель: " << image[maxRow][maxCol] << endl;
    cout << "Рядок: " << maxRow + 1 << ", стовпець: " << maxCol + 1 << endl;

    double sum = 0; 
    for(int i = 0; i < rows; i++){
        int* row = image[i];
        for(int j = 0; j < cols;j++){
            sum += *(row + j);
        }
    }
    double average = sum / (rows * cols);
    cout <<"Середня яскравість: " << fixed <<setprecision(2) << average << endl;

    cout <<"Середня яскравість рядків: ";
    for(int i = 0;i < rows;i++){
        double sumRow = 0;
        int* row = image[i];
        for(int j = 0;j < cols;j++){
            sumRow += *(row + j);
        }
    double averageRow = sumRow / cols;
    cout << averageRow << " " ;
    }
    cout << endl;
}

void invertImage(int** image, int rows, int cols){
    for(int i = 0; i < rows;i++){
        for(int j = 0; j < cols;j++){
            image[i][j] = 9 - image[i][j];
        }
    }
}

void swapPixels(int* a,int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mirrorImage(int** image,int rows,int cols){
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < cols/2;j++){
            swapPixels(&image[i][j], &image[i][cols - 1 - j]);
        }
    }
}

int** rotateRight(int** image,int rows,int cols){
    int** newImage = new int*[cols];
        for(int i = 0; i < cols;i++){
            newImage[i] = new int[rows];
        }
        for(int i = 0; i < rows;i++){
            for(int j = 0; j < cols;j++){
                newImage[j][rows - 1 -i] = image[i][j];
            }
        }
        for(int i = 0; i < rows;i++){
            delete[] image[i];
        }
        delete[]image;
        image = nullptr;
    return newImage;
}

int main(){

int rows; // рядки (висота)
int cols; // стовпці (ширина)

cout << "Введіть висоту зображення: ";
cin >> rows;
    if(cin.fail() || rows < 1 || rows > 20){
        cout << "Помилка! Висота повинна бути від 1 до 20 та бути числом!" << endl;
        return 1;
    }

cout << "Введіть ширину зображення: ";
cin >> cols; 
    if(cin.fail() || cols < 1 || cols > 20){
        cout << "Помилка! Ширина повинна бути від 1 до 20 та бути числом!" << endl;
        return 1;
    }

int** image = new int*[rows]; // виділення пам'яті для рядків
for(int i = 0; i < rows;i++){
    image[i] =new int[cols]; // виділення пам'яті для стовпців
}

bool valid = true;
cout << "Введіть яскравість пікселів (0..9): " << endl;
for(int i = 0; i < rows && valid;i++){
    for(int j = 0; j < cols;j++){
        cin >> image[i][j];
        if(cin.fail()|| image[i][j] < 0 || image[i][j] > 9){
            cout <<"Помилка! Яскравість повинна бути від 0 до 9 та бути числом!" << endl;
            valid = false;
            break;
        }
    }
}

int choice;

if(valid){
    do{
        cout << "========== МЕНЮ ==========" << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" <<endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вийти" << endl << endl;
        cout << "Ваш вибір: " ;

        choice = -1;
        cin >> choice;

        if(cin.fail()){
            if(cin.eof()){
                break;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Помилка! Введіть ціле число!" << endl;
            choice = -1;
            continue;
        }

        switch(choice){
            case 1:
                showImage(image,rows,cols);
            break;

            case 2:
                showStatistics(image,rows,cols);
            break;

            case 3:
                invertImage(image,rows,cols);
                    cout <<"Зображення після інверсії:"<< endl;
                    showImage(image,rows,cols);
            break;

            case 4:
                mirrorImage(image,rows,cols);
                    cout <<"Зображення після віддзеркалення:" << endl;
                    showImage(image,rows,cols);
            break;

            case 5: {
                image = rotateRight(image,rows,cols);
                int temp = rows;
                rows = cols;
                cols = temp;
                cout << "Зображення після повороту:"<< endl;
                showImage(image,rows,cols);
            break;}

            case 0:
            cout << "Допобачення!";
            break;

            default:
                cout << "Помилка! Такого пункту не існує";
            break;
        }

    }while (choice != 0);
}



for(int i = 0; i < rows;i++){
    delete[] image[i]; // видалення пам'яті для стовпців
}
    delete[]image; 
    image = nullptr;

    if(!valid){
        return 1;
    }

    return 0;
}