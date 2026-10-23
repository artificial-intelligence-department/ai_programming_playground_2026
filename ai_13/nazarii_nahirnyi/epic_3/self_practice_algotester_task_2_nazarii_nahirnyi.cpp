/*
Завдання: Найбільша зростаюча підпослідовність
*/
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int a[100];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int b[100];
    for (int i = 0; i < n; i++) {
        b[i] = 1;
    }

    int ans = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                if (b[j] + 1 > b[i]) {
                    b[i] = b[j] + 1;
                }
            }
        }
        if (b[i] > ans) {
            ans = b[i];
        }
    }

    cout << ans << endl;

    return 0;
}