#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    int a = 0, b = 0;      // очки в поточній партії (Коля, Вася)
    int k = 0, v = 0;      // виграні партії

    for (int i = 0; i < n; i++) {
        if (s[i] == 'K') a++;
        else b++;

        if (a >= 11 && a - b >= 2) {
            k++;
            a = b = 0;
        } else if (b >= 11 && b - a >= 2) {
            v++;
            a = b = 0;
        }
    }

    cout << k << ":" << v << "\n";
    if (a != 0 || b != 0) {
        cout << a << ":" << b << "\n";
    }

    return 0;
}