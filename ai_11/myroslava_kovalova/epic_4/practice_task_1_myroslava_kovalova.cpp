#include <iostream>
#include <string>
using namespace std;

void showArr(int** image, int rows,int cols);
void showImage(int** image, int rows,int cols, string palette);
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void invertBrightness(int** image, int rows, int cols);
void swapPixels(int *a, int *b);
void mirrorImage(int** image, int rows, int cols);
int** rotateRight( int** image, int &rows, int &cols);
void memoryDelete(int** &image, int rows);

int main(){

    string palette = " .:-=+*#%@";
    char choice = 'n';
    int minRow, minCol, maxRow, maxCol;
    int rows, cols;
    cout<<"Висота зображення(від 1 до 20):\n";
    cin>>rows;
    if (rows>20 || rows<1 || cin.fail()){
        cout<<"Ввід не входить у дозволений діапазон.\n";
        return 0;
    }
    cout<<"Ширина зображення(від 1 до 20):\n";
    cin>>cols;
    if (cols>20 || cols<1 || cin.fail()){
        cout<<"Ввід не входить у дозволений діапазон.\n";
        return 0;
    }
    int**image = new  int*[rows];
    for (int i =0; i<rows; i++){
        image [i] = new int [cols];
    }

    cout<<"\nВведіть яскравість пікселів зображення через пробіл. \n";
    for (int i = 0; i< rows; i++){
        for (int j = 0; j< cols; j++){
            cin>>image[i][j];
            if (image[i][j]<0 || image[i][j]>9 || cin.fail()){
                cout<<"Ввід не входить у дозволений діапазон.\n";
                memoryDelete(image, rows);
                return 0;
            }
        }
    }
    do{
        while(true){
            cout<<"\nМеню\n1 Показати зображення\n2 Статистика яскравості\n3 Інвертувати яскравість\n4 Віддзеркалити по горизонталі\n5 Повернути на 90 градусів праворуч\n0 Вийти\n";
            cin>>choice;
            if (choice=='1'||choice=='2'||choice=='3'||choice=='4'||choice=='5'||choice=='0')break;
            cout<<"Некоректний ввід. Ведіть цифру з доступних у меню.\n";
        }

        switch(choice){
            case '1':
                showArr(image, rows, cols);
                showImage(image, rows, cols, palette);
                break;
            case '2':
                findExtremes(image, rows,  cols,  minRow,  minCol, maxRow, maxCol);
                break;
            case '3':
                invertBrightness(image, rows, cols);
                break;
            case '4':
                mirrorImage(image, rows, cols);
                break;
            case '5':{
                image = rotateRight( image, rows, cols);
                int t=rows;
                rows = cols;
                cols = t; 
                showArr(image, rows, cols);
                break;
            }
            case '0':
                cout<<"Ви вийшли. \n";
                memoryDelete(image, rows);
                break;
            default:
                cout<<"Непередбачена дія. Введіть доступну цифру з меню.\n";
                break;
        }

    }while(choice!='0');

    return 0;
}

void showArr(int **image, int rows,int cols){

    cout<<"\nРозмір зображення "<<rows<<" х "<<cols;
    for (int i = 0; i<rows;i++){
        cout<<"\n";
        for (int j = 0; j<cols; j++){
            cout<<image[i][j]<<" ";
        }
    }
    
}

void showImage(int **image, int rows,int cols, string palette){
    cout<<"\nМалюнок:";
    for (int i = 0; i < rows; i++){
        cout<<"\n";
        for (int j = 0; j<cols; j++){
            cout<<palette[image[i][j]];
        }
    }
}

void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    short int max = 0, min=10;
    for (int i = 0; i<rows; i++){
        int *row = image[i];
        for (int j = 0; j<cols; j++){
            if (*(row+j)>max) max=*(row+j);
            if (*(row+j)<min) min=*(row+j);
        }
    }
    bool found_min=0, found_max=0;
    int total_sum=0;
    for (int i = 0; i<rows; i++){
        int *row = image[i];
        for (int j = 0; j< cols; j++){
                if(*(row+j)==min && found_min==0){
                minRow=i;
                minCol=j;
                found_min =1;
            }
            if(*(row+j)==max && found_max==0){
                maxRow=i;
                maxCol=j;
                found_max=1;
            }
            total_sum+=*(row+j);
        }
    }
    
    float total_average = (float)total_sum/(rows*cols);
    cout<<"Найтемніший піксель: "<<min<<" (рядок "<<minRow+1<< ", стовпець "<<minCol+1<<" )"<<endl;
    cout<<"Найсвітліший піксель: "<<max<<" (рядок "<<maxRow+1<< ", стовпець "<<maxCol+1<<" )"<<endl; 
    cout<<"Середня яскравість: "<<total_average<<endl;
    cout<<"Середня по рядках: ";
    for (int i = 0; i<rows; i++){
        int *row = image[i];
        float averege=0;
        int sum =0;
        for (int j=0; j<cols; j++){
            sum+=*(row+j);            
        }
        averege=(float)sum/cols;
        cout<<averege<<" ";
    }
    

}

void invertBrightness(int** image, int rows, int cols){
    for(int i = 0; i<rows; i++){
        for (int j = 0; j<cols; j++){
            image[i][j]=9-image[i][j];
        }
    }
    cout<<"Яскравість змінено.\n";
    showArr(image,rows,cols);
}

void swapPixels(int *a, int *b){
    int t = *a;
    *a=*b;
    *b=t;
}

void mirrorImage(int** image, int rows, int cols){
    cout<<"Зображення віддзеркалено. \n"<<"Початкове зображення: \n";
    showArr(image, rows, cols); 
    for (int i =0;i<rows; i++){
        for(int j=0; j<cols/2; j++){
            swapPixels(image[i]+j,image[i]+(cols-1-j));
        }
    }
    cout<<"\nРезультат: \n";
    showArr(image, rows, cols); 
}


int** rotateRight(int** image, int &rows, int &cols){
    int **rotated_image = new  int* [cols];
    for (int i = 0; i< cols; i++){
        rotated_image[i] = new int [rows];
    }
    for (int i = 0; i<rows; i++){
        for (int j = 0; j< cols; j++){
            rotated_image[j][i]=image[rows-1-i][j];
        }
    }
    memoryDelete(image, rows);
     
    return rotated_image;
}

void memoryDelete(int** &image, int rows){
    for (int i = 0; i< rows; i++){
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;
}