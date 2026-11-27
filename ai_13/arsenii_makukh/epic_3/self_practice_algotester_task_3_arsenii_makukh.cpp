/*
Назва: Спільне у змінного
Автор: Макух Арсеній
Група: ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    int q;
    cin >> q;

    int* a = new int[q + 1];
    long long* nsd = new long long[q + 1];

    int n = 0;

    for (int i = 0; i < q; i++) {
        char input;
        cin >> input;

        if (input == '+') {
            int x;
            cin >> x;

            a[n] = x;

            long long b = x;
            if (b < 0) b = -b;

            if (n == 0) {
                nsd[n] = b;
            } else {
                long long c = nsd[n - 1];

                while (b != 0) {
                    long long temp = b;
                    b = c % b;
                    c = temp;
                }

                nsd[n] = c;
            }

            n++;
        }

        else if (input == '-') {
            if (n > 0) {
                n--;
            }
        }

        else if (input == '?') {
            if (n == 0) {
                cout << 0 << '\n';
            } else {
                cout << nsd[n - 1] << '\n';
            }
        }
    }

    delete[] a;
    delete[] nsd;

    return 0;
}
