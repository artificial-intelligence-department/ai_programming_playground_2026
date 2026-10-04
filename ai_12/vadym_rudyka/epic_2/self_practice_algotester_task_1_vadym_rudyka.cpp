#include <iostream>

using namespace std;

int main() {
    // розміри шоколадки та кількість друзів
    int n, m, k;
    cin >> n >> m >> k;
    // Перевірка, чи можна розрізати шоколадку на k рівних частин
    if (n * m % k == 0) {
        cout << "Yes";
    } else {
        cout << "No";
    }
    return 0;
}