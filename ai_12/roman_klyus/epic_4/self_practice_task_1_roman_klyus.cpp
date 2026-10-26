#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int k = sqrt(n);

    char **matrix = new char*[k];

    for (int i = 0; i < k; i++) {
        matrix[i] = new char[k];
    }

    int idx = 0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            matrix[i][j] = s[idx++];
        }
    }

    for (int sum = 0; sum <= 2 * (k - 1); sum++) {
        for (int i = 0; i < k; i++) {
            int j = sum - i;
            if (j >= 0 && j < k) cout << matrix[i][j];
        }
    }

    for (int i = 0; i < k; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}