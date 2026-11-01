/*"Редактор монохромного зображення"
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
#include <iomanip>
using namespace std;

void printMenu(){
    cout<<"--------Меню--------"<<endl;
    cout<<"1 - Показати зображення"<<endl;
    cout<<"2 - Статистика яскравості"<<endl;
    cout<<"3 - Інвертувати яскравість"<<endl;
    cout<<"4 - Віддзеркалити по горизонталі"<<endl;
    cout<<"5 - Повернути на 90 градусів"<<endl;
    cout<<"0 - Вийти"<<endl;
    cout<<endl;
}
//функція для керування динамічною пам'яттю 
void deletePointerIm(int **img, int rows, int cols){
    for(int i=0; i<rows; i++){
        delete [] img[i];
        img[i]=nullptr;
    }
    delete [] img;
    img = nullptr;
}

void ImagePrint(int **img, int rows, int cols){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << img[i][j] <<" ";
        }
        cout << endl;       
    }
}
//створення малюнку
void Menu1(int **img, int rows, int cols){
    const char Pallete[] =" .:-=+*#%@";
    cout<<"Зображення "<<rows<<" x "<<cols<<":"<<endl;
    ImagePrint(img, rows, cols);
    cout << "Малюнок: "<<endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout<<Pallete[img[i][j]];
        }
        cout << endl;
    }
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    int minValue = *img[0];
    int maxValue = *img[0];
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    for (int i = 0; i < rows; ++i) {
        int *row = img[i];                 
        for (int j = 0; j < cols; ++j) {
            int value = *(row + j);        
            if (value < minValue) {          
                minValue = value;
                minRow = i;
                minCol = j;
            }
            if (value > maxValue) {          
                maxValue = value;
                maxRow = i;
                maxCol = j;
            }
        }
    }
    cout << "Найтемніший піксель: "<<minValue<<" (рядок "<<minRow+1<<", "<<"стовпець "<<minCol+1<<")"<<endl;
    cout << "Найсвітліший піксель: "<<maxValue<<" (рядок "<<maxRow+1<<", "<<"стовпець "<<maxCol+1<<")"<<endl;
}    
void Average(int **img, int rows, int cols){
    double sum = 0.0;
        for (int i = 0; i < rows; ++i) {
        int *row = img[i];                 
        for (int j = 0; j < cols; ++j) {
            sum+=*(row+j);

        }
    }
    cout << fixed << setprecision(2);
    cout<<"Середня яскравість: "<<sum/(rows*cols)<<endl;
    cout << fixed << setprecision(1);
    cout <<"Середня по рядках: ";
    for (int i = 0; i < rows; ++i) {
        int *row = img[i];
        double rowSum = 0;
        for (int j = 0; j < cols; ++j) {
            rowSum += *(row + j);
        }
        cout << rowSum / cols<<" ";
    }
    cout << endl;        
}
void Menu2(int **img, int rows, int cols){
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    Average(img, rows, cols);
}
void inversion(int **img, int rows, int cols){
    cout<<"Яскравість інвертовано."<<endl;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            img[i][j]=9-img[i][j];
        }
    }
    ImagePrint(img, rows, cols);
}
void swapPixels(int *a, int *b){
    int temporary = *a;
    *a = *b;
    *b = temporary;
}
void mirrorIm(int **img, int rows, int cols){
    cout << "Зображення віддзеркалено."<<endl;
    cout << "Початкове:" << endl;
    ImagePrint(img, rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols / 2; ++j) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    cout << "Результат:" << endl;
    ImagePrint(img, rows, cols);
}
//функція, яка повертає новий вказівник
int **rotateRight(int **img, int rows, int cols){
    int **newimage = new int *[cols];
    for (int i = 0; i < cols; ++i) {
        newimage[i] = new int[rows];
    }
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            newimage[j][rows-1-i]=img[i][j];
        }
    }
    deletePointerIm(img, rows, cols);
    return newimage;
}
void Menu5(int **&img, int &rows, int &cols){
    img = rotateRight(img, rows, cols);
    int temp = rows; 
    rows = cols;
    cols = temp;
    cout <<"Зображення повернуто. Нові розміри: "<<rows<<" x "<<cols<<endl;
    ImagePrint(img, rows,cols);
}
int main(){
    int rows;
    cout << "Висота зображення: ";
    cin >> rows;
    if(cin.fail() || rows<1|| rows>20){
        cout<<"Помилка: висота зображення має бути від 1 до 20."<<endl;
        return 1;
    }
    int cols;
    cout <<"Ширина зображення: ";
    cin >> cols;
    if(cin.fail() || cols<1|| cols>20){
        cout<<"Помилка: ширина зображення має бути від 1 до 20."<<endl;
        return 1;
    }

    int **image = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        image[i] = new int[cols];
    }
    cout<<"Яскравість пікселів(0..9): ";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> image[i][j];
            if(cin.fail() || image[i][j]<0 || image[i][j]>9){
                cout<<"Помилка: яскравість пікселів повинна бути від 0 до 9."<<endl;
                deletePointerIm(image, rows, cols);
                image = nullptr;
                return 1;
            }
        }
    } 

    int menu;
    do{
        printMenu();
        cout <<"Виберіть пункт меню: ";
        cin >> menu;
        while(cin.fail() || menu<0 || menu>5){
            cout<<"Помилка: введіть значення від 0 до 5."<<endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> menu;
        }
        switch(menu){
            case 1: Menu1(image, rows, cols); break;
            case 2: Menu2(image, rows, cols ); break;
            case 3: inversion(image, rows, cols); break;
            case 4: mirrorIm(image, rows,cols); break;
            case 5: Menu5(image, rows,cols); break;
        }
    }while(menu!=0);
    //вивільнення динамічної пам'яті
    deletePointerIm(image, rows, cols);
    image = nullptr;
    return 0;
}