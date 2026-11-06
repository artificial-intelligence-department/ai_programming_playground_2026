/*
Епік 4. Self Practice: Algotester, задача "Перехід дороги"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;

int main () {

    int n;
    cin >> n;
    if (n<1 || n>100000) return 1;

    int* a = new int[n];
    for (int i = 0; i<n; i++) {
        cin >> a[i];
        if (a[i] < 1 || a[i] > 1000000000) return 1;
    }

    int count = 0;

    for (int i = 0; i<n-1; i++) {
        if (a[i] % 2 != 0 && a[i+1] % 2 == 0) count++;
        else if (a[i] % 2 == 0 && a[i+1] % 2 != 0) count++;
    }

    cout << count << "\n";

    delete[] a;
    a = nullptr;

    return 0;
}