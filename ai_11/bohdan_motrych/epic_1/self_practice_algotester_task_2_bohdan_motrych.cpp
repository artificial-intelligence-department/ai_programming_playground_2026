#include <iostream>
using namespace std;

int main() {

    long long n = 0;
    cin >> n;

    const int denominations[] = {500, 200, 100, 50, 20, 10, 5, 2, 1};

    long long count = 0;

    for (int banknote : denominations) {
        count += n / banknote;
        n %= banknote;
    }

    cout << count << endl;

    return 0;
}