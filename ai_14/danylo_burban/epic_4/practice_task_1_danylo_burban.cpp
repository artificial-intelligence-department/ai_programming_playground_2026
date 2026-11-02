/*Epic 4 - Практичне завдання 1
Данило Бурбан
ШІ - 14 */
#include <iostream>
#include <limits>

using namespace std;
const char gradient[]=" .:-=+*#%@";
void showImage(int **matrix,int rows,int columns);
void findExtremes(int **matrix, int rows, int columns, int &min_row, int &min_col, int &max_row, int &max_col);
void invert(int **matrix,int rows,int columns);
void swapPixels(int *a, int *b);
void mirror(int **matrix,int rows,int columns);
int** rotateRight(int** matrix, int rows, int cols);
int main(){
    int min_row,max_row,min_col,max_col;
    int rows,cols;
    cout<<"кількість рядків>>";
    if(!(cin>>rows)||rows<1 || rows>20){
        cout<<"Помилка вводу рядків";
        return 1;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<"кількість стовпців>>";
    if(!(cin>>cols)||cols<1 || cols>20){
        cout<<"Помилка вводу стовців";
        return 1;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    int **image= new int*[rows];
    for (int i = 0; i<rows; i++){
        image[i]= new int[cols];
    }
    cout<<"ввід матриці"<<endl;
    for (int i = 0; i<rows;i++){
        for (int j = 0; j<cols;j++){
            if(!(cin>>image[i][j])||image[i][j]<0||image[i][j]>9){
                cout<<"Помилка вводу елемента матриці";

                for (int k = 0; k < rows; k++) {
                    delete[] image[k];
                    image[k] = nullptr;
                }

                 delete[] image;
                 image = nullptr;

                return 1;
                }               
        }
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    int choice;
    do
    {
        cout<<"Меню"<<endl<<"//////////////////////////////////////////"<<endl;
        cout<<"1\t\t Показати зображення"<<endl;
        cout<<"2\t\t Статистика яскравості"<<endl;
        cout<<"3\t\t Інвертувати яскравість"<<endl;
        cout<<"4\t\t Віддзеркалити по горизонталі"<<endl;
        cout<<"5\t\t Повернути на 90 градусів праворуч"<<endl;
        cout<<"0\t\t Вийти"<<endl;
        cout<<"Виберіть пункт меню>>";        
        if(!(cin>>choice)||choice<0 || choice>5){
            cout<<"Помилка вводу опції";
            return 1;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        switch (choice)
        {
        case 1:
            showImage(image,rows,cols);
            break;
        case 2:
            findExtremes(image,rows,cols,min_row,min_col,max_row,max_col);
            break;
        case 3:
            invert(image,rows,cols);
            break;
        case 4:
            mirror(image,rows,cols);
            break;
        case 5: {
            image = rotateRight(image, rows, cols);
            int temp = rows;
            rows = cols;
            cols = temp;
    
            break;
        }
        default:
            break;
        }
        
    } while (choice!=0);
    

    for (int i = 0; i < rows; i++) {
        delete[] image[i];
        image[i] = nullptr; 
    }
    
    delete[] image;
    image = nullptr;
}



void showImage(int **matrix,int rows,int columns){
    for (int i=0; i<rows;i++){
        for (int j=0;j<columns;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    for (int i=0; i<rows;i++){
        for (int j=0;j<columns;j++){
            cout<<gradient[matrix[i][j]];
        }
        cout<<endl;
    }
    cout<<"рядків>>"<<rows<<" стовпців>>"<<columns<<endl;
}
void findExtremes(int **matrix, int rows, int columns, int &min_row, int &min_col, int &max_row, int &max_col) {
    if (rows <= 0 || columns <= 0) return;

    int *firstRow = matrix[0];
    int minVal = *(firstRow + 0);
    int maxVal = *(firstRow + 0);
    
    min_row = 0;
    min_col = 0;
    max_row = 0;
    max_col = 0;

    double sum_of_all = 0.0;

    for (int i = 0; i < rows; i++) {
        int *row = matrix[i];
        double sum_of_row = 0.0;

        for (int j = 0; j < columns; j++) {
            int val = *(row + j);
            
            sum_of_row += val;
            sum_of_all += val;

            
            if (val < minVal) {
                minVal = val;
                min_row = i;
                min_col = j;
            }
            if (val > maxVal) {
                maxVal = val;
                max_row = i;
                max_col = j;
            }
        }

        cout << "Середня яскравість за рядок " << i + 1 << ": " << sum_of_row / columns << endl;
    }

    cout << "Найтемніший піксель: " << minVal
     << " (рядок " << min_row + 1
     << ", стовпець " << min_col + 1 << ")" << endl;

    cout << "Найсвітліший піксель: " << maxVal
     << " (рядок " << max_row + 1
     << ", стовпець " << max_col + 1 << ")" << endl;

    cout << "Середня яскравість: "
     << sum_of_all / (rows * columns) << endl;
}
void invert(int **matrix,int rows,int columns){
    for (int i = 0; i < rows; i++)
    {
       for (int j = 0; j < columns; j++)
        {
            matrix[i][j]=9-matrix[i][j];  
        }
    }
    
}
void swapPixels(int *a, int *b){
    int temp = *a;
    *a=*b;
    *b=temp;
}
void mirror(int **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns / 2; j++) {
            swapPixels(&matrix[i][j], &matrix[i][columns - 1 - j]);
        }
    }
}
int** rotateRight(int** matrix, int rows, int cols){
    int **image= new int*[cols];
    for (int i = 0; i<cols; i++){
        image[i]= new int[rows];
    }
    for (
        int i = 0; i<cols;i++){
        for (int j = 0; j<rows;j++){
            image[i][j]=matrix[rows-1-j][i];
            }
        }
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
        matrix[i]=nullptr; 
    }
    delete[] matrix;
    matrix=nullptr;
    return image;
    }
