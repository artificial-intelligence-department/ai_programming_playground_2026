#include <iostream>
using namespace::std;
// Задача 2501
int main () {
    int matrix[1000][1000];
    int n;
    char digit;
    cin >> n;
    bool Symmetric = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> digit;
            matrix[i][j] = digit - '0';
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1 && matrix[j][i] != 1) {
                Symmetric = false;
            }
        }
    }
    if (Symmetric) {
        cout << "Yes";
    } else {
        cout << "No";
    }
    
    return 0;
}