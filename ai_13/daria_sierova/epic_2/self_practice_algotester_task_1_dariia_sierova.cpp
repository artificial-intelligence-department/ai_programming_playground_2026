#include <iostream>
using namespace std;

int main() {
    long long n;
    cin >> n;

    int bills[] = {500, 200, 100, 50, 20, 10, 5, 2, 1};
    long long num = 0;

    for (int i = 0; i < 9; i++) {
        num += n / bills[i];
        n %= bills[i];
    }
    cout << num << endl;

    return 0;
}