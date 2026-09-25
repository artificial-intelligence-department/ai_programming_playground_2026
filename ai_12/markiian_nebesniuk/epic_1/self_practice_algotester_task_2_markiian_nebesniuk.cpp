#include <iostream>
using namespace std;

int main() {
    int n;
    long long sum = 0;
    cin >> n;

    for (int i; i < n; i++) {
        int s;
        cin >> s;
        sum = sum + s - 1;
    }

    cout << sum << endl;

    return 0;

}