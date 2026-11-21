#include <iostream>

int main() {
    int n, m;
    if (!(std::cin >> n >> m)) {
        return 0;
    }

    if ((n * m) % 2 != 0) {
        std::cout << "Imp\n";
    } else {
        std::cout << "Dragon\n";
    }

    return 0;
}
