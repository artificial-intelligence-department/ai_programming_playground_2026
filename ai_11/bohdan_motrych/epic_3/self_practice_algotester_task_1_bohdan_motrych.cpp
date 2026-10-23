#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    if (!(cin >> n)) {
        return 0;
    }

    long long total_cookies = 0;

    for (int i = 0; i < n; i++) {
        long long a = 0;
        cin >> a;
        if (a > 0) {
            total_cookies += (a - 1);
        }
    }

    cout << total_cookies << endl;

    return 0;
}