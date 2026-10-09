#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> r(n);
    for (int i = 0; i < n; ++i) {
        cin >> r[i];
    }

    // Якщо в масиві 1 або 2 елементи, після видалення залишається <=1 елемент, втома = 0
    if (n <= 2) {
        cout << 0 << endl;
        return 0;
    }

    // Сортуємо масив за зростанням
    sort(r.begin(), r.end());

    // Варіант 1: викидаємо найменше число r[0], тоді різниця = r[n-1] - r[1]
    long long diff1 = r[n - 1] - r[1];

    // Варіант 2: викидаємо найбільше число r[n-1], тоді різниця = r[n-2] - r[0]
    long long diff2 = r[n - 2] - r[0];

    // Виводимо найменшу з двох різниць
    cout << min(diff1, diff2) << endl;

    return 0;
}