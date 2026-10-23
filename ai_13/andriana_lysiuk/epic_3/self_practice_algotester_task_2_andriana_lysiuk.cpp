/*
Назва задачі: Свічки на Halloween
Автор: Лисюк Андріана
Група: ШІ-13
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    double l[100];
    double max_len = 0.0;

    for (int i = 0; i < m; i++) {
        cin >> l[i];
        if (l[i] > max_len) {
            max_len = l[i];
        }
    }

    double low = 0.0, high = max_len;
    for (int j = 0; j < 100; j++) {
        double mid = low + (high - low) / 2.0;

        int count = 0;
        for (int k = 0; k < m; k++) {
            count += (l[k] / mid);
        }

        if (count >= n) {
            low = mid;
        } else {
            high = mid;
        }
    }
    cout << fixed << setprecision(8) << low;
    return 0;
}