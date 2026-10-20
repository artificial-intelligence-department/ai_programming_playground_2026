#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int temperature[n];

    for (int i = 0; i < n; i++) {
        cin >> temperature[i];
    }

    for (int i = 0; i < n; i++) {
        if (temperature[i] > 0) {
            cout << i + 1 << " ";
        }
    }

    return 0;
}