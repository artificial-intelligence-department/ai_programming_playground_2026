/*
Назва:Найкраща пара
Автор: Катерина Лисенко
Група: ШІ-12
*/
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long a[1000];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a, a + n);                    // сортування за зростанням

    long long best = 0;
    for (int i = 0; i < n / 2; i++) {
        long long sum = a[i] + a[n - 1 - i];   // найменше + найбільше із залишку
        if (sum > best) best = sum;
    }

    cout << best << endl;
    return 0;
}