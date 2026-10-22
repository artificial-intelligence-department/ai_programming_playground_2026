//Задача 0393 - Аркуш
#include <iostream>
using namespace std;

int main() {
    long long n;
    if (cin >> n) {
        long long total = n * (n + 1) * (2 * n + 1) / 6;
        cout << total << "\n";
    }

    return 0;
}