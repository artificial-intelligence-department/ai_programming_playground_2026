#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int k = 0;  // загальна кількість купюр і монет
    int t;
    int m = n;  // залишок суми

    if (m >= 500) {
        t = m / 500;
        m = m - t * 500;
        k = k + t;
    }

    if (m >= 200) {
        t = m / 200;
        m = m - t * 200;
        k = k + t;
    }

    if (m >= 100) {
        t = m / 100;
        m = m - t * 100;
        k = k + t;
    }

    if (m >= 50) {
        t = m / 50;
        m = m - t * 50;
        k = k + t;
    }

    if (m >= 20) {
        t = m / 20;
        m = m - t * 20;
        k = k + t;
    }

    if (m >= 10) {
        t = m / 10;
        m = m - t * 10;
        k = k + t;
    }

    if (m >= 5) {
        t = m / 5;
        m = m - t * 5;
        k = k + t;
    }

    if (m >= 2) {
        t = m / 2;
        m = m - t * 2;
        k = k + t;
    }

    if (m >= 1) {
        t = m / 1;
        m = m - t * 1;
        k = k + t;
    }

    cout << k;
    return 0;
}