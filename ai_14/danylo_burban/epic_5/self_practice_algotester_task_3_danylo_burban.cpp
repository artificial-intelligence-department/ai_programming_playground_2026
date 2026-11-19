/*Epic 5 - Щасливі рядки
Данило Бурбан
Ші - 14*/
#include <iostream>
#include <string>

using namespace std;

int main() {
    long long n, m;
    string s, t;
    cin >> n >> m >> s >> t;

    long long s4 = 0, s7 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '4') s4++;
        else s7++;
    }

    long long t4 = 0, t7 = 0;
    for (int j = 0; j < m; j++) {
        if (t[j] == '4') t4++;
        else t7++;
    }

    long long ans = (n + 1) * (m + 1) - 1 - (s4 * t4 + s7 * t7);
    cout << ans;

    return 0;
}