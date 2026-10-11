/* 
    Назва: Algotester Lab 1v2 
    Автор: Макух Арсеній 
    Група: ШІ-13 
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    long long h[4], d[4];

    cin >> h[0] >> h[1] >> h[2] >> h[3];
    cin >> d[0] >> d[1] >> d[2] >> d[3];

    bool flipped = false;

    for (int i = 0; i < 4; i++) {
        if (d[i] > h[i]) {
            cout << "ERROR";
            return 0;
        }

        h[i] -= d[i];

        long long curr_min = *min_element(h, h + 4);
        long long curr_max = *max_element(h, h + 4);

        if (curr_min == 0 || curr_max >= 2 * curr_min) {
            flipped = true;
        }
    }

    if (flipped) {
        cout << "NO";
    } else {
        cout << "YES";
    }

    return 0;
}
