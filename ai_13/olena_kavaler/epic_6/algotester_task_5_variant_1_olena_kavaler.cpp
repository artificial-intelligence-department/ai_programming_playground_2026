
#include <iostream>
using namespace std;

int main() {
    unsigned long long a;
    int n;
    cin >> a >> n;

    for (int k = 0; k < n; k++) {
        int r, c;
        cin >> r >> c;

        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                if (i == r || j == c) {
                    int bit = (i - 1) * 8 + (j - 1);
                    a = a ^ (1ULL << bit);
                }
            }
        }
    }

    cout << a << endl;
    return 0;
}