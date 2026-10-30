/*
Задача: Лабораторна задача №5 варіант 25
Виконав : Андрій Шикоряк ШІ-13
*/

#include <iostream>
using namespace std;
void FromOneToMatrix(int a[],int rows,int cols){
    int **matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    int index_a = 0;
    int current_row = 0;
    for (int i = 0; i < rows; i++) {
        for(int j = 0;j <cols ;j++){
            matrix[i][j] = a[index_a];
            index_a++;
        }
        
    }

    for (int i = 0; i < rows; i++) {
        for(int j = 0;j < cols;j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    delete[] matrix;
}
int main()
{
    int rows,cols;
    cout << "Введіть кількість рядків: ";
    cin >> rows;
    cout << "Введіть кількість стовпців: ";
    cin >> cols;
    int total_elements = rows*cols;
    int A[total_elements] = {0};
    cout << "Введіть елементи масиву: ";
    for (int i = 0; i < total_elements; i++) {
        cin >> A[i];
    }
    FromOneToMatrix(A,rows,cols);
    return 0;
}