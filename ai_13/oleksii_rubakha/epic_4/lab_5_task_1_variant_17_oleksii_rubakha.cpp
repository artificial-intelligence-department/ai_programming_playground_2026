#include <iostream>
using namespace std;

const int MAX = 100;   // максимальний розмір статичного масиву

// сума елементів підмасиву 3x3, лівий верхній кут якого в (r, c)
int sum3x3(int a[][MAX], int r, int c){
    int s = 0;
    for (int i = r; i < r + 3; i++)
        for (int j = c; j < c + 3; j++)
            s += a[i][j];
    return s;
}

// пошук підмасиву 3x3 з максимальною сумою
// повертає максимальну суму; у br, bc записує координати лівого верхнього кута
// якщо підмасиву 3x3 немає (n < 3 або m < 3), повертає false через found
int findMaxBlock(int a[][MAX], int n, int m, int &br, int &bc, bool &found){
    found = false;
    int best = 0;
    for (int i = 0; i + 3 <= n; i++)          // i + 2 <= n - 1: не виходимо за межі
        for (int j = 0; j + 3 <= m; j++) {
            int s = sum3x3(a, i, j);
            if (!found || s > best) {
                best = s;
                br = i;
                bc = j;
                found = true;
            }
        }
    return best;
}

// друк масиву
void printArray(int a[][MAX], int n, int m){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << a[i][j] << "\t";
        cout << endl;
    }
}

// друк підмасиву 3x3
void printBlock(int a[][MAX], int r, int c){
    for (int i = r; i < r + 3; i++) {
        for (int j = c; j < c + 3; j++)
            cout << a[i][j] << "\t";
        cout << endl;
    }
}

int main(){
    int a[MAX][MAX];
    int n, m;

    cout << "Кількість рядків N (1.." << MAX << "): ";
    cin >> n;
    cout << "Кількість стовпців M (1.." << MAX << "): ";
    cin >> m;
    if (n < 1 || n > MAX || m < 1 || m > MAX) {
        cout << "Некоректні розміри" << endl;
        return 1;
    }

    cout << "Введіть елементи масиву:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    cout << "\nВихідний масив:" << endl;
    printArray(a, n, m);

    int br = 0, bc = 0;
    bool found;
    int best = findMaxBlock(a, n, m, br, bc, found);

    if (!found) {
        cout << "\nМасив менший за 3x3, підмасиву немає" << endl;
        return 0;
    }

    cout << "\nМаксимальна сума підмасиву 3x3: " << best << endl;
    cout << "Лівий верхній кут: рядок " << br + 1 << ", стовпець " << bc + 1 << endl;
    cout << "Підмасив:" << endl;
    printBlock(a, br, bc);

    return 0;
}