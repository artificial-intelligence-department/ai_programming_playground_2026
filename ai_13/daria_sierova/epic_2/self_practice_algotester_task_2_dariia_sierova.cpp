#include <iostream>
using namespace std;

int main() {
    int a; // kg
    int b; // g
    int c;
    int d;

    cin >> a >> b >> c >> d;

    if (a >= 0 && b >= 0 && c >= 0 && d >= 0) {
        int amount = (1000 * c + d) / (1000 * a + b);
        int remain = (1000 * c + d) - (amount * (1000 * a + b));
        int kg = remain / 1000;
        int g = remain % 1000;

        cout << amount << endl;
        cout << kg << " " << g << endl;
        return 0;
    } else {
        return 1;
    }
}