#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    bool used[1001] = {false};

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        used[x] = true;
    }

    int arr[1000];
    int m = 0;

    for (int i = 0; i <= 1000; i += 3) {
        if (used[i]) {
            arr[m++] = i;
        }
    }

    for (int i = 1000; i >= 0; i--) {
        if (i % 3 == 1 && used[i]) {
            arr[m++] = i;
        }
    }

    for (int i = 0; i <= 1000; i++) {
        if (i % 3 == 2 && used[i]) {
            arr[m++] = i;
        }
    }

    cout << m << '\n';

    for (int i = 0; i < m; i++) {
        cout << arr[i] << ' ';
    }

    cout << '\n';
    return 0;
}
