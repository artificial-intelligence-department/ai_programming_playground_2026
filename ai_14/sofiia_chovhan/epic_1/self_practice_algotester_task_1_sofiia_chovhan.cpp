#include <iostream>

int main() {
    int L, W, U, D;

    std::cin >> L >> W >> U >> D;

    if (L > 109 || W > 109 || U > 109 || D > 109) {
        return 1;
    }

    if (L <= U + D && L <= W) {
        std::cout << "Three times Sex on the Beach, please!";
    }
    else {
        std::cout << "Forget about the cocktails, man!";
    }

    return 0;
}