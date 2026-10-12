#include <iostream>

int types[100001];
int cnt[100001];

int main() {
    int n, k;
    std::cin >> n >> k;

    for (int i = 0; i < n; i++) {
        std::cin >> types[i];
        cnt[types[i]]++;
    }

    int main_type = 0;
    bool found = false;
    for (int t = 1; t <= 100000; t++) {
        if (cnt[t] >= k) {
            main_type = t;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Oh sh*t" << std::endl;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (types[i] == main_type) {
            std::cout << types[i] << " ";
        }
    }
    for (int i = 0; i < n; i++) {
        if (types[i] != main_type) {
            std::cout << types[i] << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}