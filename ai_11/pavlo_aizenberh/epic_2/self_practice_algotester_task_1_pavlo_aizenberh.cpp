// Задача №0216 - Темрява

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    if (n == 0 || k == 0) {
        cout << 0;
    } else {
        cout << fixed << setprecision(6) << 1.0 / (n * k);
    }

    return 0;
}