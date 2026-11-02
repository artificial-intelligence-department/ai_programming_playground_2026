#include <iostream>
using namespace::std;
// Дракон і кросворд 0101
int main () {
    int n,m;
    char a[100][100];

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bool duplicate = false;
            for (int k = 0; k < n; k++) {
                if (a[k][j] == a[i][j] && k != i) {
                    duplicate = true;
                    break;
                }
            }
            for (int k = 0; k < m; k++) {
                if (a[i][j] == a[i][k] && k != j) {
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate) {
                cout << a[i][j];
            }
        }
    } 

    return 0;
}