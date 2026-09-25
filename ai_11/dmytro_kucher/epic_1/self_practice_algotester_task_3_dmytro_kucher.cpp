/*
Епік 1. Self Practice: Algotester, задача "Апельсини"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
#include<cmath>
using namespace std;
int main() {
    int a, b, c;
    const int m = pow(10, 9); 
    cin >> a >> b >>c;
    if (a>=0 && a<=m && b>=0 && b<=m && c>=0 && c<=m) {
        if (a+b>c) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}