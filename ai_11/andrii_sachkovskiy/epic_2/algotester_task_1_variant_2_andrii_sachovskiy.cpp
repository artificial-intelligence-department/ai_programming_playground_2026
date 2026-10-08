/*
    Задача: algotester_task_1_variant_2
    Автор: Сачковський Андрій
    Група: ШІ-11
*/
#include <iostream>
using namespace std;

int main() {
    long long h[4], d[4];
    int i = 0;

    while (i < 4) {
        cin >> h[i];
        i++;
    }
    i = 0;
    while (i < 4) {
        cin >> d[i];
        i++;
    }

    // чи є ERROR
    i = 0;
    while (i < 4) {
        if (d[i] > h[i]) {
            cout << "ERROR";
            return 0;
        }
        i++;
    }

    // відпилюємо по одній ніжці і перевіряємо стіл
    bool flipped = false;
    i = 0;
    while (i < 4) {
        h[i] = h[i] - d[i];

        long long mx = h[0];
        long long mn = h[0];
        int j = 1;
        while (j < 4) {//пошук
            if (h[j] > mx) mx = h[j];
            if (h[j] < mn) mn = h[j];
            j++;
        }

        if (mx >= 2 * mn) flipped = true;
        i++;
    }

    // чи всі рівні
    if (!flipped && h[0] == h[1] && h[1] == h[2] && h[2] == h[3] && h[0] > 0) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}