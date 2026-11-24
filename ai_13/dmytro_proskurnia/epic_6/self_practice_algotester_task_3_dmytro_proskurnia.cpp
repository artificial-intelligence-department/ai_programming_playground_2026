//#1056 - Святковий торт

#include <bits/stdc++.h>

using namespace std;

#define all(X) (X).begin(), (X).end()

using ll = long long;

constexpr ll INF = 1e9+5;

struct edge {
    int u, v;
};

void zBogom(){
    int n, m, target; cin >> n >> m >> target;
    vector<edge> un_edges, edges;
    vector<vector<int>> g(n, vector<int>(n, INF));
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w; u--, v--;
        g[u][v] = min(g[u][v], (w == -1 ? 1 : w));
        g[v][u] = min(g[v][u], (w == -1 ? 1 : w));
        if (w == -1) {
            un_edges.push_back({u, v});
        }
        edges.push_back({u, v});
    }

    for (int i = 0; i < un_edges.size(); i++) {
        vector<int> dist(n, INF);
        dist[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        vector<int> from(n, -1);
        q.push({dist[0], 0});
        while (!q.empty()) {
            auto [w1, u] = q.top();
            q.pop();
            if (w1 > dist[u]) continue;

            for (int v = 0; v < n; v++) {
                if (dist[v] > dist[u] + g[u][v]) {
                    dist[v] = dist[u] + g[u][v];
                    q.push({dist[v], v});
                }
            }
        }
        if (dist[n-1] > target) {
            cout << -1;
            return;
        }
        g[un_edges[i].u][un_edges[i].v] += target - dist[n-1];
        g[un_edges[i].v][un_edges[i].u] += target - dist[n-1];
    }

    vector<int> dist(n, INF);
    dist[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    vector<int> from(n, -1);
    q.push({dist[0], 0});
    while (!q.empty()) {
        auto [w1, u] = q.top();
        q.pop();
        if (w1 > dist[u]) continue;

        for (int v = 0; v < n; v++) {
            if (dist[v] > dist[u] + g[u][v]) {
                dist[v] = dist[u] + g[u][v];
                q.push({dist[v], v});
            }
        }
    }

    if (dist[n-1] != target) {
        cout << -1;
        return;
    }

    for (auto [u, v]:edges) {
        cout << g[u][v] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t; t = 1;
    while(t--){
        zBogom();
        cout << "\n";
    }
    return 0;
}

