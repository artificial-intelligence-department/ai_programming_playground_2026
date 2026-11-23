//Сет
#include <iostream>
using namespace std;

int main() {
    int freq[81] = {0};
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        char s[5];
        cin >> s;

        int a = s[0] - '1';
        int b = (s[1] == 'R' ? 0 : s[1] == 'G' ? 1 : 2);
        int c = (s[2] == 'F' ? 0 : s[2] == 'P' ? 1 : 2);
        int d = (s[3] == 'D' ? 0 : s[3] == 'S' ? 1 : 2);

        int index = a * 27 + b * 9 + c * 3 + d;
        freq[index]++;
    }

    long long result = 0;

    for (int i = 0; i < 81; i++) {
        long long k = freq[i];

        if (k >= 3) {
            result += k * (k - 1) * (k - 2) / 6;
        }
    }

    for (int i = 0; i < 81; i++) {
        for (int j = i + 1; j < 81; j++) {
            int a = i;
            int b = j;
            int third = 0;
            int power = 1;

            for (int k = 0; k < 4; k++) {
                int x = a % 3;
                int y = b % 3;

                int z;

                if (x == y) {
                    z = x;
                } else {
                    z = 3 - x - y;
                }

                third += z * power;
                power *= 3;

                a /= 3;
                b /= 3;
            }

            if (third > j) {
                result += 1LL * freq[i] * freq[j] * freq[third];
            }
        }
    }

    cout << result << '\n';
    return 0;
}
