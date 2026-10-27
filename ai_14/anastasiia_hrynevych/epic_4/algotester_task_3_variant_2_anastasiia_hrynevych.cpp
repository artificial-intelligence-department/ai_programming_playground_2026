#include <iostream> 
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    int b[m];
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    int unique = 0, same = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                same++;
                break;
            }
        }
    }
    unique = n + m - same;
    cout << same << "\n" << unique;
}