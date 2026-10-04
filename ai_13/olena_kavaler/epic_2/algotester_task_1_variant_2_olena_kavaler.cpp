/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    long long h1, h2, h3, h4;
    long long d1, d2, d3, d4;
    cin >> h1 >> h2 >> h3 >> h4;
    cin >> d1 >> d2 >> d3 >> d4;

    if (h1 < d1 || h2 < d2 || h3 < d3 || h4 < d4) {
        cout << "ERROR" << endl;
        return 0;
    }

    bool is_failed = false;

    h1 -= d1;

    long long maxh = h1;
    if (h2 > maxh) maxh = h2;
    if (h3 > maxh) maxh = h3;
    if (h4 > maxh) maxh = h4;

    long long minh = h1;
    if (h2 < minh) minh = h2;
    if (h3 < minh) minh = h3;
    if (h4 < minh) minh = h4;

    if (maxh >= 2 * minh) {
        is_failed = true;
    }

    h2 -= d2;

    maxh = h1;
    if (h2 > maxh) maxh = h2;
    if (h3 > maxh) maxh = h3;
    if (h4 > maxh) maxh = h4;

    minh = h1;
    if (h2 < minh) minh = h2;
    if (h3 < minh) minh = h3;
    if (h4 < minh) minh = h4;

    if (maxh >= 2 * minh) {
        is_failed = true;
    }

    h3 -= d3;

    maxh = h1;
    if (h2 > maxh) maxh = h2;
    if (h3 > maxh) maxh = h3;
    if (h4 > maxh) maxh = h4;

    minh = h1;
    if (h2 < minh) minh = h2;
    if (h3 < minh) minh = h3;
    if (h4 < minh) minh = h4;

    if (maxh >= 2 * minh) {
        is_failed = true;
    }

    h4 -= d4;

    maxh = h1;
    if (h2 > maxh) maxh = h2;
    if (h3 > maxh) maxh = h3;
    if (h4 > maxh) maxh = h4;

    minh = h1;
    if (h2 < minh) minh = h2;
    if (h3 < minh) minh = h3;
    if (h4 < minh) minh = h4;

    if (maxh >= 2 * minh) {
        is_failed = true;
    }

    if (is_failed == false && h1 == h2 && h2 == h3 && h3 == h4 && h1 > 0) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }


}
