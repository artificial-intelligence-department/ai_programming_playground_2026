/*
Епік 4. Self Practice: Algotester, задача "Замовлення від квітникарів"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;

int main () {

    int n, m;
    cin >> n >> m;

    if (n<1 || n>100 || m<1 || m>100) return 1;

    int sumN[100] = {0};
    int sumM[100] = {0};

    int matrix[n][m];
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {

            cin >> matrix[i][j];

            sumN[i] += matrix[i][j];
            sumM[j] += matrix[i][j];
        }
    }

    int maxSum = 0;
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            int sum = sumN[i] + sumM[j] - matrix[i][j];
            if (sum > maxSum) maxSum = sum;
        }
    }

    cout << maxSum << "\n";

    return 0;
}