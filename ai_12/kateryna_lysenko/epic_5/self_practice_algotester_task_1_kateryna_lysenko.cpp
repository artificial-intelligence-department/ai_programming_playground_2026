/*
Задача:  Марічка вмикає лампи
Автор:   Катерирна Лисенко
Група:   ШІ-12
*/

#include <iostream>
using namespace std;

int main() {
    long long m, n;
    cin >> m >> n;

    double ans = (double)(m + 1) / (double)(m + 1 - n);

    cout.setf(ios::fixed);
    cout.precision(10);
    cout << ans << "\n";
    return 0;
}