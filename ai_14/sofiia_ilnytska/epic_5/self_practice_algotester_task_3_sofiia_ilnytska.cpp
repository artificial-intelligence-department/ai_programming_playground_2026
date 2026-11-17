/*
   Задача: Щасливі рядки (алготестер)
   Ільницька Софія
   Група ШІ-14
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    string s, t;
    cin >> s >> t;

    long long s4 = 0, s7 = 0;
    long long t4 = 0, t7 = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '4') {
            s4++;
        } else {
            s7++;
        }
    }

    for (int i = 0; i < m; i++) {
        if (t[i] == '4') {
            t4++;
        } else {
            t7++;
        }
    }

    long long result = n + m + s4 * t7 + s7 * t4;

    cout << result << endl;

    return 0;
}
