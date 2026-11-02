/*
Задача: Симетрична матриця
Карпінський Віталій
ШІ-14
*/
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    char **matrix = new char*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new char[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    bool sym = true;
    for (int i = 0; i < n; i++) {
        if (!sym) {
            break;
        }
        for (int j = 0; j < n; j++) {
            if (i == j) {
                
            } else if (matrix[i][j] != matrix[j][i]) {
                sym = false;
                break;
            }
        }
    }
    if (sym) cout << "Yes";
    else cout << "No";
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;


    return 0;
}