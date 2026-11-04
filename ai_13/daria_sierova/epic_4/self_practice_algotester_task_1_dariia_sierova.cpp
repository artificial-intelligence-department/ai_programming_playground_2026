// решта
#include <iostream>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    int change = 500 - n;

    int size = 9;
    int* cup = new int[size]{500, 200, 100, 50, 20, 10, 5, 2, 1};
    

    int total = 0;

    for (int i = 0; i < size; i++) {
        int current = cup[i];
        if (change >= current) {
            total += change / current;
            change %= current;
        }
    }

    cout << total << "\n";

    delete[] cup;
    cup = nullptr;

    return 0;
}