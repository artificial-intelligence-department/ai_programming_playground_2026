#include <iostream>
#include <algorithm>
using namespace std;

static int a[1000][1000];
int rowMin[1000];
int colMax[1000];
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            if (j == 0) {
                rowMin[i] = a[i][j];
            } else {
                rowMin[i] = min(rowMin[i], a[i][j]);
            }
            if (i == 0) {
                colMax[j] = a[i][j];
            } else {
                colMax[j] = max(colMax[j], a[i][j]);
            }
        }
    }
    int bestRow = -1;
    for (int i = 0; i < n; i++) {
        bool valid = true;
        for (int j = 0; j < m; j++) {
            if (a[i][j] != colMax[j]) {
                valid = false;
                break;
            }
        }
        if (valid) {
            bestRow = i + 1;
            break;
        }
    }
    int bestCol = -1;
    for (int j = 0; j < m; j++) {
        bool valid = true;
        for (int i = 0; i < n; i++) {
            if (a[i][j] != rowMin[i]) {
                valid = false;
                break;
            }
        }
        if (valid) {
            bestCol = j + 1;
            break;
        }
    }
    cout << bestRow << endl;
    cout << bestCol << endl;
    return 0;
}