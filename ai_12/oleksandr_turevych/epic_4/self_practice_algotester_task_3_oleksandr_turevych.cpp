#include <iostream>

using namespace std;

int main() {

    int n, m, k;
    cin >> n >> m >> k;

    long long totalTrips = 0;

    for (int i = 0; i < n; ++i) {
        int starsInRow = 0;
        for (int j = 0; j < m; ++j) {
            char ch;
            cin >> ch;
            if (ch == '*') {
                starsInRow++;
            }
        }
        
        // Якщо у рядку є зірочки, рахуємо поїздки з округленням вгору
        if (starsInRow > 0) {
            totalTrips += (starsInRow + k - 1) / k;
        }
    }

    cout << totalTrips << "\n";

    return 0;
}