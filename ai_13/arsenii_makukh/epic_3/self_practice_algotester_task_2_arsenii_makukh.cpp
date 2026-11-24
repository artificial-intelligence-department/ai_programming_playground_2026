/*
Назва: Нудне відкриття
Автор: Макух Арсеній
Група: ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    int n, q;

    cin >> n;

    if (cin.fail() || n <= 0) {
        return 1;
    }

    int* a = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i];

        if (cin.fail()) {
            delete[] a;
            return 1;
        }
    }

    cin >> q;

    if (cin.fail() || q < 0) {
        delete[] a;
        return 1;
    }

    int* l = new int[q];
    int* r = new int[q];

    for (int i = 0; i < q; i++) {
        cin >> l[i] >> r[i];

        if (cin.fail() || l[i] < 1 || r[i] > n || l[i] > r[i]) {
            delete[] a;
            delete[] l;
            delete[] r;
            return 1;
        }
    }

    for (int i = 0; i < q; i++) {
        int count = 0;

        for (int j = l[i] - 1; j < r[i]; j++) {
            int sum = 0;

            for (int k = j; k < r[i]; k++) {
                sum += a[k];

                if (sum == 0) {
                    count++;
                }
            }
        }

        cout << count << endl;
    }

    delete[] a;
    delete[] l;
    delete[] r;

    return 0;
}
