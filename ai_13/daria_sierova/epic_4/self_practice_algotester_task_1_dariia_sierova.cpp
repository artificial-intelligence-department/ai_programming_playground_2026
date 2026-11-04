// решта
#include <iostream>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    int change = 500 - n;

    int size = 9;
    int* cup = new int[size];

    *(cup + 0) = 500;
    *(cup + 1) = 200;
    *(cup + 2) = 100;
    *(cup + 3) = 50;
    *(cup + 4) = 20;
    *(cup + 5) = 10;
    *(cup + 6) = 5;
    *(cup + 7) = 2;
    *(cup + 8) = 1;

    int total = 0;

    for (int i = 0; i < size; i++) {
        int current = *(cup + i);
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