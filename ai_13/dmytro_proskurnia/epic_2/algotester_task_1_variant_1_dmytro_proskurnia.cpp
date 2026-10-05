#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int H, M; cin >> H >> M;
    int h[3], m[3];
    cin >> h[0] >> m[0] >> h[1] >> m[1] >> h[2] >> m[2];

    if (h[0] == 0 || m[0] == 0) {
        H -= h[0], M -= m[0];
    } else {
        cout << "NO";
        return 0;
    }
    if (h[1] == 0 || m[1] == 0) {
        H -= h[1], M -= m[1];
    } else {
        cout << "NO";
        return 0;
    }
    if (h[2] == 0 || m[2] == 0) {
        H -= h[2], M -= m[2];
    } else {
        cout << "NO";
        return 0;
    }

    if (H > 0 && M > 0) {
        cout << "YES";
    } else {
        cout << "NO";
    }


    return 0;
}



