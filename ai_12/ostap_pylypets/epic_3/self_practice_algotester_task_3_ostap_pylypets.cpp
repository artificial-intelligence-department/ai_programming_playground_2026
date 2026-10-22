/*
Self-practice algotestertask 3
Проста задача
Пилипець Остап
*/

#include <iostream>
using namespace std;
int main() {
    int p, q;
    cin >> p >> q;
    int n = 1;
    long long sum;
    while (true) {
        sum = 1LL * n * (n + 1) / 2;
        if ((sum * p) % (p + q) == 0) {
            break;
        }
        n++;
    }
    long long target = sum * p / (p + q);
    char colors[200001];
    for (int i = n; i >= 1; i--) {
        if (i <= target) {
            colors[i] = 'R';
            target -= i;
        } else {
            colors[i] = 'B';
        }
    }
    cout << n << "\n";
    for (int i = 1; i <= n; i++) {
        cout << colors[i];
    }
    cout << "\n";
    return 0;
}
