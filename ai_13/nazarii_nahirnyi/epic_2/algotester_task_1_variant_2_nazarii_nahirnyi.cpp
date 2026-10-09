/*
Algotster Lab 1v2, Нагірний Назарій, ШІ-13
*/
#include <iostream>

using namespace std;

int main() {
    long long h[4], d[4];

    for (int i = 0; i < 4; i++) {
        if (!(cin >> h[i]) || h[i] < 0 || h[i] > 1000000000000) {
            cout << "Помилка вводу\n";
            return 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (!(cin >> d[i]) || d[i] < 0 || d[i] > 1000000000000) {
            cout << "Помилка вводу\n";
            return 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (d[i] > h[i]) {
            cout << "ERROR\n";
            return 0;
        }
    }
     bool perevernuvsa = false;

    // Пиляємо перевертання на кожній ітерації
    for (int i = 0; i < 4; i++) {
        h[i] -= d[i];
        long long min = h[0], max = h[0];
        for (int j = 1; j < 4; j++) {
            if (h[j] < min) min = h[j];
            if (h[j] > max) max = h[j];
        }

        if (max >= 2 * min) {
            perevernuvsa = true;
        }
    }

    if (perevernuvsa) {
        cout << "NO\n";
    } else {
        long long mn = h[0];
        for (int j = 1; j < 4; j++) {
            if (h[j] < mn) mn = h[j];
        }
        
        if (mn == 0) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
    return 0;
}