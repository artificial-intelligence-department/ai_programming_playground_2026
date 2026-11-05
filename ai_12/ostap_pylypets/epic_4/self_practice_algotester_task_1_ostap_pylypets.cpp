// Коля, Вася та таємна кімната
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, k, s[100000], b[100000];
    long long res = 0;

    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    for (int i = 0; i < k; i++) {
        cin >> b[i];
    }
    sort(s, s + n, greater<int>());
    sort(b, b + k, greater<int>());
    for (int i = 0; i < n; i++) {
        res += 1LL * s[i] * b[0];
        b[0]--;
        int j = 0;
        while (j + 1 < k && b[j] < b[j + 1]) {
            swap(b[j], b[j + 1]);
            j++;
        }
    }
    cout << res;
    return 0;
}
