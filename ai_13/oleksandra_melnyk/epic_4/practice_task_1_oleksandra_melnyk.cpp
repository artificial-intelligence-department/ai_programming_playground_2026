#include <iostream>
#include <string>
using namespace std;

//функція void для виведення на екран чисел матриці
void printMatrix(int** img, int rows, int cols){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            if (j>0){
                cout<<" ";
            }
            cout<<img[i][j];
        }
        cout<<endl;
    }
}
//функція void для виведення зображення числами та символами
void Image(int** img, int rows, int cols){
    cout<<"Зображення "<<rows<<" x "<<cols<<":"<<endl;
    printMatrix(img, rows, cols);
    cout<<endl;
    cout<<"Малюнок:"<<endl;
    string palette=" .:-=+*#%@";
    //виведення матриці-палітри по символах
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            cout<<palette[img[i][j]];
        }
        cout<<endl;
    }
}
//функція void для знаходження максимального мінімального значень та середніх значень
void findExtremes(int** img, int rows, int cols, int &minrow, int &mincol, int &maxrow, int &maxcol){
    int mx=*img[0];
    int mn=*img[0];
    minrow=0, mincol=0, maxrow=0, maxcol=0;
    double sum=0;
    for (int i=0; i<rows; i++){
        int *row=img[i];
        for (int j=0; j<cols; j++){
            int pixel=*(row+j);
            if (pixel<mn)
            {
                mn=pixel;
                minrow=i;
                mincol=j;
            }
            if (pixel>mx){
                mx=pixel;
                maxrow=i;
                maxcol=j;
            }
            sum+=pixel;
        }
    }
    cout<<"Найтемніший піксель: "<<mn<<" (рядок "<<minrow+1<<", "<<"стовпець "<<mincol+1<<")"<<endl;
    cout<<"Найсвітліший піксель: "<<mx<<" (рядок "<<maxrow+1<<", "<<"стовпець "<<maxcol+1<<")"<<endl;
    //fixed і precision є в iostream, тому сторонні бібліотеки не потрібні
    cout<<fixed;
    cout.precision(2);
    cout<<"Середня яскравість: "<<sum/(rows*cols)<<endl;
    cout.precision(1);
    cout<<"Середнє по рядках:";
    for (int i=0; i<rows; i++){
        int *row=img[i];
        double row_sum=0;
        for (int j=0; j<cols; j++){
            row_sum+=*(row+j);
        }
        cout<<" "<<row_sum/cols;
    }
    cout<<endl;
}
//функція інвертування кольорів
void invert(int** img, int rows, int cols){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            img[i][j]=9-img[i][j];
        }
    }
    cout<<"Яскравість інвертовано."<<endl;
    printMatrix(img, rows, cols);
}
//функція обмін значень двох змінних за допомогою вказівників
void swapPixels( int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
//функція віддзеркалення зображення по горизонталі
void horisontal(int** img, int rows, int cols){
    cout<<"Зображення віддзеркалено."<<endl;
    cout<<"Початкове:"<<endl;
    printMatrix(img, rows, cols);
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols/2; j++){
            swapPixels(&img[i][j], &img[i][cols-1-j]);
        }
    }
    cout<<endl;
    cout<<"Результат:"<<endl;
    printMatrix(img, rows, cols);
}
//функція повороту на 90 градусів праворуч
int** rotateRight(int** img, int rows, int cols){
    //виділення памʼяті для нової матриці
    int** newimg=new int* [cols];
    for (int i=0; i<cols; i++){
        newimg[i]=new int[rows];
    }
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            newimg[j][rows-1-i]=img[i][j];
        }
    }
    //звільнення памʼяті щоб не було витоку
    for (int i=0; i<rows; i++)
    {
        delete[] img[i];
    }
    delete[] img;
    cout<<"Зображення повернуто. Нові розміри: "<<cols<<" x "<<rows<<endl;
    return newimg;
}

int main()
{
    int rows, cols;
    cout<<"Висота зображення: ";
    cin>>rows;
    //перевірка на коректність вводу даних
    if (cin.fail() || rows<1 || rows>20){
        cout<<"Помилка. Висота зображення пікселів має бути 1-20."<<endl;
        return 1;
    }
    cout<<"Ширина зображення: ";
    cin>>cols;
    //перевірка на коректність вводу даних
    if (cin.fail() || cols<1 || cols>20){
        cout<<"Помилка. Ширина зображення пікселів має бути 1-20."<<endl;
        return 1;
    }
    int** img=new int*[rows];
    for (int i=0; i<rows; i++){
        img[i]=new int[cols];
    }
    cout<<"Яскравість пікселів (0..9):"<<endl;
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            cin>>img[i][j];
            //перевірка на коректність вводу даних
            if (cin.fail() || img[i][j]<0 || img[i][j]>9){
                cout<<"Помилка. Яскравість пікселів має бути 0-9."<<endl;
                //якщо помилка - звільняємо памʼять перед виходом
                for (int k=0; k<rows; k++){
                    delete[] img[k];
                }
                delete[] img;
                img=nullptr;
                return 1;
            }
        }
    }
    int choice;
    int minrow, mincol, maxcol, maxrow;
    do{
        cout << "--- Меню ---" << endl;
        cout << "1 Показати зображення" << endl;
        cout << "2 Статистика яскравості" << endl;
        cout << "3 Інвертувати яскравість" << endl;
        cout << "4 Віддзеркалити по горизонталі" << endl;
        cout << "5 Повернути на 90 градусів праворуч" << endl;
        cout << "0 Вийти" << endl;
        cout << "Ваш вибір: ";
        cin>>choice;
        //обробка некоректного вводу меню
                if (cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            choice=-1;
        }
        switch (choice)
        {
            case 1:
            Image(img,rows,cols);
            break;
            case 2:
            findExtremes(img,rows,cols,minrow, mincol, maxrow, maxcol);
            break;
            case 3:
            invert(img, rows, cols);
            break;
            case 4:
            horisontal(img, rows, cols);
            break;
            case 5:{
            img=rotateRight(img, rows, cols);
            int temp=rows;
            rows=cols;
            cols=temp;
            printMatrix(img,rows,cols);
            break;
            }
            case 0:
            break;
            default:
            cout<<"Некоректний ввід."<<endl;
        }
    }
    while (choice!=0);
    //звільнення памʼяті перед виходом з програми
    for (int k=0; k<rows; k++)
    {
        delete[] img[k];
    }
    delete[] img;
    //зануляємо вказівник
    img=nullptr;
    return 0;
}