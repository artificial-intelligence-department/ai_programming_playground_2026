/*
Повторювані числа в матриці
Лисюк Андріана
ШІ-13
*/

#include <iostream>
#include <algorithm>

using namespace std;

long long** allocate_matrix(int n, int m) {
    long long** a = new long long*[n];
    for (int i = 0; i < n; i++) {
        a[i] = new long long[m];
    }
    return a;
}

void free_matrix(long long** a, int n) {
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    long long** matrix = allocate_matrix(n, m);

    int total_elements = n * m;
    long long* arr = new long long[total_elements];

    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
            arr[index++] = matrix[i][j];
        }
    }

    sort(arr, arr + total_elements);

    int k = 0;
    for (int i = 0; i < total_elements - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            k++;
            i++;
        }
    }

    cout << k << "\n";

    for (int i = 0; i < total_elements - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            cout << arr[i] << " ";
            i++;
        }
    }
    cout << "\n";

    free_matrix(matrix, n);
    delete[] arr;

    return 0;
}
