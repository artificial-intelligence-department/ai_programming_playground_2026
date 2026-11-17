//#0009 - Roads and Cities

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(X) (X).begin(), (X).end()
#define pb(X) push_back((X))

using ll = long long;
using vi = vector<int>;
using ii = pair<int, int>;

constexpr int MAX = 2e9+5;

class UnionFind {
private:
    vi p, rank;
    int conn_comp;

public:
    UnionFind(int n) {
        conn_comp = n;
        p.assign(n, 0);
        rank.assign(n, 0);
        for (int i = 0; i < n; i++) p[i] = i;
    }

    int find(int i) {return p[i] == i ? i : (p[i] = find(p[i]));}
    int count_comp() {return conn_comp;}
    void join(int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return;
        conn_comp--;
        if (rank[i] > rank[j]) swap(i, j);
        if (rank[i] == rank[j]) rank[j]++;
        p[i] = j;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m; cin >> n >> m;
    UnionFind uf(n);
    while (m--) {
        int i, j; cin >> i >> j;
        i--, j--;
        uf.join(i, j);
        cout << uf.count_comp() << "\n";
    }

    return 0;
}
