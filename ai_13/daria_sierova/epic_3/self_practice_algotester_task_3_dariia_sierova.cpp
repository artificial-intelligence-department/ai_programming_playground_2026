#include <iostream>
using namespace std;

void findMax(int num[], int n) {
    int max = num[0];

    for (int i = 1; i < n; ++i) {
        if (num[i] > max) {
            max = num[i];
        }
    }
    cout << max << endl;
}

int main() {
    int n;
    cin >> n;

    if (n > 0 && n < 1000) {
        int num[n];
        for (int i = 0; i < n; ++i) {
            cin >> num[i];
        }
        findMax(num, n);
    }
    return 0;
}