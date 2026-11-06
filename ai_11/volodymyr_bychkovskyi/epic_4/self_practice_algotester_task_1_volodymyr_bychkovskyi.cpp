/*
Назва: Усе погано
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
using namespace std;

int main(){
    int rows;
    cin >> rows;
    int cols;
    cin >> cols;
    char** arr = new char* [rows];

    for(int i = 0; i<rows; i++){
        arr[i] = new char [cols];
    }
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            cin >> arr[i][j];
        }
    }
    int rowsRes = 0;
    for(int i = 0; i<rows; i++){
        int a = 0;
        for(int j = 0; j<cols; j++){
            if (arr[i][j]=='1' && a==0){
                a++;
            }
        }
        rowsRes += a;
    }
    int colsRes = 0;
    for(int j = 0; j<cols; j++){
        int b = 0;
        for(int i = 0; i<rows; i++){
            if (arr[i][j]=='1' && b==0){
                b++;
            }
        }
        colsRes += b;
    }
    if(colsRes==cols||rowsRes==rows){
        cout << "YES";
    }
    else{
        cout << "NO";
    
    }
    for(int i = 0; i < rows; i++){
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
    
}
