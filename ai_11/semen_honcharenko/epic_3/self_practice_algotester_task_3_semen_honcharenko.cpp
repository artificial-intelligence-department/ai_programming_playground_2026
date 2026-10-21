/*
    Алготестер. "Спекотнi днi пiнгвiнiв"
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>

using namespace std;

int main() {
    int l = 0; // cocktail diameter
    int w = 0; // mouth width
    int u = 0; // max upper jaw
    int d = 0; // max bottom jaw

    cin >> l;
    cin >> w;
    cin >> u;
    cin >> d;

    if (w >= l and u+d >= l) {
        cout << "Three times Sex on the Beach, please!" << endl;
    }
    else {
        cout << "Forget about the cocktails, man!" << endl;
    }
    return 0;
}