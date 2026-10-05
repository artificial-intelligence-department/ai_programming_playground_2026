#include <iostream>

using namespace std;

int main() {
    int A, B;
    cin >> A >> B;
    if (A >= 0 && A <= 100 && B >= 0 && B <= 100) {
        cout << A + B << endl;
    }

    return 0;
}