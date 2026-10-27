#include <iostream>
#include <iomanip>

int main() {
    int n, m; 
    std::cin >> n >> m;
    int a[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    double l = 0.0, r = 1e9;
    for (int i = 0; i < 100; i++) {
        int c = 0;
        double  mid  = l + (r - l)/2.0;
        for (int j = 0; j < n; j++) {
            c += (int)(a[j]/mid);
        }
        if (c >= m) {
            l = mid;
        }
        if (c < m) {
            r = mid;
        }
    }
    std::cout << std::fixed << std::setprecision(7) << l << std::endl;;
}