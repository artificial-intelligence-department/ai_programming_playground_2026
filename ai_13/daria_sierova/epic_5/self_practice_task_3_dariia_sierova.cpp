//Щасливі рядки
#include <iostream>
#include <string>

using namespace std;

int main() {
    long long n, m;
    if (!(cin >> n >> m)) return 0;

    string s, t;
    cin >> s >> t;

    long long s4 = 0, s7 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '4') s4++;
        else s7++;
    }

    long long t4 = 0, t7 = 0;
    for (int i = 0; i < m; i++) {
        if (t[i] == '4') t4++;
        else t7++;
    }

    long long total = (n + 1) * (m + 1) - 1; //префікси * суфікси
    long long duplicates = s4 * t4 + s7 * t7;

    cout << total - duplicates << "\n";
    return 0;
}