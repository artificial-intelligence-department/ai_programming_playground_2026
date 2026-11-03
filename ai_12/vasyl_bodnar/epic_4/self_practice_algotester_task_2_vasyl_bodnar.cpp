#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    char **a = new char*[n];
    for (int i = 0; i < n; i++) {
        a[i] = new char[m];
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    int **b = new int*[3333];
    for (int i = 0; i < 3333; i++) {
        b[i] = new int[5];
    }
    int r = 0;
    for (int s = 0; s < n; s += 3) {
        int first = -1, last = -1;
        for (int j = 0; j < m; j++) {
            if (a[s][j] == '1' && a[s + 1][j] == '0' && a[s + 2][j] == '1') {
                b[r][0] = s + 1; b[r][1] = s + 3;
                b[r][2] = j + 1; b[r][3] = j + 1;
                b[r][4] = 1;
                r++;
                if (first < 0) first = j;
                last = j;
            }
        }
        if (first >= 0) {
            b[r][0] = s + 2; b[r][1] = s + 2;
            b[r][2] = first + 1; b[r][3] = last + 1;
            b[r][4] = 0;
            r++;
        }
        for (int j = 0; j < m; j++) {
            if (a[s][j] == '1' && a[s + 1][j] == '0' && a[s + 2][j] == '1') continue;
            int lo = -1, hi = -1;
            for (int k = 0; k < 3; k++) {
                if (a[s + k][j] == '1') {
                    if (lo < 0) lo = k;
                    hi = k;
                }
            }
            if (lo >= 0) {
                b[r][0] = s + lo + 1; b[r][1] = s + hi + 1;
                b[r][2] = j + 1; b[r][3] = j + 1;
                b[r][4] = 1;
                r++;
            }
        }
    }
    cout << r << "\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < 5; j++) {
            cout << b[i][j] << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;
    for (int i = 0; i < 3333; i++) delete[] b[i];
    delete[] b;
    return 0;
}