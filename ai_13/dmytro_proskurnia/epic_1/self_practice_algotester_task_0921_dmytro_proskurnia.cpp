#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(X) (X).begin(), (X).end()
#define pb(X) push_back((X))
#define f first
#define s second

using ll = long long;
using vi = vector<int>;
using ii = pair<int, int>;

constexpr int MAX = 2e9+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int a, b; cin >> a >> b;
    if (a > b) swap(a, b);
    if (a+1 >= b) {
        cout << -1;
    } else {
        cout << a+1;
    }

    return 0;
}

