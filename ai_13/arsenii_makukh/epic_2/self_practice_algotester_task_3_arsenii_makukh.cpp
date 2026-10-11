/*
    Назва: Спекотнi днi пiнгвiнiв
    Автор: Макух Арсеній
    Група: ШІ-13
*/

#include <iostream>

using namespace std;

int main () {
    int l, w, u, d;

    cin >> l >> w >> u >> d;

    if (l > w || l > (u + d)) {
        cout << "Forget about the cocktails, man!" << endl;
    } else {
        cout << "Three times Sex on the Beach, please!" << endl;
    }

    return 0;
}