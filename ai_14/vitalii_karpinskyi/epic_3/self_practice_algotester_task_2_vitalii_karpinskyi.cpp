#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    long a[100] = {0};
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long copy[100] = {0};
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                long temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
            }
        }
    }
    int count = 1;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] != a[i + 1]) {
        count++;
        }
    }
    cout << count;

    return 0;
}