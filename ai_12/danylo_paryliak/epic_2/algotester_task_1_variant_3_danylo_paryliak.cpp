#include <iostream>
using namespace std;

int main() {
    long long old, newc;

    cin >> old;

    // Ребро куба не може бути нульовим або від'ємним.
    if (old <= 0) {
        cout << "ERROR" << endl;
        return 0;
    }

    // Перевіряємо ще чотири куби по одному.
    for (int i = 1; i < 5; i++) {
        cin >> newc;

        if (newc <= 0) {
            cout << "ERROR" << endl;
            return 0;
        }

        // Наступний куб має бути не більшим за попередній.
        if (newc > old) {
            cout << "LOSS" << endl;
            return 0;
        }

        old = newc;
    }

    cout << "WIN" << endl;
    return 0;
}
