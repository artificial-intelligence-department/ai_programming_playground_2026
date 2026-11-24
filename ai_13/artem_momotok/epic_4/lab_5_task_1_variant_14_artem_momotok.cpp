/*
    Lab 5v14, Момоток Артем, ШІ-13
*/
#include <iostream>
   
using namespace std;
    
const int MAXN = 10; // максимальний розмір масиву
    
// Введення розмірності з перевіркою
int inputSize() {
    
    int n;
    do {
        cout << "Введіть розмір матриці n (1.." << MAXN << "): ";
        cin >> n;
    } while (n < 1 || n > MAXN);
    return n;
}
    
// Введення елементів масиву з клавіатури одним рядком (n*n чисел через пробіл, рядок за рядком)
void inputMatrix(int a[][MAXN], int n) {
    cout << "Введіть " << n * n << " елементів матриці через пробіл (по рядках): ";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
}
    
// Виведення масиву на екран
void printMatrix(int a[][MAXN], int n) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}
    
// Максимальний елемент серед елементів обох діагоналей
int maxOnDiagonals(int a[][MAXN], int n) {
    int mx = a[0][0];
    for (int i = 0; i < n; i++)
    {
        if (a[i][i] > mx)
            mx = a[i][i];             // головна діагональ
        if (a[i][n - 1 - i] > mx)
            mx = a[i][n - 1 - i];     // бічна діагональ
    }
    return mx;
}
    
// Перевірка стовпця: чи перший елемент більший за всі елементи діагоналей
bool isGoodColumn(int a[][MAXN], int n, int col, int maxDiag) {
    return a[0][col] > maxDiag;
}
    
// Добуток елементів одного стовпця
long long columnProduct(int a[][MAXN], int n, int col) {
    long long p = 1;
    for (int i = 0; i < n; i++)
        p *= a[i][col];
    return p;
}
    
// Добуток усіх підходящих стовпців. Повертає кількість знайдених стовпців, результат - через параметр result.
int productOfGoodColumns(int a[][MAXN], int n, long long &result) {
    int maxDiag = maxOnDiagonals(a, n);
    int count = 0;
    result = 1;
    
    for (int j = 0; j < n; j++) {
        if (isGoodColumn(a, n, j, maxDiag)) {
            long long p = columnProduct(a, n, j);
            cout << "Стовпець " << j + 1 << " підходить, добуток його елементів = "
                << p << endl;
            result *= p;
            count++;
        }
    }
    return count;
}
    
int main() {
    int a[MAXN][MAXN];
    int n = inputSize();
    
    inputMatrix(a, n);
    
    cout << "\nМасив:\n";
    printMatrix(a, n);
    
    long long result;
    int count = productOfGoodColumns(a, n, result);
    
    if (count == 0)
        cout << "Підходящих стовпців немає." << endl;
    else
        cout << "\nЗагальний добуток підходящих стовпців = " << result << endl;
    
    return 0;
}
       