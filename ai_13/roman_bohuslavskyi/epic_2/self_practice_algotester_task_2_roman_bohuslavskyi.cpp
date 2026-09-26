//Where to run?
#include <iostream>
using namespace std;

int main() {
    int sd, su, v;

    cin >> sd >> su >> v;

    if (sd < 4 * su) {
        cout << "Down" << endl;
    }
    else if (sd > 4 * su) {
        cout << "Up" << endl;
    }
    else {
        cout << "Never mind" << endl;
    }

    return 0;
}
