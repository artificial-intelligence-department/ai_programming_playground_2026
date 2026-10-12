#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // Шукаємо найдешевшу цукерку Зеника
    long long min_a;
    cin >> min_a; // Зчитуємо першу цукерку як початковий мінімум
    for (int i = 1; i < n; ++i) {
        long long current;
        cin >> current;
        if (current < min_a) {
            min_a = current;
        }
    }

    // Шукаємо найдешевшу цукерку Марічки
    long long min_b;
    cin >> min_b; // Зчитуємо першу цукерку як початковий мінімум
    for (int i = 1; i < m; ++i) {
        long long current;
        cin >> current;
        if (current < min_b) {
            min_b = current;
        }
    }

    // Виводимо загальну суму подарунка
    cout << min_a + min_b << "\n";

    return 0;
}
