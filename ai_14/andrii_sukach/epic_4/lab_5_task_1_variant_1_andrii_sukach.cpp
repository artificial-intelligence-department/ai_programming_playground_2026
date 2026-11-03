/*Лабораторна робота 5 варіант 17
Ім'я: Сукач Андрій
Група: ШІ-14*/
#include <iostream>

using namespace std;

int matrixSum(int a[][100], int r, int c);

int main() {
    int n, m;
    int maxSum = -999999999;
    int BestRow = 0, BestCol = 0;
    
    cin >> n >> m;
    if (n < 3 || m < 3) {
        cout << "Мінімум 3x3" << endl;
        return 1;
    }
    
    int a[100][100];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    
    for (int r = 0; r <= n - 3; r++) {
        for (int c = 0; c <= m - 3; c++) {
            int sum = matrixSum(a, r, c);
            if (sum > maxSum) {
                maxSum = sum;
                BestRow = r;
                BestCol = c;
            }
        }
    }
    
    cout << "Максимальна сума: " << maxSum << endl;

    return 0;
}

int matrixSum(int a[][100], int r, int c) {
    int sum = 0;
    
    // Проходимося тільки по блоку 3х3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += a[r + i][c + j];
        }
    }
    
    return sum;
}