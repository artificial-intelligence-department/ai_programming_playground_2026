//зуби
#include <iostream>
using namespace std;

int main() {
    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    long long* teeth = new long long[n];

    for (int i = 0; i < n; i++) {
        cin >> *(teeth + i); 
    }

    int max_len = 0;
    int current_len = 0;

    for (int i = 0; i < n; i++) {
        if (*(teeth + i) >= k) {
            current_len++;
            if (current_len > max_len) {
                max_len = current_len;
            }
        } else {
            current_len = 0;
        }
    }

    cout << max_len << "\n";

    delete[] teeth;
    teeth = nullptr;

    return 0;
}