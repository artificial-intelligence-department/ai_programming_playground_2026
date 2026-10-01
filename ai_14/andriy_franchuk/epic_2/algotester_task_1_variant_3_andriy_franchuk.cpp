#include <iostream>
using namespace std;

int main() {
    // Використовуємо long long для великих цілих чисел
    long long a1, a2, a3, a4, a5;
    cin >> a1 >> a2 >> a3 >> a4 >> a5;

    // 1-й куб
    if (a1 <= 0) { cout << "ERROR"; return 0; }

    // 2-й куб
    if (a2 <= 0) { cout << "ERROR"; return 0; }
    if (a1 < a2) { cout << "LOSS"; return 0; }

    // 3-й куб
    if (a3 <= 0) { cout << "ERROR"; return 0; }
    if (a2 < a3) { cout << "LOSS"; return 0; }

    // 4-й куб
    if (a4 <= 0) { cout << "ERROR"; return 0; }
    if (a3 < a4) { cout << "LOSS"; return 0; }

    // 5-й куб
    if (a5 <= 0) { cout << "ERROR"; return 0; }
    if (a4 < a5) { cout << "LOSS"; return 0; }

    // Якщо пройшли всі перевірки
    cout << "WIN";
    return 0;
}
