#include <iostream>
// Задача 1172
using namespace std;

int main() {
    int n;
    cin >> n;

    int evens[n];
    int odds[n];

    int even_count = 0;
    int odd_count = 0;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        if (val % 2 == 0) {
            evens[even_count++] = val;
        } else {
            odds[odd_count++] = val;
        }
    }

    if (even_count - odd_count > 1 || odd_count - even_count > 1) {
        cout << -1 << "\n";
    } else {
        int e_idx = 0;
        int o_idx = 0;

        bool next_is_odd = (odd_count >= even_count);

        for (int i = 0; i < n; i++) {
            if (next_is_odd) {
                cout << odds[o_idx++] << " ";
            } else {
                cout << evens[e_idx++] << " ";
            }
            next_is_odd = !next_is_odd;
        }
    }

    return 0;
}