#include <iostream>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    // Статичний масив
    int* a = new int[n + 1]; //int a[1000];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int L = 1;
    int R = n;

    // Перевірка до зльоту
    if (L == R) {
        cout << L << " " << R << endl;
        cout << "Collision" << endl;
        return 0;
    }
    if (L > R) {
        cout << L << " " << R << endl;
        cout << "Miss" << endl;
        return 0;
    }
    if (L == R - 1) {
        cout << L << " " << R << endl;
        cout << "Stopped" << endl;
        return 0;
    }

    // Польоти дронів
    while (true) {
        L += a[L];
        R -= a[R];

        if (L == R) {
            cout << L << " " << R << endl;
            cout << "Collision" << endl;
            break;
        }
        if (L > R) {
            cout << L << " " << R << endl;
            cout << "Miss" << endl;
            break;
        }
        if (L == R - 1) {
            cout << L << " " << R << endl;
            cout << "Stopped" << endl;
            break;
        }
    }

    return 0;
}