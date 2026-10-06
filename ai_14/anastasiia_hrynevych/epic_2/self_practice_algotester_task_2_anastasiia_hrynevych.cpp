#include <iostream>
using namespace std;

int main() {
    long long a, b, c, d; cin >> a >> b >> c >> d;
    int coordinate1 = 0, coordinate2 = 0;
    if (a > 0 && b > 0) coordinate1 = 1;
    else if (a < 0 && b > 0) coordinate1 = 2;
    else if (a < 0 && b < 0) coordinate1 = 3;
    else if (a > 0 && b < 0) coordinate1 = 4;
    if (c > 0 && d > 0) coordinate2 = 1;
    else if (c < 0 && d > 0) coordinate2 = 2;
    else if (c < 0 && d < 0) coordinate2 = 3;
    else if (c > 0 && d < 0) coordinate2 = 4;
    if (coordinate1 == coordinate2) cout << "Yes" << endl;
    else cout << "No" << endl;
}