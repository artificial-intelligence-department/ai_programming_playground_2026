// Щасливі рядки
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    string s, t;
    cin >> s >> t;

    int countS[10] = {0};
    int countT[10] = {0};

    for (int i = 0; i < n; i++) {
        countS[s[i] - '0']++;
    }

    for (int i = 0; i < m; i++) {
        countT[t[i] - '0']++;
    }

    long long result = 1LL * (n + 1) * (m + 1) - 1;

    for (int i = 0; i < 10; i++) {
        result -= 1LL * countS[i] * countT[i];
    }

    cout << result << '\n';

    return 0;
}
