//Проскурня Дмитро ШІ-13

#include <bits/stdc++.h>
using namespace std;
#define int long long

constexpr int MAX = 2e9+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    int arr[n]; for (auto& el:arr) cin >> el;
    int a, b, c; cin >> a >> b >> c;
    int arr_d[n];

    int m = 0;
    for (int i = 0;  i < n; i++) {
        if (arr[i] != a && arr[i] != b && arr[i] != c) {
            arr_d[m] = arr[i];
            m++;
        }
    }
    if (m == 0) m++;
    cout << m-1 << "\n";
    for (int i = 1; i < m; i++) {
        cout << arr_d[i] + arr_d[i-1] << " ";
    }

    return 0;
}

