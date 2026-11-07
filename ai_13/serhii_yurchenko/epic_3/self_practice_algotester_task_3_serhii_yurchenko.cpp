// Cikaviy masiv
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a[100];
    int total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total += a[i];
    }

    string ans = "NI";
    if (total % 2 == 0) {
        int half = total / 2;
        int cur = 0;
        for (int k = 0; k < n - 1; k++) {
            cur += a[k];
            if (cur == half) {
                ans = "TAK";
                break;
            }
        }
    }

    cout << ans << endl;
    return 0;
}