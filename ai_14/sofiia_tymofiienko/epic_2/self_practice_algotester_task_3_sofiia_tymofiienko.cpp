#include <iostream>
using namespace std;
int main() {
    long long n, m, k;
    cin >> n >> m >> k;
    long long total = (n * 100 + m) * k;
    cout << total / 100 << " " << total % 100 << "\n";
    return 0;
}
