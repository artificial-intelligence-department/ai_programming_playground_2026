#include <iostream>
using namespace std;
 int main () {
    long long a, b;
    cin >> a >> b;
    if ((b - a) % 12 != 0) {
        cout << -1 << endl;
    } else {
        cout << (b + a) * 13 / 2 << endl;
    }
return 0;
 }