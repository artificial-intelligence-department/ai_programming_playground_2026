/*
Редактор монохромного зображення
Автор: Мадяр Андрій
Група: ШІ-13
*/
#include <iostream>
#include <iomanip>
using namespace std;
//ф-ція для переводу яскравості(числа в таблиці) в символ палітри
char numInSym(int a);
//функція для виводу таблиці
void coutImg(int **img, int rows, int cols);
//функція для пункту меню "1"
void showImg(int **img, int rows, int cols);
//функція для пункту меню "2"
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
//ф-ція для пункту меню "3"
void invert(int **img,int rows,int cols);
//функція для обміну двох значень
void swapPixels(int *a, int *b);
//ф-ція для пункту меню "4"
void mirror(int **img,int rows,int cols);
//ф-ція для пункту меню "5"
int** rotateRight(int** img, int* rows, int* cols);
int main(){
    int rows = 0, cols = 0,minRow = 0, minCol = 0, maxRow = 0, maxCol = 0, choice;
    cout << "Висота зображення: ";
    cin >> rows;
    if(rows < 1 || rows > 20){
        cout << "Помилка: має бути число між 1 і 20\n";
        return 1;//в умові вводу якщо неправильний ввід повідомляти користувача і завершувати роботу програми
    }
    cout << "Ширина зображення: ";
    cin >> cols;
    if(cols < 1 || cols > 20){
        cout << "Помилка: має бути число між 1 і 20\n";
        return 1;
    }
    cout << "Яскравість пікселів (0..9): \n";
    int **img = new int*[rows];
    for(int i = 0; i<rows; i++){
        img[i] = new int[cols];//двовимірний динамічний масив
        for(int j = 0; j<cols; j++){
            cin >> img[i][j];
            if(img[i][j] < 0 || img[i][j] > 9){
        cout << "Помилка: має бути число між 0 і 9\n";
        return 1;
        }
        }
    }
    do{
        cout << "Меню:\n" 
        << "Показати зображення(1)\n" 
        << "Статистика яскравості(2)\n" 
        << "Інвертувати яскравість(3)\n" 
        << "Віддзеркалити по горизонталі(4)\n" 
        << "Повернути на 90 градусів праворуч(5)\n" 
        << "Вийти(0)\n";
        while(!(cin >> choice)){ //перевірка на коректний ввід вже вільний вибір дій
            cout << "Помилка! виберіть існуючий варіант\n";
            cin.clear();
            cin.ignore(100, '\n');
        }
        switch(choice){//свіч через функції
        case 1:{showImg(img, rows, cols);
            break;}
        case 2:{findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
            break;}
        case 3:{invert(img, rows, cols);
            break;}
        case 4:{mirror(img, rows, cols);
            break;}
        case 5:{img = rotateRight(img, &rows, &cols);//редагуєм масив за допомогою присвоєнню поверненого результату
            break;}//передаємо rows i cols за допомогою адреси щоб потім обміняти їх значення поза мейном
        case 0: break;
        default:{//якщо ввести число якого нема в меню
            cout << "Введіть існуючий варіант\n";
        }
    }
    }while(choice != 0);//умова продовження роботи
    for(int i = 0; i<rows; i++){
        delete[] img[i];
        img[i] = nullptr;
    }//повне очищення пам'яті та міняєм вказівник на nullptr(нікуди не вказує)
    delete[] img;
    img = nullptr;
    return 0;
}
char numInChar(int a){
    switch(a){
        case 0:return ' ';
        case 1:return '.';
        case 2:return ':';
        case 3:return '-';
        case 4:return '=';
        case 5:return '+';
        case 6:return '*';
        case 7:return '#';
        case 8:return '%';
        case 9:return '@';
        default: return 0;//який ніколи не спрацює
    }
}
void coutImg(int **img, int rows, int cols){
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            cout << img[i][j] << " ";//просто напросто вивід щоб вічно не писати
        }
        cout << "\n";
    }
}
void showImg(int **img, int rows, int cols){//примітивні виводи
    cout << "Зображення " << rows << " x " << cols << ":\n";
    coutImg(img, rows, cols);
    cout << "Малюнок:\n";
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            cout << numInChar(img[i][j]);
        }
        cout << "\n";
    }
    return;
}
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    double count = 0.0, sum = 0.0, rowAvg[rows] = {0};//масив щоб не створювати ще один цикл під rowAvg
    int min = 9, max = 0;
    for(int i = 0; i<rows; i++){
        double rowSum = 0;
        int* row = img[i];//вкацівник на позицію img[i][0]
        for(int j = 0; j<cols; j++){
            if(*(row+j) < min){//перевіка завдяки вказівника на позицію а не самим img[i][j]
                min = *(row+j);
                minRow = i;
                minCol = j;
            }
            if(*(row+j) > max){//перевірка після натрапляння на 9 вже мінятися не буде бо умова строга(>)
                max = *(row+j);
                maxRow = i;
                maxCol = j;
            }
            sum += *(row+j);
            rowSum += *(row+j);
            count++;
        }
        rowAvg[i] = (rowSum/cols);
    }
    cout << "Найтемніший піксель: " << min << " (рядок " << minRow+1 << ", стовпець " << minCol+1 << ")\n";
    cout << "Найсвітліший піксель: " << max << " (рядок " << maxRow+1 << ", стовпець " << maxCol+1 << ")\n";
    cout << "Середня яскравість: " << fixed << setprecision(2) << (sum/count) <<endl;
    cout << "Середня по рядках: ";
    for(int i = 0; i<rows; i++){
        cout << fixed << setprecision(1) << rowAvg[i] << " ";
    }
    cout <<endl;
}
void invert(int **img, int rows, int cols){
    cout << "Яскравість інвертовано.\n";
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            img[i][j] = 9 - img[i][j];//інвертація працює бо знаачення яскравості від 0 до 9
            cout << img[i][j] << " ";
        }
        cout <<endl;
    }
}
void swapPixels(int *a, int *b){//через вказівник щоб могти взаємодіяти поза мейном
    int temp = *a;
    *a = *b;
    *b = temp;
}
void mirror(int **img,int rows,int cols){
    cout << "Зображення віддзеркалено.\n";
    cout << "Початкове:\n";
    coutImg(img, rows, cols);
    for(int i = 0; i<rows; i++){
        int *ptrRow = img[i];//знову через вказівник а не непряму 
        for(int j = 0; j<cols/2; j++){
            swapPixels(ptrRow + j,ptrRow + (cols-j-1));//маятником свапаєм
        }
    }
    cout << "Результат:\n";
    coutImg(img, rows, cols);//вивід
}
int** rotateRight(int** img, int* rows, int* cols) {
    int** rotated = new int*[*cols];
    for (int i = 0; i < *cols; i++) {
        rotated[i] = new int[*rows];
    }//створення нового динамічного масиву з новими розмірами
    for (int i = 0; i < *cols; i++){
        for (int j = 0; j < *rows; j++){
            rotated[i][j] = img[j][i];
        }
    }//поворот вправо можна реалізувати через дію arr[i][j]=arr[j][i] та віддзеркалення як у вункції mirror
    for(int i = 0; i<*cols; i++){
        int *ptrRow = rotated[i];
        for(int j = 0; j<*rows/2; j++){
            swapPixels(ptrRow + j,ptrRow + (*rows-j-1));
        }
    }
    cout << "Зображення повернуто. Нові розміри: " << *cols << " x " << *rows <<endl;
    coutImg(rotated, *cols, *rows);
    for (int i = 0; i < *rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }//видалення старого масиву і вказівники на nullptr
    delete[] img;
    img = nullptr;
    int temp = *rows;
    *rows = *cols;//к-сь рядків стає к-тю стовпців і навпаки щоб при повторному вик. пункту "5"
    *cols = temp;
    return rotated;
}