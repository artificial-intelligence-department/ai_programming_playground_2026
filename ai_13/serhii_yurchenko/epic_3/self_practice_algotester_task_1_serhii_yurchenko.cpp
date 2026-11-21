//matricia
#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, a, b;
        cin >> n >> m >> a >> b;
        int zeros = 0;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            for (char c : s)
                if (c == '0') zeros++;
        }
        int need = (n / a) * (m / b);
        if (zeros >= need) {
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }
    return 0;
}