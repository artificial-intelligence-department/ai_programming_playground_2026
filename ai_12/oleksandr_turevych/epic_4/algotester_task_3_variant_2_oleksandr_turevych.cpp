#include <iostream>

using namespace std;

int main() {

    int n;
    cin >> n;

    int a[100];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int m;
    cin >> m;

    int b[100];
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    // Рахуємо спільні елементи в обох масивах
    int commonCount = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                commonCount++;
                break;
            }
        }
    }

    // Кількість усіх унікальних = N + M - спільні
    int totalUnique = n + m - commonCount;

    cout << commonCount << "\n";
    cout << totalUnique << "\n";

    return 0;
}