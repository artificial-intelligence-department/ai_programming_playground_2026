#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a[100000];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int left = 0;
    int right = n - 1;

    while (true) {
        if (left == right) {
            cout << left + 1 << " " << right + 1 << "\n";
            cout << "Collision\n";
            break;
        }

        if (left > right) {
            cout << left + 1 << " " << right + 1 << "\n";
            cout << "Miss\n";
            break;
        }

        if (left + 1 == right) {
            cout << left + 1 << " " << right + 1 << "\n";
            cout << "Stopped\n";
            break;
        }

        left += a[left];
        right -= a[right];
    }

    return 0;
}