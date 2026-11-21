#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) {
        return 0;
    }

    long long total_eaten = 0;
    for (int i = 0; i < n; ++i) {
        long long a;
        std::cin >> a;
        if (a > 0) {
            total_eaten += (a - 1);
        }
    }

    std::cout << total_eaten << "\n";

    return 0;
}
