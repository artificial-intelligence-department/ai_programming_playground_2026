#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n, min = 10000, minq = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        int d = a * a + b * b;
        if (d < min) { min = d; minq = 1; }
        else if (d == min) minq++;
    }
    cout << minq << endl;
}