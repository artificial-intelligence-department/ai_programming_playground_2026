/*
* Задача: Найпростіші запити
* Поліщук Вероніка
* Група 14
*/

#include <iostream>
using namespace std;

const int MAXN = 100005;

int a[MAXN];
long long pref[MAXN];

long long sum(int l, int r) {
    return pref[r] - pref[l - 1];
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }

    while (m--) {
        int type;
        cin >> type;

        if (type == 1) {
            int l, r;
            cin >> l >> r;

            cout << sum(l, r) << '\n';
        } else {
            int i, d;
            cin >> i >> d;

            a[i] += d;

            for (int j = i; j <= n; j++) {
                pref[j] += d;
            }
        }
    }

    return 0;
}
