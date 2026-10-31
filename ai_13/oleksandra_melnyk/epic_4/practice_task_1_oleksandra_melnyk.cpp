#include <iostream>
#include <algorithm>
using namespace std;

void Image(int** img, int rows, int cols){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            cout<<img[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    string palette=" .:-=+*#%@";
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            cout<<palette[img[i][j]];
        }
        cout<<endl;
    }
    cout<<"Розміри: "<<rows<<"x"<<cols<<endl;
}
void findExtremes(int** img, int rows, int cols, int &minrow, int &mincol, int &maxrow, int &maxcol){
    int mx=*img[0];
    int mn=*img[0];
    minrow=0, mincol=0, maxrow=0, maxcol=0;
    float middle=0;  
    float sum=0;
    for (int i=0; i<rows; i++){
        int *row=img[i];
        float row_sum=0;
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
            row_sum+=pixel;
        }
        sum+=row_sum;
        cout<<"Середнє по рядках: "<<i+1<<" "<<row_sum/cols<<endl;
    }
    cout<<"Найтемніший піксель: "<<mn<<" (рядок "<<minrow+1<<", "<<"стовпець "<<mincol+1<<")"<<endl;
    cout<<"Найсвітліший піксель: "<<mx<<" (рядок "<<maxrow+1<<", "<<"стовпець "<<maxcol+1<<")"<<endl;
    cout<<"Середня яскравість: "<<sum/(rows*cols)<<endl;
}
void invert(int** img, int rows, int cols){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            img[i][j]=9-img[i][j];
        }
    }
    cout<<"Яскравість інвертовано. "<<endl;
}
void swapPixels( int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
void horisontal(int** img, int rows, int cols){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols/2; j++){
            swapPixels(&img[i][j], &img[i][cols-1-j]);
        }
    }
    cout<<"Зображення віддзеркалено."<<endl;
}
int** rotateRight(int** img, int rows, int cols){
    int** newimg=new int* [cols];
    for (int i=0; i<cols; i++){
        newimg[i]=new int[rows];
    }
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            newimg[j][rows-1-i]=img[i][j];
        }
    }
     for (int i=0; i<rows; i++)
    {
        delete[] img[i];
    }
    delete[] img;
    cout<<"Зображення повернуто. Нові розміри: "<<cols<<"x"<<rows<<endl;
    return newimg;
}

int main()
{
    int rows, cols, image;
    cout<<"Висота зображення пікселів "<<endl;
    cin>>rows;
    if (cin.fail() || rows<1 || rows>20){
        cout<<"Помилка. Висота зображення пікселів має бути 1-20.";
        return 1;
    }
    cout<<"Ширина зображення пікселів "<<endl;
    cin>>cols;
    if (cin.fail() || cols<1 || cols>20){
        cout<<"Помилка. Ширина зображення пікселів має бути 1-20.";
        return 1;
    }
    int** img=new int*[rows];
    for (int i=0; i<rows; i++){
        img[i]=new int[cols];
    }
    cout<<"Яскравість пікселів "<<endl;
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            cin>>img[i][j];
            if (cin.fail() || img[i][j]<0 || img[i][j]>9){
            cout<<"Помилка. Яскравість пікселів має бути 0-9.";
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
            Image(img,rows,cols);
            break;
            case 4:
            Image(img,rows,cols);
            horisontal(img, rows, cols);
            Image(img,rows,cols);
            break;
            case 5:{
            img=rotateRight(img, rows, cols);
            int temp=rows;
            rows=cols;
            cols=temp;
            Image(img,rows,cols);
            break;
            }
            case 0:
            break;
            default:
            cout<<"Некоректний ввід."<<endl;
        }
    }
    while (choice!=0);
    for (int k=0; k<rows; k++)
    {
        delete[] img[k];
    }
    delete[] img;
    img=nullptr;
    return 0;
}