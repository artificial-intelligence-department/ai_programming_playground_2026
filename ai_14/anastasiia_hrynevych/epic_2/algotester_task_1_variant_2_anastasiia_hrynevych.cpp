#include <iostream>
using namespace std;

long long findmax(long long a, long long b, long long c, long long d) {
    long long max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    if (d > max) max = d;
    return max;
}
long long findmin(long long a, long long b, long long c, long long d) {
    long long min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    if (d < min) min = d;
    return min;
}

int main() {
    long long h[4] = {0, 0, 0, 0};
    cin >> h[0] >> h[1] >> h[2] >> h[3];
    long long d[4] = {0, 0, 0, 0};
    cin >> d[0] >> d[1] >> d[2] >> d[3];
    for (int i = 0; i < 4; i++) {
        if (d[i] > h[i]) {
            cout << "ERROR" << endl;
            return 0;
        }
    }
    for (int i = 0; i < 4; i++) {
    h[i] = h[i] - d[i];
    if (findmax(h[0], h[1], h[2], h[3]) >= 2*findmin(h[0], h[1], h[2], h[3])) {
        cout << "NO" << endl;
        return 0;
    }
    else
    if ( findmin(h[0], h[1], h[2], h[3]) > 0) {
        if (i != 3) continue;
        else { cout << "YES" << endl;
        return 0; }
    }
    else { cout << "NO" << endl;
    return 0; }
}
}
