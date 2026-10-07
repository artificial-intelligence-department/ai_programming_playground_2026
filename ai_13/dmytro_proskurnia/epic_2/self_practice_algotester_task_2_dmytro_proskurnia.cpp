//#0114 Тренер слонів

#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAX = 2e9+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    int arr[n];
    for (auto& el:arr)
        cin >> el;

    int min_el = MAX, max_el = -MAX;
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_el) {
            min_el = arr[i];
        }
        if (arr[i] > max_el) {
            max_el = arr[i];
        }
    }

    cout << max_el-min_el;

    return 0;
}

