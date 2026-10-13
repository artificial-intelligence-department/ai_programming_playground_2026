//#0483
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s; cin >> s;
    int x, y; cin >> x >> y;
    int cn_x = 0, cn_y = 0;
    for (auto c:s) {
        if (c == 'R')
            cn_x++;
        else
            cn_y++;
    }

    cout << (cn_x >= x && cn_y >= y ? "YES" : "NO");

    return 0;
}

