//Pifrahunok holosiv
#include <iostream>
using namespace std;

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;

    long long sum = 0;
    int cnt = 1;

    for (int i = 0; i < m; i++) {
        long long a;
        cin >> a;
        if (sum + a > k) {
            cnt++;
            sum = a;
        } else {
            sum = sum + a;
        }
    }

    if (cnt > n) {
        cout << -1 << endl;
    } else {
        cout << n - cnt << endl;
    }
    return 0;
}