#include <iostream>

int main() {
    long long n;
    if (!(std::cin >> n)) return 0;

    int bills[] = {500, 200, 100, 50, 20, 10, 5, 2, 1};
    long long ans = 0;

    for (int b : bills) {
        ans += n / b;
        n %= b;
    }

    std::cout << ans << "\n";
    return 0;
}
