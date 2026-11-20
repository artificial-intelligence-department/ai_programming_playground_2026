#include <iostream>
using namespace std;

int main() {
    char symbol;
    cin >> symbol;
    if (symbol >= 'a' && symbol <= 'z') {
        cout << symbol - 'a' + 1;
    }
    else if (symbol >= 'A' && symbol <= 'Z') {
        cout << symbol - 'A' + 1;
    }
    else if (symbol >= '0' && symbol <= '9') {
        cout << "digit";
    }
    else {
        cout << "weird symbol";
    }
    return 0;
}