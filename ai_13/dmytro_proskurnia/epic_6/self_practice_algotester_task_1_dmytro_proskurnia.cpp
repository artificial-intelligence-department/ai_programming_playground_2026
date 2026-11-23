//#2292 - Найменше число

#include <bits/stdc++.h>

using namespace std;

#define all(X) (X).begin(), (X).end()
#define pb(X) push_back((X))

constexpr int MAX = 2e9+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string n; cin >> n;
    int k; cin >> k;
    k = min(k, (int)n.size()-1);
    int ans = MAX;
    for (int i = 0; i < (1 << n.size()); i++) {
        if (__builtin_popcountll(i) > k)
            continue;
        string res;
        for (int j = 0; j < n.size(); j++) {
            if ((i & (1 << j)) == 0) {
                res.pb(n[j]);
            }
        }

        if (res[0] != '0') {
            ans = min(ans, (int)stoi(res));
        }
    }

    cout << ans;

    return 0;
}


