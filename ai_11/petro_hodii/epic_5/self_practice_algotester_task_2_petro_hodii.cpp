#include <iostream>

using namespace std;

int parent[100005];
int rank_arr[100005];
int components;

int find_root(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_root(parent[v]);
}

void unite(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a != b) {
        if (rank_arr[a] < rank_arr[b]) {
            int temp = a;
            a = b;
            b = temp;
        }
        parent[b] = a;
        if (rank_arr[a] == rank_arr[b]) {
            rank_arr[a]++;
        }
        components--;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m,u,v;
    if (!(cin >> n >> m)) return 0;

    components = n;
    
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        rank_arr[i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        unite(u, v);
        cout << components << endl;
    }

    return 0;
}
