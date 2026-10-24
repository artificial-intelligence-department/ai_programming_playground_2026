/*
Олексійчук Захар ШІ-14
*/

#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;

    int r[N];
    for (int i = 0; i < N; i++) {
        cin >> r[i];
    }

    int a, b, c;
    cin >> a >> b >> c;

    int new_r[N];
    int new_N = 0;
    for (int i = 0; i < N; i++) {
        if (!(r[i] == a || r[i] == b || r[i] == c)) {
            new_r[new_N] = r[i];
            new_N++;
        }
    }

    if (new_N < 2) {
        cout << 0 << endl;
        return 0;
    }

    int M = new_N-1;
    int sum[M];

    for (int i = 0; i < M; i++) {
        sum[i] = new_r[i] + new_r[i+1];
    }

    cout << M << endl;
    for (int i = 0; i < M; i++) {
        cout << sum[i] << " ";
    }
    cout << endl;
}