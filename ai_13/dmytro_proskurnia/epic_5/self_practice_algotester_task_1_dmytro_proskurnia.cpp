//#1161 - Trilandia

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(X) (X).begin(), (X).end()
#define pb(X) push_back((X))

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;

constexpr int MAX = 2e9+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    int s, f; cin >> s >> f; s--, f--;
    map<pair<string, string>, vector<int>> m;
    vector<vector<int>> g(n);
    string tr; getline(cin, tr);
    for (int i = 0; i < n; i++) {
        string i1, i2, i3;
        getline(cin, i1);
        getline(cin, i2);
        getline(cin, i3);
        if (i1 > i2) swap(i1, i2);
        if (i2 > i3) swap(i2, i3);
        if (i1 > i2) swap(i1, i2);
        m[{i1, i2}].push_back(i);
        m[{i1, i3}].push_back(i);
        m[{i2, i3}].push_back(i);
    }

    for (auto &[a, b]:m) {
        for (int i = 0; i < b.size(); i++) {
            for (int j = 0; j < b.size(); j++) {
                if (i == j) continue;
                g[b[i]].push_back(b[j]);
            }
        }
    }

    vi dist(n, -1);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int from = q.front();
        q.pop();
        for (auto &to:g[from]) {
            if (dist[to] == -1) {
                dist[to] = dist[from]+1;
                q.push(to);
            }
        }
    }

    cout << dist[f];


    return 0;
}


