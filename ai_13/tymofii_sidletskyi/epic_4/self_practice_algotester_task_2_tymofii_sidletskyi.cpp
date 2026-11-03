#include <iostream>
using namespace::std;
// Задача 2461
int main () {
    int n;
    long long a[100000];
    int len1 = 1;
    int len2 = 1;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n - 1; i++) {
        if (a[i] < a[i+1]) {
            len1++;
        } else {
            len1 = 1;
        }

        if (len1 > len2) {
            len2 = len1;
        }
    }

    cout << len2;

    return 0;
}