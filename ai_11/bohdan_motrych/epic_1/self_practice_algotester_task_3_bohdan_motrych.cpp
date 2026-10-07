#include <iostream>
using namespace std;

int main() {

    long long n = 0;
    long long m = 0;

    if (cin >> n >> m) {
        if ((n * m) % 2 != 0) {
            cout << "Imp" << endl;
        } else {
            cout << "Dragon" << endl;
        }
    }

    return 0;
}