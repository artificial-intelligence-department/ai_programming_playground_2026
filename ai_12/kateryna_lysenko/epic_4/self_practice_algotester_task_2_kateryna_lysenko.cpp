/*
Назва:Матриця
Автор: Катерина Лисенко
Група: ШІ-12
*/
#include <iostream>
#include <string>

using namespace std;

int main() {

    int t;
    cin >> t;

    while (t--) {
        int n, m, a, b;
        cin >> n >> m >> a >> b;

        int ones = 0;

        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;

            for (int j = 0; j < m; ++j) {
                if (s[j] == '1') {
                    ++ones;
                }
            }
        }

        int maximumOnes = n * m - (n / a) * (m / b);

        if (ones <= maximumOnes) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }

    return 0;
}