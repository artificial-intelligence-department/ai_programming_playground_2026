//Проскурня Дмитро ШІ-13
//#0671 Голодна змія

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(X) (X).begin(), (X).end()
using vi = vector<int>;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    int m; cin >> m;
    vi arr(n); for (auto& el:arr) cin >> el;
    int ans = 0;
    for (int i = 0; i < (1 << n); i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                sum += arr[j];
            }
        }
        if (sum == m) {
            ans++;
        }
    }
    cout << ans;

    return 0;
}

