//#0365
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    vi cnt(101, 0);
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        cnt[a]++;
    }
    int ans = 0;
    for (auto el:cnt) {
        if (el > 0) {
            ans++;
        }
    }
    cout << ans;

    return 0;
}

