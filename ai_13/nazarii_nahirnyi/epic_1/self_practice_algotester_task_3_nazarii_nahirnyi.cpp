#include <iostream>
using namespace std;

int main() {
    int a, b;

    if (!(cin >> a) || a < 0 || a > 100) {
        cout << "Помилка: A має бути цілим числом від 0 до 100.\n";
        return 1;
    }
    if (!(cin >> b) || b < 0 || b > 100) {
        cout << "Помилка: B має бути цілим числом від 0 до 100.\n";
        return 1;
    }

    cout << a + b << "\n";
    return 0;
}
