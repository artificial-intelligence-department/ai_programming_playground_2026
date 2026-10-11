
/*
Непередбачувана погода, Олексій Рубаха, ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int temperature[1000];

    // Зчитуємо температури
    for (int i = 0; i < n; i++) {
        cin >> temperature[i];
    }

    // Виводимо дні з позитивною температурою
    for (int i = 0; i < n; i++) {
        if (temperature[i] > 0) {
            cout << i + 1 << " ";
        }
    }

    return 0;
}
