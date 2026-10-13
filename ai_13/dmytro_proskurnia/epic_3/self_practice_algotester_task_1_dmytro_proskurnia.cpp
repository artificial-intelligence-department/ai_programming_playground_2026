//#0021
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    int cnt = 0;
    vi m{500, 200, 100, 50, 20, 10, 5, 2, 1};

    while (n) {
        for (auto el:m) {
            if (n-el>=0) {
                cnt++;
                n-=el;
                break;
            }
        }
    }
    cout << cnt;

    return 0;
}

