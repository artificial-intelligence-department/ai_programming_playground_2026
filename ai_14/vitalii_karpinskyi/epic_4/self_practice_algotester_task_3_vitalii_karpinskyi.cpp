/*
Задача: Замовлення від квітникарів
Карпінський Віталій
ШІ-14
*/
#include <iostream> 

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int **matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[m];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }
    int sumRow[101] = {0};
    int maxRow = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sumRow[i] += matrix[i][j];
        }
        if (maxRow < sumRow[i]) {
            maxRow = sumRow[i];
        }
    }

    int sumCol[101] = {0};
    int maxCol = 0;
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            sumCol[j] += matrix[i][j];
        }
        if (maxCol < sumCol[j]) {
            maxCol = sumCol[j];
        }
    }
    int answer = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (answer < sumRow[i] + sumCol[j] - matrix[i][j]) {
                answer = sumRow[i] + sumCol[j] - matrix[i][j];
            }
        }
    }
    cout << answer;

    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
    return 0;
}