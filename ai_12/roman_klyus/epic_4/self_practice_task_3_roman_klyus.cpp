#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int *x = new int[n];
    int *y = new int[n];

    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

    int max_x = 0, max_y = 0;
    for (int i=0; i<n; i++) {
        if(x[i] > max_x) max_x = x[i];
        if(y[i] > max_y) max_y = y[i];
    }

    long long res = 0;
    for (int i = 0; i < n; i++) res += (max_x - x[i]) + (max_y - y[i]);
    cout << res << endl;

    delete[] x;
    delete[] y;
}