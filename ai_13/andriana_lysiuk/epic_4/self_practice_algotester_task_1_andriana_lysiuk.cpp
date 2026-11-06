/*
Велике чаювання
Лисюк Андріана
ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int a[101], b[101];
    int group[101];
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        group[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        int old_group = group[y];
        int new_group = group[x];
        for (int j = 1; j <= n; j++) {
            if (group[j] == old_group) {
                group[j] = new_group;
            }
        }
    }
    int sum_tea[101] = {0};
    for (int i = 1; i <= n; i++) {
        sum_tea[group[i]] += (a[i] - b[i]);
    }
    int max_tea = 0;
    for (int g = 1; g <= n; g++) {
        if (sum_tea[g] > 0) {
            max_tea += sum_tea[g];
        }
    }
    cout << max_tea << endl;
    return 0;
}