/*
Практична задача: Редактор монохромного зображення
група ШІ-12
Козій Василь Іванович
*/
#include <iostream>
#include <iomanip>
using namespace std;
//Функція виводу яскравості зображення
void cout_brightness(int** image, int rows, int cols)
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            cout <<image[i][j] <<" ";
        }
        cout <<endl;
    }
}
//Функція виводу зображення
void cout_image(int** image, int rows, int cols)
{
    cout <<"Малюнок:" <<endl;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            switch(image[i][j])
            {
                case 0: {cout <<" " <<" "; break;}
                case 1: {cout <<"." <<" "; break;}
                case 2: {cout <<":" <<" "; break;}
                case 3: {cout <<"-" <<" "; break;}
                case 4: {cout <<"=" <<" "; break;}
                case 5: {cout <<"+" <<" "; break;}
                case 6: {cout <<"*" <<" "; break;}
                case 7: {cout <<"#" <<" "; break;}
                case 8: {cout <<"%" <<" "; break;}
                case 9: {cout <<"@" <<" "; break;}
            }
        }
        cout <<endl;
    }
}
//Функція виведення інвертованої яскравості
void invert_brightness(int** image, int rows, int cols)
{
    cout <<"Яскравість інвертовано." <<endl;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            cout <<(9-image[i][j]) <<" ";
        }
        cout <<endl;
    }
}
//Функція повороту масива
int** rotateRight(int** image, int rows, int cols)
{
    int** image_rotated = new int*[cols];
    for(int i=0; i<cols; i++)
    {
        image_rotated[i] = new int[rows];
    }
    for(int i=0; i<cols; i++)
    {
        for(int j=0; j<rows; j++)
        {
            image_rotated[i][j]=image[rows-j-1][i];
        }
    }
    return image_rotated;
}
//Функція пошуку мінімальних і максимальних значень яскравості і запамятовування їхніх координат
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    int max=-1;
    int min=10;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(image[i][j]>max)
            {
                max=image[i][j];
                maxRow=i+1;
                maxCol=j+1;
            }
            if(image[i][j]<min)
            {
                min=image[i][j];
                minRow=i+1;
                minCol=j+1;
            }
        }
    }
}
//Функція виводу середньої яскравості і середньої яскравості по рядках
void avarage_brightness(int** image, int rows, int cols)
{
    double* avarage_brightness = new double[rows];
    double avarage_brightness_number=0;
    double avarage_brightness_by_row=0;
    for(int i=0; i<rows; i++)
    {
        avarage_brightness_by_row=0;
        for(int j=0; j<cols; j++)
        {
            avarage_brightness_by_row+=*(image[i]+j);
        }
        avarage_brightness[i]=avarage_brightness_by_row/cols;
    }
    for(int i=0; i<rows; i++)
    {
        avarage_brightness_number+=avarage_brightness[i];
    }
    avarage_brightness_number=avarage_brightness_number/rows;
    cout <<"Середня яскравість: " <<fixed <<setprecision(2) <<avarage_brightness_number <<endl;
    cout <<"Середня по рядках: ";
    for(int i=0; i<rows; i++)
    {
        cout <<fixed <<setprecision(1) <<avarage_brightness[i] <<" ";
    }
    cout <<endl;
    delete[] avarage_brightness;
}
//Функція зміни двох значень одне на одне
void swapPixels(int *a, int *b)
{
    int c= *a;
    *a=*b;
    *b=c;
}
//Функція для відзеркалення масиву
void swap(int** image, int rows, int cols)
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols/2; j++)
        {
            swapPixels(&image[i][j], &image[i][cols-1-j]);
        }
    }
}
int main()
{
    int minRow, minCol, maxRow, maxCol;
    //Введення даних і їхня перевірка
    int rows, cols;
    cout <<"Висота зображення: ";
    if(cin >>rows)
    {
        if(rows<1 || rows>20)
        {
            cout <<"Будь ласка, тут ведіть ціле число від 1 до 20" <<endl;
            return 1;
        }
    } else
    {
        cout <<"Будь ласка, тут ведіть ціле число від 1 до 20" <<endl;
        return 1;
    }
    cout <<"Ширина зображення: ";
    if(cin >>cols)
    {
        if(cols<1 || cols>20)
        {
            cout <<"Будь ласка, тут ведіть ціле число від 1 до 20" <<endl;
            return 1;
        }
    } else
    {
        cout <<"Будь ласка, тут ведіть ціле число від 1 до 20" <<endl;
        return 1;
    }
    //Створюємо масив
    int** image = new int*[rows];
    for(int i=0; i<rows; i++)
    {
        image[i] = new int[cols]{};
    }
    int n;
    cout <<"Яскравість пікселів (0..9): " <<endl;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(cin >>n){image[i][j]=n;}
            else
            {
                cout <<"Будь ласка, тут введіть матрицю чисел висотою " <<rows <<" і шириною " <<cols <<" із чисел від 0 до 9" <<endl;
                return 1;
            }
        }
    }
    //Створення масиву, щоб в нього покласти розвернутий
    int**image_rotated = rotateRight(image, rows, cols);
    int choice;
    do
    {
        cout <<"Оберіть дію:" <<endl;
        cout <<"1-Показати зображення" <<endl;
        cout <<"2-Статистика яскравості" <<endl;
        cout <<"3-Інвертувати яскравість" <<endl;
        cout <<"4-Віддзеркалити по горизонталі" <<endl;
        cout <<"5-Повернути на 90 градусів праворуч" <<endl;
        cout <<"0-Вийти" <<endl;
        cout <<"Ваш вибір дії: ";
        cin >>choice;
        switch(choice)
        {
            case 1:
            {
                cout <<"Зображення 4 x 5: " <<endl;
                cout_brightness(image, rows, cols);
                cout <<" " <<endl;
                cout_image(image, rows, cols);
                break;
            }
            case 2:
            {
                findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
                cout <<"Найтемніший піксель: " <<image[minRow-1][minCol-1] <<" (рядок " <<minRow <<", стовпець " <<minCol <<") " <<endl;
                cout <<"Найсвітліший піксель: " <<image[maxRow-1][maxCol-1] <<" (рядок " <<maxRow <<", стовпець " <<maxCol <<") " <<endl;
                avarage_brightness(image, rows, cols);
                break;
            }
            case 3:
            {
                invert_brightness(image, rows, cols);
                break;
            }
            case 4: 
            {
                cout <<"Зображення віддзеркалено." <<endl;
                cout <<"Початкове:" <<endl;
                cout_brightness(image, rows, cols);
                swap(image, rows, cols);
                cout <<endl;
                cout <<"Результат:" <<endl;
                cout_brightness(image, rows, cols);
                swap(image, rows, cols);
                break;
            }
            case 5:
            {
                cout <<"Зображення повернуто. Нові розміри: " <<cols <<" x " <<rows <<endl;
                cout_brightness(image_rotated, cols, rows);
                break;
            }
            default: 
            {
                if(choice!=0){cout <<"Будь ласка, введіть один із варіантів вибору дії" <<endl;}
            }
        }
    } while(choice!=0);
    //Звільнення памяті
    for(int i=0; i<cols; i++)
    {
        delete[] image_rotated[i];
    }
    delete[] image_rotated;
    for(int i=0; i<rows; i++)
    {
        delete[] image[i];
    }
    delete[] image;
    delete[] image_rotated;
}