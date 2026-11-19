#include <iostream>

using namespace std;

int find(int vertex, int *vertices) {
    int parent = vertices[vertex];
    if (parent == vertex) { return parent; }
    return find(parent, vertices);
}

bool isUnite(int a, int b, int *vertices) {
    int a_parent = find(a, vertices);
    int b_parent = find(b, vertices);

    if (a_parent != b_parent) {
        vertices[b_parent] = a_parent;
        return true;
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    int vertices[100000];
    int edges[100000][2];
    int a, b;

    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        edges[i][0] = a;
        edges[i][1] = b;
        vertices[a] = a;
        vertices[b] = b;
    }

    int component = n;
    for (int i = 0; i < m; ++i) {
        if (isUnite(edges[i][0], edges[i][1], vertices)) {
            component--;
        }
        cout << component << endl;
    }

    return 0;
}