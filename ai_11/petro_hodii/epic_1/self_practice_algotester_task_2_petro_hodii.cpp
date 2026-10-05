#include <iostream>

using namespace std;

int main() {

    int res;
    int a;
    cin >> a;

    res += a / 500;
    a %= 500;
    res += a / 200;
    a %= 200;
    res += a / 100;
    a %= 100;
    res += a / 50;
    a %= 50;
    res += a / 20;
    a %= 20;
    res += a / 10;
    a %= 10;
    res += a / 5;
    a %= 5;
    res += a / 2;
    a %= 2;
    res += a;

    cout << res << endl;

    return 0;
}