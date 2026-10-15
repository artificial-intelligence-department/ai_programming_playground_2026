#include <iostream>
using namespace std;

int count[3][10001]; 

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int d = 0; d < 3; d++) { 
            int x;
            cin >> x;
            count[d][x]++;
        }
    }

    long long total = 0;

    for (int d = 0; d < 3; d++) {
        int seen = 0, M = 0;
        for (int v = 0; v <= 10000; v++) {
            seen += count[d][v];
            if (seen > n / 2) {
                M = v;
                break;
            }
        }
        for (int v = 0; v <= 10000; v++) {
            int diff = v > M ? v - M : M - v;
            total += static_cast<long long>(count[d][v]) * diff;
        }
    }

    cout << total;
    return 0;
}
