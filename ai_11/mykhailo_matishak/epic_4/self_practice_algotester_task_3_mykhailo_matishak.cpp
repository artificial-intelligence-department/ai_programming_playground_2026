#include <iostream>
using namespace std;

long long t[100000];
int n, m;

// додає d до елемента з номером i
void add(int i, long long d) {
    for (; i <= n; i += i & (-i)) {
        t[i] += d;
    }
}
long long sum(int i) {
    long long s = 0;
    for (; i > 0; i -= i & (-i)) {
        s += t[i];
    }
    return s;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        add(i, x);
    }

    for (int k = 0; k < m; k++) {
        int type;
        cin >> type;

        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << sum(r) - sum(l - 1) << "\n";
        } else {
            int i;
            long long d;
            cin >> i >> d;
            add(i, d);
        }
    }

    return 0;
}