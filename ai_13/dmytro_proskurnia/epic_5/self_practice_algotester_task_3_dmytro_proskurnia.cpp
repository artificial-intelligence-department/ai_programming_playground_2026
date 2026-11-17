//#1684 - Dangerous friends

#include <bits/stdc++.h>

using namespace std;

#define all(X) (X).begin(), (X).end()
#define pb(X) push_back((X))

using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vpi = vector<pi>;
using vpll = vector<pll>;

constexpr ll INF = 2e9+5;

vi p, rang, seek, sz;
void init(int n) {
    p.resize(n, 0); iota(all(p), 0);
    rang.resize(n, 0);
    seek.resize(n, 0);
}

int find(int i) {return i == p[i] ? i : p[i] = find(p[i]);}
bool isSeek(int i) {return seek[find(i)];}
int siz(int i) {return sz[find(i)];}

void unite(int i, int j) {
    i = find(i), j = find(j);
    if (i == j) return;
    if (rang[i] > rang[j]) swap(i, j);
    if (rang[i] == rang[j]) rang[j]++;
    p[i] = j;
}

void zBogom(){
    int n, m, k; cin >> n >> m >> k;
    init(n);
    vi you;
    while (m--) {
        int u, v; cin >> u >> v; u--, v--;
        if (u == 0) {
            you.pb(v);
            continue;
        }
        if (v == 0) {
            you.pb(u);
            continue;
        }
        unite(u, v);
    }
    for (int i = 0; i < k; i++) {
        int u; cin >> u; u--;
        seek[find(u)] = 1;
    }

    vi ch(n, 0);
    vector<int> unf;
    for (auto el:you) {
        if (isSeek(el)) {
            unf.pb(el);
        }
    }

    sort(all(unf));
    unf.erase(unique(all(unf)), unf.end());
    cout << unf.size() << "\n";
    for (auto el:unf) cout << el+1 << " ";



}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t; t = 1;
    while(t--){
        zBogom();
    }
    return 0;
}


