#include <iostream>

using namespace std;

int cnt[100005];
int r[100005];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    int index = 0;
    for (int val = 0; val <= 100000; ++val) {
        while (cnt[val] > 0) {
            r[index] = val;
            index++;
            cnt[val]--;
        }
    }

    if (n <= 1) {
        cout << 0 << endl;
        return 0;
    }

    int option1 = r[n - 1] - r[1];

    int option2 = r[n - 2] - r[0];

    int ans = (option1 < option2) ? option1 : option2;

    cout << ans << endl;

    return 0;
}
