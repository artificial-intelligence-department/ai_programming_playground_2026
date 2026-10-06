#include <iostream>
#include <algorithm>

using namespace std;

int main () {
    long long h1, h2, h3, h4;
    cin >> h1 >> h2 >> h3 >> h4;

    long long d1, d2, d3, d4;
    cin >> d1 >> d2 >> d3 >> d4;

    // 1. Спочатку перевіряємо всі ніжки на ERROR
    if (d1 > h1 || d2 > h2 || d3 > h3 || d4 > h4) {
        cout << "ERROR" << endl;
        return 0;
    }

    bool isYes = true;

    // --- Перевірка після відпилювання 1-ї ніжки ---
    h1 -= d1;
    long long h_max = max({h1, h2, h3, h4});
    long long h_min = min({h1, h2, h3, h4});
    if (h_max >= 2 * h_min) isYes = false;

    // --- Перевірка після відпилювання 2-ї ніжки ---
    h2 -= d2;
    h_max = max({h1, h2, h3, h4});
    h_min = min({h1, h2, h3, h4});
    if (h_max >= 2 * h_min) isYes = false;

    // --- Перевірка після відпилювання 3-ї ніжки ---
    h3 -= d3;
    h_max = max({h1, h2, h3, h4});
    h_min = min({h1, h2, h3, h4});
    if (h_max >= 2 * h_min) isYes = false;

    // --- Відпилюємо 4-ту ніжку ---
    h4 -= d4;
    
    // після 4-ї ніжки перевіряємо стан кінцевого столу:
    h_max = max({h1, h2, h3, h4});
    h_min = min({h1, h2, h3, h4});
    if (h_max >= 2 * h_min) isYes = false;

    // --- Перевірка підсумкового стану ---
    bool all_equal = (h1 == h2 && h2 == h3 && h3 == h4);
    bool not_zero = (h1 > 0);

    if (isYes && all_equal && not_zero) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}