/*
Назва задачі: Підрахунок голосів
Автор: Лисюк Андріана
Група: ШІ-13
*/

#include <iostream>

using namespace std;

long long a[100005];

int main() {
    int n, m;
    long long k;
    if (!(cin >> n >> m >> k)) return 1;

    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }

    int used_members = 1;
    long long current_sum = 0;

    for (int i = 0; i < m; i++) {
        if (current_sum + a[i] <= k) {
            current_sum += a[i];
        } else {
            used_members++;
            current_sum = a[i];
        }
    }

    if (used_members > n) {
        cout << "-1" << endl;
    } else {
        cout << n - used_members << endl;
    }

    return 0;
}
