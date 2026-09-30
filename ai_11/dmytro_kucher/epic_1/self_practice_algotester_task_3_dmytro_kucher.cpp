/*
Епік 1. Self Practice: Algotester, задача "Апельсини"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;
int main() {
    int a, b, c;
    cin >> a >> b >>c;
    if (a>=0 && b>=0 && c>=0) {
        if (a+b>c) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
