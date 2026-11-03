#include <iostream>
#include <string>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    int a[100][100];
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < m; j++) {
            a[i][j] = row[j] - '0';
        }
    }
    bool allRows = true;
    for (int i = 0; i < n; i++) {
        bool hasOne = false;
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 1) {
                hasOne = true;
            }
        }
        if (!hasOne) {
            allRows = false;
        }
    }
    bool allColumns = true;
    for (int j = 0; j < m; j++) {
        bool hasOne = false;
        for (int i = 0; i < n; i++) {
            if (a[i][j] == 1) {
                hasOne = true;
            }
        }
        if (!hasOne) {
            allColumns = false;
        }
    }
    if (allRows || allColumns) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
