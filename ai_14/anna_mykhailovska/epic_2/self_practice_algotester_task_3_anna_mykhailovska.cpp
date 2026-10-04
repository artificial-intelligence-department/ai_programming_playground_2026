/*
    Задача: Зуби
    Михайловська Анна
    ШІ-14
*/
#include <iostream>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;

    int current = 0;
    int answer = 0;

    for (int i = 0; i < n; ++i) {
        long long a;
        cin >> a;

        if (a >= k) {
            ++current;
            if (current > answer) {
                answer = current;
            }
        } else {
            current = 0;
        }
    }

    cout << answer << '\n';
}
