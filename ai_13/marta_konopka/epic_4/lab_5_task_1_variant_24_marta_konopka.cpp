// variant 24 
#include<iostream>
using namespace std;

const int MAX_ROWS = 100;
const int MAX_COLS = 100;


int findMaxDiagonal(int arr[MAX_ROWS][MAX_COLS], int n){
    int maxDiagonal = arr[0][0];
    for(int i = 1; i < n; i++){
        if(arr[i][i] > maxDiagonal){
            maxDiagonal = arr[i][i];
        }
    }
    return maxDiagonal;
}
int countElement(int arr[MAX_ROWS][MAX_COLS], int rows, int cols,int value){
    int count = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
        if(arr[i][j] > value){
            count++;
        }
    }
}
return count;
}

int main(){
    int rows, cols;

    cout << "Введіть кількість рядків (до 100): ";
    cin >> rows;
    cout << "Введіть кількість стовпців (до 100): ";
    cin >> cols;

    if(rows <= 0 || rows > MAX_ROWS || cols <= 0 || cols > MAX_COLS){
        cout << "Помилка. Розміри мають бути в межах від 1 до 100" << endl;
        return 1;
    }
    int arr[MAX_ROWS][MAX_COLS];

    cout << "Введіть елементи масиву: " << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cin >> arr[i][j];
    }

}
cout << "Матриця елементів масиву: " << endl;
for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << arr[i][j] << " "; 
    }
    cout << endl;
}

int diagonalSize;
if(rows < cols) {
    diagonalSize = rows;

}
else if(cols < rows){
    diagonalSize = cols;

}
else{
    diagonalSize = rows;
}

int maxDiagonal = findMaxDiagonal(arr,diagonalSize);
int resultCount = countElement(arr, rows, cols, maxDiagonal);

cout << "Максимальний елемент на головній діагоналі: " << maxDiagonal << endl;
cout << "Кількість елементів, більших за будь-який елемент діагоналі: " << resultCount << endl;

return 0;
}
