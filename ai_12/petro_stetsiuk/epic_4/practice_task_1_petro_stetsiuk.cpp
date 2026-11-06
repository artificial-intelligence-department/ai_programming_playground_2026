/*
Редактор монохромного зображення
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>
#include <iomanip>
using namespace std;
char symbols[] = {' ','.',':','-','=','+','*','#','%','@'};
void deletes(int**& img,int rows)
{
    for(int i=0;i<rows;i++)
    {
        delete[] img[i];
        img[i]=nullptr;
    }
    delete[] img;
    img = nullptr;
}
void image_output_clear(int** img, int rows, int cols)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            cout<<img[i][j]<<" ";
        }
        cout<<endl;
    }
}
void image_output(int** img, int rows, int cols)
{
    cout<<"Зображення "<<rows<<" x "<<cols<<":"<<endl;
    image_output_clear(img, rows, cols);
    cout<<endl;
    cout<<endl<<"Малюнок:"<<endl;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            cout<<symbols[img[i][j]]<<" ";
        }
        cout<<endl;
    }
}
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    int* row = img[0];
    int Min = *row;
    int Max = *row;
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    for (int i = 0; i < rows; i++)
    {
        row = img[i];
        for (int j = 0; j < cols; j++)
        {
            if(*(row+j) < Min)
            {
                Min = *(row+j);
                minRow = i;
                minCol = j;
            }
            if(*(row+j) > Max)
            {
                Max = *(row+j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}
void AverageBrightness(int **img, int rows, int cols)
{
    int* row = img[0];
    double average = 0,averagerow = 0;
    for (int i = 0; i < rows; i++)
    {
        row = img[i];
        for (int j = 0; j < cols; j++)
        {
            average += *(row+j);
        }
    }
    average = average / (rows * cols);
    cout << "Середня яскравість: " <<fixed<<setprecision(2)<< average << endl;
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++)
    {
        averagerow = 0;
        row = img[i];
        for (int j = 0; j < cols; j++)
        {
            averagerow += *(row+j);
        }
        cout<<fixed<<setprecision(1)<<averagerow/cols<<" ";

    }
}
void invertBrightness(int **img, int rows, int cols)
{
    cout<<"Яскравість інвертовано."<<endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(img[i] + j) = 9 - *(img[i] + j);
            cout<<*(img[i] + j)<<" ";
        }
        cout<<endl;
    }
}
void swapPixels(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void Mirror(int **img, int rows, int cols)
{
    cout<<"Зображення віддзеркалено."<<endl;
    cout<<"Початкове:"<<endl;
    image_output_clear(img, rows, cols);
    cout<<"Віддзеркалене:"<<endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols / 2; j++)
        {
            swapPixels(&img[i][j], &img[i][cols - j - 1]);
            
        }
    }
    image_output_clear(img, rows, cols);
}
int** rotateRight(int **img, int rows, int cols)
{
    
    int **rotatedImg = new int*[cols];
    for (int i = 0; i < cols; i++)
    {
        rotatedImg[i] = new int[rows];
        for (int j = 0; j < rows; j++)
        {
            rotatedImg[i][j] = img[rows - j - 1][i];
        }
    }
    deletes(img, rows);
    return rotatedImg;
}
void case2(int **img, int rows, int cols)
{
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "Найтемніший піксель: " << *(img[minRow] + minCol) << " (рядок: " << minRow+1 << ", стовпець: " << minCol+1 << ")" << endl;
    cout << "Найсвітліший піксель: " << *(img[maxRow] + maxCol) << " (рядок: " << maxRow+1 << ", стовпець: " << maxCol+1 << ")" << endl;
    AverageBrightness(img, rows, cols);
}
void case5(int **&img, int &rows, int &cols)
{
    img = rotateRight(img, rows, cols);
    int temp = rows;
    rows = cols;
    cols = temp;
    cout << "Зображення повернуто на 90 градусів праворуч. Нові розміри: " << rows << " x " << cols << endl;
    image_output_clear(img, rows, cols);
}
int main()
{
    int rows, cols, i, j, choice,flag=1;
    int **img = nullptr;
    cout << "Введіть висоту зображення(1-20): ";
    cin >> rows;
    if(cin.fail()||rows<1||rows>20)
    {
        cout<<"Wrong data input!";
        return 0;
    }
    cout << "Введіть ширину зображення(1-20): ";
    cin >> cols;
    if(cin.fail()||cols<1||cols>20)
    {
        cout<<"Wrong data input!";
        return 0;
    }
    img = new int*[rows];
    for(i = 0;i<rows;i++)
        img[i] = new int[cols];
    cout << "Яскравість пікселів (0..9):"<<endl;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
           cin>>img[i][j]; 
           if(cin.fail()||img[i][j]<0||img[i][j]>9)
           {
            cout<<"Wrong data input!";
            deletes(img,rows);
            return 0;
           }
        }
        
    }
    do
    {
        cout<<endl<<"======== Меню ========"<<endl;
        cout<<"Пункт    Операція"<<endl;
        cout<<"1        Показати зображення"<<endl;
        cout<<"2        Статистика яскравості"<<endl;
        cout<<"3        Інвертувати яскравість"<<endl;
        cout<<"4        Віддзеркалити по горизонталі"<<endl;
        cout<<"5        Повернути на 90 градусів праворуч"<<endl;
        cout<<"0        Вийти"<<endl;
        cin>>choice;
        if(cin.fail()||choice<0||choice>5) 
        {
            cin.clear();
            cin.ignore(10000,'\n');
            cout<<"Помилка введення! Спробуйте ще раз."<<endl;
            continue;
        }
        switch(choice)
        {
            case 1:
                image_output(img, rows, cols);
                break;
            case 2:
                case2(img, rows, cols);
                break;
            case 3:
                invertBrightness(img, rows, cols);
                break;
            case 4:
                Mirror(img, rows, cols);
                break;
            case 5:
                case5(img, rows, cols);
                break;
            case 0:
            flag=0;
            break;
        }
        
    } while (flag!=0);
    deletes(img, rows);
    img = nullptr;
}   