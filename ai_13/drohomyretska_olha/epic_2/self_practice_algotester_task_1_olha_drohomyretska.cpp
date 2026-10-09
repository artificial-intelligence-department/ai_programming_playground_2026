/*
Задача: Where to run?
Автор: Дрогомирецька Ольга
Група: ШІ-13
*/
#include <iostream>
using namespace std;

int main() {
    long long d1, d2, v;
    cin >> d1 >> d2 >> v;

    if (d1 < 4 * d2) {
        cout << "Down"<< endl;
    }
    else if (d1 > 4 * d2) {
        cout << "Up"<< endl;
    }
    else {
        cout << "Never mind"<< endl;
    }

    return 0;
}