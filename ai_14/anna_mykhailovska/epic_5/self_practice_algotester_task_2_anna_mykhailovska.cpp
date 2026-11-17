/*
    Задача: Щасливі рядки
    Михайловська Анна
    ШІ-14
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;

    long long s4 = 0, s7 = 0;
    long long t4 = 0, t7 = 0;

    for (char x : s) {
        if (x == '4') s4++;
        else s7++;
    }

    for (char x : t) {
        if (x == '4') t4++;
        else t7++;
    }

    long long answer = n + m + s4 * t7 + s7 * t4;
    cout << answer << '\n';

    return 0;
}