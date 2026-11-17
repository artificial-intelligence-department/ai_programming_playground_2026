#include <iostream>

using namespace std;


int main() {
    long long n, m, k;
    cin >> n >> m >> k;

    long long common = n + m - k;
    if (common < 1 || common > n || common > m) {
        cout << "NI\n";
        return 0;
    }

    cout << "TAK\n";

    long long total = n * m;
    long long small = 1;
    long long large = total - k + 1;

    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < m; ++j) {
            long long value;

            if (i == j && i < common) {
                value = total - i;
            } else if ((i == 0 && j >= common) ||
                       (j == 0 && i >= common)) {
                value = large++;
            } else {
                value = small++;
            }

            if (j > 0) {
                cout << ' ';
            }
            cout << value;
        }
    }
}