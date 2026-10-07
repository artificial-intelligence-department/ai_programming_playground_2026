//#0182 Зуби

#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAX = 2e9+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k; cin >> n >> k;
    int arr[n];
    for (auto& el:arr)
        cin >> el;
    int ans = 0;
    int curr = 0;
    for (auto el:arr) {
        if (el >= k) {
            curr++;
            if (curr > ans)
                ans = curr;
        } else {
            curr = 0;
        }
    }

    cout << ans;

    return 0;
}

