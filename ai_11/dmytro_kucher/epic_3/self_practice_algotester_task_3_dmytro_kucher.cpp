/*
Епік 3. Self Practice: Algotester, задача "Складний екзамен"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
#include<string>
using namespace std;

int main () {

    const char lucky1 = '4';
    const char lucky2 = '7';

    string n; cin >> n;

    for (int i = 0; i<n.length(); i++) {
        if (n[i] == lucky1 && n[i+1] == lucky2) {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";


    return 0;
}