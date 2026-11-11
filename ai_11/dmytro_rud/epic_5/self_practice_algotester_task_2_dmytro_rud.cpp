#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y, z;

    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }
};

int main() {


    int n;
    if (!(cin >> n)) return 0;

    int start_sector, end_sector;
    cin >> start_sector >> end_sector;

    if (start_sector == end_sector) {
        cout << 0 << "\n";
        return 0;
    }

    map<pair<Point, Point>, vector<int>> edge_to_triangles;

    for (int i = 1; i <= n; i++) {
        Point p[3];
        for (int k = 0; k < 3; k++) {
            double x, y, z;
            cin >> x >> y >> z;
            p[k].x = llround(x * 1000.0);
            p[k].y = llround(y * 1000.0);
            p[k].z = llround(z * 1000.0);
        }

        pair<Point, Point> edges[3] = {
            {min(p[0], p[1]), max(p[0], p[1])},
            {min(p[1], p[2]), max(p[1], p[2])},
            {min(p[0], p[2]), max(p[0], p[2])}
        };

        for (int e = 0; e < 3; e++) {
            edge_to_triangles[edges[e]].push_back(i);
        }
    }

    vector<vector<int>> graph(n + 1);

    for (auto& item : edge_to_triangles) {
        vector<int>& tris = item.second;
        for (size_t a = 0; a < tris.size(); a++) {
            for (size_t b = a + 1; b < tris.size(); b++) {
                int u = tris[a];
                int v = tris[b];
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }
    }

    vector<int> dist(n + 1, -1);
    queue<int> q;

    dist[start_sector] = 0;
    q.push(start_sector);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == end_sector) {
            break;
        }

        for (int neighbor : graph[current]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[current] + 1;
                q.push(neighbor);
            }
        }
    }

    cout << dist[end_sector] << "\n";

    return 0;
}
