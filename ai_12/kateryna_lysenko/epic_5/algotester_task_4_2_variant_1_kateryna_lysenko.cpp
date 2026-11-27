/*
Задача: Algotester Lab 4(2)
Автор:   Катерирна Лисенко
Група:   ШІ-12
*/
#include <iostream>
using namespace std;

const int MAXV = 100;

// k[v] — скільки разів число v входить у результат
void printSet(const int k[]) {
    int total = 0;
    for (int v = 1; v <= MAXV; v++) total += k[v];
    cout << total << "\n";
    bool first = true;
    for (int v = 1; v <= MAXV; v++) {
        for (int j = 0; j < k[v]; j++) {
            if (!first) cout << " ";
            cout << v;
            first = false;
        }
    }
    cout << "\n";
}

int main() {
    int a[MAXV + 1] = {0}, b[MAXV + 1] = {0};
    int n, m, x;
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> x; a[x]++; }
    cin >> m;
    for (int i = 0; i < m; i++) { cin >> x; b[x]++; }

    int r[MAXV + 1];
    for (int op = 0; op < 5; op++) {
        for (int v = 1; v <= MAXV; v++) {
            if (op == 0)      r[v] = a[v] > b[v] ? a[v] - b[v] : 0;            // N-M
            else if (op == 1) r[v] = b[v] > a[v] ? b[v] - a[v] : 0;            // M-N
            else if (op == 2) r[v] = a[v] < b[v] ? a[v] : b[v];                // перетин
            else if (op == 3) r[v] = a[v] > b[v] ? a[v] : b[v];                // об'єднання
            else              r[v] = a[v] > b[v] ? a[v] - b[v] : b[v] - a[v];  // симетрична різниця
        }
        printSet(r);
        if (op < 4) cout << "\n";
    }
    return 0;
}