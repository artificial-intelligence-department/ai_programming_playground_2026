/*
Епік 2. Self Practice: Algotester, задача "Розподіл шоколадки"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;

int main() {
    short n, m, k;
    cin >> n >> m >> k;
    if ((n*m)%k == 0) cout << "Yes\n";
    else cout << "No\n";

    return 0;
}