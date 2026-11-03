#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int** matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }

    // Масив для збереження максимумів у кожному стовпці
    int* colMax = new int[m];

    // Шукаємо максимум для кожного стовпця j
    for (int j = 0; j < m; ++j) {
        colMax[j] = matrix[0][j];
        for (int i = 1; i < n; ++i) {
            if (matrix[i][j] > colMax[j]) {
                colMax[j] = matrix[i][j];
            }
        }
    }

    //найменше значення серед знайдених максимумів
    int result = colMax[0];
    for (int j = 1; j < m; ++j) {
        if (colMax[j] < result) {
            result = colMax[j];
        }
    }

    cout << result << "\n";

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] colMax;

    return 0;
}