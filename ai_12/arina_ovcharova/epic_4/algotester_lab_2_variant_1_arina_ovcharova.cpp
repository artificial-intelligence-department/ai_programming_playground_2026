// Algotester Lab 2, варіант 1: "Дорога і втома"
// відповідь: менше з max1 - min2 і max2 - min1
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int *r = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    // якщо елемент один, втома 0
    if (n == 1) {
        cout << 0 << endl;
        delete[] r;
        r = nullptr;
        return 0;
    }

    int min1, min2, max1, max2;
    if (r[0] <= r[1]) {
        min1 = r[0];
        min2 = r[1];
        max1 = r[1];
        max2 = r[0];
    } else {
        min1 = r[1];
        min2 = r[0];
        max1 = r[0];
        max2 = r[1];
    }

    for (int i = 2; i < n; i++) {
        int x = r[i];

        if (x < min1) {
            min2 = min1;
            min1 = x;
        } else if (x < min2) {
            min2 = x;
        }

        if (x > max1) {
            max2 = max1;
            max1 = x;
        } else if (x > max2) {
            max2 = x;
        }
    }

    int variant1 = max1 - min2;
    int variant2 = max2 - min1;

    if (variant1 < variant2) {
        cout << variant1 << endl;
    } else {
        cout << variant2 << endl;
    }

    delete[] r;
    r = nullptr;

    return 0;
}