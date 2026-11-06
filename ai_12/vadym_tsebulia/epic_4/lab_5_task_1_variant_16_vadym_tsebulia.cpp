/*
Лабораторна робота №5, Завдання №1, Варіант №16.
Цебуля Вадим
ШІ-12
*/
#include <iostream>
#include <climits>
using namespace std;

int **allocateMatrix(int n){
        int **a = new int*[n];
        for (int i = 0; i < n; i++){
                a[i] = new int[n];
        }
        return a;
}

void freeMatrix(int **a, int n){
        for (int i = 0; i < n; i++){
                delete[] a[i];
        }
        delete[] a;
}

void printMatrix(int **a, int n){
        for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                        cout << a[i][j] << " ";
                }
                cout << endl;
        }
}

bool findNextinColumn(int **a, int n, int col, int prev, int &result){
        int minvalue;
        bool found = false;
        for (int i = 0; i < n; i++){
                if (a[i][col] > prev){
                        if (!found || a[i][col] < minvalue){
                                minvalue = a[i][col];
                                found = true;
                        }
                }
        }
        if (found){
                result = minvalue;
                return true;
        }
        return false;
}

bool canArrange(int **a, int n){
        int prev = INT_MIN;
        for (int col = n - 1; col >= 0; col--){
                int next;
                if (!findNextinColumn(a, n, col, prev, next)) return false;
                prev = next;
        }
        return true;
}

int main(){
        int n;
        cout << "Введіть розмір матриці: ";
        if (!(cin >> n) || n < 1){
                cout << "Помилка: введено некоректне значення розміру матриці." << endl;
                return 1;
        }

        int **a = allocateMatrix(n);

        cout << "Введіть елементи матриці:" << endl;
        for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                        if (!(cin >> a[i][j])){
                                cout << "Помилка: введено некоректне значення елемента матриці." << endl;
                                freeMatrix(a, n);
                                return 1;
                        }
                }
        }

        cout << "Введена матриця:" << endl;
        printMatrix(a, n);

        cout << "Результат: " << (canArrange(a, n) ? "Так" : "Ні") << endl;
        freeMatrix(a, n);
        return 0;
}