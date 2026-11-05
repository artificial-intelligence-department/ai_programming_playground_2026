/*
Завдання: Тойлет-мен
*/
#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    long long* c = new long long[m + 1]();

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x <= m) c[x]++;
    }

    long long ans = 0, prod = 1, mod = 1e9 + 7;

    for (int i = 1; i <= m; i++) {
        prod = (prod * c[i]) % mod;
        if (prod == 0) break;
        ans = (ans + prod) % mod;
    }

    cout << ans << "\n";

    delete[] c;
    return 0;
}