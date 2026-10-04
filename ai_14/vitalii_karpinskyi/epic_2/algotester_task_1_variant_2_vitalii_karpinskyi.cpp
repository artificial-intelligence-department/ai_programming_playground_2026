#include <iostream>

using namespace std;

int main() {
    // Введення даних
    long long l[4], d[4];
    for (int i = 0; i < 4; i++) {
        cin >> l[i];
    }
    for (int i = 0; i < 4; i++) {
        cin >> d[i];
        if (d[i] > l[i]) {
            cout << "ERROR" << endl;
            return 0;
        }
    }
    bool flip = false;
    // Перевірка всіх умов
    for (int i = 0; i <4; i++) {
        l[i] = l[i] - d[i];
        long long min = l[0];
        long long max = l[0];
        for (int j = 0; j < 4; j++) {
            if (l[j] < min) {
                min = l[j];
            }
            if (l[j] > max) {
                max = l[j];
            }
        }
        if (max >= min * 2) {
            flip = true;

        }

    }

    // Визначення й виведення результату
    if (l[0] == l[1] && l[1] == l[2] && l[2] == l[3] && l[1] != 0 && !flip) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}