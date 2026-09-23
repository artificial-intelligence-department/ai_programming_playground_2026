#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long totalCookies = 0;
    long long fullPacks = 0;

    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;

        totalCookies += a;

        if (a > 0) {
            fullPacks++;
        }
    }

    long long answer = totalCookies - fullPacks;

    cout << answer << endl;

    return 0;
}