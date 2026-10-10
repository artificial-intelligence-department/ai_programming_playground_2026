/*
Епік 2. Self Practice: Algotester, задача "Народна вакцина"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;

int main() {
    long a, b;
    cin >> a >> b;
    if ((b-a)%12 == 0) cout << (a+b)/2*13 << endl;
    else cout << "-1\n";

    return 0;
}