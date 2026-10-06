#include <iostream>

using namespace std;

int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

     long long n;
    if (!(cin >> n)) return 0;

    long long coins[] = {500, 200, 100, 50, 20, 10, 5, 2, 1};
    long long total_bills = 0;

    for (long long coin : coins) {
        total_bills += n / coin;
        n %= coin;
    }

    cout << total_bills << "\n";

    return 0;
}