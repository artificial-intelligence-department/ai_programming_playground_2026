#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0, k = 0;
    if (!(cin >> n >> k)) {
        return 0;
    }

    if (n < k || n > 3 * k) {
        cout << "Impossible" << endl;
        return 0;
    }

    int teams[100] = {};
    for (int i = 0; i < k; i++) {
        teams[i] = 1;
    }

    int remaining_students = n - k;

    for (int i = 0; i < k && remaining_students > 0; i++) {
        int add = (remaining_students < 2) ? remaining_students : 2;
        teams[i] += add;
        remaining_students -= add;
    }

    for (int i = 0; i < k; i++) {
        cout << teams[i] << (i == k - 1 ? "" : " ");
    }

    return 0;
}