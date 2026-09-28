#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    vector<long long> b(n);

    for (int i = 0; i < n; i = i + 1) {
        cin >> a[i];
    }

    b[0] = a[0];

    for (int i = 1; i < n; i = i + 1) {
        if (a[i] == b[i - 1]) {
            b[i] = a[i] + 1;
        } else {
            b[i] = a[i];
        }
    }

    for (int i = 0; i < n; i = i + 1) {
        cout << b[i] << " ";
    }
    cout << endl;

    return 0;
}
