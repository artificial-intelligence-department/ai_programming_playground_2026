#include <iostream>
#include <vector>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    long long cap;
    long long flow;
    int rev;
};

vector<vector<Edge>> adj;
vector<int> level;
vector<int> ptr;

void add_edge(int from, int to, long long cap) {
    adj[from].push_back({ to, cap, 0, (int)adj[to].size() });
    adj[to].push_back({ from, 0, 0, (int)adj[from].size() - 1 });
}

// Самописний BFS з використанням звичайного вектора як черги
bool bfs(int s, int t, int num_vertices) {
    for (int i = 0; i < num_vertices; ++i) {
        level[i] = -1;
    }
    level[s] = 0;

    vector<int> q;
    q.push_back(s);

    int head = 0;
    while (head < (int)q.size()) {
        int v = q[head++];
        for (size_t i = 0; i < adj[v].size(); ++i) {
            Edge& edge = adj[v][i];
            if (edge.cap - edge.flow > 0 && level[edge.to] == -1) {
                level[edge.to] = level[v] + 1;
                q.push_back(edge.to);
            }
        }
    }
    return level[t] != -1;
}

long long dfs(int v, int t, long long pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;

    for (int& cid = ptr[v]; cid < (int)adj[v].size(); ++cid) {
        Edge& edge = adj[v][cid];
        int tr = edge.to;

        if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0) continue;

        // Власна заміна для std::min
        long long current_min = (pushed < edge.cap - edge.flow) ? pushed : (edge.cap - edge.flow);

        long long tr_pushed = dfs(tr, t, current_min);
        if (tr_pushed == 0) continue;

        edge.flow += tr_pushed;
        adj[tr][edge.rev].flow -= tr_pushed;
        return tr_pushed;
    }
    return 0;
}

long long dinic(int s, int t, int num_vertices) {
    long long flow = 0;
    while (bfs(s, t, num_vertices)) {
        for (int i = 0; i < num_vertices; ++i) {
            ptr[i] = 0;
        }
        while (long long pushed = dfs(s, t, INF)) {
            flow += pushed;
        }
    }
    return flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<long long>> A(n, vector<long long>(m));
    long long total_sum = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> A[i][j];
            total_sum += A[i][j];
        }
    }

    int source = n * m;
    int sink = n * m + 1;
    int num_vertices = n * m + 2;

    adj.resize(num_vertices);
    level.resize(num_vertices);
    ptr.resize(num_vertices);

    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = i * m + j;

            if ((i + j) % 2 == 0) {
                add_edge(source, u, A[i][j]);

                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d];
                    int nj = j + dy[d];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                        int v = ni * m + nj;
                        add_edge(u, v, INF);
                    }
                }
            }
            else {
                add_edge(u, sink, A[i][j]);
            }
        }
    }

    long long max_flow = dinic(source, sink, num_vertices);
    long long max_independent_sum = total_sum - max_flow;

    cout << max_independent_sum << "\n";

    return 0;
}