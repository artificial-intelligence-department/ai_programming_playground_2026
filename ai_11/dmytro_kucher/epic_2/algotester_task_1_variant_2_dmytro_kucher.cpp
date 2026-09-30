/*
Епік 2. Завдання з Алготестера. Лабораторна робота №1. Завдання №1. Варіант №2
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;

int main() {

    long long h[4];
    long long d[4];
    bool isfallen = 0;

    for (int i = 0; i<4; i++) {
        cin >> h[i];
    }

    for (int i = 0; i<4; i++) {
        cin >> d[i];
    }

    for (int i = 0; i<4; i++) {
        if (d[i]>h[i]) {
            cout << "ERROR\n";
            return 0;
        }
    }

    for (int i = 0; i<4; i++) {
        h[i] -= d[i];

        long long hmax = h[0];
        long long hmin = h[0];

        for (int j = 1; j < 4; j++) {
            if (h[j]> hmax) hmax = h[j];
            if (h[j]< hmin) hmin = h[j];
        }

        if (hmax >= 2*hmin) isfallen = 1; 
    }

    long long hmin = h[0];
    for (int i = 1; i<4; i++) {
        if (h[i]< hmin) hmin = h[i];
    }
    if (hmin <= 0) {
        cout << "NO\n";
        return 0;
    }

    for (int i = 0; i < 4; i++) {
        if (h[i] != hmin) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";

    return 0;
}