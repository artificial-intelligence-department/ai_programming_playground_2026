/*
    Задача: Банківські депозити
    Михайловська Анна
    ШІ-14
*/

#include <iostream>
using namespace std;

int main() {
    int a[1000], n = 0, x;
    char comma;

    while (cin >> x) {
        a[n] = x;
        n++;

        if (cin.peek() == ',') {
            cin >> comma;
        } else {
            break;
        }
    }

    int answer = a[0];
    int bestCount = 0;

    for (int i = 0; i < n; i++) {
        int count = 0;

        for (int j = 0; j < n; j++) {
            if (a[i] == a[j]) {
                count++;
            }
        }

        if (count > bestCount || (count == bestCount && a[i] > answer)) {
            bestCount = count;
            answer = a[i];
        }
    }

    cout << answer << ", " << bestCount << '\n';

    return 0;
}
