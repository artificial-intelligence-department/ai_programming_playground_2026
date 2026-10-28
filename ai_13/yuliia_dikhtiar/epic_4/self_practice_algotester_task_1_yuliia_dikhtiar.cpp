/*
Назва задачі: Замовлення від квітникарів
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>

using namespace std;
 
int main() {

    int n;
    int m;
    int a[100][100] = {};

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    int sumRows = 0;
    int sumR[100] = {};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sumRows+=a[i][j];
            sumR[i] = sumRows;
        }
        sumRows = 0;
    }

    int sumCols = 0;
    int sumC[100] = {};

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            sumCols+=a[i][j];
            sumC[j] = sumCols;
        }
        sumCols = 0;
    }

    int finalMax = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int sum = sumR[i] + sumC[j] - a[i][j];

            if (sum > finalMax) {
                finalMax = sum;
            }
        }
    }

    cout << finalMax;

    return 0;
}