#include <iostream>

using namespace std;

const int MAXN = 10;

void createMatrix(int a[][MAXN], int n);
void printMatrix(int a[][MAXN], int n);
void transposeMatrix(int a[][MAXN], int b[][MAXN], int n);
void sumMatrix(int a[][MAXN], int b[][MAXN], int c[][MAXN], int n);

int main(){

    int n;
    cout << "Розмір матриці: ";
    cin >> n;

    if (n > MAXN) n = MAXN;

    int a[MAXN][MAXN];
    int b[MAXN][MAXN];
    int c[MAXN][MAXN];

    createMatrix(a, n);
    printMatrix(a, n);
    cout << endl;
    transposeMatrix(a, b, n);
    printMatrix(b, n);
    cout << endl;
    sumMatrix(a, b, c, n);
    printMatrix(c, n);

    
    return 0;
}


void createMatrix(int a[][MAXN], int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            a[i][j] = rand() % 11;
        }
    }
}

void printMatrix(int a[][MAXN], int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }
}

void transposeMatrix(int a[][MAXN], int b[][MAXN], int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b[i][j] = a[j][i]; 
        }
    }
}

void sumMatrix(int a[][MAXN], int b[][MAXN], int c[][MAXN], int n){
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}