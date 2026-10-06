#include <iostream>
using namespace std;

int main() {
    long long h1, h2, h3, h4;
    long long d1, d2, d3, d4;
    cin >> h1 >> h2 >> h3 >> h4;
    cin >> d1 >> d2 >> d3 >> d4;
    if (d1 > h1 || d2 > h2 || d3 > h3 || d4 > h4) {
        cout << "ERROR";
        return 0;
    }

    bool fell = false;
    long long mx, mn;
    h1 = h1 - d1;
    mx = h1;
    if (h2 > mx) mx = h2;
    if (h3 > mx) mx = h3;
    if (h4 > mx) mx = h4;
    mn = h1;
    if (h2 < mn) mn = h2;
    if (h3 < mn) mn = h3;
    if (h4 < mn) mn = h4;
    if (mx >= 2 * mn) fell = true;
    h2 = h2 - d2;
    mx = h1;
    if (h2 > mx) mx = h2;
    if (h3 > mx) mx = h3;
    if (h4 > mx) mx = h4;
    mn = h1;
    if (h2 < mn) mn = h2;
    if (h3 < mn) mn = h3;
    if (h4 < mn) mn = h4;
    if (mx >= 2 * mn) fell = true;
    h3 = h3 - d3;
    mx = h1;
    if (h2 > mx) mx = h2;
    if (h3 > mx) mx = h3;
    if (h4 > mx) mx = h4;
    mn = h1;
    if (h2 < mn) mn = h2;
    if (h3 < mn) mn = h3;
    if (h4 < mn) mn = h4;
    if (mx >= 2 * mn) fell = true;
    h4 = h4 - d4;
    mx = h1;
    if (h2 > mx) mx = h2;
    if (h3 > mx) mx = h3;
    if (h4 > mx) mx = h4;
    mn = h1;
    if (h2 < mn) mn = h2;
    if (h3 < mn) mn = h3;
    if (h4 < mn) mn = h4;
    if (mx >= 2 * mn) fell = true;
    if (fell == false && h1 == h2 && h2 == h3 && h3 == h4 && h1 > 0) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
