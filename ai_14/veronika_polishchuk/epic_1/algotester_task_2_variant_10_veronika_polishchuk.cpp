#include <iostream>
#include <algorithm>

long long a[100007];
long long n, i;

int main() {
    std::cin >> n;
    for (i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::sort(a + 1, a + 1 + n);
    std::cout << a[n] - a[1];
}
