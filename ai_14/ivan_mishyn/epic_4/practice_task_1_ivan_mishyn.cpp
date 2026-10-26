#include <iostream>
#include <iomanip>
using namespace std;

void freeImage(int** &img, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] img[i];
    }
    delete[] img;
    img=nullptr;
}
void OutNums(int** img, int rows,int cols){
    for(int i=0;i<rows;i++){
        cout<<"\n";
        for(int j=0; j<cols;j++){
            cout<<img[i][j]<<" ";
        }
    }
}
char intToImage(int n){
    static string pallete=" .:-=+*#%@";
    return pallete[n];
}

//Показати зображення
void showImage(int** img, int rows, int cols){
    cout<<"\nЗображення "<<rows<<" x "<<cols<<" :";
    OutNums(img,rows,cols);
    cout<<"\nМалюнок:";
    for(int i=0;i<rows;i++){
        cout<<"\n";
        for(int j=0; j<cols;j++){
            cout<<intToImage(img[i][j]);
        }
    }
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    int minVal=10;
    int maxVal=-1;
    for(int i=0;i<rows;i++){
        int *row=img[i];
        for(int j=0;j<cols;j++){
            int current=*(row+j);

            if(current>maxVal){
                maxVal=current;
                maxRow=i;
                maxCol=j;
            }
            if(current<minVal){
                minVal=current;
                minRow=i;
                minCol=j;
            }
        }
    }
}

void showStatisticks(int **img, int rows, int cols){
    int minRow,minCol,maxRow,maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    int minVal = *(img[minRow] + minCol);
    int maxVal = *(img[maxRow] + maxCol);
    cout<<"\nНайтемніший піксель: "<<minVal<<" (рядок "<<minRow+1<<", стовпець "<<minCol+1<<")";
    cout<<"\nНайсвітліший піксель: "<<maxVal<<" (рядок "<<maxRow+1<<", стовпець "<<maxCol+1<<")";
    float avgsum=0;
    for(int i=0;i<rows;i++){
        int *row=img[i];
        for(int j=0;j<cols;j++){
            avgsum+=*(row+j);
        }
    }
    avgsum=avgsum/(rows*cols);
    cout << fixed << setprecision(2);
    cout<<"\nСередня яскравість: "<<avgsum;
    cout << fixed << setprecision(1);
    cout<<"\nСередня по рядках: ";
    for(int i=0;i<rows;i++){
        float sumRow=0;
        int *row=img[i];
        for(int j=0;j<cols;j++){
            sumRow+=*(row+j);
        }
        cout<<sumRow/cols<<" ";
    }

}
void invert(int **img, int rows,int cols){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            img[i][j]=9-img[i][j];
        }
    }
    cout<<"\nЯскравість інвертовано: "; 
    OutNums(img,rows,cols);
}
void swapPixels(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void mirror(int **img, int rows, int cols){
    cout<<"\nЗображення віддзеркалено.";
    cout<<"\nПочаткове:";
    OutNums(img,rows,cols);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols/2;j++){
            swapPixels(&img[i][j],&img[i][cols-1-j]);
        }
    }
    cout<<"\n\nРезультат:";
    OutNums(img,rows,cols);
}
int** rotateRight(int **img, int rows, int cols){
    int rowsNew=cols;
    int colsNew=rows;
    int** imageNew= new int*[rowsNew];
    for(int i=0;i<rowsNew;i++){
        imageNew[i] = new int[colsNew];
    }
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            imageNew[c][rows - 1 - r] = img[r][c];
        }
    }
    freeImage(img, rows);
    cout<<"\nЗображення "<<rowsNew<<" x "<<colsNew<<" :";
    OutNums(imageNew,rowsNew,colsNew);
    return imageNew;
}

int main(){
    int rows=0;
    int cols=0;
    

    cout << "Висота зображення: ";
    cin >> rows;

    if (cin.fail() || rows < 1 || rows > 20) {
         cout << "Помилка! Висота має бути цілим числом від 1 до 20.\n";
         return 0;  
    }
    cout << "Ширина зображення: ";
    cin >> cols;

    if (cin.fail() || cols < 1 || cols > 20) {
            cout << "Помилка! Ширина має бути цілим числом від 1 до 20.\n";
            return 0;
    }
    int** image = new int*[rows]; 
    for (int i = 0; i < rows; ++i) {
        image[i] = new int[cols];
    }
    cout << "Яскравість пікселів (0..9):\n";

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> image[i][j];
            if (cin.fail() || image[i][j] < 0 || image[i][j] > 9) {
                cout << "Помилка для пікселя. Число мусить бути від 0 до 9";
                freeImage(image, rows);
                return 0;
            }
        }
    }
    int menu=-1;
    int temp;
    do{
        menu = -1;
        cout<<"\n 1 - Показати зображення"
        <<"\n 2 - Статистика яскравості"
        <<"\n 3 - Інвертувати яскравість"
        <<"\n 4 - Віддзеркалити по горизонталі"
        <<"\n 5 - Повернути на 90 градусів праворуч"
        <<"\n 0 - Вийти"
        <<"\n\nВиберіть пункт меню:";
        cin>>menu;
        switch(menu){
            case 1:
            showImage(image,rows,cols);
            break;
            case 2:
            showStatisticks(image,rows,cols);
            break;
            case 3:
            invert(image,rows,cols);
            break;
            case 4:
            mirror(image,rows,cols);
            break;
            case 5:
            image = rotateRight(image, rows, cols);
            temp = rows;
            rows = cols;
            cols = temp;
            break;
            case 0:
            cout << "\nВихід з програми\n";
            break;
            default:
            menu=-1;
            cout << "Помилка вводу\n";
            freeImage(image,rows);
            return 0;
        }
            
    }while(menu!=0);
    freeImage(image,rows);
    
    return 0;
}