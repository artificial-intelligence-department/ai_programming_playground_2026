#include <iostream>
using namespace std;

int main() {
    char c;
    cin >> c;

    if (c >= 'a' && c <= 'z') {
        cout << c - 'a' + 1;
    }
    else if (c >= 'A' && c <= 'Z') {
        cout << c - 'A' + 1;
    }
    else if (c >= '0' && c <= '9') {
        cout << "digit";
    }
    else {
        cout << "weird symbol";
    }

    return 0;
}