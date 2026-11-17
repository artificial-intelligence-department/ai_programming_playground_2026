/*
Задача: Щасливі рядки
Карпінський Віталій
ШІ-14
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    string s, t;
    cin >> s;
    cin >> t;
    long long first_4 = 0, first_7 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '4') {
            first_4++;
        } else if (s[i] == '7') {
            first_7++;
        }
    }

    long long second_4 = 0, second_7 = 0;
    for (int i = 0; i < m; i++) {
        if (t[i] == '4') {
            second_4++;
        } else if (t[i] == '7') {
            second_7++;
        }
    }

    long long result = (n + 1) * (m + 1) - 1 - (first_4 * second_4 + first_7 * second_7);
    cout << result;
    return 0;
}