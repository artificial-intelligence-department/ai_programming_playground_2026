/* 
Епік 4. lab_5_task_1_variant_4
Авторка: Софія Ліс
Група: ші-11
*/
#include <iostream>

using namespace std;

    const int N = 100;
    const int M = 100;

int scalarProduct(int (*arr)[M], int m, int a, int b ) {
    int scalar = 0;
    for(int j = 0; j < m; j++) {
        scalar += arr[a][j] * arr[b][j];
    }
    return scalar;
}

bool isOrthonormal(int (*arr)[M], int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(i == j) {
                if(scalarProduct(arr, m, i, j) != 1) {
                    return false;
                }

            }

            else {
                if(scalarProduct(arr, m, i, j) != 0) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

int main() {
    int n, m;

    cout << "Введіть кількість рядків матриці: "; 
    cin >> n;
    cout << "Введіть кількість стовпців матриці: ";
    cin >> m;

    int matrix[N][M];
    cout << "Введіть елементи матриці: ";
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        } 
    }   

    if(isOrthonormal(matrix, n, m) == false) {
        cout << "Матриця не є ортонормованою" << endl;
    }
    else {
        cout << "Матриця є ортонормованою!" << endl;
    }

    return 0;
}