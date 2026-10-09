#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int year;
    if (cin >> year) {
        cout << "16.02." << setfill('0') << setw(4) << year << "\n";
    }

    return 0;
}