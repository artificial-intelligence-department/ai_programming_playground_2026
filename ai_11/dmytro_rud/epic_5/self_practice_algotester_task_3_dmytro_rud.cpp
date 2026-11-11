#include <iostream>
#include <vector>

using namespace std;

vector<int> leader;

int find_leader(int v) {
    if (leader[v] == v) {
        return v;
    }
    return leader[v] = find_leader(leader[v]);
}

int main() {


    int n, m;
    cin >> n >> m;

    leader.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        leader[i] = i;
    }

    int groups = n;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        int main_a = find_leader(a);
        int main_b = find_leader(b);

        if (main_a != main_b) {
            leader[main_b] = main_a;
            groups--;
        }

        cout << groups << "\n";
    }

    return 0;
}
