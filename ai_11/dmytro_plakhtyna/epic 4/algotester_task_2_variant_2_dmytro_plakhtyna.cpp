#include <iostream>
using namespace std;

int r[100000];
int newarr[100000];

int main() {
    int n, a, b, c;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }
    cin >> a >> b >> c;
    int newN = 0;
    for (int i = 0; i < n; i++) {
        if (r[i] != a && r[i] != b && r[i] != c) {
            newarr[newN] = r[i];
            newN++;
        }
    }
    if (newN < 2) {
        cout << 0 << endl;
        return 0;
    }
    cout << newN - 1 << endl;
    for (int i = 0; i < newN - 1; i++) {
        cout << newarr[i] + newarr[i + 1] << " ";
    }
    cout << endl;
    return 0;
}
