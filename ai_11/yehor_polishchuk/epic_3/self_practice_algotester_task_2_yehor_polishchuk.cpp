#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long x[1000], y[1000], r[1000];
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> r[i];
    }

    int best = 0;

    for (int i = 0; i < n; i++) {          // i: кратер, у якому шукаємо
        int cnt = 0;

        for (int j = 0; j < n; j++) {      // j: кратер, який може лежати всередині
            if (i == j) continue;          // кратер сам у собі не лежить
            if (r[j] > r[i]) continue;     // більший не може лежати в меншому

            __int128 dx = x[i] - x[j];
            __int128 dy = y[i] - y[j];
            __int128 dr = r[i] - r[j];

            if (dx * dx + dy * dy <= dr * dr) {
                cnt++;
            }
        }

        if (cnt > best) {
            best = cnt;
        }
    }

    cout << best << endl;

    return 0;
}