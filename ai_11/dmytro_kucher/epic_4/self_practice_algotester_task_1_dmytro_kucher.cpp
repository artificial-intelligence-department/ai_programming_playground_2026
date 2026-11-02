/*
Епік 4. Self Practice: Algotester, задача "Портрети"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;

int main () {

    int n, m, k;

    cin >> n >> m >> k;

    if (n<1 || n>1000 || m<1 || m>1000 || k<1 || k>1000) return 1;

    char matrix[n][m];
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            cin >> matrix[i][j];
        }
    }

    int count = 0;
    for (int i = 0; i<n; i++) {
        int r = 0;
        for (int j = 0; j<m; j++) {
            if (matrix[i][j] == '*') {
                r++;
                if (r == k) {
                    count++;
                    r = 0;
                }
            }
        }
        if (r > 0) count++;
    }

    cout << count << "\n";

    return 0;
}