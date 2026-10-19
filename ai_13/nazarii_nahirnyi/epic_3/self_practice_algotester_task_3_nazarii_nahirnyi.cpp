/*
Завдання: Офісна Вулиця. Частина 1
*/
#include <iostream>
#include <algorithm>

using namespace std;

pair<int, int> a[100005];

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }

    sort(a, a + n);

    for (int i = 0; i < n; i++) {
        cout << a[i].second << " ";
    }

    return 0;
}