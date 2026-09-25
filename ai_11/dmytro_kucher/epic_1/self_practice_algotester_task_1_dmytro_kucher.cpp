/*
Епік 1. Self Practice: Algotester, задача "A плюс B"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;
int main() {
    short a, b;
    cin >> a >> b;
    if (a<0 || b < 0 || a > 100 || b > 100) return  1;
    cout << a+b;
    return 0;
}