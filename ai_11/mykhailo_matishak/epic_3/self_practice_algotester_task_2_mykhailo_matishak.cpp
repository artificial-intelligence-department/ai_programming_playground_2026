#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long a[5000];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long swaps = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                swaps++;
            }
        }
    }

    cout << swaps << endl;
    return 0;
}