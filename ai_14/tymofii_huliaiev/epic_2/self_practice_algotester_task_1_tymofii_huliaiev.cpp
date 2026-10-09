#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    int max_count = 0;
    int current_count = 0;

    for (int i = 0; i < n; ++i) {
        long long a;
        cin >> a;

        if (a >= k) {
            current_count++;
            max_count = max(max_count, current_count);
        } else {
            current_count = 0;
        }
    }

    cout << max_count << "\n";

    return 0;
}