/*
Автор: Вероніка Третяк
Задача: Лабораторна робота  №5
Група: ШІ-13
*/
#include <iostream>

using namespace std;

int** Matrix(int n);
void showMatrix(int** matrix, int n);
int** Transp(int** matrix, int n);
bool Symmetric(int** matrix, int** transp, int n);
void Delete(int** &matrix, int n);

int main(){
 int n;
 if(!(cin >> n) || n < 1 || n > 100){
    cout << "Помилка: Введіть число від 1 до 100" << endl;
    return 1;
 }
 int** matrix = Matrix(n);
 for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
        if(!(cin >> matrix[i][j])){
            cout << "Помилка: Введіть ціле число." << endl;
            Delete(matrix, n);
            return 1;
        }
    }
 }
 cout << "Початкова матриця: " << endl;
 showMatrix(matrix, n);
 int** transp = Transp(matrix, n);
 cout << "Транспонована матриця: " << endl;
 showMatrix(transp, n);

 if(Symmetric(matrix, transp, n)){
    cout << "Матриця симетрична!" << endl;
 }
 else{
    cout << "Матриця не симетрична!" << endl;
 }
 Delete(matrix, n);
 Delete(transp, n);
 return 0;
}
int** Matrix(int n){
    int** matrix = new int*[n];
    for(int i = 0; i < n; i++){
        matrix[i] = new int[n];
    }
    return matrix;
}
void showMatrix(int** matrix, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
int** Transp(int** matrix, int n){
    int** result = Matrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}
bool Symmetric(int** matrix, int** transp, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(matrix[i][j] != transp[i][j]){
                return false;
            }
        }
    }
    return true;
}
void Delete(int** &matrix, int n){
    for(int i = 0; i < n; i++){
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
   delete[] matrix;
   matrix = nullptr;

}
