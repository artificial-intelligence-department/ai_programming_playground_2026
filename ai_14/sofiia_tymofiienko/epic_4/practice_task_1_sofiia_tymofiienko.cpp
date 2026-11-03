#include <iostream>
#include <iomanip>
using namespace std;
int** rotateRight(int **image, int rows, int cols){
    int **newimage= new int*[cols];
    for (int i=0; i<cols; i++){
      newimage[i]=new int[rows];
    }
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            newimage[j][rows-1-i]=image[i][j];
        }
    }
    for(int i=0; i<rows; i++){
        delete[]image[i];
        image[i]=nullptr;
    }
    delete[] image;
    image=nullptr;
    return newimage; 
}
void swapPixels(int *a, int *b){
    int temp= *a;
    *a=*b;
    *b=temp;
}
void gorizont( int **image, int rows, int cols){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols/2; j++){
            swapPixels(&image[i][j], &image[i][cols-1-j]);
        }
    }
}
void invert( int**image, int rows, int cols){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
          image[i][j]=9-image[i][j];
        }
    }
}
void findExtremes (int **image, int rows, int cols, int &minrow, int &mincol, int &maxrow, int &maxcol){
    minrow=0;
    mincol=0;
    maxrow=0;
    maxcol=0;
    int minval=**image;
    int maxval=**image;
    for (int i=0; i<rows; i++){
        int *row=image[i];
        for (int j=0; j<cols; j++){
            int val =*(row+j);
            if (val<minval){
                minval=val;
                minrow=i;
                mincol=j;
            }
            if (val>maxval){
                maxval=val;
                maxrow=i;
                maxcol=j;
            }
        }
    }
}
    void show(int **image, int rows, int cols){
        string palette= " .:-=+*#%@";
        cout<<"Табличне зображення: "<<endl;
        for (int i=0; i<rows; i++){
            for (int j=0; j<cols; j++){
                cout<<image[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"Графічне зображення: "<<endl;
        for (int i=0; i<rows; i++){
            for (int j=0; j<cols; j++){
                int photo=image[i][j];
                cout<<palette[photo];
            } 
            cout<<endl;
        }
        cout<<"Поточні розміри: "<<endl;
        cout<<"Висота: "<<rows<<endl;
        cout<<"Ширина: "<<cols<<endl;
    }
    void stats( int**image, int rows, int cols){
        int minrow, mincol, maxrow, maxcol;
        findExtremes(image, rows, cols, minrow, mincol, maxrow, maxcol);
        int *minrowptr=image[minrow];
        int *maxrowptr=image[maxrow];
        int minval= *(minrowptr+mincol);
        int maxval= *(maxrowptr+maxcol);
        cout<<"Статистика яскравості: "<<endl;
        cout<<"Найтемніший піксель: "<<minval<<" (рядок "<<minrow+1<<" , стовпець "<<mincol+1<<")"<<endl;
        cout<<"Найсвітліший піксель: "<<maxval<<" (рядок "<<maxrow+1<<" , стовпець "<<maxcol+1<<")"<<endl;
double tsum=0;
cout<<fixed<<setprecision(2);
cout<<"Середня яскравість по рядках: ";
for (int i=0; i<rows; i++){
    int *row= image[i];
    double rowsum=0;
    for (int j=0; j<cols; j++){
        rowsum += *(row+j);
    }
    tsum +=rowsum;
    cout<<rowsum/cols<<" ";
}
cout<<endl;
double avg=tsum/(rows*cols);
cout<<"Середня яскравість зображення: "<<avg<<endl;
}

int main(){
 int rows, cols;
cout<<"Введіть висоту пікселів: "<<endl;
if (!(cin>>rows)){
    cout<<"Помилка! Введено не число! "<<endl;
    return 0;
}
cout<<"Введіть ширину пікселів: "<<endl;
if (!(cin>>cols)){
    cout<<"Помилка! Введено не число! "<<endl;
    return 0;
}
    if (rows<=0 || cols<=0 ){
        cout<<"Помилка! Значення повинні бути від 0 . "<<endl;
        return 0;
    }
    int ** image= new int*[rows];
    for (int i=0; i<rows; i++){
        image[i]=new int[cols];
    }
cout<<"Введіть яскравість пікселів (0-9): "<<endl;
for (int i=0; i<rows; i++){
    for (int j=0; j<cols; j++){
       if(!(cin>>image[i][j]) || image[i][j]<0 || image[i][j]>9){
        cout<<"Помилка! Введіть значення від 0 до 9."<<endl;
        for (int k=0; k<rows; k++){
            delete[] image[k];
            image[k]=nullptr;
        }
        delete[] image;
        image=nullptr;
        return 0;
       }
    }
} 
int choice;
do{
    cout<<"===Меню операцій: "<<endl;
    cout<<"1. Показати зображення"<<endl;
    cout<<"2. Статистика яскравості"<<endl;
    cout<<"3. Інвертувати яскравість"<<endl;
    cout<<"4. Віддзеркалити по горизонталі"<<endl;
    cout<<"5. Повернути на 90 градусів праворуч"<<endl;
    cout<<"0. Вийти"<<endl;
    cout<<"Оберіть опцію: ";
    if (!(cin>>choice)){
            cout<<"Помилка некоректного вводу!"<<endl;
            break;
        }
switch (choice){
    case 1:
    show (image, rows, cols);
    break;
    case 2: 
    stats (image, rows, cols);
    break;
    case 3:
    cout<<"Яскравість інвертовано! "<<endl;
    invert (image, rows, cols);
    break;
    case 4:
    cout<<"Зображення віддзеркалено! "<<endl;
    gorizont(image, rows, cols);
    break;
    case 5:
    image=rotateRight(image, rows, cols);
    swap(rows, cols);
    cout<<"Зображення повернуте на 90 градусів праворуч!"<<endl;
    break;
    case 0:
    cout<<"Вихід!";
    break;
        default:
    cout<<"Некоректний вибір! Оберіть опції 1-5 для операцій, 0-вихід."<<endl;
    break;
    }
}while (choice !=0);
for (int i=0; i<rows; i++){
    delete[] image [i];
    image[i]=nullptr;
}
delete []image;
image = nullptr;
    return 0;
}
