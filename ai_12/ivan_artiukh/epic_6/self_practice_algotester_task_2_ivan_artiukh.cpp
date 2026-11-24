//гори
#include <iostream>

using namespace std;

struct Battery {
    int x;
};

const int MAXN = 100005;
Battery bats[MAXN];
bool lifted[MAXN];
int main() {
    int n;
    if (!(cin >> n)) return 0;

    for (int i = 0; i < n; ++i) {
        cin >> bats[i].x;
    }

    int p;
    cin >> p;

    lifted[p] = true;

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int x = bats[i].x;

        if (lifted[x] || lifted[x + 1]) {
            ans++;
            lifted[x] = true;
            lifted[x + 1] = true;
        }
    }

    cout << ans << '\n';
    return 0;
}