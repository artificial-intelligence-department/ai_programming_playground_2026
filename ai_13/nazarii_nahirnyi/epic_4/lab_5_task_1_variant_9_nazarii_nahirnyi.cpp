/*
Lab 5 task 1, Нагірний Назарій, ШІ-13, Варіант № 9
*/
#include <iostream>
using namespace std;

int sum(int m, int a[100][100]) {
    int s = 0;
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < i; j++) {
            s += a[i][j];
        }
    }
    return s;
}

int main() {
    int n, m;
    cout << "Введіть N та M: ";
    cin >> n >> m;

    int a[100][100];
    int max_sum;

    for (int k = 0; k < n; k++) {
        cout << "Матриця #" << k + 1 << ":\n";
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
            }
        }

        int current_sum = sum(m, a);
        cout << "Сума нижче діагоналі: " << current_sum << "\n";

        if (k == 0 || current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    cout << "Максимальна сума: " << max_sum << "\n";

    return 0;
}