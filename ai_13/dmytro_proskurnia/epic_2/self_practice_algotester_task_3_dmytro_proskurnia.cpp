//#0121 Літня школа

#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAX = 2e9+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k; cin >> n >> k;
    int arr[k];
    for (auto& el:arr)
        el = 0;

    for (int i = 0; i < k; i++) {
        if (n <= 0) {
            cout << "Impossible";
            return 0;
        }
        arr[i]++;
        n--;
    }
    for (int i = 0; i < k; i++) {
        if (n <= 0) {
            break;
        }
        arr[i]++;
        n--;
    }
    for (int i = 0; i < k; i++) {
        if (n <= 0) {
            break;
        }
        arr[i]++;
        n--;
    }

    if (n > 0) {
        cout << "Impossible";
        return 0;
    }

    for (auto& el:arr)
        cout << el << " ";

    return 0;
}

