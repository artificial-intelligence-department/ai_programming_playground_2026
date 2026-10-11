/*
    Назва: Class Practice Work
    Автор: Макух Арсеній
    Група: ШІ-13
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    long long h[4], d[4];

    cout << "Введіть висоту ніжок стола: ";
    for(int i = 0; i < 4; i++) {
        cin >> h[i];
    }

    cout << "Введіть довжину, яку потрібно відпиляти від ніжок: ";
    for(int i = 0; i < 4; i++) {
        cin >> d[i];
    }

    if (h[0] < d[0] || h[1] < d[1] || h[2] < d[2] || h[3] < d[3]) {
        cout << "ERROR" << endl;
        return 0;
    }

    bool flipped = false;

    if (max({h[0], h[1], h[2], h[3]}) >= 2 * min({h[0], h[1], h[2], h[3]})) {
        flipped = true;
    }

    for (int i = 0; i < 4; i++) {
        h[i] -= d[i];

        long long max_height = max({h[0], h[1], h[2], h[3]});
        long long min_height = min({h[0], h[1], h[2], h[3]});

        if (max_height >= (2 * min_height)) {
            flipped = true;
        }

    }

    if (!flipped && h[0] == h[1] && h[1] == h[2] && h[2] == h[3] && h[0] > 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}