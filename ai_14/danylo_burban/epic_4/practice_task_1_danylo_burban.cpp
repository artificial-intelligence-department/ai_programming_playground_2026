#include <iostream>
#include <limits>

using namespace std;
const char gradient[]=" .:-=+*#%@";
void showImage(int **matrix,int rows,int columns);
void findExtremes(int **matrix, int rows, int columns, int &min_row, int &min_col, int &max_row, int &max_col);
void invert(int **matrix,int rows,int columns);
int main(){
    int min_row,max_row,min_col,max_col;
    int rows,cols;
    cout<<"кількість рядків>>";
    if(!(cin>>rows)||rows<1 || rows>20){
        cout<<"Помилка вводу рядків";
        return 1;
    }
    cout<<"кількість стовпців>>";
    if(!(cin>>cols)||cols<1 || cols>20){
        cout<<"Помилка вводу стовців";
        return 1;
    }
    int **image= new int*[rows];
    for (int i = 0; i<rows; i++){
        image[i]= new int[cols];
    }
    cout<<"ввід матриці"<<endl;
    for (
        int i = 0; i<rows;i++){
        for (int j = 0; j<rows;j++){
            if(!(cin>>image[i][j])||image[i][j]<0||image[i][j]>9){
                cout<<"Помилка вводу елемента матриці";
                return 1;
            }
        }
    }
    findExtremes(image,rows,cols,min_row,min_col,max_row,max_col);
    cout<<"max col and row>>"<<max_col<<" "<<max_row<<" min "<<min_col<<" "<<min_row<<endl;
    showImage(image,rows,cols);
    invert(image,rows,cols);
    showImage(image,rows,cols);

    for (int i = 0; i < rows; i++) {
        delete[] image[i]; 
    }
    delete[] image;
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

    cout << "Середня яскравість за всі: " << sum_of_all / (rows * columns) << endl;
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