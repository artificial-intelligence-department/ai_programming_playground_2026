#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i%2 == 0) {
                if (j%4 == 0 || j%4 == 1) cout << "x";
                else cout << "o";
            }
            else {
                if (j%4 == 0 || j%4 == 1) cout << "o";
                else cout << "x";
            }
            if (j == m - 1) cout << "\n";
        }
    }
}